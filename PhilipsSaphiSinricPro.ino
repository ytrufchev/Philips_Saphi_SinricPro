#include <ArduinoJson.h>

#include <WakeOnLan.h>
WiFiUDP UDP;

#include <WakeOnLan.h>
WakeOnLan WOL(UDP); // Pass WiFiUDP class

#include <ESP8266HTTPClient.h>

/*
 * Example for how to use SinricPro TV device:
 * - setup a TV device
 * - handle request using callbacks
 *
 * If you encounter any issues:
 * - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
 * - ensure all dependent libraries are installed
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
 * - open serial monitor and check whats happening
 * - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
 * - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
 */

#include <Arduino.h>
#ifdef ESP8266 
       #include <ESP8266WiFi.h>
#endif 
#ifdef ESP32   
       #include <WiFi.h>
#endif

#include "SinricPro.h"
#include "SinricProTV.h"

#define WIFI_SSID         ""    
#define WIFI_PASS         ""
#define APP_KEY           ""      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        ""   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define TV_ID             ""    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         115200              // Change baudrate to your need

bool tvPowerState;
unsigned int tvVolume;
unsigned int tvChannel;
bool tvMuted;

// channelNames used to convert channelNumber into channelName
// please put in your TV channel names
// channel numbers starts counting from 0!
// so "ZDF" is channel 2
const char* channelNames[] = {
  "A/V",
  "ard", 
  "ZDF", 
  "n. d. r.", 
  "kabel eins", 
  "VOX", 
  "Sat.1", 
  "ProSieben", 
  "rtl", 
  "RTL II", 
  "SUPER RTL", 
  "KiKA"
};

#define MAX_CHANNELS sizeof(channelNames) / sizeof(channelNames[0])  // just to determine how many channels are in channelNames array

// map channelNumbers used to convert channelName into channelNumber
// This map is initialized in "setupChannelNumbers()" function by using the "channelNames" array
std::map<String, unsigned int> channelNumbers;

void setupChannelNumbers() {
  for (unsigned int i=0; i < MAX_CHANNELS; i++) {
    channelNumbers[channelNames[i]] = i;
  }
}

// TV device callbacks

bool onAdjustVolume(const String &deviceId, int &volumeDelta, bool volumeDefault) {
  tvVolume += volumeDelta;  // calcualte new absolute volume
  Serial.printf("Volume changed about %i to %i\r\n", volumeDelta, tvVolume);
  volumeDelta = tvVolume; // return new absolute volume
  return true;
}

bool onChangeChannel(const String &deviceId, String &channel) {
  tvChannel = channelNumbers[channel]; // save new channelNumber in tvChannel variable
  Serial.printf("Change channel to \"%s\" (channel number %d)\r\n", channel.c_str(), tvChannel);
  return true;
}

bool onChangeChannelNumber(const String& deviceId, int channelNumber, String& channelName) {
  tvChannel = channelNumber; // update tvChannel to new channel number
  if (tvChannel < 0) tvChannel = 0;
  if (tvChannel > MAX_CHANNELS-1) tvChannel = MAX_CHANNELS-1;

  channelName = channelNames[tvChannel]; // return the channelName

  Serial.printf("Change to channel to %d (channel name \"%s\")\r\n", tvChannel, channelName.c_str());
  return true;
}

bool onMediaControl(const String &deviceId, String &control) {
  Serial.printf("MediaControl: %s\r\n", control.c_str());
  if (control == "Play") {
          HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\": \"PlayPause\"}");


     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }           // do whatever you want to do here
  if (control == "Pause") {
          HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\": \"Pause\"}");


     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }          // do whatever you want to do here
  if (control == "Stop") {
          HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\": \"Stop\"}");


     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }           // do whatever you want to do here
  if (control == "StartOver") {}      // do whatever you want to do here
  if (control == "Previous") {
          HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\": \"Previous\"}");


     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }       // do whatever you want to do here
  if (control == "Next") {
          HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\": \"Netxt\"}");


     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }           // do whatever you want to do here
  if (control == "Rewind") {
          HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\": \"Rewind\"}");


     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }         // do whatever you want to do here
  if (control == "FastForward") {
          HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\": \"FastForward\"}");


     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }    // do whatever you want to do here
  return true;
}

bool onMute(const String &deviceId, bool &mute) {
           HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\": \"Mute\"}");


     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
  Serial.printf("TV volume is %s\r\n", mute?"muted":"unmuted");
  tvMuted = mute; // set tvMuted state
  return true;
}

