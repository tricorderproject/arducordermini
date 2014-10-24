// main.c
// This firmware is a work in progress, and is currently test/development firmware 
// used to verify the functionality of the hardware.  

#include <Client.h>
#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include <math.h>
#include <I2Cdev.h>
#include <MPU6050.h>

// Graphics
#include "SSD1351.h"
#include "FramebufferGFX.h"
#include "FramebufferGraphs.h"

// Sensors
#include "Adafruit_MPR121.h"
#include "sensorbuffer.h"
#include "sensor_HMC5883L.h"
#include "sensor_microphone.h"
#include "Adafruit_SI1145.h"
#include "sensor_HTU21D.h"
#include "sensor_BMP180.h"
#include "sensor_AS3935.h"
#include "SensorMLX90620.h"
#include "SensorSpecHamamatsu.h"
#include "SensorRadiation.h"

// User Interface
#include "Tile.h"
#include "Fonts.h"
#include "Bitmaps.h"
#include "TileGUI.h"

// Communications
#include <Adafruit_CC3000.h>
#include "PlotlyInterface.h"


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
SensorBuffer sbRad(100);

SensorBuffer sbSpectMeasurement(100);            // Sensor buffer test
FramebufferGraphs SpectrometerGraph(&GFX);  

// Sensor Variables
SensorHMC5883L sensorHMC5883L;                      // Magnetometer
Adafruit_MPR121 touchWheel = Adafruit_MPR121();     // MPR121 touch sensor
Adafruit_SI1145 uv = Adafruit_SI1145();             // SI1445 UV sensor
SensorMicrophone sensorMicrophone;                  // ADMP401 microphone
HTU21D sensorHTU21D;                                // HTU21D temperature/humidity sensor

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);  // BMP180 barometric pressure sensor

MPU6050 accelgyro(0x69); // <-- use for AD0 low     // MPU9150 Inertial measurement unit

SensorMLX90620 thermalImager;                       // MLX90620 16x4 Thermal Imager
SensorSpecHamamatsu sensorSpectrometer;             // Hamamatsu C12666MA micro spectroemter
SensorRadiation sensorRadiation(&sbRad);            // Radiation Watch Type 5 High-energy Particle Detector


// Plotly Web Interface
Adafruit_CC3000 cc3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIV2);  
PlotlyInterface plotly = PlotlyInterface(&cc3000);
int plotlyStatus = PLOTLY_UNINITIALIZED;


// User interface -- modes
uint8_t userInterfaceMode;
#define UI_MODE_TILE     10
#define UI_MODE_GRAPH    20

// User interface -- graph based displays
#define GRAPH_MAGXYZ         1
#define GRAPH_MAGSTRENGTH    2
#define GRAPH_MIC            3
#define GRAPH_HUMIDITY       4
#define GRAPH_PRESSURE       5
#define GRAPH_ACCELGYRO      6
#define GRAPH_RADIATION      7
#define GRAPH_SPECTROMETER   8
#define GRAPH_THERMAL        9

uint16_t showGraph = GRAPH_MAGXYZ;

// User interface -- push buttons (MPR121 electrode numbers)
#define BUTTON_TOUCH_SELECT    10  
#define BUTTON_TOUCH_BACK      9

// Temporary buffer for string operations
char stringBuffer[10];

