// PlotlyInterface.cpp
// Heavy adapted from the Plotly Arduino interface example: https://github.com/plotly/arduino-api
// 
// Note: This library requires that the larger ("maximal") CC3000 transmit buffer is enabled in the Adafruit CC3000 library:
// cc3000_common.h: approximatly line 170:
//  #define CC3000_RX_BUFFER_SIZE   (CC3000_MAXIMAL_RX_SIZE)
//  #define CC3000_TX_BUFFER_SIZE   (CC3000_MAXIMAL_TX_SIZE)

#include "PlotlyInterface.h"

PlotlyInterface::PlotlyInterface(Adafruit_CC3000 *cc3000Ptr) {
  // Logging level
  logLevel = 2;  // 0 = Debugging, 1 = Informational, 2 = Status, 3 = Errors, 4 = Quiet (// Serial Off)
  dryRun = false;
  worldReadable = true;
  
  // The user may pass in a CC3000 pointer, or specify a null pointer for this interface to create a CC3000 object
  if (cc3000Ptr == NULL) {
    cc3000 = new Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIV2, &Serial);  
  } else {
    cc3000 = cc3000Ptr;
  }

  // IP Address of plotly stream server
  uint32_t ip = cc3000->IP2U32(107,21,214,199);

  // Initialize buffers
  sendBuffer[0] = '\0';
  dataBuffer[0] = '\0';
  numBuffer[0] = '\0';

}

// Destructor
PlotlyInterface::~PlotlyInterface() {
}

// Setup methods
void PlotlyInterface::connectWifi() {
  // Initialize CC3000 Module
  Serial.println("Initializing CC3000...");
  if (!cc3000->begin()) {
    Serial.println("ERROR: CC3000.begin() failed...");
    while(1);
  }

  // Optional SSID scan
  // listSSIDResults();

  Serial.println ("Connecting to Access Point...");
  if (!cc3000->connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println("Connection Failed!");
    while(1);
  }

  // Request DHCP address
  Serial.println("CC3000: Requesting DHCP Address...");
  while (!cc3000->checkDHCP()) {
    delay(100); // ToDo: Insert a DHCP timeout!
  }

  Serial.println("CC3000: Connected!");

}

// Buffered plot -- this is much faster than sending plot points one at a time
boolean PlotlyInterface::plot(unsigned long x, float y, char *token) {  
  // First, create the JSON string defining the data
  dataBuffer[0] = '\0';
  strcat(dataBuffer, "{\"x\": ");        // X value
  sprintf(numBuffer, "%d", x);        
  strcat(dataBuffer, numBuffer);
  strcat(dataBuffer, ", \"y\": ");       // Y value
  sprintf(numBuffer, "%.3f", y);        
  strcat(dataBuffer, numBuffer);
  strcat(dataBuffer, ", \"streamtoken\": \"");    // Stream token
  strcat(dataBuffer, token);
  strcat(dataBuffer, "\"}");
  
  // Add the JSON string to the larger transmit buffer
  int length = strlen(dataBuffer);
  if (length + strlen(sendBuffer) > (PLOTLY_TRANSMITBUF_SIZE - 10)) {    // 10 for a little wiggle room
  
    return false;
  }
  sprintf(numBuffer, "%X", length+1);    // length in *HEX*
  strcat(sendBuffer, numBuffer);
  strcat(sendBuffer, "\r\n"); 
  strcat(sendBuffer, dataBuffer);
  strcat(sendBuffer, "\n\r\n");  
  
/*  
  Serial.print ("Buffer: ");
  Serial.println (sendBuffer);
  Serial.println ("End of buffer. ");
*/

  return true;
}


// Send plot buffer to Plotly server
void PlotlyInterface::transmitBuffer() {
  reconnectStream();
  Serial.println ("Sending Buffer:");
  print_(sendBuffer);
  
  // Clear buffer
  Serial.println ("Clearing buffer");  
  sendBuffer[0] = '\0';
  
}


