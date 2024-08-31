# README.md

## Overview

This README provides an explanation of the provided NodeMCU code, which sets up a simple web server that allows you to control an LED via HTTP requests. The code uses the ESP8266 or ESP32 microcontroller to connect to a Wi-Fi network and listen for incoming client requests to toggle the state of an LED.

## Table of Contents

1. [Libraries Used](#libraries-used)
2. [Wi-Fi Configuration](#wi-fi-configuration)
3. [Setup Function](#setup-function)
4. [Loop Function](#loop-function)
5. [Controlling the LED](#controlling-the-led)
6. [How to Use the Web Server](#how-to-use-the-web-server)

---

## Libraries Used

The code includes several libraries necessary for Wi-Fi connectivity and web server functionality:

```cpp
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
```

- **ESP8266WiFi.h**: Provides Wi-Fi functionality for the ESP8266 microcontroller.
- **WiFi.h**: Used for the ESP32 microcontroller for Wi-Fi connectivity.
- **ESPAsyncWebServer.h**: Allows for asynchronous handling of web server requests, enabling non-blocking operations.

## Wi-Fi Configuration

The following lines set up the Wi-Fi credentials:

```cpp
const char* ssid = "Ayush";
const char* pass = "ayush2004";
```

- **ssid**: The name of the Wi-Fi network to connect to.
- **pass**: The password for the Wi-Fi network.

## Setup Function

The `setup()` function is called once when the program starts. It initializes the serial communication, sets up the LED pin, and connects to the Wi-Fi network:

```cpp
void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  delay(10);
  pinMode(led, OUTPUT); // Set the LED pin as an output
  digitalWrite(led, LOW); // Turn off the LED initially
  Serial.println();
  Serial.print("connecting to :");
  Serial.println(ssid);
  WiFi.begin(ssid, pass); // Start the Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // Print dots while connecting
  }
  Serial.println();
  Serial.println("WiFi connected");
  server.begin(); // Start the web server
  Serial.println("server started");
  Serial.print("Use this URL to connect to the program: ");
  Serial.print(WiFi.localIP()); // Print the local IP address
  Serial.print("/");
}
```

### Key Steps in `setup()`:

1. **Serial Communication**: Initializes serial communication for debugging.
2. **LED Pin Setup**: Configures the built-in LED pin as an output.
3. **Wi-Fi Connection**: Connects to the specified Wi-Fi network and waits until connected.
4. **Web Server Initialization**: Starts the web server on port 80 and prints the local IP address for access.

## Loop Function

The `loop()` function runs continuously after the `setup()` function. It checks for incoming client connections and processes requests:

```cpp
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return; // Exit if no client is connected
  }

  Serial.println("new client");
  while (!client.available()) {
    delay(1); // Wait for client data
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println("user requested :");
  Serial.print(request);
  client.flush();
```

### Key Steps in `loop()`:

1. **Client Connection Check**: Uses `server.available()` to check for a connected client.
2. **Request Handling**: Reads the HTTP request from the client and logs it to the serial monitor.

## Controlling the LED

The code checks the incoming request to determine whether to turn the LED on or off:

```cpp
  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(led, HIGH); // Turn the LED off
  }
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(led, LOW); // Turn the LED on
  }

  client.println("user requested " + request); // Send response back to the client
}
```

### Key Steps for LED Control:

- **Turning Off the LED**: If the request contains `/LED=OFF`, the LED is turned off by setting the pin HIGH.
- **Turning On the LED**: If the request contains `/LED=ON`, the LED is turned on by setting the pin LOW.
- **Response to Client**: Sends back a confirmation message to the client indicating the request received.

## How to Use the Web Server

1. **Upload the Code**: Upload the provided code to your NodeMCU or ESP32 board using the Arduino IDE.
2. **Open Serial Monitor**: Open the Serial Monitor in the Arduino IDE to view the connection status and the local IP address.
3. **Connect to the Web Server**: In a web browser, enter the URL shown in the Serial Monitor (e.g., `http://192.168.1.100/`).
4. **Control the LED**: Use the following URLs to control the LED:
   - To turn the LED **ON**: `http://<your_ip_address>/LED=ON`
   - To turn the LED **OFF**: `http://<your_ip_address>/LED=OFF`

Replace `<your_ip_address>` with the actual IP address displayed in the Serial Monitor.

<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/c1.png)

---

## Conclusion

This NodeMCU code sets up a simple web server that allows users to control an LED over Wi-Fi. By sending HTTP requests to the server, the LED can be turned on or off remotely. This project demonstrates basic web server functionality and can be expanded for more complex IoT applications. Now. let's give this thing a web page and more functionality with good looks.

Feel free to customize the code further to suit your needs! If you have any questions or need assistance, don't hesitate to reach out. Happy coding! 🎉