// Functions
void setup() {
  Serial.begin(9600);
  Serial.println("Initializing... "); 

  // Initialize framebuffer
  Serial.println("Initializing Framebuffer...");  
  Framebuffer.begin();  
  GFX.displayFlashBitmap4Bit(5, 32, &symbArducorderSplashBitmap, 0);
  GFX.updateScreen();

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
//  thermalImager.debugPrint();  
  
  // Initialize C12666MA Micro Spectrometer
  Serial.println ("Initializing C12666MA...");
  sensorSpectrometer.begin();    
  
  // Initialize HMC5883L
  Serial.println("Initializing HMC5883L...");
  sensorHMC5883L.init_HMC5883L();
  delay(500);
  
  // Initialize UV sensor
  Serial.println("Initializing UV Sensor...");
  uv.begin();
  
  // Initialize pressure sensor
  Serial.println("Initializing BMP180...");     
  if (!bmp.begin()) {
    Serial.println("ERROR: Could not initialize BMP180...");     
  }
  
  // Initialize AS3935 
  //Serial.println("Initializing AS3935...");     
  //AS3935_setup();
   
  // Initialize MPU6050
  Serial.println("Initializing MPU9050...");     
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");   

    
  // Initialize Radiation sensor (interrupt driven)
  Serial.println("Initializing Radiation sensor...");       
  setupRadiationISR(&sensorRadiation);     // MUST be called before begin()
  sensorRadiation.begin();


  // Re-initialize the MLX90620 
  // TODO: The thermal imager seems to require initialization twice -- check into this
  Serial.println("Initializing Thermal Imager...");  
  thermalImager.begin();    

  // Visualization
  Serial.println("Initializing Sensor Graph...");  
  initSensorGraph();
  
  
  
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
  tileGUI.addTile(TILE_ATMTEMP)->Initialize("Temp", RGB(0, 0, 128), &symbTempBitmap, &sbTemp);
  // Set unit text to "[degree]C"
  strcpy(stringBuffer, " C");
  stringBuffer[0] = 176;
  tileGUI.getTile(TILE_ATMTEMP)->setUnitText(stringBuffer);
  
  // TILE: Ambient Humidity (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_ATMHUMIDITY)->Initialize("Humidity", RGB(0, 0, 128), &symbHumidityBitmap, &sbHumidity);
  tileGUI.getTile(TILE_ATMHUMIDITY)->setUnitText("%");
  
  // TILE: Ambient Pressure (2x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_ATMPRESSURE)->Initialize("Pressure", RGB(0, 128, 0), &symbPressureBitmap, &sbPressure);
  tileGUI.getTile(TILE_ATMPRESSURE)->setSize(2, 1);
  tileGUI.getTile(TILE_ATMPRESSURE)->setUnitText("mbar");    
  tileGUI.getTile(TILE_ATMPRESSURE)->setSensorTextFormat(TEXT_FLOAT1DEC);
  
  // ******************************************  
  // THEME: Electromagnetic Readings (1)
  // ******************************************  
  // TILE: Magnetic Field Strength (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_MAGFIELD)->Initialize("Magnetic", RGB(0, 0, 128), &symbMagBitmap, &sb);
  strcpy(stringBuffer, " T");
  stringBuffer[0] = 181;
  tileGUI.getTile(TILE_MAGFIELD)->setUnitText(stringBuffer);
  
  // TILE: Magnetic Field Direction (1x1)  
  // NOTE: Arrow tile currently unimplemented
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_MAGDIR)->Initialize("Magnetic", RGB(0, 0, 128), &symbMagBitmap, NULL);
  tileGUI.getTile(TILE_MAGDIR)->setText("DIR");

  // TILE: Lightning (strike distance) (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_LIGHTNING_STR)->Initialize("Lightning", RGB(0, 0, 128), &symbLightningBitmap, NULL);
  tileGUI.getTile(TILE_LIGHTNING_STR)->setText("5");
  tileGUI.getTile(TILE_LIGHTNING_STR)->setUnitText("km");

  // TILE: Radiation (counts per minute) (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_RADIATION_CPM)->Initialize("Radiation", RGB(0, 0, 128), &symbRadiationBitmap, NULL);
  tileGUI.getTile(TILE_RADIATION_CPM)->setUnitText("cpm");



  // ******************************************
  // THEME: Electromagnetic Readings (2)
  // ******************************************  
  // TILE: Spectrometer (2x1)
  // NOTE: Spectrum (1D data) tile
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_SPECTROMETER)->Initialize("Spectrum", RGB(0, 0, 128), NULL, NULL);
  tileGUI.getTile(TILE_SPECTROMETER)->setSize(2, 1);
  tileGUI.getTile(TILE_SPECTROMETER)->setText("");   
  
  SpectrometerGraph.clearSeries();
  SpectrometerGraph.addSeries( &sbSpectMeasurement, RGB(128, 128, 255) );
  tileGUI.getTile(TILE_SPECTROMETER)->setLiveGraph(&SpectrometerGraph);   

  
  // TILE: UV (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_UV)->Initialize("UV Index", RGB(128, 0, 128), &symbUVBitmap, NULL);
  tileGUI.getTile(TILE_UV)->setText("0");  
  tileGUI.getTile(TILE_UV)->setUnitText("i");

  // TILE: Linear Polarization (1x1)  
  Serial.println ("Adding tile...");  
  tileGUI.addTile(TILE_LINEAR_POL)->Initialize("Polarization", RGB(128, 0, 128), &symbPolarizationBitmap, NULL);
  tileGUI.getTile(TILE_LINEAR_POL)->setText("25");
  tileGUI.getTile(TILE_LINEAR_POL)->setUnitText("%");  

  
        
        
  // ******************************************        
  // THEME: Electromagnetic Readings (3)
  // ******************************************  
  // TILE: Thermal Imager (16x4)
  // NOTE: Image (2D data) tile
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_THERMAL_CAM)->Initialize("Thermal", RGB(0, 0, 128), NULL, NULL);
  tileGUI.getTile(TILE_THERMAL_CAM)->setSize(1, 2);
  tileGUI.getTile(TILE_THERMAL_CAM)->setText("");   
  tileGUI.getTile(TILE_THERMAL_CAM)->setLiveBitmap(&thermalImager.image[0][0], 4, 16);
  
  // TILE: Lightning (disturber) (1x1)
  Serial.println ("Adding tile...");  
  tileGUI.addTile(TILE_LIGHTNING_DIS)->Initialize("Disturber", RGB(0, 0, 128), &symbLightningBitmap, NULL);
  tileGUI.getTile(TILE_LIGHTNING_DIS)->setText("1");  
  tileGUI.getTile(TILE_LIGHTNING_DIS)->setUnitText("km");

  // TILE: IMU (acceleration) (1x1)
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_IMU_ACCEL)->Initialize("Accel", RGB(0, 0, 128), &symbIMUBitmap, NULL);
  tileGUI.getTile(TILE_IMU_ACCEL)->setText("1.0");
  tileGUI.getTile(TILE_IMU_ACCEL)->setUnitText("g");

  


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
  tileGUI.addTile(TILE_AUDIO_MIC)->Initialize("Microphone", RGB(102, 29, 89), &symbMicrophoneBitmap, &sbMic);
  tileGUI.getTile(TILE_AUDIO_MIC)->setUnitText("v");
  tileGUI.getTile(TILE_AUDIO_MIC)->setSensorTextFormat(TEXT_FLOAT2DEC);
  tileGUI.getTile(TILE_AUDIO_MIC)->setSensorTextMinMaxRecent(DISP_MAX);

  // ******************************************
  // THEME: Settings/Utilities
  // ******************************************  
  tileGUI.addTile(TILE_ALTITUDE)->Initialize("Altitude", RGB(0, 128, 0), &symbIMUBitmap, NULL);
  tileGUI.getTile(TILE_ALTITUDE)->setSize(2, 1);
  tileGUI.getTile(TILE_ALTITUDE)->setText("0");    
  tileGUI.getTile(TILE_ALTITUDE)->setUnitText("m");    
