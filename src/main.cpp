#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
#ifdef __cplusplus
#define LED 2

extern "C"
{
#endif
  uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();
// Masukan ssid dan password dari router
const char *ssid = "Galaxy M624912";
const char *password = "farid782";
// Alamat IP server dengan portnya
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(2500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
void loop()
{
  if ((millis() - lastTime) > timerDelay)
  {
    // cek koneksi

    if (WiFi.status() == WL_CONNECTED)
    {
      digitalWrite(LED, HIGH);
      WiFiClient client;
      HTTPClient http;
      float temp = (temprature_sens_read() - 32) / 1.8;
      char serverName[100];
      sprintf(serverName, "http://127.0.0.1:5000/esp?temperature=%3.2f",
              temp);
      http.begin(client, serverName);
      // kirimkan HTTP POST
      int httpResponseCode = http.POST("");
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }
    else
    {
      digitalWrite(LED, LOW);
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}