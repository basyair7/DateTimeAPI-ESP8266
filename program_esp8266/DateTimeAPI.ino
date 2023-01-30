// buat variable millis pengganti delay
unsigned long lastTime = 0;

void DateTime(long pending) {
  unsigned long currentTime = millis();
  if((unsigned)(currentTime - lastTime) >= pending){
    lastTime = currentTime;
    if (WiFi.status() == WL_CONNECTED) {
      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

      // Ignore SSL certificate validation
      client->setInsecure();

      // Create an HTTPClient instance
      HTTPClient https;

      // Initializing an HTTPS communication using the secure client
      if (https.begin(*client, DateTimeAPI)) { // HTTPS
        int httpsCode = https.GET();
        // httpCode will be negative on error
        if (httpsCode > 0) {
          // HTTP header has been send and Server response header has been handled
          // file found at server
          if (httpsCode == HTTP_CODE_OK || httpsCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String val = https.getString();
            DynamicJsonBuffer jsonBuffer;
            JsonObject& data = jsonBuffer.parseObject(val);
            if (data == JsonObject::invalid()){
              jsonBuffer.clear();
              Serial.println(F("Data Invalid"));
              return;
            }

            String clock = data["waktu"];
            String date = data["tanggal"];
            waktu = clock;
            tanggal = date;
            // Serial.println(val);
            // Serial.printf("Waktu : %s\n", waktu);
            // Serial.printf("Tanggal : %s\n", tanggal);
          }
        }
      }
    } else {
      Serial.println(F("WiFi Disconnected..."));
    }
  }
}