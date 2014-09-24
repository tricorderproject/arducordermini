// main.c
// This firmware is a work in progress, and is currently test/development firmware 
// used to verify the functionality of the hardware.  

#include <Wire.h>
#include <SD.h>
#include <math.h>

#include <I2Cdev.h>

#include <MPU6050.h>

#include "SSD1351.h"
#include "FramebufferGFX.h"
#include "FramebufferGraphs.h"

#include "Adafruit_MPR121.h"

#include "sensorbuffer.h"
#include "sensor_HMC5883L.h"
#include "sensor_microphone.h"
#include "Adafruit_SI1145.h"
#include "sensor_HTU21D.h"
#include "sensor_BMP180.h"
#include "sensor_AS3935.h"
#include "SensorMLX90620.h"

#include "Tile.h"
#include "Fonts.h"
#include "Bitmaps.h"
#include "TileGUI.h"

// Defines
#define SD_CS  84

#define TOUCH_HIST_SIZE  50

// Variables
SSD1351 Framebuffer;                        // Display driver
FramebufferGFX GFX(&Framebuffer);           // Graphics functions
FramebufferGraphs Graph(&GFX);              // Graph display/visualization
TileGUI tileGUI(&GFX);                      // Tile-based GUI

SensorBuffer sb(100);                       // Sensor buffer test
SensorBuffer sbx(100);                       // Sensor buffer test
SensorBuffer sby(100);                       // Sensor buffer test
SensorBuffer sbz(100);                       // Sensor buffer test
SensorBuffer sbMic(100);                       // Sensor buffer test
SensorBuffer sbTemp(100);                       // Sensor buffer test
SensorBuffer sbHumidity(100);                       // Sensor buffer test
SensorBuffer sbPressure(100);                       // Sensor buffer test
SensorBuffer sbAccelX(100);                       // Sensor buffer test
SensorBuffer sbAccelY(100);                       // Sensor buffer test
SensorBuffer sbAccelZ(100);                       // Sensor buffer test
SensorBuffer sbGyroX(100);                       // Sensor buffer test
SensorBuffer sbGyroY(100);                       // Sensor buffer test
SensorBuffer sbGyroZ(100);                       // Sensor buffer test

// Sensor Variables
SensorHMC5883L sensorHMC5883L;                      // Magnetometer
Adafruit_MPR121 touchWheel = Adafruit_MPR121();     // MPR121 touch sensor
Adafruit_SI1145 uv = Adafruit_SI1145();             // SI1445 UV sensor
SensorMicrophone sensorMicrophone;                  // ADMP401 microphone
HTU21D sensorHTU21D;                                // HTU21D temperature/humidity sensor

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);  // BMP180 barometric pressure sensor

MPU6050 accelgyro(0x69); // <-- use for AD0 low     // MPU9150 Inertial measurement unit

SensorMLX90620 thermalImager;                       // MLX90620 16x4 Thermal Imager


#define GRAPH_MAGXYZ  1
#define GRAPH_MAGSTRENGTH  2
#define GRAPH_MIC  3
#define GRAPH_HUMIDITY 4
#define GRAPH_PRESSURE 5
#define GRAPH_ACCELGYRO 6
#define GRAPH_MAX 6
uint16_t showGraph = GRAPH_MAGXYZ;



// Functions
void setup() {
  Serial.begin(9600);
  Serial.println("Initializing... "); 

  // Initialize framebuffer
  Serial.println("Initializing Framebuffer...");  
  Framebuffer.begin();  

  // Initialize touch
  Serial.println("Initializing MPR121...");  
  if (!touchWheel.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
  }
  Serial.println("MPR121 found!");
  touchWheel.initTouchWheel(8, -20);
  touchWheel.takeWheelBaseline();  
  
  Serial.print("Initializing SD card...");
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, 1);
 

  // see if the card is present and can be initialized:
  // Note: I'm not sure why, but SD.begin() is failing, but subsequent functions seem fine. 
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card failed, or not present");
    Serial.println("Halting... ");
//    while(1);
    // don't do anything more:
