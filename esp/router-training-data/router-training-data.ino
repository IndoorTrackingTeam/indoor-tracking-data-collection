#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

String nome = "Node1";
const char* ssid = "PedroGuimaraes";
const char* password = "ronk1234";
WiFiClient wifiClient;

void setup_wifi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callAPI() 
{
  if (WiFi.status() == WL_CONNECTED) 
  {
    Serial.println("Connected to the WiFi network");
    HTTPClient http;
    http.begin(wifiClient, "https://run-api-dev-131050301176.us-east1.run.app/users/read-all");
    
    Serial.println("Attempting to connect to API...");
    int httpCode = http.GET();
    
    Serial.println("HTTP CODE: " + String(httpCode));
    if (httpCode == HTTP_CODE_MOVED_PERMANENTLY || httpCode == HTTP_CODE_FOUND) 
    {
      // HTTP 301 or 302 Redirection
      String newLocation = http.header("Location");
      Serial.println("Redirected to: " + newLocation);
      
      http.end();  // End the first request
      
      // Start a new request to the new URL
      http.begin(wifiClient, newLocation);
      httpCode = http.GET();
      
      if (httpCode > 0) 
      {
        String payload = http.getString();
        Serial.println("New HTTP CODE: " + String(httpCode));
        Serial.println(payload);
      } else 
      {
        Serial.println("Error on redirected request");
      }
    } 
    else if (httpCode > 0) 
    {
      String payload = http.getString();
      Serial.println(payload);
    } 
    else 
    {
      Serial.println("Error on HTTP request");
    }
    http.end();
  }
  else 
  {
    Serial.println("Error in WiFi connection");
  }
  delay(600);
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
}

void loop() {
  int networks = WiFi.scanNetworks();

  for (int i = 0; i < networks; i++) {
    String SSID = WiFi.SSID(i);
    String BSSID = WiFi.BSSIDstr(i);
    String RSSI = String(WiFi.RSSI(i));    
    delay(500);
  }

  callAPI();
  delay(100);
}
