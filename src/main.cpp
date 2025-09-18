/*
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// ====== WiFi Config ======
const char* ssid = "huy";
const char* password = "113234234";

// ====== ThinkSpeak Config ======
String apiKey = "D88ZBIF0UMVPDMEK";  
const char* server = "http://api.thingspeak.com/update";

// ====== DHT Config ======
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(1000);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // In ra Serial Monitor
  Serial.printf("Temp: %.2f °C | Humidity: %.2f %%\n", t, h);

  // Gửi dữ liệu lên ThinkSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey +
                 "&field1=" + String(t) +
                 "&field2=" + String(h);

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.printf("ThinkSpeak Response: %d\n", httpCode);
    } else {
      Serial.printf("Error sending data: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }

  delay(15000); 
}
*/
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "huy";
const char* password = "113234234";

String readAPIKey = "3JTY6WK3JG9OJKS3";  
unsigned long channelID =  3071978;  

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = "http://api.thingspeak.com/channels/" + String(channelID) +
                 "/fields/1/last.json?api_key=" + readAPIKey;

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("ThingSpeak Data: " + payload);
    } else {
      Serial.printf("Error reading data: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }

  delay(10000);  
}