//    return;
  }
  Serial.println("card initialized.");

  // Initialize sensors
  Serial.println("Initializing sensors...");
  Wire.begin();
  delay(500);

  // Initialize MLX90620
  Serial.println ("Initializing MLX90620...");
  thermalImager.begin();    
  thermalImager.debugPrint();  
  
  Serial.println("Initializing HMC5883L...");
  sensorHMC5883L.init_HMC5883L();
  delay(500);
  
  // Initialize UV sensor
  Serial.println("Initializing UV Sensor...");
  uv.begin();
  
   
   // AS3935 setup
   //AS3935_setup();
   
   // Initialize MPU6050
  Serial.println("Initializing MPU9050...");     
   accelgyro.initialize();
   Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");   
    
  // Visualization
  Serial.println("Initializing Sensor Graph...");  
  initSensorGraph();
  
  
/*    
  // TEST of touch wheel scrolling wheel high-level delta increment function
  while (1) {
    // Touch wheel
    int16_t touchAngle = touchWheel.getWheelAngle();
    int16_t deltaWheel = touchWheel.getWheelIncrement();  
    Serial.print (" Wheel degree: ");
    Serial.println(touchAngle, DEC);
    Serial.print (" Wheel Increment: ");
    Serial.println(deltaWheel, DEC);
    delay(250);
  }
*/  
  
  // ******************************************
  // Initialize Tile-based GUI
  // ******************************************  
  Serial.println ("Initializing tileGUI");

     
  // ******************************************     
  // Initialize tiles 
  // ******************************************
  // THEME: Ambient atmospheric measurements
  // ******************************************  
  // TILE: Ambient Temperature (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_ATMTEMP)->Initialize("Temp", RGB(0, 0, 128), &symbTempBitmap, NULL);
  char buffer[10];
  strcpy(buffer, "24");
  strcat(buffer, " ");
  strcat(buffer, "C");
  buffer[2] = 176;
  tileGUI.getTile(TILE_ATMTEMP)->setText(buffer);
  
  // TILE: Ambient Humidity (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_ATMHUMIDITY)->Initialize("Humidity", RGB(0, 0, 128), &symbHumidityBitmap, NULL);
  tileGUI.getTile(TILE_ATMHUMIDITY)->setText("30%");  
  
  // TILE: Ambient Pressure (2x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_ATMPRESSURE)->Initialize("Pressure", RGB(0, 128, 0), &symbPressureBitmap, NULL);
  tileGUI.getTile(TILE_ATMPRESSURE)->setSize(2, 1);
  tileGUI.getTile(TILE_ATMPRESSURE)->setText("1200mbar"); 
  
  
  // ******************************************  
  // THEME: Electromagnetic Readings (1)
  // ******************************************  
  // TILE: Magnetic Field Strength (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_MAGFIELD)->Initialize("Magnetic", RGB(0, 0, 128), &symbMagBitmap, &sb);
  char buffer1[10];
  strcpy(buffer1, "100");
  strcat(buffer1, " ");
  strcat(buffer1, "T");
  buffer1[2] = 181;
  tileGUI.getTile(TILE_MAGFIELD)->setText(buffer1);
  
  // TILE: Magnetic Field Direction (1x1)  
  // NOTE: Arrow tile currently unimplemented
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_MAGDIR)->Initialize("Magnetic", RGB(0, 0, 128), &symbMagBitmap, NULL);
  tileGUI.getTile(TILE_MAGDIR)->setText("DIR");

  // TILE: Lightning (strike distance) (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_LIGHTNING_STR)->Initialize("Lightning", RGB(0, 0, 128), &symbLightningBitmap, NULL);
  tileGUI.getTile(TILE_LIGHTNING_STR)->setText("5km");

  // TILE: Radiation (counts per minute) (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_RADIATION_CPM)->Initialize("Radiation", RGB(0, 0, 128), &symbRadiationBitmap, NULL);
  tileGUI.getTile(TILE_RADIATION_CPM)->setText("100cpm");


  // ******************************************
  // THEME: Electromagnetic Readings (2)
  // ******************************************  
  // TILE: Spectrometer (2x1)
  // NOTE: Spectrum (1D data) tile
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_SPECTROMETER)->Initialize("Spectrum", RGB(0, 0, 128), NULL, NULL);
  tileGUI.getTile(TILE_SPECTROMETER)->setSize(2, 1);
  tileGUI.getTile(TILE_SPECTROMETER)->setText("");   
  
  // TILE: UV (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_UV)->Initialize("UV Index", RGB(128, 0, 128), &symbUVBitmap, NULL);
  tileGUI.getTile(TILE_UV)->setText("6i");  

  // TILE: Linear Polarization (1x1)  
  Serial.println ("Adding tile...");  
  tileGUI.addTile(TILE_LINEAR_POL)->Initialize("Polarization", RGB(128, 0, 128), &symbPolarizationBitmap, NULL);
  tileGUI.getTile(TILE_LINEAR_POL)->setText("25%");  
        
        
  // ******************************************        
  // THEME: Electromagnetic Readings (3)
  // ******************************************  
  Serial.println ("Adding tile...");
  // TILE: Lightning (disturber) (1x1)
  tileGUI.addTile(TILE_LIGHTNING_DIS)->Initialize("Disturber", RGB(0, 0, 128), &symbLightningBitmap, NULL);
  tileGUI.getTile(TILE_LIGHTNING_DIS)->setText("1km");  

  // TILE: IMU (acceleration) (1x1)
  tileGUI.addTile(TILE_IMU_ACCEL)->Initialize("Accel", RGB(0, 0, 128), &symbIMUBitmap, NULL);
  tileGUI.getTile(TILE_IMU_ACCEL)->setText("1.2g");  
  
  // TILE: Thermal Imager (16x4)
  // NOTE: Image (2D data) tile
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_THERMAL_CAM)->Initialize("Thermal Imager", RGB(0, 0, 128), NULL, NULL);
  tileGUI.getTile(TILE_THERMAL_CAM)->setSize(2, 1);
  tileGUI.getTile(TILE_THERMAL_CAM)->setText("");   


  // ******************************************  
  // THEME: Gas measurements
  // ******************************************  
  // TILE: Gas (CO) (1x1)
  tileGUI.addTile(TILE_GAS_CO)->Initialize("CO Gas", RGB(0, 128, 0), &symbGasBitmap, NULL);
  tileGUI.getTile(TILE_GAS_CO)->setText("10ppm");  

  // TILE: Gas (NO2) (1x1)
  tileGUI.addTile(TILE_GAS_NO2)->Initialize("NO2 Gas", RGB(0, 128, 0), &symbGasBitmap, NULL);
  tileGUI.getTile(TILE_GAS_NO2)->setText("1ppm");  

  // TILE: Gas (NH3) (1x1)
  tileGUI.addTile(TILE_GAS_NH3)->Initialize("NH3 Gas", RGB(0, 128, 0), &symbGasBitmap, NULL);
  tileGUI.getTile(TILE_GAS_NH3)->setText("5ppm");  

  // TILE: Audio (microphone) (1x1)
  tileGUI.addTile(TILE_AUDIO_MIC)->Initialize("Microphone", RGB(128, 0, 128), &symbMicrophoneBitmap, NULL);
  tileGUI.getTile(TILE_GAS_NH3)->setText("10db");  


  // ******************************************
  // THEME: Settings/Utilities
  // ******************************************  
  // TILE: data.sparkfun.com
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_UTIL_DATASPARKFUN)->Initialize("enabled", RGB(128, 0, 0), &symbSparkfunDataBitmap, NULL);
  tileGUI.getTile(TILE_UTIL_DATASPARKFUN)->setSize(2, 1);

  // ******************************************  
  // Pack tiles (must be called after adding tiles)
  // ******************************************
  tileGUI.packTiles();


}