bool onPowerState(const String &deviceId, bool &state) {
               HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/system";
      http.begin(Link); 
      int httpResponseCode = http.GET();
      Serial.println(httpResponseCode);
      if (httpResponseCode == 200){
        HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\": \"Standby\"}");
      http.end();
bool state = false;   
}
else if (httpResponseCode != 200){
  WOL.setRepeat(3, 10); // Repeat the packet three times with 100ms delay between
  const char *MACAddress = "2C:D9:74:DF:D4:FE";
  WOL.sendMagicPacket(MACAddress, 7);
          HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"Standby\"}");
      http.end();
bool state = true;
}
      http.end();
  Serial.printf("TV turned %s\r\n", state?"on":"off");
  tvPowerState = state; // set powerState
  return true; 
}

bool onSelectInput(const String &deviceId, String &input) {
  if(input == "PLAYSTATION FOUR"){
            HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"Source\"}");
      http.end();
      for (int count = 0; count <= 8; count++){
         HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"CursorLeft\"}");
      http.end();
      }
      for (int count = 0; count <= 3; count++){
         HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"CursorRight\"}");
      http.end();
      }
               HTTPClient http1;
      
      String Link1 = "http://192.168.1.15:1925/6/input/key";
      http1.begin(Link1); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http1.addHeader("Content-Type", "application/json");
      int httpResponse = http1.POST("{\"key\" : \"Confirm\"}");
      http1.end();
      
  }
  if(input == "TV"){
                HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"Source\"}");
      http.end();

            for (int count = 0; count <= 8; count++){
         HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"CursorLeft\"}");
      http.end();
      delay(100);
      }
      delay(100);
      for (int count = 0; count <= 5; count++){
         HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"CursorRight\"}");
      http.end();
      }
      delay(100);
               HTTPClient http1;
      
      String Link1 = "http://192.168.1.15:1925/6/input/key";
      http1.begin(Link1); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http1.addHeader("Content-Type", "application/json");
      int httpResponse = http1.POST("{\"key\" : \"Confirm\"}");
      http1.end();

  }
  Serial.printf("Input changed to %s\r\n", input.c_str());
  return true;
}

bool onSetVolume(const String &deviceId, int &volume) {
//                  HTTPClient http;
//      
//      String Link = "http://192.168.1.15:1925/6/audio/volume";
//      http.begin(Link); 
//      int httpResponseCode = http.GET();
//      String payload = http.getString();
//      DynamicJsonDocument doc(2048);
//deserializeJson(doc, http.getString());

// Read values
//Serial.println(doc["current"].as<long>());
//http.end();
          HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/audio/volume";
      http.begin(Link); 
      String val = String(volume);
      String data = "{\"current\": " + val + "}";
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST(data);


     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
  Serial.printf("Volume set to:  %i\r\n", volume);
  tvVolume = volume; // update tvVolume
  return true;
}

bool onSkipChannels(const String &deviceId, const int channelCount, String &channelName) {
  tvChannel += channelCount; // calculate new channel number
  if (tvChannel < 0) tvChannel = 0;
  if (tvChannel > MAX_CHANNELS-1) tvChannel = MAX_CHANNELS-1;
  channelName = String(channelNames[tvChannel]); // return channel name

  Serial.printf("Skip channel: %i (number: %i / name: \"%s\")\r\n", channelCount, tvChannel, channelName.c_str());

  return true;
}

// setup function for WiFi connection
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  IPAddress localIP = WiFi.localIP();
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %d.%d.%d.%d\r\n", localIP[0], localIP[1], localIP[2], localIP[3]);
}

// setup function for SinricPro
void setupSinricPro() {
  // add device to SinricPro
  SinricProTV& myTV = SinricPro[TV_ID];

  // set callback functions to device
  myTV.onAdjustVolume(onAdjustVolume);
  myTV.onChangeChannel(onChangeChannel);
  myTV.onChangeChannelNumber(onChangeChannelNumber);
  myTV.onMediaControl(onMediaControl);
  myTV.onMute(onMute);
  myTV.onPowerState(onPowerState);
  myTV.onSelectInput(onSelectInput);
  myTV.onSetVolume(onSetVolume);
  myTV.onSkipChannels(onSkipChannels);

  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  Serial.printf("%d channels configured\r\n", MAX_CHANNELS);

  setupWiFi();
  setupSinricPro();
  setupChannelNumbers();
}

void loop() {
  SinricPro.handle();
  delay(2000);
                HTTPClient http;
      
      String Link = "http://192.168.1.15:1925/6/system";
      http.begin(Link); 
      int httpResponseCode = http.GET();
      Serial.println(httpResponseCode);
      if (httpResponseCode == 200){
       bool state = true;
bool setPowerState (bool state);
}
   if (httpResponseCode != 200){
      bool state = false;
bool setPowerState (bool state);
}
http.end();
}
