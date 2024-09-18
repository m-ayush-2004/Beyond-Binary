# Web-page Hosting and control

## Explanation of the Node-Code
Here’s a code explanation, with a shortened definition for later refference :

### NodeMCU Code Explanation

#### 1. **Library Inclusions and Wi-Fi Credentials**
```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <WiFiClient.h>

const char *ssid = "YOUR_SSID";
const char *pass = "YOUR_PASS";
```
- The code includes essential libraries for Wi-Fi connectivity and web server functionality. The SSID and password for the Wi-Fi network are defined as constants.

#### 2. **Pin Definitions**
```cpp
#define blue D5
#define red D7
```
- **Pin Definitions**: Pins D5 and D7 are designated for controlling the blue and red LEDs, respectively.

#### 3. **Function Declarations**
```cpp
void handleRoot();
void set_connect();
void set_server();
void blue_f();
void red_f();
```
- Function prototypes are declared for handling tasks such as serving the root webpage, connecting to Wi-Fi, and setting up the server.

#### 4. **Global Variables**
```cpp
String act_state;
ESP8266WebServer server(80);
String state;
float temp = 435;
```
- Global variables are initialized to manage the state of the application and temperature readings.

#### 5. **Sensor Data Function**
```cpp
void sensor_data() {
    temp /= 4.35;
    String sensor_value = String(temp);
    server.send(200, "text/plain", sensor_value);
}
```
- The `sensor_data()` function processes the temperature data by scaling it down and converting it to a string. It then sends this value back to the client as a plain text response.

#### 6. **HTML Content**
```cpp
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Automation</title>
    <style>
      body {
        background-color: #DAD4B5;
        color: #F2E8C6;
        margin: 0;
        width: 99%;
      }
      ...
    </style>
  </head>
  <body>
    <div class="nav">
      <ul class="nav-list">
        <li>TECHNO-VIT</li>
        <li>Product ID: http://techno-vit.localhost/</li>
      </ul>
    </div>
    <div class="container">
      <div class="grid-1">
        <h1 id="dist1">32<sup style="font-size: 30px;"> cm </sup></h1>
        <div id="blue-status" class="values">Blue Status: <div id="ac-0">ON</div></div>
        <div id="red-status" class="values">Red Status: <div id="ac-1">ON</div></div>
      </div>
    </div>
  </body>
</html>
)rawliteral";
```
- The HTML content is stored in a string format in program memory, allowing the NodeMCU to serve a webpage.

#### 7. **Server Handling Function**
```cpp
void handleRoot() {
    server.send(200, "text/html", index_html);
}
```
- The `handleRoot()` function is triggered when a client accesses the root URL ("/"). It sends the HTML content stored in `index_html` as a response to the client.

#### 8. **set_connect Function**
```cpp
void set_connect() {
    WiFi.begin(ssid, pass);  // Initiates connection to the Wi-Fi network using the defined SSID and password.
    Serial.print("Connecting to Wi-Fi");
    
    while (WiFi.status() != WL_CONNECTED) {  // Loop until the connection is established.
        delay(500);  // Wait for 500 milliseconds before checking the status again.
        Serial.print(".");  // Print a dot to indicate progress in connecting.
    }
    
    Serial.println("Connected to Wi-Fi!");  // Print a message once connected.
    Serial.print("IP Address: ");  // Print the local IP address assigned to the NodeMCU.
    Serial.println(WiFi.localIP());
}
```
- The `set_connect()` function establishes a connection to the specified Wi-Fi network:
  - It calls `WiFi.begin(ssid, pass)` to start the connection process.
  - A loop checks the connection status using `WiFi.status()`, printing dots to indicate progress until connected.
  - Once connected, it prints a confirmation message and the assigned IP address.

#### 9. **set_server Function**
```cpp
void set_server() {
    server.on("/", handleRoot);  // Associates the root URL with the handleRoot function.
    server.on("/red", []() {  // Defines an endpoint for controlling the red LED.
        // Logic to handle red LED requests
    });
    server.on("/blue", []() {  // Defines an endpoint for controlling the blue LED.
        // Logic to handle blue LED requests
    });
    server.on("/all", []() {  // Defines an endpoint for controlling all LEDs.
        // Logic to handle all LED requests
    });
    server.begin();  // Starts the server, allowing it to listen for incoming requests.
    Serial.println("Server started!");  // Print confirmation that the server is running.
}
```
- The `set_server()` function configures the web server:
  - It uses `server.on()` to define routes for different endpoints. Each route is associated with a function that will handle requests to that endpoint.
    - The root URL ("/") is linked to the `handleRoot()` function.
    - Additional routes for controlling the red, blue, and all LEDs are defined, with logic to handle requests.
  - Finally, it calls `server.begin()` to start the server, enabling it to listen for incoming client requests. A confirmation message is printed to the Serial Monitor.