//  tileGUI.getTile(TILE_ALTITUDE)->setSensorTextFormat(TEXT_FLOAT1DEC);
  
  
  // TILE: plotly.com
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_UTIL_PLOTLY)->Initialize("not connected", RGB(102, 29, 89), &symbPlotlyBitmap, NULL);
  tileGUI.getTile(TILE_UTIL_PLOTLY)->setSize(2, 1);

  // TILE: plotly.com
  Serial.println ("Adding tile...");
  tileGUI.addTile(TILE_UTIL_WIFI)->Initialize("disabled", RGB(0, 0, 128), &symbWifiBitmap, NULL);
  tileGUI.getTile(TILE_UTIL_WIFI)->setSize(1, 1);

  
  // ******************************************  
  // Pack tiles (must be called after adding tiles)
  // ******************************************
  tileGUI.packTiles();
  
  // Debug: Skip to Thermal Camera time
  tileGUI.selectedTile = 0;   // First page
//  tileGUI.selectedTile = 7;   // Spectrometer
//  tileGUI.selectedTile = 10;  // Thermal camera

  // Set initial user interface mode (tile)
  userInterfaceMode = UI_MODE_TILE;
}

//float count1 = 0.0f;
//int incrementDirection = 1;
int interfaceMode = 0;
void loop() {
  // ******************************************    
  // Update sensor data
  // ******************************************      
  Serial.println ("Updating Sensor Data...");
  updateSensorData();  
  

  // ******************************************    
  // Render tile or graph display
  // ******************************************      
  if (userInterfaceMode == UI_MODE_TILE) {
    Serial.println ("Tile Interface...");
      
    // Tile display
    userInterfaceTiles();
    // If the SELECT button has been pressed, transition to a graph view for this tile
    if (touchWheel.isButtonPressed(BUTTON_TOUCH_SELECT)) {

      int selectedTile = tileGUI.getSelectedTileID();
      
      // Setup graph display
      boolean validSwitch = true;
      switch(selectedTile) {
        case TILE_ATMTEMP:
        case TILE_ATMHUMIDITY:
          showGraph = GRAPH_HUMIDITY;
          break;
        case TILE_ATMPRESSURE:
          showGraph = GRAPH_PRESSURE;
          break;
        case TILE_MAGFIELD:
          showGraph = GRAPH_MAGXYZ;
          break;
        case TILE_RADIATION_CPM:
          showGraph = GRAPH_RADIATION;
          break;
        case TILE_SPECTROMETER:
          showGraph = GRAPH_SPECTROMETER;
          break;
        case TILE_THERMAL_CAM:
          showGraph = GRAPH_THERMAL;
          break;
        case TILE_IMU_ACCEL:
          showGraph = GRAPH_ACCELGYRO;
          break;
        case TILE_AUDIO_MIC:
          showGraph = GRAPH_MIC;
          break;
        
          
        default:
          validSwitch = false;
          break;
      }
      
      if (validSwitch) {
        userInterfaceMode = UI_MODE_GRAPH;       
        initSensorGraph();
      }
      
      // Special cases for utility tiles
      if (selectedTile == TILE_UTIL_WIFI) {
        connectToWifi(); 
      }
      if (selectedTile == TILE_UTIL_PLOTLY) {
        connectToPlotly(); 
      }
    }
  } else if (userInterfaceMode == UI_MODE_GRAPH) {
    Serial.println ("Graph Display...");    
    // Graph display
    int selectedTile = tileGUI.getSelectedTileID();
    Tile* curTile = tileGUI.getTile(selectedTile);
    showSensorGraph(curTile);
    
    // If the BACK button has been pressed, transition back to the tile view
    if (touchWheel.isButtonPressed(BUTTON_TOUCH_BACK)) {
      userInterfaceMode = UI_MODE_TILE; 
    }    
  }

}


