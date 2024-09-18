#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <Firebase_ESP_Client.h>
#define blue D5
#define red D7
String uid;
// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Define Wi-Fi credentials
const char *ssid = "YOUR_SSID";
const char *pass = "YOUR_PASS";
#define WIFI_SSID "YOUR_SSID"     // Wi-Fi SSID
#define WIFI_PASSWORD "YOUR_PASS" // Wi-Fi password

// Define Firebase project API Key
#define API_KEY "YOUR_API_KEY"

// Define user email and password for Firebase authentication
#define USER_EMAIL "test@gmail.com"
#define USER_PASSWORD "test123"

// Define the Firebase Realtime Database URL
#define DATABASE_URL "YOUR_DATABASE_LINK"

// Create Firebase Data object for database operations
FirebaseData fbdo;

// Create Firebase Authentication and Configuration objects
FirebaseAuth auth;
FirebaseConfig config;

// Variables for database path and timing
String databasePath;
unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void handleRoot();
void set_connect();
void set_server();
void blue_f();
void red_f();
void sensor_data();
String act_state;
ESP8266WebServer server(80);
String state;
float temp = 500;


const char index_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <style>
      body {
        background-color: #DAD4B5;
        color: #F2E8C6;
        margin: 0px;
        width: 99%;
      }
      
      .nav {
        background-color: #952323;
        display: absolute;
        margin: 0px !important;
        padding: 10px 5px;
        width: 100%;
        height: 40px;
      }
      
      .nav-list {
        margin: 0px !important;
        padding: 10px 10px;
        font-size: 20px;
      }

      ul {
        list-style: none;
        display: flex;
        justify-content: space-between;
      }

      .container {
        display: flex;
        align-items: center;
        justify-content: center;
        height: auto;
        margin: 0px 0px;
      }
      .grid-2{
        display: grid;
        width: 100%;
        height: 100vh;
        grid-template-columns: 1fr 1fr;
      }
      .grid-1 {
        display: grid;
        grid-template-columns: 1fr 1fr;
        width: 98%;
        row-gap: 10px;
        column-gap: 10px;
        order: 1;
      }
      button{
        margin: 0px;
        font-family: 'Times New Roman', Times, serif;
        font-size: 18px;
        padding: 0px;
      }
      .grid-1 button{
        text-decoration: none;
        color: #F2E8C6;
        text-align: center;
        width: 90%;
        padding: 15px 5px;
        background-color: #A73121;
        border: none;
        margin: 5px 15px;
        border-radius: 5%;
      }
      .distance{
        display: grid;
        height: 100vh;
        grid-template-columns: 1fr 1fr;
        grid-template-rows: 3fr 1fr 1fr;
        color: #F2E8C6 !important;
      }
      .dist {
        grid-column: span 2;
        justify-content: center;
        display: flex;
        font-size: 45px;
        color: #2a2206a1 !important;
      }
      .values{
        color: #2a2206a1 !important;
        font-size: 20px;
        text-align: center;
      }
      @media (max-width:800px) {
        .grid-2 {
          display: grid;
          grid-column: 1fr;
          grid-template-rows: 1fr 1fr;
          width: 98%;
          row-gap: 10px;
          column-gap: 10px;
          order: 1;
        }  
        .distance{
        display: grid;
        height: auto;
        grid-template-columns: 1fr 1fr;
        grid-template-rows: 3fr 1fr 1fr;
        color: #F2E8C6 !important;
      }   
         .grid-2{
        display: grid;
        width: 100%;
        grid-template-columns: 1fr 1fr;
      }
        .container {
          display: flex;
          align-items: center;
          justify-content: center;
          height: auto;
          flex-direction: column;
          margin: 0px 0px;
        }
.values {
    font-size: 20px;
    text-align: center;
    margin: 0px 26px;
}
.nav-list {
        margin: 0px !important;
        padding: 10px 10px;
        font-size: 20px;
      }
      }
      @media (max-width:600px) {
        .nav-list {
        margin: 0px !important;
        padding: 10px 10px;
        font-size: 15px;
      }
      }
    </style>
    <title>automation</title>
  </head>

  <body>
    <div class="nav">
      <ul class="nav-list">
        <li class="nav-items1">TECHNO-VIT</li>
        <li class="nav-items">product ID : http://techno-vit.localhost/</li>
      </ul>
    </div>
    <div class="container grid-2">
      <div class="grid-1 controles">
          <button onclick="send_b(1)"  >BLUE ON</button>
        <button onclick="send_b(0)"  > BLUE OFF  </button>
          <button onclick="send_r(1)"> RED ON</button>
        <button onclick="send_r(0)"> RED OFF  </button>
        <button onclick="send_a(1)"> ALL ON</button>
        <button onclick="send_a(0)"> ALL OFF</button>
      </div>
      <div class="distance">
        <div class="dist">
          <h1 id="dist1">32<sup style="font-size: 30px;">  cm </sup></h1>
        </div>
        <div id="blue-status" class="values">
          Blue  Status : <div id="ac-0">ON</div>
        </div>
        <div id="red-status" class="values">
          Red   Status : <div id="ac-1">ON</div>
          
        </div>
        <div id="purple-status" class="values">
          Purple   Status : <div id="ac-2">ON</div>
          
        </div>
        <div id="volume-status" class="values">
          Volume   Status : <div id="ac-3">ON</div>
          
        </div>
      </div>
      </div>
    </div>


    <script>
      function send_r(stat) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            
            console.log(this.response);
            document.getElementById("red-status").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "red?state=" + stat, true);
        xhttp.send();
      }
      function send_b(stat) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200  && this.responseType != "document") {
            document.getElementById("blue-status").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "blue?state=" + stat, true);
        xhttp.send();
      }
      function send_a(stat) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.response);
            document.getElementById("ac-0").innerHTML = this.responseText;
            document.getElementById("ac-1").innerHTML = this.responseText;
            document.getElementById("ac-2").innerHTML = this.responseText;
            document.getElementById("ac-3").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "all?state=" + stat, true);
        xhttp.send();
      }
      setInterval(function () {
        getData();
      }, 6000);
      function getData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("dist1").innerHTML = this.responseText+'<sup style="font-size: 30px;">  cm </sup>';
          }
        };
        xhttp.open("GET", "dist", true);
        xhttp.send();
      }
    </script>
  </body>
  </html>

)rawliteral";