#### 10. **Loop Function**
```cpp
void loop() {
    server.handleClient();
}
```
- The `loop()` function continuously checks for incoming client requests and processes them using `server.handleClient()`. This allows the server to respond to user interactions in real-time.

---
<br>

# Explanation for the Client-page Scripting

here's a detailed explanation of the JavaScript section and how it interacts with the HTML:

```html
<!DOCTYPE html>
<html>
  <head>
    <!-- HTML and CSS section -->
  </head>

  <body>
    <!-- HTML structure -->

    <script>
      function send_r(stat) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("red-status").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "red?state=" + stat, true);
        xhttp.send();
      }
```

### JavaScript Functions for LED Control

The JavaScript section contains functions that handle the interaction with the server to control the LEDs and update the display.

1. **`send_r(stat)`**:
   - This function is called when the user clicks on the "RED ON" or "RED OFF" button.
   - It creates an `XMLHttpRequest` object (`xhttp`) to send a GET request to the server.
   - The request URL includes the `state` parameter, which determines whether to turn the red LED on or off.
   - When the server responds, the `onreadystatechange` event is triggered.
   - If the request is complete (`readyState == 4`) and the status is successful (`status == 200`), the function updates the HTML element with the ID "red-status" using `innerHTML`. The `this.responseText` contains the server's response.

```javascript
      function send_b(stat) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("blue-status").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "blue?state=" + stat, true);
        xhttp.send();
      }
```

2. **`send_b(stat)`**:
   - This function is similar to `send_r(stat)` but is used for controlling the blue LED.
   - It sends a GET request to the server with the `state` parameter, indicating whether to turn the blue LED on or off.
   - When the server responds, it updates the HTML element with the ID "blue-status" using `innerHTML`.

```javascript
      function send_a(stat) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("ac-0").innerHTML = this.responseText;
            document.getElementById("ac-1").innerHTML = this.responseText;
            document.getElementById("ac-2").innerHTML = this.responseText;
            document.getElementById("ac-3").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "all?state=" + stat, true);
        xhttp.send();
      }
```

3. **`send_a(stat)`**:
   - This function is called when the user clicks on the "ALL ON" or "ALL OFF" button.
   - It sends a GET request to the server with the `state` parameter, indicating whether to turn all LEDs on or off.
   - When the server responds, it updates the HTML elements with IDs "ac-0", "ac-1", "ac-2", and "ac-3" using `innerHTML`.

```javascript
      setInterval(function () {
        getData();
      }, 6000);

      function getData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("dist1").innerHTML = this.responseText + "<sup style='font-size: 30px;'> cm </sup>";
          }
        };
        xhttp.open("GET", "dist", true);
        xhttp.send();
      }
    </script>
  </body>
</html>
```

### Periodic Data Retrieval and Display Update

The JavaScript code also includes a function to periodically retrieve the distance data from the server and update the display.

1. **`setInterval`**:
   - This function calls the `getData()` function every 6 seconds (6000 milliseconds).

2. **`getData()`**:
   - This function creates an `XMLHttpRequest` object (`xhttp`) to send a GET request to the server.
   - The request URL is "dist", which indicates that the server should provide the current distance reading.
   - When the server responds, the `onreadystatechange` event is triggered.
   - If the request is complete (`readyState == 4`) and the status is successful (`status == 200`), the function updates the HTML element with the ID "dist1" using `innerHTML`. The `this.responseText` contains the server's response, which is the current distance reading.
   - The distance reading is displayed with a superscript "cm" using HTML tags.

In summary, the JavaScript code interacts with the server to control the LEDs and retrieve distance data. It sends GET requests to specific URLs with parameters and updates the HTML elements accordingly based on the server's responses. The periodic data retrieval function ensures that the distance display is updated every 6 seconds without user interaction.

Feel free to customize the code further to suit your needs! If you have any questions or need assistance, don't hesitate to reach out. Happy coding! 🎉