float count1 = 0.0f;
int incrementDirection = 1;
void loop() {
  // Update sensor data
  float length = sensorHMC5883L.read_HMC5883L();
  sb.put( length );
  sbx.put( sensorHMC5883L.x );
  sby.put( sensorHMC5883L.y );
  sbz.put( sensorHMC5883L.z );

  thermalImager.updateThermalImage();
  thermalImager.debugPrint();
/*
  count1 += 0.1;
  sb.put( count1 );
  if (count1 > 200) {
    count1 = 0.0f;
  }
*/  
  
  // ******************************************    
  // Render tiles
  // ******************************************    
  // Step 1: Render
  Serial.println ("Rendering");
  tileGUI.render();
  Serial.println ("Updating Screen");
  GFX.updateScreen(); 
    
  // Step 2: Read user input
  // Increment/Decrement selected tile based on touch wheel input
  int16_t deltaWheel = touchWheel.getWheelIncrement();  
  // Negative delta: select previous tile
  if (deltaWheel < 0) {      
    for (int i=0; i<-deltaWheel; i++) {
      tileGUI.selectPrevTile();
    } 
  }
  // Positive delta: select next tile
  if (deltaWheel > 0) {      
    for (int i=0; i<deltaWheel; i++) {
      tileGUI.selectNextTile();
    } 
  }

/*    
    Serial.println ("Selecting next tile");  
    if (incrementDirection == 1) {  
      if (!tileGUI.selectNextTile() ) incrementDirection = 0;      
    } else {
      if (!tileGUI.selectPrevTile() ) incrementDirection = 1;      
    }
*/  
  
}

