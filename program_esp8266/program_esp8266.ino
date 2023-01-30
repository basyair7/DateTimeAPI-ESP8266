#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>

// Konfigurasi WiFi
#ifndef STASSID
#define STASSID "YOUR-NAME-HOSTPOT"
#define STAPSK  "YOUR-PASSWORD"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

// reconnect wifi if hotspot disconnect
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

// buat link server api
const String DateTimeAPI = "https://datetime.basyair7.repl.co/";

// buat fungsi waktu, tanggal dan datetimes
String waktu = "";
String tanggal = "";
String datetimes = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // untuk kecepatan kirim dan terima serial data dalam 9600 bit per detik
  // Register Event Handler
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
  
  initWiFi();
  Serial.print(F("RSSI : "));
  Serial.println(WiFi.RSSI());
}

void loop() {
  // put your main code here, to run repeatedly:

  // jalankan (refresh setiap 5 detik)
  DateTime(5000);
  datetimes = String(tanggal) + "(" + String(waktu) +")";
  Serial.println(datetimes);

}
