// Huffman encoder for images
// 
// INSTRUCTIONS FOR USE: 
//  1) Make sure to point the three setup variables (below) to your image name and output file. Then run.
//  2) The image will be displayed for your review. You do not need to do anything else.
//
// SETUP VARIABLES (These must be set to your image, output filename, and variable name before running)
String filenameIn = "earthatnight1.jpg";
String filenameOut = "out.h";
String variableName = "background";

// Parameter which controls a time/space tradeoff.
// Decrease towards 1.0 to encourage fast decode
// Increase to encourage small
double threshold_path_length = 1.4;

import java.util.PriorityQueue;
import java.util.LinkedList;
import java.util.Iterator;

double log2(double x) {
  return Math.log(x) / Math.log(2.0);
}

void exportIntArray(PrintWriter output, ArrayList<Integer> a) {
  for (int i = 0; i < a.size(); i++) {
    output.print("0x" + hex(a.get(i), 8));
    if (i < (a.size() - 1)) {
      output.print(", ");
    }
    if ((i % 8) == 7) {
      output.println("");
    }
  }
}

void setup() {
  PImage img;
  int color_counts[] = new int[65536 * 33]; // 16 bits for colors + 5 bits for alpha

  colorMode(RGB, 1.0);  
  img = loadImage(filenameIn);
  img.loadPixels();
  size(img.width, img.height);
  int argb_array[] = new int[img.width * img.height];

  // Reduce color depth to 16 bit and count colors
  for (int i = 0; i < color_counts.length; i++) {
    color_counts[i] = 0;
  }
  int argb_array_index = 0;
  for (int y = 0; y < img.height; y++) {
    for (int x = 0; x < img.width; x++) {
      int offset = y * width + x;
      int r = round(red(img.pixels[offset]) * 31.0);
      int g = round(green(img.pixels[offset]) * 63.0);
      int b = round(blue(img.pixels[offset]) * 31.0);
      int a = round(alpha(img.pixels[offset]) * 32.0);
      int argb5565 = a << 16 | r << 11 | g << 5 | b;
      argb_array[argb_array_index++] = argb5565;
      color_counts[argb5565]++;
      img.pixels[offset] = color(r / 31.0, g / 63.0, b / 31.0, a / 32.0);          
    }
  }
  img.updatePixels();

  // Display checkerboard background pattern to test transparency
  fill(0.70);
  stroke(0.70);
  int counter1 = 0;
  int counter2 = 0;
  for (int y = 0; y < img.height; y += 16) {
    counter2 = 0;
    for (int x = 0; x < img.width; x += 16) {
      if (((counter1 ^ counter2) & 1) != 0) {
        rect(x, y, 16, 16);
      }
      counter2++;
    }
    counter1++;
  }

  // Display the image at its actual size
  image(img, 0, 0);
  
  // Get normalisation factor for weights
  double sum = 0.0;
  int num_colors = 0;
  for (int i = 0; i < color_counts.length; i++) {
    sum += color_counts[i];
  }

  // Calculate per-pixel entropy of image
  double entropy = 0.0;
  for (int i = 0; i < color_counts.length; i++) {
    double weight = (double)color_counts[i] / sum;
    if (weight != 0.0) {
      entropy -= weight * log2(weight);
      num_colors++;
    }
  }

  // Optimise time/space tradeoff by increasing codeword size until average
  // pixel encodes into < threshold_path_length codewords.
  int codeword_size = 1; // in number of bits
  boolean passed_threshold = false;
  double average_path_length; // in number of codewords 
  HuffmanNode head;
  do {
    int num_children = 1 << codeword_size;

    // Initialise priority queue with all nodes
    PriorityQueue<HuffmanNode> nodes = new PriorityQueue<HuffmanNode>();
    for (int i = 0; i < color_counts.length; i++) {
      double weight = (double)color_counts[i] / sum;
      if (weight != 0.0) {
        nodes.add(new HuffmanNode(weight, i));
      }
    }
    // Add dummy nodes to ensure Huffman tree will be full
    if (num_children > 2) {
      while ((nodes.size() % (num_children - 1)) != 1) {
        nodes.add(new HuffmanNode(0.0, 0));
      }
    }
  
    while (nodes.size() > 1) {
      // Get n nodes with lowest weights
      HuffmanNode lowest[] = new HuffmanNode[num_children];
      for (int j = 0; j < num_children; j++) {
        lowest[j] = nodes.poll();
        //println("Removed node with weight " + lowest[j].weight);
      }
  
      // Add new node which has lowest weight nodes as children
      double new_weight_sum = 0.0;
      for (int j = 0; j < num_children; j++) {
        new_weight_sum += lowest[j].weight;
      }
      HuffmanNode parent = new HuffmanNode(new_weight_sum, 0);
      parent.children = lowest;
      nodes.add(parent);
      //println("Added node with weight " + parent.weight);
    }

    head = nodes.poll();
    average_path_length = head.getWeightedPathLength(0);
    if (average_path_length <= threshold_path_length) {
      // Good enough
      passed_threshold = true;
    } else {
      // Codes are too long (decoder will be slow)
      // Increasing codeword size will make pixels encode to less codewords
      codeword_size *= 2;
    }
  } while (!passed_threshold);

  println("Entropy (in bits) per pixel: " + entropy);
  println("Entropy is the theoretical minimum attainable with an entropy code");
  println("Distinct colors: " + num_colors);
  println("Bits per codeword: " + codeword_size);
  println("Longest code: " + head.getMaxDepth() + " codewords");
  println("Actual weighted path length (in bits): " + (average_path_length * codeword_size));

  // Generate color -> codeword sequence lookup table
  // using an ArrayList instead of array because you can't create
  // arrays of generics in Java
  ArrayList<LinkedList<Integer>> sequences = new ArrayList<LinkedList<Integer>>(color_counts.length);
  for (int i = 0; i < color_counts.length; i++) {
    sequences.add(null);
  }
  head.enumerateCodes(sequences, new LinkedList<Integer>());

  ArrayList<Integer> output_tree = new ArrayList<Integer>();
  head.dumpTree(output_tree);

  // Pack bitmap codewords into ints, LSB first.
  ArrayList<Integer> output_data = new ArrayList<Integer>();
  int current_output_int = 0;
  int current_output_bits = 0;
  for (int i = 0; i < argb_array.length; i++) {
    LinkedList<Integer> seq = sequences.get(argb_array[i]);
    Iterator<Integer> j = seq.iterator();
    while (j.hasNext()) {
      current_output_int |= j.next() << current_output_bits;
      current_output_bits += codeword_size;
      if ((current_output_bits + codeword_size) > 32) {
        // flush current output int
        output_data.add(current_output_int);
        current_output_int = 0;
        current_output_bits = 0;
      }
    }
  }
  if (current_output_bits != 0) {
    // add any remaining bits
    output_data.add(current_output_int);
  }

  int bytesOut = 4 * (output_tree.size() + output_data.size());

  // Write data out
  PrintWriter output;
  output = createWriter(filenameOut);
  println ("Writing output file...");
  output.println ("// This file was automatically generated by the Huffman encoder tool");
  output.println ("// It is estimated that this bitmap will take approximately " + bytesOut + " bytes of flash. ");
  output.println ("#include \"BitmapHuffmanStructure.h\"");
  output.println ("#if !defined(" + variableName.toUpperCase() + "_BITMAPHUFFMAN_H)");
  output.println ("#define " + variableName.toUpperCase() + "_BITMAPHUFFMAN_H");
  output.println ("");
  // Step 2: Export tree
  output.println("const uint32_t " + variableName + "Tree[] = {");
  exportIntArray(output, output_tree);
  output.println ("}; ");
  output.println ("");
  // Step 3: Export pixel data
  output.println("const uint32_t " + variableName + "Data[] = {");
  exportIntArray(output, output_data);
  output.println("};");
  output.println();
  // Step 4: Export structure
  output.println("const BITMAPHUFFMANSTRUCT " + variableName + "Bitmap = {");
  output.println(" " + img.width + ", \t // width");
  output.println(" " + img.height + ", \t // height");
  output.println(" " + codeword_size + ", \t // bpc");
  output.println(" " + variableName + "Tree,");
  output.println(" " + variableName + "Data");
  output.println("};");
  output.println ("");
  // Step 5: Footer
  output.println ("#endif");
  output.flush();
  output.close();
  println("Output file written: " + filenameOut);
  println("Approximate size is " + bytesOut + " bytes");
}

void draw() {
}

