#include <Arduino.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncHTTPUpdateServer.h>
#include <SPIFFS.h>
#include <Wire.h>
#ifdef VDISP
#include <vdisp.h>
#endif
#ifdef EDISP
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#endif

#define BYPASS_PIN 0
#define RESET_PIN 15
#define PWR_PIN 14
#define AUTO_PIN 4

#define I2C_FREQ 200000
#define SDA_1 21
#define SCL_1 22
#define SDA_2 33
#define SCL_2 32

bool on = false;

#ifdef VDISP
bool dirty = false;
unsigned long cleanTime = 0;
bool published = true;

char ddram[LCD_LENGTH];
bool ramIndex = DDRAM;
uint8_t currentAddress = 0;
bool entryModeIncrement = true;
bool entryModeShift = false;
bool nibbleIndex = 0;
uint8_t loNibble = 0;
uint8_t hiNibble = 0;
#endif

#ifdef EDISP
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, -1);
#endif

StaticJsonDocument<1024> doc;

AsyncWebServer server(80);
ESPAsyncHTTPUpdateServer updateServer;

void addBool(JsonDocument *doc, String name, bool value) {
  if (value) {
    (*doc)[name].set("true");
  } else {
    (*doc)[name].set("false");
  }
}

void addString(JsonDocument *doc, String name,String value) {
    (*doc)[name].set(value);
}

void getStatus(AsyncWebServerRequest *request) {
  char buffer[1024];
  addBool(&doc,"power",on);
  serializeJson(doc, buffer);
  
  request->send(200, "application/json", buffer);
}

void setupApi() {
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  server.serveStatic("/s/", SPIFFS, "/");
  server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest *request){
    getStatus(request);
  });
  server.on("/api/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(RESET_PIN, HIGH);
    delay(250);
    digitalWrite(RESET_PIN, LOW);
    getStatus(request);
  });
  server.on("/api/tune", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(RESET_PIN, HIGH);
    delay(500);
    digitalWrite(RESET_PIN, LOW);
    getStatus(request);
  });
  server.on("/api/bypass", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(BYPASS_PIN, HIGH);
    delay(500);

    digitalWrite(BYPASS_PIN, LOW);
    getStatus(request);
  });
  server.on("/api/auto", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(AUTO_PIN, HIGH);
    delay(500);
    digitalWrite(AUTO_PIN, LOW);
    getStatus(request);
  });
  server.on("/api/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(PWR_PIN, HIGH);
    on=true;
    #ifdef VDISP
    delay(500);
    Wire.begin(LCD_ADDRESS);
    Wire.onReceive(onReceive);
    addBool(&doc,"info",true);
    for (int i = 0; i < LCD_LENGTH; i+=1) {
      ddram[i] = 0x20;
    }
    #endif
    getStatus(request);
  });
  server.on("/api/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(PWR_PIN, LOW);
    on=false;
    getStatus(request);
  });
  updateServer.setup(&server);
  updateServer.setup(&server,OTA_USER,OTA_PASSWORD);
  server.begin();
}

void setup() {
    // put your setup code here, to run once:

    Serial.begin(115200);
    // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
    delay(1500);
    
    Serial.println("setup start");

#ifdef EDISP
    Serial.println("initializing wire2 and oled");
    Wire1.begin(SDA_2, SCL_2, I2C_FREQ);

    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println(F("failed to start SSD1306 OLED"));
      delay(2000);
      ESP.restart();
    }

    oled.clearDisplay(); // clear display
    oled.setTextSize(1);         // set text size
    oled.setTextColor(WHITE);    // set text color
    oled.setCursor(2, 5);       // set position to display
    oled.println("SA0LEF ATU100 CTL"); // set text
    oled.display();   
#endif
    Serial.println("wifi setup");
#ifdef EDISP
    oled.setCursor(2,20);
    oled.print("wifi: ");
    oled.display();