uint8_t mode = 1;
int count = 0;

int16_t touchHist[TOUCH_HIST_SIZE]; 

float cosd(float angle) {
 float angleRad = (angle / 180.0f) * 3.1415926f; 
 return cos(angleRad);
}

float sind(float angle) {
 float angleRad = (angle / 180.0f) * 3.1415926f; 
 return sin(angleRad);
}


void loop1() {

/*  
  // Touch wheel
  int16_t touchAngle = touchWheel.getWheelAngle();
  Serial.print (" Wheel degree: ");
  Serial.println(touchAngle, DEC);


  // Save touch wheel history
  if (touchAngle >= 0) {
    for (int i=0; i<(TOUCH_HIST_SIZE-1); i++) {
      touchHist[i] = touchHist[i+1];
    }  
    touchHist[TOUCH_HIST_SIZE-1] = touchAngle;
  }

  // Render touch wheel history
  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  
  for (int i=0; i<TOUCH_HIST_SIZE; i++) {
    float proportion = ((float)i / (float)TOUCH_HIST_SIZE);
    float rotation = (float)touchHist[i];
    float x = 0.0f;    
    float y = -50.0f * proportion;
    float x0 = (x * cosd(rotation)) - (y * sind(rotation));
    float y0 = (y * cosd(rotation)) + (x * sind(rotation));
//    float x0 = (cos(rotation) * x) – (sin(rotation) * y);
//    float y0 = cos(rotation) * y + sin(rotation) * x;
//    float x0 = 0.0f;
//    float y0 = 0.0f;
    uint16_t col = RGB(255*proportion, 255*proportion, 255*proportion);
    GFX.drawCircle(ceil(x0 + 64), ceil(y0 + 64), ceil(5 * proportion), col);
  }
  
  GFX.drawCircle(64, 64, 50, RGB(128, 128, 128));
  
  GFX.updateScreen();  
*/  
  
  
  
/*  
  // Rotate graphs every N measurements
  count += 1;
  if (((count == 100) && (showGraph == GRAPH_MAGXYZ)) ||
      ((count == 100) && (showGraph == GRAPH_MAGSTRENGTH)) ||
      ((count == 100) && (showGraph == GRAPH_HUMIDITY)) ||
      ((count == 100) && (showGraph == GRAPH_PRESSURE)) ||
      ((count == 100) && (showGraph == GRAPH_ACCELGYRO)) ||      
      ((count == 100) && (showGraph == GRAPH_MIC))) {
       
    count = 0;
    
    mode = (mode + 1) % GRAPH_MAX;
    showGraph = mode + 1;

    //##    
//    showGraph = GRAPH_ACCELGYRO;
    
    initSensorGraph();
  }
  
  showSensorGraph();
*/  
    
  
  /*
  // Read UV Sensor  
  Serial.println("===================");
  Serial.print("Vis: "); Serial.println(uv.readVisible());
  Serial.print("IR: "); Serial.println(uv.readIR());
  
  // Uncomment if you have an IR LED attached to LED pin!
  Serial.print("Prox: "); Serial.println(uv.readProx());
  
  float UVIndex = uv.readUV();
  UVIndex /= 100.0;  
  Serial.print("UV: "); 
  Serial.println(UVIndex);
  */  
  
//  delay(10);
     
/*     
    // Include timestamp
    int h,m,s,ms;
    unsigned long over;
    unsigned long elapsed=millis();
    h=int(elapsed/3600000);
    over=elapsed%3600000;
    m=int(over/60000);
    over=over%60000;
    s=int(over/1000);
    ms=over%1000;
    Serial.print(h);
    Serial.print("h:");
    Serial.print(m);
    Serial.print("m:");
    Serial.print(s);
    Serial.print("s:");
    Serial.print(ms);
    Serial.print("ms  : ");

    // Message
    Serial.print("Hello world!    ");
    Serial.println (count);
    count += 1;
*/

  // Pause on key press, to take pictures
  if (Serial.available() > 0) {
    // get incoming byte:
    int inByte = Serial.read();
    delay(10000);
  }  

}