// Low-level communication
bool PlotlyInterface::initializeStreamingGraph(char* plotlyFilename, int nTraces, const char* const streamTokens[]) {  
    //
    //  Validate a stream with a REST post to plotly
    //
    if(dryRun && logLevel < 3){
        Serial.println(F("... This is a dry run, we are not connecting to plotly's servers..."));
    }
    else if(logLevel < 3) {
        Serial.println(F("... Attempting to connect to plotly's REST servers"));
    }
    uint32_t ip = cc3000->IP2U32(107,21,214,199);
    // Try looking up the website's IP address
    client = cc3000->connectTCP(ip, 80);
    while ( !client.connected() ) {
        if(logLevel < 4){
            Serial.println(F("... Couldn\'t connect to plotly's REST servers... trying again!"));
        }
        delay(5000);
        client = cc3000->connectTCP(ip, 80);
    }

    if(logLevel < 3){} Serial.println(F("... Connected to plotly's REST servers"));
    if(logLevel < 3){} Serial.println(F("... Sending HTTP Post to plotly"));
    print_(F("POST /clientresp HTTP/1.1\r\n"));
    print_(F("Host: 107.21.214.199\r\n"));
    print_(F("User-Agent: Arduino/0.5.1\r\n"));
    print_(F("Content-Length: "));
    int contentLength = 126 + len_(PLOTLY_USERNAME) + len_(PLOTLY_STREAM_FILEMODE) + nTraces*(87+len_(PLOTLY_STREAM_MAXPOINTS)) + (nTraces-1)*2 + len_(plotlyFilename);
    if(worldReadable){
        contentLength += 4;
    } else {
        contentLength += 5;
    }
    print_(contentLength);
    // contentLength =
    //   44  // first part of querystring below
    // + len_(username)  // upper bound on username length
    // + 5   // &key=
    // + 10  // api_key length
    // + 7  // &args=[...
    // + nTraces*(87+len(maxpoints)) // len({\"y\": [], \"x\": [], \"type\": \"scatter\", \"stream\": {\"token\": \") + 10 + len(\", "maxpoints": )+len(maxpoints)+len(}})
    // + (nTraces-1)*2 // ", " in between trace objects
    // + 22  // ]&kwargs={\"fileopt\": \"
    // + len_(fileopt)
    // + 16  // \", \"filename\": \"
    // + len_(filename)
    // + 21 // ", "worldReadable":
    // + 4 if worldReadable, 5 otherwise
    // + 1   // closing }
    //------
    // 126 + len_(username) + len_(fileopt) + nTraces*(86+len(maxpoints)) + (nTraces-1)*2 + len_(filename)
    //
    // Terminate headers with new lines
    print_(F("\r\n\r\n"));

    // Start printing querystring body
    print_(F("version=2.3&origin=plot&platform=arduino&un="));
    print_(PLOTLY_USERNAME);
    print_(F("&key="));
    print_(PLOTLY_APIKEY);
    print_(F("&args=["));
    // print a trace for each token supplied
    for(int i=0; i<nTraces; i++){
        print_(F("{\"y\": [], \"x\": [], \"type\": \"scatter\", "));
        
        print_(F("\"stream\": {\"token\": \""));
        print_(streamTokens[i]);
        print_(F("\", \"maxpoints\": "));
        print_(PLOTLY_STREAM_MAXPOINTS);
        print_(F("}}"));
        if(nTraces > 1 && i != nTraces-1){
            print_(F(", "));
        }
    }
    print_(F("]&kwargs={\"fileopt\": \""));
    print_(PLOTLY_STREAM_FILEMODE);
    print_(F("\", \"filename\": \""));
    print_(plotlyFilename);
    print_(F("\", \"worldReadable\": "));
    if(worldReadable){
        print_("true");
    } else{
        print_("false");
    }
    print_(F("}"));
    // final newline to terminate the POST
    print_(F("\r\n"));

    //
    // Wait for a response
    // Parse the response for the "All Streams Go!" and proceed to streaming
    // if we find it
    //
    char allStreamsGo[] = "All Streams Go!";
    char error[] = "\"error\": \"";
    int asgCnt = 0; // asg stands for All Streams Go
    char url[] = "\"url\": \"http://107.21.214.199/~";
    char fid[4];
    int fidCnt = 0;
    int urlCnt = 0;
    int usernameCnt = 0;
    int urlLower = 0;
    int urlUpper = 0;
    bool proceed = false;
    bool fidMatched = false;

    if(logLevel < 2){
        Serial.println(F("... Sent message, waiting for plotly's response..."));
    }

    if(!dryRun){
        while(client.connected()){
            if(client.available()){
                char c = client.read();
                if(logLevel < 2) Serial.print(c);

                //
                // Attempt to read the "All streams go" msg if it exists
                // by comparing characters as they roll in
                //

                if(asgCnt == len_(allStreamsGo) && !proceed){
                    proceed = true;
                }
                else if(allStreamsGo[asgCnt]==c){
                    asgCnt += 1;
                } else if(asgCnt > 0){
                    // reset counter
                    asgCnt = 0;
                }

                //
                // Extract the last bit of the URL from the response
                // The url is in the form http://107.21.214.199/~USERNAME/FID
                // We'll character-count up through char url[] and through username_, then start
                // filling in characters into fid
                //

                if(logLevel < 3){
                    if(url[urlCnt]==c && urlCnt < len_(url)){
                        urlCnt += 1;
                    } else if(urlCnt > 0 && urlCnt < len_(url)){
                        // Reset counter
                        urlCnt = 0;
                    }
                    if(urlCnt == len_(url) && fidCnt < 4 && !fidMatched){
                        // We've counted through the url, start counting through the username
                        if(usernameCnt < len_(PLOTLY_USERNAME)+2){
                            usernameCnt += 1;
                        } else {
                            // the url ends with "
                            if(c != '"'){
                                fid[fidCnt] = c;
                                fidCnt += 1;
                            } else if(fidCnt>0){
                                fidMatched = true;
                            }

                        }
                    }
                }
            }
        }
        client.close();
    }

    if(!dryRun && !proceed && logLevel < 4){
        Serial.println(F("... Error initializing stream, aborting. Try again or get in touch with Chris at chris@plot.ly"));
    }

    if(!dryRun && proceed && logLevel < 3){
        Serial.println(F("... A-ok from plotly, All Streams Go!"));
        if(fidMatched){
            Serial.print(F("... View your streaming plot here: https://plot.ly/~"));
            Serial.print(PLOTLY_USERNAME);
            Serial.print(F("/"));
            for(int i=0; i<fidCnt; i++){
                Serial.print(fid[i]);
            }
            Serial.println(F(""));
        }
    }
    return proceed;  
}