void userInterfaceTiles() {
  // ******************************************    
  // Step 1: Render tiles
  // ******************************************    
  Serial.println ("Rendering");
  tileGUI.render();
  Serial.println ("Updating Screen");
  GFX.updateScreen(); 

  // *********************************************    
  // Step 2: Read user input for scrolling (tile based display)
  // *********************************************    
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
}

void updateSensorData() {
  // Update sensor data based on tiles that are currently visible on the display

  // Atmospheric temperature and pressure
  if (( tileGUI.isTileOnScreen(TILE_ATMTEMP) )
    || ( tileGUI.isTileOnScreen(TILE_ATMHUMIDITY) )) {
    float humd = sensorHTU21D.readHumidity();
    float temp = sensorHTU21D.readTemperature();
    sbTemp.put( temp );
    sbHumidity.put( humd );    
  }
  
  // Atmospheric pressure
  if ( tileGUI.isTileOnScreen(TILE_ATMPRESSURE) || tileGUI.isTileOnScreen(TILE_ALTITUDE) ) { 
    // Measure pressure
    sensors_event_t event;
    bmp.getEvent(&event);
    sbPressure.put(event.pressure);  
    
    // Measure altitute (NOTE: currently unused)    
    // Determine average pressure over the last 10 measurements (this will make the altitude more accurate)
    sbPressure.resetRingIdx();
    int numValid = sbPressure.getSize();
    float avg = 0.0f;
    for (int idx=0; idx<numValid; idx++) {
      if (idx >= (numValid - 20)) {
        avg += sbPressure.getNext();    // add to average
      } else {
        sbPressure.getNext();           // disregard
      }
    }
    avg = avg/20;
    
    float temperature;
    bmp.getTemperature(&temperature);
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    float altitude = bmp.pressureToAltitude(seaLevelPressure, avg, temperature); 
    
    char buffer[10];
    sprintf(buffer, "%.1fm", altitude);
    tileGUI.getTile(TILE_ALTITUDE)->setText(buffer);    
  }
     
  
  // Magnetometer
  if ( tileGUI.isTileOnScreen(TILE_MAGFIELD) ) { 
    float length = sensorHMC5883L.read_HMC5883L();
    sb.put( length );
    sbx.put( sensorHMC5883L.x );
    sby.put( sensorHMC5883L.y );
    sbz.put( sensorHMC5883L.z );
  }

  // Thermal Imager
  if ( tileGUI.isTileOnScreen(TILE_THERMAL_CAM) ) { 
    thermalImager.updateThermalImage();
//    thermalImager.debugPrint();
  }
    
  // Spectrometer
  if ( tileGUI.isTileOnScreen(TILE_SPECTROMETER) ) {   
    sensorSpectrometer.takeMeasurement();
    sensorSpectrometer.populateSensorBuffer(&sbSpectMeasurement, SPEC_DATA);
  }
  
  // Radiation Sensor (measurement is interrupt driven, so here we just need to update the text)
  if ( tileGUI.isTileOnScreen(TILE_RADIATION_CPM) ) { 
    char buffer[10];
    sprintf(buffer, "%.0f", sensorRadiation.calculateCPM());
    tileGUI.getTile(TILE_RADIATION_CPM)->setText(buffer);
  }
  
  if ( tileGUI.isTileOnScreen(TILE_UV) ) { 
    char buffer[10];
    // Read UV index
    float UVIndex = uv.readUV();
    UVIndex /= 100.0;  
    
    // Dynamically scale 
    if (UVIndex < 1.0f) {    
      sprintf(buffer, "%.2f", UVIndex);      // Two decimal places if less than one
    } else {
      sprintf(buffer, "%.1f", UVIndex);      // One decimal place if above one
    }
    tileGUI.getTile(TILE_UV)->setText(buffer);    
  }
  
  
  // Acceleration/IMU
  if ( tileGUI.isTileOnScreen(TILE_IMU_ACCEL) ) { 
    int16_t unitConvA = 16384;      // +/- 2g
    float unitConvG = 131/57.3;     // to degrees, then to radians
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    // read raw accel/gyro measurements from device 
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    // Convert to g's
    float axF, ayF, azF;
    axF = (float)ax/(float)unitConvA;
    ayF = (float)ay/(float)unitConvA;    
    azF = (float)az/(float)unitConvA;

    // Convert to radians/sec
    float gxF, gyF, gzF;
    gxF = (float)gx/unitConvG;
    gyF = (float)gy/unitConvG;
    gzF = (float)gz/unitConvG;    
    
    // Store motion
    sbAccelX.put( axF );
    sbAccelY.put( ayF );
    sbAccelZ.put( azF );
    sbGyroX.put( (float)gx );
    sbGyroY.put( (float)gy );
    sbGyroZ.put( (float)gz );
    
    // Calculate length of acceleration vector
    float length = sqrt(pow((float)axF, 2) + pow((float)ayF, 2) + pow((float)azF, 2));

    // Set text
    sprintf(stringBuffer, "%.2fg", length);
    tileGUI.getTile(TILE_IMU_ACCEL)->setText(stringBuffer);
  }
  
  // Microphone
  if ( tileGUI.isTileOnScreen(TILE_AUDIO_MIC) ) {    
    uint16_t micVal = sensorMicrophone.readValue();
    sbMic.put ((float)micVal / 1024);    
  }

}