void initSensorGraph() {
  if (showGraph == GRAPH_MAGXYZ) {
    initMagGraphXYZL();
  } else if (showGraph == GRAPH_MAGSTRENGTH) {
    initMagGraphLength();    
  } else if (showGraph == GRAPH_MIC) {
    initMicGraph();
  } else if (showGraph == GRAPH_HUMIDITY) {
    initHumidityGraph();    
  } else if (showGraph == GRAPH_ACCELGYRO) {
    initAccelGyroGraph();        
  }
}

void showSensorGraph() {
  if (showGraph == GRAPH_MAGXYZ) {
    doMagGraphXYZL();
  } else if (showGraph == GRAPH_MAGSTRENGTH) {
    doMagGraphLength();    
  } else if (showGraph == GRAPH_MIC) {
    doMicGraph();
  } else if (showGraph == GRAPH_HUMIDITY) {
    doHumidityGraph();    
  } else if (showGraph == GRAPH_ACCELGYRO) {
    doAccelGyroGraph();        
  }  
}


// Graphs
/* 
 * Magnetometer
 */ 
void initMagGraphXYZL() {
  // Initialize magnetometer graph (x, y, z, and field strength)
  Graph.clearSeries();
  Graph.addSeries( &sbx, RGB(255, 0, 0) );
  Graph.addSeries( &sby, RGB(0, 255, 0) );
  Graph.addSeries( &sbz, RGB(0, 0, 255) );  
  Graph.addSeries( &sb, RGB(255, 255, 255) );    
}

void doMagGraphXYZL() {
  // Read magnetometer
  float length = sensorHMC5883L.read_HMC5883L();
  sb.put( length );
  sbx.put( sensorHMC5883L.x );
  sby.put( sensorHMC5883L.y );
  sbz.put( sensorHMC5883L.z );

  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  Graph.renderGraph(10, 10, 100, 100);
  
  GFX.updateScreen();  
}

void initMagGraphLength() {
  // Initialize magnetometer graph (Just display total field strength)
  Graph.clearSeries();
  Graph.addSeries( &sb, RGB(0, 0, 255) );    
}

void doMagGraphLength() {
  // Read magnetometer
  float length = sensorHMC5883L.read_HMC5883L();
  sb.put( length );
  
  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  Graph.renderGraph(10, 10, 100, 100);
  
  GFX.updateScreen();  
}

/*
 * Audio (Microphone)
 */ 
void initMicGraph() {
  // Initialize magnetometer graph
  Graph.clearSeries();
  Graph.addSeries( &sbMic, RGB(255, 0, 255) );
}

void doMicGraph() {
  // Read microphone
  uint16_t micVal = sensorMicrophone.readValue();
  sbMic.put ((float)micVal);
  
  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  Graph.renderGraph(10, 10, 100, 100);
  
  GFX.updateScreen();
}


/*
 * Humidity
 */ 

void initHumidityGraph() {
  // Initialize humidity graph
  Graph.clearSeries();
  Graph.addSeries( &sbTemp, RGB(255, 0, 0) );
  Graph.addSeries( &sbHumidity, RGB(0, 255, 0) );
}

void doHumidityGraph() {
  // Read humidity
  float humd = sensorHTU21D.readHumidity();
  float temp = sensorHTU21D.readTemperature();

  Serial.print ("Humidity: ");
  Serial.println (humd);
  Serial.print ("Ambient Temperature: ");
  Serial.println (temp);
  
  sbTemp.put( temp );
  sbHumidity.put( humd );

  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  Graph.renderGraph(10, 10, 100, 100);
  
  GFX.updateScreen();  
//  delay(250);
}


