// Posterizer for Arducorder-mini
// Peter Jansen, Sept 2014
// This program allows the user to manually select (using the mouse) a pallette of 
// 16 colours that will be used to posterize an image, then store it in an array
// for use in the Arducorder Mini (or another Arduino compatible platform). 
// Posterizing can be done using automated algorithms, but this manual selection and
// adjustment allows for optimized results. 
//
// This quick data processing tool was put together in about an hour, and is
// meant to be quick and functional (rather than beautiful) code. Make your mistakes cheaply.   
// Modified Example From http://www.learningprocessing.com
// Example 15-7: Displaying the pixels of an image
// 
// INSTRUCTIONS FOR USE: 
//  1) Make sure to point the three setup variables (below) to your image name and output file. Then run.
//  2) Using the mouse, hover over pixels in the original (left) image.  The color of the pixel
//     will be displayed below.
//  3) Select a color by left clicking.
//  4) As you select additional colors, the posterized (right) image will populate
//  5) Modify or change colours in the pallete (lower left) using the Z/X keys.
//  6) Once you're happy with the results, press SPACE to save.  
//
// ====================================================================
// SETUP VARIABLES (These must be set to your image, output filename, and variable name before running)
// NOTE: Image dimensions must be evenly divisible by 2. 
//String filenameIn = "earthatnight1.jpg";
String filenameIn = "c:\\stuffs\\interfacenotes\\symbols\\symbol_amb_temp.png";
String filenameOut = "out.h";
String variableName = "symbTemp";

// ====================================================================

int MAX_COLORS = 16;
PImage img;
PFont f;
color[] Palette = new color[MAX_COLORS];
int curCol = 0;
int picHeight = 0;
int picWidth = 0;

// States
int alreadyPressed = 0;
int doSave = 0;

int postOffset = 0; 

void setup() {   
  size(640,250);  
  
  img = loadImage(filenameIn);
  picHeight = img.height;
  picWidth = img.width;
  postOffset = picWidth + 64;
  
  f = createFont("Arial", 12);
  textFont(f);  
  textAlign(LEFT);
}


void draw() {

  // Step 1: Convert display window into a set of addressable pixels  
  loadPixels();

  // We must also call loadPixels() on the PImage since we are going to read its pixels.
  img.loadPixels();
  for (int y = 0; y < picHeight; y++ ) {
    for (int x = 0; x < picWidth; x++ ) {
      int locIn = x + y*picWidth;
      // The functions red(), green(), and blue() pull out the three color components from a pixel.
      float r = red(img.pixels [locIn]); 
      float g = green(img.pixels[locIn]);
      float b = blue(img.pixels[locIn]);

      // Set the display pixel to the image pixel
      int locOut = x + y*width;
      pixels[locOut] = color(r,g,b);
    }
  }
  
  
  // Step 2: Perform posterization, and display posterized image to the right
  for (int y = 0; y < picHeight; y++ ) {
    for (int x = 0; x < picWidth; x++ ) {
      int locIn = x + y*picWidth;
      // The functions red(), green(), and blue() pull out the three color components from a pixel.
      float r = red(img.pixels [locIn]); 
      float g = green(img.pixels[locIn]);
      float b = blue(img.pixels[locIn]);

      // Image Processing would go here
      // If we were to change the RGB values, we would do it here, before setting the pixel in the display window.

      color postColor = closestColor(r, g, b);      
      // Set the display pixel to the image pixel
      int locOut = (x + postOffset) + y*width;
      //pixels[locOut] = color(r,g,b);
      pixels[locOut] = postColor;
    }
  }
    
  // Step 3: Perform Save (If enabled)
  if (doSave == 1) {
    doSave = 0;
    int bytesOut = (picHeight * picWidth) / 2;
    int dataOut[] = new int[bytesOut]; 
    int outIdx = 0;
    
    int pack = 0;
    int outByte = 0;    
    for (int y = 0; y < picHeight; y++ ) {
      for (int x = 0; x < picWidth; x++ ) {
        int locOut = (x + picWidth + 64) + y*width;
        // The functions red(), green(), and blue() pull out the three color components from a pixel.
        float r = red(pixels [locOut]); 
        float g = green(pixels[locOut]);
        float b = blue(pixels[locOut]);

        // Image Processing would go here
        // If we were to change the RGB values, we would do it here, before setting the pixel in the display window.

        int palIdx = whichColor(r, g, b);
        if (pack == 0) {
          outByte = (int)(palIdx << 4);          
        } 
        if (pack == 1) {
          outByte += (int)palIdx;
          
          // Store byte                   
          dataOut[outIdx] = outByte;
          println ("outIdx: " + outIdx + " byte: " + dataOut[outIdx]);
          outIdx += 1;
          
        }
        
        pack = (pack + 1) % 2;
      }          
    }
    
    // Write data out
    PrintWriter output;
    output = createWriter(filenameOut);
    println ("Writing output file...");
    
    output.println ("// This file was automatically generated by the posterizer tool");
    output.println ("// It is estimated that this bitmap will take approximately " + bytesOut + " bytes of flash. ");
    output.println ("#include \"BitmapStructure.h\"");
    output.println ("#if !defined(" + variableName.toUpperCase() + "_BITMAP_H)");
    output.println ("#define " + variableName.toUpperCase() + "_BITMAP_H");
    output.println ("");     

    // Step 2: Export Palette 
    output.print("uint16_t " + variableName + "Palette[] = {");
    for (int i=0; i<MAX_COLORS; i++) {
      output.print ( colorToRGB565(Palette[i]) );
      if (i < (MAX_COLORS-1)) {
        output.print(", ");
      }      
    }
    output.println ("}; ");
    output.println ("");
    
    // Step 3: Export pixel data 
    output.print("uint8_t " + variableName + "Data[] = {"); 
    for (int i = 0; i<bytesOut; i++) {
      output.print( dataOut[i] );
      if (i < (bytesOut-1)) {
        output.print(", ");
      }
      if ((i % 20) == 19) {
        output.println ("");
        output.print("         ");
      }
    }
    output.println("};");
    output.println();
    
    // Step 4: Export structure
    output.println("const BITMAPSTRUCT " + variableName + "Bitmap = {");
    output.println("         " + picWidth + ", \t // width");
    output.println("         " + picHeight + ", \t // height");
    output.println("         " + 4 + ", \t // bpp");       // Static, change this if the posterizer ever supports different bit depths
    output.println("         " + variableName + "Palette,");
    output.println("         " + variableName + "Data");
    output.println("};");
    output.println ("");
    

    // Step 5: Footer    
    output.println ("#endif");
    
    output.flush();
    output.close();
    
    println ("Output file written: " + filenameOut );
    
  }
    
  updatePixels();     

  
  
  
  // Step 4: Display User-Selected Posterizing Palette
  for (int i=0; i<MAX_COLORS; i++) {
    fill( Palette[i] );
    stroke(128);
    rect((i * 16), height-16, 16, 16); 
 
    if (i == curCol) {
      stroke(255);
      fill(255);
    } else {
      stroke(0);
      fill(0);
    }
    ellipse((i * 16) + 8, height-24, 5, 5);   
  }
  
  
  // Step 5: Colour picker
  fill(128);
  int loc = mouseX + mouseY*img.width;
  if (loc < (img.width * img.height)) {
    float r = red(img.pixels [loc]); 
    float g = green(img.pixels[loc]);
    float b = blue(img.pixels[loc]);
  
    color point = color(r, g, b);
    fill(point);
    rect(picWidth-64, height-96, 48, 48);
  
    if (mousePressed) {
      if (alreadyPressed == 0) {
        if (curCol < 16) {
          Palette[curCol] = point;    
          curCol+= 1;
        }
      } 
      alreadyPressed = 1;   
    } else {
      alreadyPressed = 0;
    }
    
  }
  
  // Step 6: Display Instructions
  stroke(128);
  fill(0);
  text("Z - Palette left", 5, height - 100);
  text("X - Palette right", 5, height - 80);
  text("SPACE - save", 5, height - 60);
  
}