#endif
    //WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;
    WiFi.mode(WIFI_STA);

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result
    bool res;      
    //wm.setDebugOutput(true);
    res = wm.autoConnect();

    if(!res) {
        Serial.println("Failed to connect");
#ifdef EDISP
        oled.println(" FAIL!");
        oled.display();
#endif
        delay(2000);
        //ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
#ifdef EDISP
        oled.println("connected");
        oled.display();
#endif
        Serial.println("Connected...yeey :)");
    }

    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    gpio_pad_select_gpio(RESET_PIN);
    pinMode(RESET_PIN,OUTPUT);
    gpio_pad_select_gpio(PWR_PIN);
    pinMode(PWR_PIN,OUTPUT);
    gpio_pad_select_gpio(AUTO_PIN);
    pinMode(AUTO_PIN,OUTPUT);
    gpio_pad_select_gpio(BYPASS_PIN);
    pinMode(BYPASS_PIN,OUTPUT);
#ifdef EDISP
    oled.setCursor(2,30);
    oled.print("api: ");
    oled.display();
#endif
    setupApi();
    doc.clear();
    addBool(&doc,"info",false);
#ifdef EDISP
    oled.println("done");
    oled.display();
#endif
}

unsigned const int interval = 30*1000;
unsigned long last = 0;
void loop() {
    unsigned long cur = millis();
    // if WiFi is down, try reconnecting
    if ((WiFi.status() != WL_CONNECTED) && (cur - last >= interval)) {
        Serial.print(millis());
        Serial.println("Reconnecting to WiFi...");
        WiFi.disconnect();
        WiFi.reconnect();
        last = cur;
    }

#ifdef VDISP
    if (dirty) {
        dirty = false;
        published = false;
        cleanTime = millis();
    } else if ((millis() - cleanTime > PUBLISH_THRESHOLD) && !published) {
        
        String displayContent = ddram;
        if (displayContent.substring(0, 4) != "PWR=") {
            Serial.printf("wrong line format (%s)\n",displayContent);
        } else {
            String pwrIn = displayContent.substring(4, 7);
            pwrIn.trim();
            bool autoMode = (displayContent.charAt(8) == '.');
            bool txing = (displayContent.charAt(11) == '=') || ((displayContent.charAt(76) == '='));
            bool tuning = displayContent.substring(68, 72) == "TUNE";
            bool resetting = displayContent.substring(64, 69) == "RESET";

            String swr = "";
            if (displayContent.substring(64, 68) == "SWR=" && !tuning) {
                swr = displayContent.substring(68, 72);
            }
            String pwrOut = "";
            String efficiency = "";
            bool lcNetwork = false;
            String inductance = "";
            String capacitance = "";
            if (txing) {
                pwrOut = displayContent.substring(12, 15);
                efficiency = displayContent.substring(77, 79);
            } else if (displayContent.charAt(9) == 'L') {
                lcNetwork = true;
                inductance = displayContent.substring(11, 15);
                capacitance = displayContent.substring(75, 79);
                capacitance.trim();
            } else {
                lcNetwork = true;
                inductance = displayContent.substring(75, 79);
                capacitance = displayContent.substring(11, 15);
                capacitance.trim();
            }
            doc.clear();
            addBool(&doc,"tuning", tuning);
            addBool(&doc,"resetting", resetting);
            addBool(&doc,"auto_mode",autoMode);
            addString(&doc,"pwr_in",pwrIn);
            if (txing) {
                addBool(&doc,"txing",true);
                addString(&doc,"pwr_out",pwrOut);
                addString(&doc,"efficiency",efficiency);
            } else {
                addBool(&doc,"txing",false);
                addString(&doc,"pwr_out","0");
                addString(&doc,"efficiency","0");
            }
            if (swr != "") {
                addString(&doc,"swr",swr);
            } else {
                addString(&doc,"swr","0");
            }
            if (inductance != "" && capacitance != "") {
                addString(&doc,"inductance",inductance);
                addString(&doc,"capacitance",capacitance);
            }
            published = true;
        }
    }
#endif
    delay(1);
}                          
