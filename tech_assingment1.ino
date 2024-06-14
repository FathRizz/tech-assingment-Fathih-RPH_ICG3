#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Lab Komputer";
const char* password = "bekengapaso";
const char* serverName = "http://192.168.110.212_ip:5000/post-data";

const int MQ135_PIN = 4;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int sensorValue = analogRead(MQ135_PIN);
  sendSensorData(sensorValue);
  delay(60000); // Send data every 60 seconds
}

void sendSensorData(int sensorValue) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"sensor_value\":" + String(sensorValue) + "}";
    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}
