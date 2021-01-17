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


String TV_IP =            "192.168.1.15"; //IP address of your TV
String TV_PORT =          "1925"; //Port for the TV API
String API_V =            "6"; // API version of the TV
#define WIFI_SSID         "Mihaela89"    
#define WIFI_PASS         "bjjjbjjj"
#define APP_KEY           "f334caaa-d38f-4a4b-b273-d9a29f00632e"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "a41c5a7f-f782-438a-87e8-eb5069f0051c-294b2e36-4338-4e0f-8d48-9830b0b39836"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define TV_ID             "5fdc5dd52418ce762ce533ea"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         115200              // Change baudrate to your need

bool tvPowerState;
unsigned int tvVolume;
unsigned int tvChannel;
bool tvMuted;

bool onAdjustVolume(const String &deviceId, int &volumeDelta, bool volumeDefault) {
  tvVolume += volumeDelta;  // calcualte new absolute volume
  Serial.printf("Volume changed about %i to %i\r\n", volumeDelta, tvVolume);
  volumeDelta = tvVolume; // return new absolute volume
  return true;
}

bool onMediaControl(const String &deviceId, String &control) {
  Serial.printf("MediaControl: %s\r\n", control.c_str());
  if (control == "Play") {
          HTTPClient http;
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/system";
      http.begin(Link); 
      int httpResponseCode = http.GET();
      Serial.println(httpResponseCode);
      if (httpResponseCode == 200){
        HTTPClient http;
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
  if(input == "HDMI ONE"){
                HTTPClient http;
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"Source\"}");
      http.end();

            for (int count = 0; count <= 8; count++){
         HTTPClient http;
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"CursorLeft\"}");
      http.end();
      delay(100);
      }
      delay(100);
      for (int count = 0; count <= 3; count++){
         HTTPClient http;
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"CursorRight\"}");
      http.end();
      }
      delay(100);
               HTTPClient http1;
      
      String Link1 = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
      http1.begin(Link1); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http1.addHeader("Content-Type", "application/json");
      int httpResponse = http1.POST("{\"key\" : \"Confirm\"}");
      http1.end();

  }
  if(input == "PLAYSTATION FOUR"){
            HTTPClient http;
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"Source\"}");
      http.end();
      for (int count = 0; count <= 8; count++){
         HTTPClient http;
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"CursorLeft\"}");
      http.end();
      delay(100);
      }
      for (int count = 0; count <= 4; count++){
         HTTPClient http;
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"CursorRight\"}");
      http.end();
      delay(100);
      }
               HTTPClient http1;
      
      String Link1 = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
      http1.begin(Link1); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http1.addHeader("Content-Type", "application/json");
      int httpResponse = http1.POST("{\"key\" : \"Confirm\"}");
      http1.end();
      
  }
  if(input == "TV"){
                HTTPClient http;
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"Source\"}");
      http.end();

            for (int count = 0; count <= 8; count++){
         HTTPClient http;
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
      http.begin(Link); 
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"key\" : \"CursorRight\"}");
      http.end();
      }
      delay(100);
               HTTPClient http1;
      
      String Link1 = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/input/key";
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
          HTTPClient http;
      
      String Link = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/audio/volume";
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
  myTV.onMediaControl(onMediaControl);
  myTV.onMute(onMute);
  myTV.onPowerState(onPowerState);
  myTV.onSelectInput(onSelectInput);
  myTV.onSetVolume(onSetVolume);

  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");

  setupWiFi();
  setupSinricPro();
}

int powerState;

void loop() {
  SinricPro.handle();
  delay(2000);

                HTTPClient http1;
      
      String Link1 = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/system";
      http1.begin(Link1); 
      int httpResponseCode1 = http1.GET();
      Serial.println(httpResponseCode1);

      if (httpResponseCode1 == 200 && powerState != 200){
             SinricProTV& myTV = SinricPro[TV_ID];
myTV.sendPowerStateEvent(true);   

}
   if (httpResponseCode1 != 200 && powerState == 200){
         SinricProTV& myTV = SinricPro[TV_ID];
myTV.sendPowerStateEvent(false);   
}
http1.end();
powerState = httpResponseCode1;
HTTPClient http2;
      
      String Link2 = "http://"+ TV_IP +":"+TV_PORT+"/"+API_V+"/audio/volume";
      http2.begin(Link2); 
      int httpResponseCode2 = http2.GET();
      String responseData = http2.getString();
       const char* json = responseData.c_str();
        DynamicJsonDocument doc(2048);
        deserializeJson(doc, json);
         int current = doc["current"];
         bool muted = doc["muted"];
      http2.end();
                  if (tvVolume != current){
         SinricProTV& myTV = SinricPro[TV_ID];
bool success = myTV.sendVolumeEvent(current); 
tvVolume = current;
}
            if (muted != tvMuted){
               SinricProTV& myTV = SinricPro[TV_ID];
bool success = myTV.sendMuteEvent(muted);  
tvMuted = muted;
}
}