void setup()
{
    // put your setup code here, to run once:
    pinMode(blue, OUTPUT);
    pinMode(red, OUTPUT);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
    Serial.begin(115200);
    delay(1000);
    WiFi.mode(WIFI_STA);
    Serial.println("\n\n\nserial monitor is now online !!\n\n\n");
    // Connect to WiFi network
    set_connect();
    // Start the server
    set_server();
    // Assign the API key to the Firebase configuration
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;       // Set user email for authentication
    auth.user.password = USER_PASSWORD; // Set user password for authentication

    // Assign the Realtime Database URL to the Firebase configuration
    config.database_url = DATABASE_URL;

    // Enable automatic reconnection to Wi-Fi
    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096); // Set the response size for Firebase data

    // Assign the callback function for token generation
    config.token_status_callback = tokenStatusCallback; // Function defined in TokenHelper.h
    config.max_token_generation_retry = 5;              // Set maximum retries for token generation

    // Initialize Firebase with the configuration and authentication
    Firebase.begin(&config, &auth);
    Serial.println("Getting User UID");

    // Wait until the user UID is available
    while ((auth.token.uid) == "")
    {
        Serial.print('.'); // Print a dot while waiting for UID
        delay(1000);       // Wait for 1 second
    }

    // Store the user UID
    uid = auth.token.uid.c_str();
    Serial.print("User UID: ");
    Serial.println(uid); // Print the user UID

    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP()); // Print the local IP address
    Serial.println();

    // Reconnect to Firebase and set the database path
    Firebase.reconnectWiFi(true);
    for(int j=0; j<9;j++){
        if (Firebase.ready() && (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0))
        {
            sendDataPrevMillis = millis(); // Update the last send time

            Serial.print("[Info] Data sent to node was:: "); // Indicate reading from serial

            // Write the integer value from serial input to the database at path "led"
            if (Firebase.RTDB.setInt(&fbdo, "distance/" + String(j) + "/y", 0))
            {
                Serial.println("PASSED");                   // Indicate successful data write
                Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
                Serial.println("TYPE: " + fbdo.dataType()); // Print the data type
                Serial.println("DATA: " + String(0));    // Print the data
            }
            else
            {
                Serial.println("FAILED TO UPLOAD DISTANCE");     // Indicate failure in writing data
                Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
            }
            unsigned long x = millis();
            if (Firebase.RTDB.setInt(&fbdo, "distance/" + String(j) + "/x", x))
            {
                Serial.println("PASSED");                   // Indicate successful data write
                Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
                Serial.println("TYPE: " + fbdo.dataType()); // Prnt the data type
                Serial.println("DATA: " + String(x));       // Print the data
            }
            else
            {
                Serial.println("FAILED TO UPLOAD TIME");         // Indicate failure in writing data
                Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
            }
        }
        
    }
}
int i=9;
void loop()
{
    // put your main code here, to run repeatedly:
    server.handleClient();
        temp /= 1.5;
        if (i % 2 == 0)
            temp /= 1.3;
        if (i % 3 == 0)
            temp *= 2.5;
        String sensor_value = String(temp);

        if (Firebase.ready() && (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0))
        {
            sendDataPrevMillis = millis(); // Update the last send time

            Serial.print("[Info] Data sent to node was:: "); // Indicate reading from serial

            // Write the integer value from serial input to the database at path "led"
            if (Firebase.RTDB.setInt(&fbdo, "distance/" + String(i) + "/y", temp))
            {
                Serial.println("PASSED");                   // Indicate successful data write
                Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
                Serial.println("TYPE: " + fbdo.dataType()); // Print the data type
                Serial.println("DATA: " + String(temp));    // Print the data
            }
            else
            {
                Serial.println("FAILED TO UPLOAD DISTANCE");     // Indicate failure in writing data
                Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
            }
            unsigned long x = millis();
            if (Firebase.RTDB.setInt(&fbdo, "distance/" + String(i) + "/x", x))
            {
                Serial.println("PASSED");                   // Indicate successful data write
                Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
                Serial.println("TYPE: " + fbdo.dataType()); // Prnt the data type
                Serial.println("DATA: " + String(x));       // Print the data
            }
            else
            {
                Serial.println("FAILED TO UPLOAD TIME");         // Indicate failure in writing data
                Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
            }
        }
        i--;
        if(i<0){
          i=9;
        }
}