// Draw a status window for blocking updates
void drawStatusWindow(char* label, char* text) {
  int mid = (GFX.height/2);
  GFX.fillRoundRect(13, mid-31, GFX.width-13, mid+31, 5, RGB(0, 0, 0));
  GFX.drawRoundRect(14, mid-30, GFX.width-14, mid+30, 5, RGB(128, 128, 128));  
  
  // Label text on the bottom
  GFX.drawJustifiedText(label, 14, GFX.width-14, mid-16, &Ubuntu10, JUST_CENTER, RGB(255, 255, 255) );
  GFX.drawJustifiedText(text, 14, GFX.width-14, mid+10, &Ubuntu10, JUST_CENTER, RGB(255, 255, 255) );    
  GFX.drawLine(20, mid - 13, GFX.width-21, mid - 13, RGB(128, 128, 128) );
  
}


// Connect to the Wifi network (if not currently connected)
void connectToWifi() {
  if (plotlyStatus == PLOTLY_UNINITIALIZED) {
    drawStatusWindow("Connection Status", "Connecting to WiFi");  
    GFX.updateScreen();
    plotly.connectWifi();

    // Connected    
    drawStatusWindow("Connection Status", "Success!");  
    GFX.updateScreen();
    delay(1000);    
    
    // Update status
    tileGUI.getTile(TILE_UTIL_WIFI)->setTileName("connected");            
    plotlyStatus = PLOTLY_WIFI_CONNECTED;
  }  
}

