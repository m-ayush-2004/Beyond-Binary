#include <ESP8266WiFi.h> // Include the ESP8266 WiFi library

// Define the WiFi network credentials
const char* ssid = "Ayush"; // WiFi network SSID (name)
const char* pass = "ayush2004"; // WiFi network password

// Create a WiFi server on port 80 (default HTTP port)
WiFiServer server(80);

void setup() {
  // Initialize the serial communication at 9600 baud
  Serial.begin(9600);
  delay(10); // Wait for 10ms to ensure serial communication is established

  // Print a newline character to separate the output
  Serial.println();

  // Print the WiFi network SSID we're trying to connect to
  Serial.print("connecting to :");
  Serial.println(ssid);

  // Start the WiFi connection process
  WiFi.begin(ssid, pass);

  // Wait until the WiFi connection is established
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); // Wait for 500ms before checking again
    Serial.print("."); // Print a dot to indicate the connection process
  }

  // Print a success message when the WiFi connection is established
  Serial.println();
  Serial.println("WiFi connected");

  // Start the WiFi server
  server.begin();
  Serial.println("server started");

  // Print the IP address of the ESP8266 board
  Serial.print("User this url to connect to the program : ");
  Serial.print(WiFi.localIP()); // Get the local IP address of the ESP8266 board
  Serial.print("/"); // Print a slash to indicate the root URL
}

void loop() {
  // Check if a new client has connected to the server
  WiFiClient client = server.available();
  if (!client) {
    return; // If no client is connected, exit the loop
  }

  // Print a message to indicate a new client has connected
  Serial.println("new client");

  // Wait until the client sends some data
  while (!client.available()) {
    delay(1); // Wait for 1ms before checking again
  }

  // Read the first line of the request from the client
  String request = client.readStringUntil('\r');
  Serial.println(request); // Print the request to the serial console

  // Clear the client's input buffer
  client.flush();

  // Send a response back to the client
  client.println("Hello world");
}
