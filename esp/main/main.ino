#include <ESP8266WiFi.h>

String nome = "Node1";
const char* ssid = "PedroGuimaraes";
const char* password = "ronk1234";

void setup_wifi() {

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  WiFi.mode(WIFI_STA);
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
    String retorno = "ESP Name: " + nome + "\n Name: " + SSID + "\n MAC: " + BSSID + "\n RSSI: " + RSSI;

    Serial.print(retorno);
    delay(500);
  }

  delay(100);
}