// Connect to Plotly Web Graphing Interface
void connectToPlotly() {  
  // Initialize the CC3000 Wifi and connect to the access point
  if (plotlyStatus == PLOTLY_UNINITIALIZED) {
    connectToWifi();
  }
  
  // Initialize stream plots
  drawStatusWindow("Connection Status", "Setup Graphs");  
  GFX.updateScreen();
  
  // GRAPH_ATMSTREAM / GRAPHTOKENS_ATM[] = {STKN_ATMTEMP, STKN_HUMIDITY, STKN_PRESSURE}
  if (!plotly.initializeStreamingGraph(GRAPH_ATMSTREAM, 3, GRAPHTOKENS_ATM)) {
    Serial.println("ERROR: Unable to initialize graph"); 
  }

  // GRAPH_MAGSTREAM / GRAPHTOKENS_MAG = {STKN_MAGX, STKN_MAGY, STKN_MAGZ, STKN_MAGLEN}
  if (!plotly.initializeStreamingGraph(GRAPH_MAGSTREAM, 4, GRAPHTOKENS_MAG)) {
    Serial.println("ERROR: Unable to initialize graph"); 
  }
  
  // GRAPH_RADSTREAM / GRAPHTOKENS_RAD[] = {STKN_RADCPM}
  if (!plotly.initializeStreamingGraph(GRAPH_RADSTREAM, 1, GRAPHTOKENS_RAD)) {
    Serial.println("ERROR: Unable to initialize graph"); 
  }   
  
  // GRAPH_MOTIONSTREAM / GRAPHTOKENS_MOTION[] = {STKN_ACCELX, STKN_ACCELY, STKN_ACCELZ, STKN_GYROX, STKN_GYROY, STKN_GYROZ}
  if (!plotly.initializeStreamingGraph(GRAPH_MOTIONSTREAM, 6, GRAPHTOKENS_MOTION)) {
    Serial.println("ERROR: Unable to initialize graph"); 
  }   
  
  // GRAPH_SPECSTREAM / GRAPHTOKENS_SPEC[] = {STKN_SPEC}
  if (!plotly.initializeStreamingGraph(GRAPH_SPECSTREAM, 1, GRAPHTOKENS_SPEC)) {
    Serial.println("ERROR: Unable to initialize graph"); 
  }   

  // Open the plotly stream 
  drawStatusWindow("Connection Status", "Opening Streams");  
  GFX.updateScreen();  
  plotly.openStream();
  
  // Notify user of success
  drawStatusWindow("Connection Status", "Success!");  
  GFX.updateScreen();
  delay(1000);
  
  // Update plotly and tile status
  plotlyStatus = PLOTLY_STREAMING;
  tileGUI.getTile(TILE_UTIL_PLOTLY)->setTileName("streaming");    
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
  switch (showGraph) {
    case GRAPH_HUMIDITY:
      initHumidityGraph();    
      break;
    case GRAPH_PRESSURE:
      initPressureGraph();    
      break;      
    case GRAPH_MAGXYZ:
      initMagGraphXYZL();
      break;
    case GRAPH_RADIATION:
      initRadiationGraph();
      break;
    case GRAPH_SPECTROMETER:
      initSpectrometerGraph();
      break;    
    case GRAPH_ACCELGYRO:
      initAccelGyroGraph();                  
      break;            
    case GRAPH_MIC:
      initMicGraph();
      break;
  }
  
}

