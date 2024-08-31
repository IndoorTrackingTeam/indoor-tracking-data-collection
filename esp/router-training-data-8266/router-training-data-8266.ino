#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

const char* ntpServer = "pool.ntp.org";
const long utcOffsetInSeconds = -3 * 3600;

const char* ssid = "PedroGuimaraes";
const char* password = "ronk1234";
const char* host = "run-api-dev-131050301176.us-east1.run.app";
const char* url = "/router/training-data/create";

String esp_id = "3019";
String room = "Room 1";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, utcOffsetInSeconds);

String formatNumber(int number) {
  if (number < 10) {
    return "0" + String(number);
  }
  return String(number);
}

String getFormattedDateTime() {
  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();

  time_t rawTime = (time_t)epochTime;
  struct tm* timeinfo;
  timeinfo = localtime(&rawTime);

  String formattedDateTime = formatNumber(timeinfo->tm_year + 1900) + "-" +
                             formatNumber(timeinfo->tm_mon + 1) + "-" +
                             formatNumber(timeinfo->tm_mday) + "T" +
                             formatNumber(timeinfo->tm_hour) + ":" +
                             formatNumber(timeinfo->tm_min) + ":" +
                             formatNumber(timeinfo->tm_sec) + ".000000";
  
  return formattedDateTime;
}

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("WiFi connected");  

  timeClient.begin();
  timeClient.setTimeOffset(utcOffsetInSeconds);
  timeClient.update();
}

void sendDataToAPI(String mac, String esp_id, int rssi, String date, String room) {
  delay(5000);

  WiFiClientSecure client;
  client.setInsecure();

  if (!client.connect(host, 443)) {
    Serial.println("Connection failed");
    return;
  }

  String payload = "{"
                   "\"mac\": \"" + mac + "\", "
                   "\"esp_id\": \"" + esp_id + "\", "
                   "\"rssi\": " + String(rssi) + ", "
                   "\"date\": \"" + date + "\", "
                   "\"room\": \"" + room + "\""
                   "}";

  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/json\r\n" + 
               "Content-Length: " + String(payload.length()) + "\r\n" +
               "Connection: close\r\n\r\n" +
               payload);

  Serial.println(client.readStringUntil('\n'));
  
  client.stop();
}

void loop() {
  timeClient.update();

  String formattedDateTime = getFormattedDateTime();
  String bssid;
  int rssi = 0;

  int networks = WiFi.scanNetworks();
  if (networks > 0) {
    bssid = WiFi.BSSIDstr(0);
    rssi = WiFi.RSSI(0);
  }

  sendDataToAPI(bssid, esp_id, rssi, formattedDateTime, room);
  delay(10000);
}