void keyPressed() {
  // Palette left
  if ((key == 'Z') || (key == 'z')) {
    if (curCol > 0) {
      curCol -= 1;
    }
  }
  
  // Palette right
  if ((key == 'X') || (key == 'x')) {
    if (curCol < 16) {
      curCol += 1;
    }
  }

  // Save  
  if (key == ' ') {
    doSave = 1;
  }
  
}

// Returns the closest color() that's in the palette
color closestColor(float r, float g, float b) {
  float minDist = 100000.0f;
  int minIdx = 0;
  
  for (int i=0; i<MAX_COLORS; i++) {
    float r1 = red( Palette[i] );
    float g1 = green( Palette[i] );
    float b1 = blue( Palette[i] );
    
    float dist = pow((r - r1), 2) + pow((g - g1), 2) + pow((b - b1), 2);
    if (dist < minDist) {
      minDist = dist;
      minIdx = i;
    } 
  }

  return Palette[minIdx];
}

// Returns the index of a given color in the palette
int whichColor(float r, float g, float b) {
  float minDist = 100000.0f;
  int minIdx = 0;
  
  for (int i=0; i<MAX_COLORS; i++) {
    float r1 = red( Palette[i] );
    float g1 = green( Palette[i] );
    float b1 = blue( Palette[i] );
    
    float dist = pow((r - r1), 2) + pow((g - g1), 2) + pow((b - b1), 2);
    if (dist < minDist) {
      minDist = dist;
      minIdx = i;
    } 
  }

  return minIdx;
}

// Converts a color() object into a 2-byte RGB565 encoded color
int colorToRGB565(color col) {
  int colOut = 0;
  int r = (int)red( col );
  int g = (int)green( col );
  int b = (int)blue( col );
  
  int r1 = (r >> 3) & 0x1F;
  int g1 = (g >> 2) & 0x3F;
  int b1 = (b >> 3) & 0x1F;
  colOut = (r1 << 11) + (g1 << 5) + b1;
  
  println ("r: " + r + " g: " + g + " b: " + b);
  println ("r1: " + r1 + " g1: " + g1 + " b1: " + b1 + "   colOut = " + colOut);
  
  return colOut;
}
