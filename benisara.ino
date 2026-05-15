#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* servername = "http://192.168.0.164/BeniSara/insert.php";
const char* ssid = "ange";
const char* pass = "1234567890";

#define trigpin D1
#define echopin D2
#define bluepin D6
#define redpin D5
#define greenpin D4

void setup() {
  Serial.begin(9600);

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(redpin, OUTPUT);

  WiFi.begin(ssid, pass);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  // Send ultrasonic signal
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin, LOW);

  // Read echo
  long duration = pulseIn(echopin, HIGH);

  // Calculate distance
  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check WiFi connection
  if (WiFi.status() == WL_CONNECTED) {

    WiFiClient client;
    HTTPClient http;

    http.begin(client, servername);

    http.addHeader("Content-Type", "application/json");

    // Create JSON document
    StaticJsonDocument<200> Benitha;

    Benitha["device_name"] = "esp8266";
    Benitha["intera"] = distance;

    String jsondoc;

    serializeJson(Benitha, jsondoc);

    // Send POST request
    int responsecode = http.POST(jsondoc);

    Serial.print("Response Code: ");
    Serial.println(responsecode);

    if (responsecode > 0) {
      Serial.println("Data inserted successfully");
    } else {
      Serial.println("Server failed");
    }

    http.end();

  } else {
    Serial.println("Failed to connect to WiFi");
  }

  // LED conditions
  digitalWrite(greenpin, LOW);
  digitalWrite(bluepin, LOW);
  digitalWrite(redpin, LOW);

  if (distance <= 20) {
    digitalWrite(greenpin, HIGH);
     digitalWrite(bluepin, LOW);
     digitalWrite(redpin, LOW);
    delay(350);

  } else if (distance <= 40) {
    digitalWrite(redpin, HIGH);
    digitalWrite(bluepin, LOW);
    digitalWrite(greenpin, LOW);
    delay(400);

  } else if (distance <= 60) {
    digitalWrite(greenpin, LOW);
    digitalWrite(bluepin, HIGH);
    digitalWrite(redpin, LOW);
    delay(450);

  } else {
    Serial.println("Safe on the gate");
  }

  delay(500);
}