void PlotlyInterface::openStream() {
  //
  // Start request to stream servers
  //
  if(logLevel < 3){
  } 
  Serial.println(F("... Connecting to plotly's streaming servers..."));

  /*
    #define STREAM_SERVER "arduino.plot.ly"
   uint32_t stream_ip = 0;
   // Try looking up the website's IP address
   while (stream_ip == 0) {
   if (! cc3000->getHostByName(STREAM_SERVER, &stream_ip)) {
   if(logLevel < 4){} Serial.println(F("Couldn't resolve!"));
   }
   }
   */
  uint32_t stream_ip = cc3000->IP2U32(107, 21, 214, 199);

  client = cc3000->connectTCP(stream_ip, 80);
  while ( !client.connected() ) {
    if(logLevel < 4){
    } 
    Serial.println(F("... Couldn\'t connect to servers... trying again!"));
    delay(5000);    // 5 second timeout
    client = cc3000->connectTCP(stream_ip, 80);
  }
  if(logLevel < 3){
  } 
  Serial.println(F("... Connected to plotly's streaming servers\n... Initializing stream"));

  print_(F("POST / HTTP/1.1\r\n"));
  print_(F("Host: arduino.plot.ly\r\n"));
  print_(F("User-Agent: Python\r\n"));
  print_(F("Transfer-Encoding: chunked\r\n"));
  print_(F("Connection: close\r\n"));

  // Convert timestamp
  print_(F("plotly-convertTimestamp: \""));
  print_(PLOTLY_TIMEZONE);
  print_(F("\"\r\n"));

  print_(F("\r\n"));

  if(logLevel < 3){
  } 
  Serial.println(F("... Done initializing, ready to stream!"));
}

void PlotlyInterface::closeStream(){
  print_(F("0\r\n\r\n"));
  client.close();
}

void PlotlyInterface::reconnectStream(){
  while(!client.connected()){
    if(logLevel<4) Serial.println(F("... Disconnected from streaming servers"));
    closeStream();
    openStream();
  }
}

int PlotlyInterface::len_(int i){
  // int range: -32,768 to 32,767
  if(i > 9999) return 5;
  else if(i > 999) return 4;
  else if(i > 99) return 3;
  else if(i > 9) return 2;
  else if(i > -1) return 1;
  else if(i > -10) return 2;
  else if(i > -100) return 3;
  else if(i > -1000) return 4;
  else if(i > -10000) return 5;
  else return 6;
}
int PlotlyInterface::len_(unsigned long i){
  // max length of unsigned long: 4294967295
  if(i > 999999999) return 10;
  else if(i > 99999999) return 9;
  else if(i > 9999999) return 8;
  else if(i > 999999) return 7;
  else if(i > 99999) return 6;
  else if(i > 9999) return 5;
  else if(i > 999) return 4;
  else if(i > 99) return 3;
  else if(i > 9) return 2;
  else return 1;
}
int PlotlyInterface::len_(char *i){
  return strlen(i);
}

void PlotlyInterface::print_(int d){
  if(logLevel < 2) Serial.print(d);
  client.print(d);
}
void PlotlyInterface::print_(unsigned long d){
  if(logLevel < 2) Serial.print(d);
  client.print(d);
}
void PlotlyInterface::print_(float d){
  if(logLevel < 2) Serial.print(d);
  client.print(d);
}
void PlotlyInterface::print_(char *d){
  if(logLevel < 2) Serial.print(d);
  client.fastrprint(d);
}

void PlotlyInterface::print_(const char *d){
  if(logLevel < 2) Serial.print(d);
  client.fastrprint(d);
}


