#include <ESP8266WiFi.h>
#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
const char* ssid = "YOUR SSID";
const char* pass = "YOUR PASS";
int led = LED_BUILTIN;
WiFiServer server(80);

void setup() {
 Serial.begin(9600);
  delay(10);
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);
  Serial.println();
  Serial.print("connecting to :");
  Serial.println(ssid);
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("server started");
  Serial.print("User this url to connect to the program : ");
  Serial.print(WiFi.localIP());
  Serial.print("/"); 
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  Serial.println("new client");
  while (!client.available())
  {
    delay(1);
  }


  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println("user requested :");
  Serial.print(request);
  client.flush();
  if (request.indexOf("/LED=OFF") != -1)
  {
    digitalWrite(led, HIGH);
  }
  if (request.indexOf("/LED=ON") != -1)
  {
    digitalWrite(led, LOW);
  }

  client.println("user requested " + request);
}
