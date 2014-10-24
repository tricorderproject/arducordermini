// PlotlyInterface.h

#if !defined(PLOTLY_INTERFACE_h) 
#define PLOTLY_INTERFACE_h

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Client.h>
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>



// CC3000 Arducorder Mini pinouts
#define ADAFRUIT_CC3000_IRQ   2  // MUST be an interrupt pin!
#define ADAFRUIT_CC3000_VBAT  70
#define ADAFRUIT_CC3000_CS    53

// CC3000 WiFi Authentication
#define WLAN_SSID       "NETGEAR69"
#define WLAN_PASS       "curlyocean4"
#define WLAN_SECURITY   WLAN_SEC_WPA2

// Plotly Variables
#define PLOTLY_USERNAME  "arducordermini"
#define PLOTLY_APIKEY    "meo5gmkf9h"
#define PLOTLY_TIMEZONE  "America/Montreal"
#define PLOTLY_STREAM_MAXPOINTS    1000
#define PLOTLY_STREAM_FILEMODE     "overwrite"      //"extend"


// Plotly stream structure
typedef struct plotlyStream {
  const char* streamToken;
  const char* name;
  int lastUpdateTime; 
} PLOTLYSTREAM;


// Plotly Stream Tokens
// GRAPH_ATMSTREAM / GRAPHTOKENS_ATM[] = {STKN_ATMTEMP, STKN_HUMIDITY, STKN_PRESSURE}
#define STKN_ATMTEMP     "od2ntylgww" 
#define STKN_HUMIDITY    "sqm4a13zam" 
#define STKN_PRESSURE    "e4ksyqpxco" 
const char* const GRAPHTOKENS_ATM[] = {STKN_ATMTEMP, STKN_HUMIDITY, STKN_PRESSURE};

// GRAPH_MAGSTREAM / GRAPHTOKENS_MAG = {STKN_MAGX, STKN_MAGY, STKN_MAGZ, STKN_MAGLEN}
#define STKN_MAGX        "az7j8to4gc" 
#define STKN_MAGY        "fltbm456ks" 
#define STKN_MAGZ        "3yxuxsvwfo" 
#define STKN_MAGLEN      "on8hylf9gp" 
const char* const GRAPHTOKENS_MAG[] = {STKN_MAGX, STKN_MAGY, STKN_MAGZ, STKN_MAGLEN};

// GRAPH_RADSTREAM / GRAPHTOKENS_RAD[] = {STKN_RADCPM}
#define STKN_RADCPM      "zqa6zrzyu4" 
const char* const GRAPHTOKENS_RAD[] = {STKN_RADCPM};

// GRAPH_MOTIONSTREAM / GRAPHTOKENS_MOTION[] = {STKN_ACCELX, STKN_ACCELY, STKN_ACCELZ, STKN_GYROX, STKN_GYROY, STKN_GYROZ}
#define STKN_ACCELX      "5snk03wu6b"
#define STKN_ACCELY      "lj2rzknk3k"
#define STKN_ACCELZ      "1fo3rccdy6"
#define STKN_GYROX       "c8fv9pnjpl"
#define STKN_GYROY       "o1k8qt6b33"
#define STKN_GYROZ       "rplqna6020"
const char* const GRAPHTOKENS_MOTION[] = {STKN_ACCELX, STKN_ACCELY, STKN_ACCELZ, STKN_GYROX, STKN_GYROY, STKN_GYROZ};

// GRAPH_SPECSTREAM / GRAPHTOKENS_SPEC[] = {STKN_SPEC}
#define STKN_SPEC        "f0dw3z6jnn"
const char* const GRAPHTOKENS_SPEC[] = {STKN_SPEC};

#define STKN_THERM       "bx8zl5zbk1"
const char* const GRAPHTOKENS_THERM[] = {STKN_THERM};

// Plotly streaming graph names
#define GRAPH_ATMSTREAM      "AtmosphericStreaming"
#define GRAPH_MAGSTREAM      "MagneticFieldsStreaming"
#define GRAPH_RADSTREAM      "RadiationStreaming"
#define GRAPH_MOTIONSTREAM   "MotionStreaming"
#define GRAPH_SPECSTREAM     "SpectrometerStreaming"

// Transmit buffer
#define PLOTLY_TRANSMITBUF_SIZE  512
#define PLOTLY_DATABUF_SIZE      80
#define PLOTLY_NUMBUF_SIZE       20


// Plotly status indicators
#define PLOTLY_UNINITIALIZED     0
#define PLOTLY_WIFI_CONNECTED    10
#define PLOTLY_STREAMING         20

class PlotlyInterface {
  // Variables  
  public:
  Adafruit_CC3000 *cc3000;
  Adafruit_CC3000_Client client;
  uint32_t ip;
  
  // Buffer
  char sendBuffer[PLOTLY_TRANSMITBUF_SIZE];
  char dataBuffer[PLOTLY_DATABUF_SIZE];
  char numBuffer[PLOTLY_NUMBUF_SIZE];
  
  // Flags
  bool dryRun;
  bool worldReadable;
  int logLevel;
  int16_t stat;  
  boolean isConnected;  

  // Constructor/Destructor
  PlotlyInterface(Adafruit_CC3000 *cc3000Ptr);
  ~PlotlyInterface();
  
  // Setup methods
  void connectWifi();
  
  // Data methods
//  void plot(unsigned long x, int y, char *token);
  boolean plot(unsigned long x, float y, char *token);
  
  boolean bufferedPlot(unsigned long x, float y, char *token);
  void transmitBuffer();
    
  // Low-level communication 
  public: 
    bool initializeStreamingGraph(char* plotlyFilename, int nTraces, const char* const streamTokens[]); 
    
    void openStream();
    void closeStream();
    void reconnectStream();

  private:

    int len_(int i);
    int len_(unsigned long i);
    int len_(char *i);

    void print_(int d);
    void print_(unsigned long d);
    void print_(float d);
    void print_(char *d);
    void print_(const char *d);
    
  // Debug 
  void debugPrint();
};


#endif