void showSensorGraph(Tile* curTile) {  
  
  // Step 1: Clear framebuffer
  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  
  // Step 2: Draw gradient tile backdrop
  uint16_t r = getRed(curTile->color);
  uint16_t g = getGreen(curTile->color);
  uint16_t b = getBlue(curTile->color);
  r += 64;
  g += 64;
  b += 64;
  if (r > 255) r = 255;
  if (g > 255) g = 255;
  if (b > 255) b = 255;
  uint16_t color2 = RGB(r, g, b);

  GFX.gradientRect(2, 2, 126, 126, 45, curTile->color, color2);    // small angle 
  
  // Step 3: Render graph
  Graph.renderGraph(25, 10, 100, 100);
    
  // Step 4: Label text
  GFX.drawJustifiedText(curTile->name, 1, 126, 126, &Ubuntu14, JUST_RIGHT, RGB(255, 255, 255) );
  
  // Step 4: Update Screen
  GFX.updateScreen();  

  /*
  switch (showGraph) {
    case GRAPH_HUMIDITY:
      doHumidityGraph();    
      break;
    case GRAPH_PRESSURE:
      doPressureGraph();    
      break;            
    case GRAPH_MAGXYZ:
      doMagGraphXYZL();
      break;
    case GRAPH_ACCELGYRO:
      doAccelGyroGraph();        
      break;
    case GRAPH_MIC:
      doMicGraph();
      break;
  }
  */
  
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
  Graph.setLabelMode(LABELMODE_MINMAX);
}

void doMagGraphXYZL() {
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
  Graph.setLabelMode(LABELMODE_MINMAX);
}

void doMicGraph() {  
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
  Graph.setLabelMode(LABELMODE_MINMAX);  
}

void doHumidityGraph() {
  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  Graph.renderGraph(10, 10, 100, 100);
  
  GFX.updateScreen();  
}

/*
 * Pressure 
 */ 
void initPressureGraph() {
  // Initialize pressure graph
  Graph.clearSeries();
  Graph.addSeries( &sbPressure, RGB(255, 255, 0) );
  Graph.setLabelMode(LABELMODE_MINMAX);  
}

void doPressureGraph() {
  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  Graph.renderGraph(10, 10, 100, 100);
  
  GFX.updateScreen();  
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
  Graph.setLabelMode(LABELMODE_MINMAX);  
}

void doAccelGyroGraph() {
  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));    
  Graph.renderGraph(10, 10, 100, 100);

  //Serial.println ("Updating...");
  GFX.updateScreen();  
}

/*
 * Radiation
 */ 
void initRadiationGraph() {
  Graph.clearSeries();
  Graph.addSeries( &sbRad, RGB(128, 255, 128) );
  Graph.setLabelMode(LABELMODE_MINMAX);  
}

void doRadiationGraph() {
  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  Graph.renderGraph(10, 10, 100, 100);
  
  GFX.updateScreen();  
}

/*
 * Spectrometer
 */ 
void initSpectrometerGraph() {
  Graph.clearSeries();
  Graph.addSeries( &sbSpectMeasurement, RGB(128, 128, 255) );
  Graph.setLabelMode(LABELMODE_MINMAX);  
}

void doSpectrometerGraph() {
  GFX.fillRect(0, 0, GFX.width, GFX.height, RGB(0, 0, 0));
  Graph.renderGraph(10, 10, 100, 100);
  
  GFX.updateScreen();  
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
void AS3935Irq() {
  AS3935IrqTriggered = 1;
}
