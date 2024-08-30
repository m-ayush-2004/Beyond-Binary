#include <Arduino.h>  // Include the Arduino core library

// Include WiFi library based on the platform (ESP32 or ESP8266)
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>  // Include the Firebase ESP client library

String uid;  // Variable to store the user ID

// Include token generation and RTDB helper functions
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Define Wi-Fi credentials
#define WIFI_SSID "YOUR_SSID"  // Wi-Fi SSID
#define WIFI_PASSWORD "YOUR_PASS"  // Wi-Fi password

// Define Firebase project API Key
#define API_KEY "AIzaSyAxrJCnE9B2MSC7Vp31bgYbGcxPe5I__Qo"

// Define user email and password for Firebase authentication
#define USER_EMAIL "test@gmail.com"
#define USER_PASSWORD "test123"

// Define the Firebase Realtime Database URL
#define DATABASE_URL "https://technovit-24-default-rtdb.firebaseio.com/"

// Create Firebase Data object for database operations
FirebaseData fbdo;

// Create Firebase Authentication and Configuration objects
FirebaseAuth auth;
FirebaseConfig config;

// Variables for database path and timing
String databasePath;
unsigned long sendDataPrevMillis = 0;  // To track the time for sending data
int count = 0;  // Counter variable
bool signupOK = false;  // Flag to check if signup was successful

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);  // Set the built-in LED pin as output
    Serial.begin(115200);  // Start serial communication at 115200 baud rate
    pinMode(D3, OUTPUT);  // Set pin D3 as output for additional use

    // Start Wi-Fi connection
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    
    // Wait until the Wi-Fi is connected
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");  // Print a dot while connecting
        delay(300);  // Wait for 300 milliseconds
    }

    // Assign the API key to the Firebase configuration
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;  // Set user email for authentication
    auth.user.password = USER_PASSWORD;  // Set user password for authentication

    // Assign the Realtime Database URL to the Firebase configuration
    config.database_url = DATABASE_URL;

    // Enable automatic reconnection to Wi-Fi
    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096);  // Set the response size for Firebase data

    // Assign the callback function for token generation
    config.token_status_callback = tokenStatusCallback;  // Function defined in TokenHelper.h
    config.max_token_generation_retry = 5;  // Set maximum retries for token generation

    // Initialize Firebase with the configuration and authentication
    Firebase.begin(&config, &auth);
    Serial.println("Getting User UID");

    // Wait until the user UID is available
    while ((auth.token.uid) == "") {
        Serial.print('.');  // Print a dot while waiting for UID
        delay(1000);  // Wait for 1 second
    }

    // Store the user UID
    uid = auth.token.uid.c_str();
    Serial.print("User UID: ");
    Serial.println(uid);  // Print the user UID

    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());  // Print the local IP address
    Serial.println();

    // Reconnect to Firebase and set the database path
    Firebase.reconnectWiFi(true);
    databasePath = "/UsersData/" + uid + "/readings";  // Set the path for user readings
}

// Variables to hold integer values
int p = 0;  // Variable to store integer value from Firebase
int w = 0;  // Variable for future use
int y = 0;  // Variable for future use

void loop() {
    // Check if Firebase is ready and enough time has passed to send data
    if (Firebase.ready() && (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0)) {
        sendDataPrevMillis = millis();  // Update the last send time

        // Read integer value from the database at the path "led"
        if (Firebase.RTDB.getInt(&fbdo, "led")) {
            // Check if the data type is an integer
            if (fbdo.dataTypeEnum() == firebase_rtdb_data_type_integer) {
                Serial.println("PASSED");  // Indicate successful data retrieval
                Serial.println("PATH: " + fbdo.dataPath());  // Print the path from which data was retrieved
                Serial.println("TYPE: " + fbdo.dataType());  // Print the data type
                int p = fbdo.intData();  // Get the integer value directly
                Serial.print("[Info] Data sent to node was:: ");  // Indicate reading from serial
                Serial.println(p);  // Print the integer value

                // Control the built-in LED based on the retrieved value
                if (p == 1)
                    digitalWrite(LED_BUILTIN, LOW);  // Turn on the LED if p is 1
                else
                    digitalWrite(LED_BUILTIN, HIGH);  // Turn off the LED if p is not 1
            }
        } else {
            Serial.println(fbdo.errorReason());  // Print error reason if data retrieval failed
        }

        // Check if there is data available on the serial port
        if (Serial.available()) {
            Serial.print("[Info] Data sent to node was:: ");  // Indicate reading from serial
            String str = Serial.readString();  // Read the incoming string from serial
            Serial.println(str);
            // Write the integer value from serial input to the database at path "led"
            if (Firebase.RTDB.setInt(&fbdo, "led", str.toInt())) {
                Serial.println("PASSED");  // Indicate successful data write
                Serial.println("PATH: " + fbdo.dataPath());  // Print the path where data was written
                Serial.println("TYPE: " + fbdo.dataType());  // Print the data type
            } else {
                Serial.println("FAILED");  // Indicate failure in writing data
                Serial.println("REASON: " + fbdo.errorReason());  // Print the reason for failure
            }
        }
    }
}