/*
 * Pressure 
 */ 
void initPressureGraph() {
  // Initialize pressure graph
  Graph.clearSeries();
  Graph.addSeries( &sbPressure, RGB(255, 255, 0) );
}

void doPressureGraph() {
  // Read pressure
  /*
  float humd = sensorHTU21D.readHumidity();
  float temp = sensorHTU21D.readTemperature();

  Serial.print ("Humidity: ");
  Serial.println (humd);
  Serial.print ("Ambient Temperature: ");
  Serial.println (temp);
  
  sbTemp.put( temp );
  sbHumidity.put( humd );
  */
  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  Graph.renderGraph(10, 10, 100, 100);
  
  GFX.updateScreen();  
//  delay(250);
}

/* 
 * Accelerometer / Gyro 
 */ 
void initAccelGyroGraph() {
  // Initialize accelerometer/gyro graph (x, y, z, for both acceleration and rotation)
  Graph.clearSeries();
  Graph.addSeries( &sbAccelX, RGB(255, 0, 0) );
  Graph.addSeries( &sbAccelY, RGB(0, 255, 0) );
  Graph.addSeries( &sbAccelZ, RGB(0, 0, 255) );
  Graph.addSeries( &sbGyroX, RGB(255, 255, 0) );  
  Graph.addSeries( &sbGyroY, RGB(255, 0, 255) );  
  Graph.addSeries( &sbGyroZ, RGB(0, 255, 255) );    
}

void doAccelGyroGraph() {
  // Read magnetometer
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  // read raw accel/gyro measurements from device
  //Serial.println ("Reading motion...");
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  //Serial.println ("Storing motion...");
  sbAccelX.put( (float)ax );
  sbAccelY.put( (float)ay );
  sbAccelZ.put( (float)az );
  sbGyroX.put( (float)gx );
  sbGyroY.put( (float)gy );
  sbGyroZ.put( (float)gz );

  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  
  //Serial.println ("Rendering graph...");
  Graph.renderGraph(10, 10, 100, 100);

  //Serial.println ("Updating...");
  GFX.updateScreen();  
}







// TEST
void bmp180_test() {
  Serial.println("Pressure Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  while (1) {
    /* Get a new sensor event */ 
  sensors_event_t event;
  bmp.getEvent(&event);
 
  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    /* Display atmospheric pressue in hPa */
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    
    /* Calculating altitude with reasonable accuracy requires pressure    *
     * sea level pressure for your position at the moment the data is     *
     * converted, as well as the ambient temperature in degress           *
     * celcius.  If you don't have these values, a 'generic' value of     *
     * 1013.25 hPa can be used (defined as SENSORS_PRESSURE_SEALEVELHPA   *
     * in sensors.h), but this isn't ideal and will give variable         *
     * results from one day to the next.                                  *
     *                                                                    *
     * You can usually find the current SLP value by looking at weather   *
     * websites or from environmental information centers near any major  *
     * airport.                                                           *
     *                                                                    *
     * For example, for Paris, France you can check the current mean      *
     * pressure and sea level at: http://bit.ly/16Au8ol                   */
     
    /* First we get the current temperature from the BMP085 */
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    /* Then convert the atmospheric pressure, SLP and temp to altitude    */
    /* Update this next line with the current SLP for better results      */
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitude:    "); 
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure,
                                        temperature)); 
    Serial.println(" m");
    Serial.println("");
  }
  else
  {
    Serial.println("Sensor error");
  }
  delay(1000);

  
  }  
  
}


//## TEST
void AS3935Irq();
volatile int AS3935IrqTriggered;

// First parameter - SPI transfer function, second - Arduino pin used for CS
// and finally third argument - Arduino pin used for IRQ
// It is good idea to chose pin that has interrupts attached, that way one can use
// attachInterrupt in sketch to detect interrupt
// Library internally polls this pin when doing calibration, so being an interrupt pin
// is not a requirement
#define AS3935_INT_PIN  4
AS3935 AS3935( AS3935_INT_PIN );

