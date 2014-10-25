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
#define PLOTLY_STREAM_MAXPOINTS    200
#define PLOTLY_STREAM_FILEMODE     "overwrite"
#define PLOTLY_STREAM_TIMEOUT      10000  // in Milliseconds

// Plotly stream structure
typedef struct plotlyStream {
  const char* token;
  const char* name;
} PLOTLYSTREAM;

#define MAX_STREAMS_PER_GRAPH  6
typedef struct plotlyGraph {
  const char* name;  
  int numStreams;
  PLOTLYSTREAM* streams[MAX_STREAMS_PER_GRAPH];
  long lastUpdateTime;
} PLOTLYGRAPH;

// Plotly stream tokens
extern PLOTLYSTREAM streamATMTEMP;
extern PLOTLYSTREAM streamHUMIDITY;
extern PLOTLYSTREAM streamPRESSURE;
extern PLOTLYSTREAM streamMAGX;
extern PLOTLYSTREAM streamMAGY;
extern PLOTLYSTREAM streamMAGZ;
extern PLOTLYSTREAM streamMAGLEN;
extern PLOTLYSTREAM streamRADCPM;
extern PLOTLYSTREAM streamACCELX;
extern PLOTLYSTREAM streamACCELY;
extern PLOTLYSTREAM streamACCELZ;
extern PLOTLYSTREAM streamGYROX;
extern PLOTLYSTREAM streamGYROY;
extern PLOTLYSTREAM streamGYROZ;
extern PLOTLYSTREAM streamSPEC;
extern PLOTLYSTREAM streamTHERM;

// Plotly Graphs
extern PLOTLYGRAPH graphAtmospheric;
extern PLOTLYGRAPH graphMagnetic;
extern PLOTLYGRAPH graphRad;
extern PLOTLYGRAPH graphMotion;
extern PLOTLYGRAPH graphSpectrometer;


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
  
  int plotlyStatus;
  
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
  boolean plotStream(unsigned long x, float y, PLOTLYSTREAM* stream);
  void transmitBuffer();
    
  // Low-level communication 
  public: 
    bool initializeStreamingGraph(PLOTLYGRAPH* graph); 
    boolean needsUpdateOrTimeout(long time, PLOTLYGRAPH* graph);
    
    void openStream();
    void closeStream();
    void reconnectStream();


  private:

    int len_(int i);
    int len_(unsigned long i);
    int len_(char *i);
    int len_(const char *i);
  
    void print_(int d);
    void print_(unsigned long d);
    void print_(float d);
    void print_(char *d);
    void print_(const char *d);
    
  // Debug 
  void debugPrint();
};


#endif