void set_connect()
{

    Serial.print("Connecting to :");
    Serial.println(ssid);

    // Start the WiFi connection process
    WiFi.begin(ssid, pass);

    // Wait until the WiFi connection is established
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);        // Wait for 500ms before checking again
        Serial.print("."); // Print a dot to indicate the connection process
    }

    Serial.println("");
    Serial.print("\n\nConnected to :");
    Serial.println(WiFi.SSID());
    Serial.print("\nIPadress (Connect with this IP):");
    Serial.println(WiFi.localIP());
}

void set_server()
{
    server.on("/", handleRoot);

    server.on("/blue", blue_f);

    server.on("/red", red_f);

    server.on("/all", all_f);

    server.on("/dist", sensor_data);

    server.begin();

    Serial.println("\n\n\nserver started!!\n\n\n");
}

void handleRoot()
{ // When URI / is requested, send a web page with a buttonto toggle the LED
    server.send(200, "text/html", index_html);
}

void all_f()
{

    act_state = server.arg("state");
    if (act_state == "0")
    {
        Serial.println("all off called");
        digitalWrite(blue, LOW);
        digitalWrite(red, LOW);
        state = "OFF";
        if (Firebase.ready() && (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0))
        {
            sendDataPrevMillis = millis(); // Update the last send time

            Serial.print("[Info] Data sent to node was:: "); // Indicate reading from serial

            // Write the integer value from serial input to the database at path "led"
            if (Firebase.RTDB.setInt(&fbdo, "led1/", 0))
            {
                Serial.println("PASSED");                   // Indicate successful data write
                Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
                Serial.println("TYPE: " + fbdo.dataType()); // Print the data type
                Serial.println("DATA: " + String(0));       // Print the data
            }
            else
            {
                Serial.println("FAILED TO UPLOAD LED1 STATE");   // Indicate failure in writing data
                Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
            }
            // Write the integer value from serial input to the database at path "led"
            if (Firebase.RTDB.setInt(&fbdo, "led2/", 0))
            {
                Serial.println("PASSED");                   // Indicate successful data write
                Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
                Serial.println("TYPE: " + fbdo.dataType()); // Print the data type
                Serial.println("DATA: " + String(0));       // Print the data
            }
            else
            {
                Serial.println("FAILED TO UPLOAD LED2 STATE");   // Indicate failure in writing data
                Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
            }
        }
    }
    else
    {
        Serial.println("all on called");
        digitalWrite(blue, HIGH);
        digitalWrite(red, HIGH);
        state = "ON";
        if (Firebase.ready() && (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0))
        {
            Serial.print("[Info] Data sent to node was:: "); // Indicate reading from serial

            // Write the integer value from serial input to the database at path "led"
            if (Firebase.RTDB.setInt(&fbdo, "led1/", 1))
            {
                Serial.println("PASSED");                   // Indicate successful data write
                Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
                Serial.println("TYPE: " + fbdo.dataType()); // Print the data type
                Serial.println("DATA: " + String(1));       // Print the data
            }
            else
            {
                Serial.println("FAILED TO UPLOAD LED1 STATE");   // Indicate failure in writing data
                Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
            }
            // Write the integer value from serial input to the database at path "led"
            if (Firebase.RTDB.setInt(&fbdo, "led2/", 1))
            {
                Serial.println("PASSED");                   // Indicate successful data write
                Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
                Serial.println("TYPE: " + fbdo.dataType()); // Print the data type
                Serial.println("DATA: " + String(1));       // Print the data
            }
            else
            {
                Serial.println("FAILED TO UPLOAD LED2 STATE");   // Indicate failure in writing data
                Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
            }
        }
    }
    server.send(200, "text/plane", state);
}

