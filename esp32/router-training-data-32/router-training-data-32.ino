#include <WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "PedroGuimaraes";
const char* password = "ronk1234";
const char* host = "run-api-dev-131050301176.us-east1.run.app";
const char* url = "/router/training-data/create";

String esp_id = "325470";
String room = "Room 1";

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("WiFi connected");
}

void sendDataToAPI(String esp_id, String room, int networks) {

  WiFiClientSecure client;
  client.setInsecure();

  if (!client.connect(host, 443)) {
    Serial.println("Connection failed");
    return;
  }

  String payload = "{";
  payload += "\"room\": \"" + room + "\",";
  payload += "\"networks\": [";

  for (int i = 0; i < networks; ++i) {
    String mac = WiFi.BSSIDstr(i);
    String ssid = WiFi.SSID(i);
    int rssi = WiFi.RSSI(i);  

    payload += "{\"mac\": \"" + mac + "\", \"name_router\": \"" + ssid + "\", \"esp_id\": \"" + esp_id + "\", \"rssi\": " + String(rssi) + "}";

    if (i < networks - 1) {
      payload += ",";
    }
  }

  payload += "]}";

  client.print(String("POST ") + url + " HTTP/1.1\r\n" + 
               "Host: " + host + "\r\n" + 
               "Content-Type: application/json\r\n" + 
               "Content-Length: " + String(payload.length()) + "\r\n" + 
               "Connection: close\r\n\r\n" + 
               payload);

  Serial.println(client.readStringUntil('\n'));

  client.stop();

  delay(5000);
}


void loop() {
  String ssid;
  String bssid;
  int rssi = 0;

  int networks = WiFi.scanNetworks();
  if (networks > 0) {
    sendDataToAPI(esp_id, room, networks);
  }

  delay(5000);
}
