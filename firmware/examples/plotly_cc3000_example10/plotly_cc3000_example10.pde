#include <Client.h>
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>

#include "PlotlyInterface.h"

// Sign up to plotly here: https://plot.ly
// View your API key and streamtokens here: https://plot.ly/settings
// View your tokens here: https://plot.ly/settings
Adafruit_CC3000 cc3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIV2);  
PlotlyInterface pi2 = PlotlyInterface(&cc3000);

void setup() {

//  streamATMTEMP.lastUpdateTime = 10;
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // Initialize the CC3000 Wifi and connect to the access point
  pi2.connectWifi();
  
  // Initialize stream plots
  // GRAPH_ATMSTREAM / GRAPHTOKENS_ATM[] = {STKN_ATMTEMP, STKN_HUMIDITY, STKN_PRESSURE}
  if (!pi2.initializeStreamingGraph(&graphAtmospheric)) {
    Serial.println("ERROR: Unable to initialize graph"); 
  }

  // GRAPH_MAGSTREAM / GRAPHTOKENS_MAG = {STKN_MAGX, STKN_MAGY, STKN_MAGZ, STKN_MAGLEN}
  if (!pi2.initializeStreamingGraph(&graphMagnetic)) {
    Serial.println("ERROR: Unable to initialize graph"); 
  }
  
  // GRAPH_RADSTREAM / GRAPHTOKENS_RAD[] = {STKN_RADCPM}
  if (!pi2.initializeStreamingGraph(&graphRad)) {
    Serial.println("ERROR: Unable to initialize graph"); 
  }   
  
  // GRAPH_MOTIONSTREAM / GRAPHTOKENS_MOTION[] = {STKN_ACCELX, STKN_ACCELY, STKN_ACCELZ, STKN_GYROX, STKN_GYROY, STKN_GYROZ}
  if (!pi2.initializeStreamingGraph(&graphMotion)) {
    Serial.println("ERROR: Unable to initialize graph"); 
  }   
  

  // GRAPH_SPECSTREAM / GRAPHTOKENS_SPEC[] = {STKN_SPEC}
  if (!pi2.initializeStreamingGraph(&graphSpectrometer)) {
    Serial.println("ERROR: Unable to initialize graph"); 
  } 

  // Open the plotly stream 
  pi2.openStream();

}


char sendBuffer[512];
char buffer[80];

// Safe Plot Stream -- if the transmit buffer is full, transmit the buffer, then retry
boolean safePlotStream(unsigned long x, float y, PLOTLYSTREAM* stream) {  
  if (!pi2.plotStream(x, y, stream)) {
    // plot() returned with failure, signifying a full buffer.  transmit buffer, and try again
    transmitPlotlyBuffer();
    return pi2.plotStream(x, y, stream);
  }
  return true;
}

// Transmit the Plotly graphing buffer to Plotly
void transmitPlotlyBuffer() {
//    Serial.println ("Transmitting buffer...");
    pi2.transmitBuffer();  
}


void loop() {
  
  Serial.println ("Sending plot...");
  
  /*
  // Example 1: Uncomment for transfering a static graph (also comment out the
  // InitializeStreamingGraph() and openStream() calls in setup()  
  
  uint16_t data[] = {1, 2, 3, 4, 5};
  pi2.plotStaticGraph("TestGraph", "ylabel", 5, data, "xlabel", 0.0f, 1.0f, false);
  
  Serial.println ("Done...");  
  while (1) {}
  */
  
  // Example 2: Multiple streaming plots
  float jitter = random(10) / 10.0f;
  long time = millis();
  
  Serial.print ("Sending data... (");
  Serial.print (time, DEC);
  Serial.println(")");

  // The first two streams are an example of a periodic timeout -- so the data is only sent at 
  // 10 second intervals
  // GRAPH_ATMSTREAM / GRAPHTOKENS_ATM: STKN_ATMTEMP, STKN_HUMIDITY, STKN_PRESSURE
  long start = millis();
  if (pi2.needsUpdateOrTimeout(time, &graphAtmospheric)) {
    safePlotStream(time, 24.0f + jitter, &streamATMTEMP);
    safePlotStream(time, 35.0f + jitter, &streamHUMIDITY);
    safePlotStream(time, 94.0f + jitter, &streamPRESSURE);  
    graphAtmospheric.lastUpdateTime = time;
  }

  // GRAPH_MAGSTREAM / GRAPHTOKENS_MAG = {STKN_MAGX, STKN_MAGY, STKN_MAGZ, STKN_MAGLEN}
  if (pi2.needsUpdateOrTimeout(time, &graphMagnetic)) {
    safePlotStream(time, 30.0f + jitter, &streamMAGX);
    safePlotStream(time, -5.0f + jitter, &streamMAGY);
    safePlotStream(time, 10.0f + jitter, &streamMAGZ);
    safePlotStream(time, 35.0f + jitter, &streamMAGLEN);  
    graphMagnetic.lastUpdateTime = time;    
  }
  
  // The second two streams update data everytime the loop is run
  // GRAPH_RADSTREAM / GRAPHTOKENS_RAD[] = {STKN_RADCPM}
  safePlotStream(time, 20.0f + jitter, &streamRADCPM);

  // Flush the buffer to Plotly  
  transmitPlotlyBuffer();
  
  // GRAPH_MOTIONSTREAM / GRAPHTOKENS_MOTION[] = {STKN_ACCELX, STKN_ACCELY, STKN_ACCELZ, STKN_GYROX, STKN_GYROY, STKN_GYROZ}
  safePlotStream(time, 1.0f + jitter, &streamACCELX);
  safePlotStream(time, 0.1f + jitter, &streamACCELY);
  safePlotStream(time, 0.02f + jitter, &streamACCELZ);
  safePlotStream(time, 0.01f + jitter, &streamGYROX);
  safePlotStream(time, 0.02f + jitter, &streamGYROY);
  safePlotStream(time, 0.03f + jitter, &streamGYROZ);
  
  // GRAPH_SPECSTREAM / GRAPHTOKENS_SPEC[] = {STKN_SPEC}
  safePlotStream(time, 1.0f + jitter, &streamSPEC);

  // Flush the buffer to Plotly
  transmitPlotlyBuffer();

  long end = millis();
  Serial.print ("Send time: "); Serial.println(end - start, DEC);

  delay(1000);
}
