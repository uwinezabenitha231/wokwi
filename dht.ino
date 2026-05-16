#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN D4
#define DHTTYPE DHT11  
 // change to DHT22 if needed

DHT dht(DHTPIN, DHTTYPE);

const char* ssid ="ange";
const char* password ="1234567890";
const char* server = "http://192.168.0.164/BeniSara/insert_dht.php";
#define DHT D4
#define DHTTYPE DHT11  

void setup() {
  Serial.begin(9600);
  dht.begin();
  delay(200);

  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
}

void loop() {

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read DHT sensor");
    delay(2000);
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C | Hum: ");
  Serial.print(hum);
  Serial.println(" %");

  if (WiFi.status() == WL_CONNECTED) {

    WiFiClient client;
    HTTPClient http;

    http.begin(client, server);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"temperature\":" + String(temp) + ",\"humidity\":" + String(hum) + "}";

    int code = http.POST(json);

    Serial.print("Response Code: ");
    Serial.println(code);

    http.end();
  }

  delay(5000);
}