void AS3935_setup() {
  Serial.println("AS3935: Setup (starting)");
  
  AS3935.reset();
  // and run calibration
  // if lightning detector can not tune tank circuit to required tolerance,
  // calibration function will return false
  if(!AS3935.calibrate())
    Serial.println("Tuning out of range, check your wiring, your sensor and make sure physics laws have not changed!");

  // since this is demo code, we just go on minding our own business and ignore the fact that someone divided by zero

  // first let's turn on disturber indication and print some register values from AS3935
  // tell AS3935 we are indoors, for outdoors use setOutdoors() function
  AS3935.setIndoors();
  // turn on indication of distrubers, once you have AS3935 all tuned, you can turn those off with disableDisturbers()
  AS3935.enableDisturbers();
  printAS3935Registers();
  AS3935IrqTriggered = 0;
  // Using interrupts means you do not have to check for pin being set continiously, chip does that for you and
  // notifies your code
  // demo is written and tested on ChipKit MAX32, irq pin is connected to max32 pin 2, that corresponds to interrupt 1
  // look up what pins can be used as interrupts on your specific board and how pins map to int numbers

  // ChipKit Max32 - irq connected to pin 2
  attachInterrupt(1,AS3935Irq,RISING);
  // uncomment line below and comment out line above for Arduino Mega 2560, irq still connected to pin 2
  // attachInterrupt(0,AS3935Irq,RISING);
}

void AS3935_test() {
  Serial.println("AS3935: Test (starting)");
  while (1) {
  // here we go into loop checking if interrupt has been triggered, which kind of defeats
  // the whole purpose of interrupts, but in real life you could put your chip to sleep
  // and lower power consumption or do other nifty things
  if(AS3935IrqTriggered)
  {
    // reset the flag
    AS3935IrqTriggered = 0;
    // first step is to find out what caused interrupt
    // as soon as we read interrupt cause register, irq pin goes low
    int irqSource = AS3935.interruptSource();
    // returned value is bitmap field, bit 0 - noise level too high, bit 2 - disturber detected, and finally bit 3 - lightning!
    if (irqSource & 0b0001)
      Serial.println("Noise level too high, try adjusting noise floor");
    if (irqSource & 0b0100)
      Serial.println("Disturber detected");
    if (irqSource & 0b1000)
    {
      // need to find how far that lightning stroke, function returns approximate distance in kilometers,
      // where value 1 represents storm in detector's near victinity, and 63 - very distant, out of range stroke
      // everything in between is just distance in kilometers
      int strokeDistance = AS3935.lightningDistanceKm();
      if (strokeDistance == 1)
        Serial.println("Storm overhead, watch out!");
      if (strokeDistance == 63)
        Serial.println("Out of range lightning detected.");
      if (strokeDistance < 63 && strokeDistance > 1)
      {
        Serial.print("Lightning detected ");
        Serial.print(strokeDistance,DEC);
        Serial.println(" kilometers away.");
      }
    }
  }
  }

}


void printAS3935Registers()
{
  int noiseFloor = AS3935.getNoiseFloor();
  int spikeRejection = AS3935.getSpikeRejection();
  int watchdogThreshold = AS3935.getWatchdogThreshold();
  Serial.print("Noise floor is: ");
  Serial.println(noiseFloor,DEC);
  Serial.print("Spike rejection is: ");
  Serial.println(spikeRejection,DEC);
  Serial.print("Watchdog threshold is: ");
  Serial.println(watchdogThreshold,DEC);  
}

// this is irq handler for AS3935 interrupts, has to return void and take no arguments
// always make code in interrupt handlers fast and short
void AS3935Irq()
{
  AS3935IrqTriggered = 1;
}

/*
//##
void initMPU6050() {  
    accelgyro.initialize();
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void readMPU6050() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  
  while (1) {
      // read raw accel/gyro measurements from device
    //accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    accelgyro.getAcceleration(&ax, &ay, &az);
    accelgyro.getRotation(&gx, &gy, &gz);

        // display tab-separated accel/gyro x/y/z values
        Serial.print("a/g:\t");
        Serial.print(ax); Serial.print("\t");
        Serial.print(ay); Serial.print("\t");
        Serial.print(az); Serial.print("\t");
        Serial.print(gx); Serial.print("\t");
        Serial.print(gy); Serial.print("\t");
        Serial.println(gz);
    
    delay(250);
  }
}
*/