void blue_f()
{

    act_state = server.arg("state");
    if (act_state == "0")
    {
        Serial.println("blue off called");
        digitalWrite(blue, LOW);
        state = "Blue Status : OFF";
        Serial.print("[Info] Data sent to node was:: "); // Indicate reading from serial

        // Write the integer value from serial input to the database at path "led"
        if (Firebase.RTDB.setInt(&fbdo, "led1/", 0))
        {
            Serial.println("PASSED");                   // Indicate successful data write
            Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
            Serial.println("TYPE: " + fbdo.dataType()); // Print the data type
            Serial.println("DATA: " + String(0));       // Print the data
        }
        else
        {
            Serial.println("FAILED TO UPLOAD LED1 STATE");   // Indicate failure in writing data
            Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
        }
    }
    else
    {
        Serial.println("blue on called");
        digitalWrite(blue, HIGH);
        state = "Blue Status : ON";
        Serial.print("[Info] Data sent to node was:: "); // Indicate reading from serial

        // Write the integer value from serial input to the database at path "led"
        if (Firebase.RTDB.setInt(&fbdo, "led1/", 1))
        {
            Serial.println("PASSED");                   // Indicate successful data write
            Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
            Serial.println("TYPE: " + fbdo.dataType()); // Print the data type
            Serial.println("DATA: " + String(1));       // Print the data
        }
        else
        {
            Serial.println("FAILED TO UPLOAD LED1 STATE");   // Indicate failure in writing data
            Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
        }
    }
    server.send(200, "text/plane", state);
}

void red_f()
{

    act_state = server.arg("state");
    if (act_state == "0")
    {
        Serial.println("red off called");
        digitalWrite(red, LOW);
        state = "Red Status : OFF";
        Serial.print("[Info] Data sent to node was:: "); // Indicate reading from serial

        // Write the integer value from serial input to the database at path "led"
        if (Firebase.RTDB.setInt(&fbdo, "led2/", 0))
        {
            Serial.println("PASSED");                   // Indicate successful data write
            Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
            Serial.println("TYPE: " + fbdo.dataType()); // Print the data type
            Serial.println("DATA: " + String(0));       // Print the data
        }
        else
        {
            Serial.println("FAILED TO UPLOAD LED2 STATE");   // Indicate failure in writing data
            Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
        }
    }
    else
    {
        Serial.println("red on called");
        digitalWrite(red, HIGH);
        state = "Red Status : ON";

        Serial.print("[Info] Data sent to node was:: "); // Indicate reading from serial

        // Write the integer value from serial input to the database at path "led"
        if (Firebase.RTDB.setInt(&fbdo, "led2/", 1))
        {
            Serial.println("PASSED");                   // Indicate successful data write
            Serial.println("PATH: " + fbdo.dataPath()); // Print the path where data was written
            Serial.println("TYPE: " + fbdo.dataType()); // Print the data type
            Serial.println("DATA: " + String(1));       // Print the data
        }
        else
        {
            Serial.println("FAILED TO UPLOAD LED1 STATE");   // Indicate failure in writing data
            Serial.println("REASON: " + fbdo.errorReason()); // Print the reason for failure
        }
    }
    server.send(200, "text/plane", state);
}

void sensor_data()
{
        temp /= 1.5;
        if (i % 2 == 0)
            temp /= 1.3;
        if (i % 3 == 0)
            temp *= 2.5;
        String sensor_value = String(temp);

        server.send(200, "text/plane", sensor_value);
   
}
