
---

# Setting Up Firebase Authentication 🔒
Here's a detailed guide for getting started with Firebase Authentication, formatted similarly to your previous examples. This guide includes steps for setting up Firebase Authentication, creating users, and managing authentication state.

## Step 1: Access the Authentication Section
Click on the three horizontal bars (☰) in the top left corner of the Firebase console to open the navigation menu.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/au1.png)

## Step 2: Navigate to Authentication
Select **Build** from the menu, then click on **Authentication**. This will take you to the section where you can manage user authentication for your project.

## Step 3: Get Started with Authentication
Click on the **Get Started** button. This will enable Firebase Authentication for your project.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/au2.png)

## Step 4: Choose Sign-In Method
In the Authentication section, click on the **Sign-in method** tab. Here, you will see various authentication providers you can enable.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/au3.png)


### Enable Email/Password Authentication
1. Find the **Email/Password** option in the list.
2. Click on the toggle to enable it.
3. Click on **Save** to apply the changes.


![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/au3.png)
 
## Step 5: Create a User
To create a new user for testing, you can do this directly from the Firebase console:

1. Click on the **Users** tab.
2. Click on **Add user**.
3. Enter the following details:
   - **Email**: `test@gmail.com`
   - **Password**: `test123`
4. Click on **Add User** to save the new user.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/au4.png)
 
## Step 6: Obtain Your Firebase Configuration
To integrate Firebase Authentication into your web application, you need to obtain your Firebase configuration details:

1. Go to the **Project settings** by clicking on the gear icon next to **Project Overview**.
2. In the **General** tab, scroll down to find your **Firebase SDK snippet**.
3. Copy the configuration object, which looks like this:

```javascript
const firebaseConfig = {
    apiKey: "YOUR_API_KEY",
    authDomain: "YOUR_PROJECT_ID.firebaseapp.com",
    projectId: "YOUR_PROJECT_ID",
    storageBucket: "YOUR_PROJECT_ID.appspot.com",
    messagingSenderId: "YOUR_SENDER_ID",
    appId: "YOUR_APP_ID"
};
```
![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/au4.png)

---
# Code explanation and upload 

### Library Installation 
Installation guide for firebase Library package

Here are the detailed steps to install the Firebase library for NodeMCU in the Arduino IDE:

## Step 1: Open the Arduino Library Manager
1. Launch the Arduino IDE on your computer.
2. Click on **Sketch** in the top menu.
3. Hover over **Include Library** and select **Manage Libraries...**


![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/au7.png)
 
## Step 2: Search for the Firebase Library
1. In the Library Manager window, type **"Firebase ESP Client"** in the search bar.
2. The search results should show the **"Firebase ESP Client Library for ESP8266 and ESP32"** by Mobizt.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/au7.png)
 

## Step 3: Install the Library
1. Click on the **"Firebase ESP Client Library for ESP8266 and ESP32"** entry in the search results.
2. Click on the **"Install"** button to install the library.


![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/au7.png)
 

## Step 4: Install Dependencies
1. The library may have dependencies on other libraries. 
2. If prompted, install any required dependencies, such as **"ArduinoJson"** or **"Firebase Arduino based on WiFiNINA"**.
3. Make sure to install the correct versions of the dependencies as specified in the library documentation.

## Step 5: Verify Installation
1. After the installation is complete, you should see the **"Firebase ESP Client"** library listed under **"Sketch > Include Library"**.
2. You can also check the **"Examples"** menu under **"File > Examples"** to see if the library examples are available.

That's it! You have successfully installed the Firebase ESP Client library for NodeMCU in the Arduino IDE. You can now use this library to connect your NodeMCU board to Firebase and perform various operations like reading, writing, and streaming data.

### Code Breakdown

Here’s the code broken down into **10 sections** with concise explanations for each:

```cpp
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
```

### 1. **Library Inclusions**
The code begins by including essential libraries:
- **Arduino.h**: Core library for Arduino functions.
- **WiFi library**: Conditional inclusion based on whether the ESP32 or ESP8266 board is used.
- **Firebase_ESP_Client.h**: Library for Firebase communication.
- **TokenHelper.h & RTDBHelper.h**: Helper functions for token management and Realtime Database operations.

```cpp
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
```

### 2. **Configuration Constants**
This section defines constants for:
- Wi-Fi credentials (SSID and password).
- Firebase API key, user email, user password, and the Realtime Database URL. These values are essential for connecting to Firebase services.

```cpp
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
```

### 3. **Firebase Objects and Variables**
Here, objects for Firebase operations are created:
- `FirebaseData fbdo`: For handling database operations.
- `FirebaseAuth auth` and `FirebaseConfig config`: For managing authentication and configuration settings.
- Additional variables for tracking database paths and timing.

```cpp
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
```

### 4. **Setup Function and Wi-Fi Connection**
The `setup()` function initializes the device:
- It sets the LED pin and starts serial communication.
- The program attempts to connect to the specified Wi-Fi network, printing dots to indicate connection progress.

```cpp
    // Assign the API key and user credentials to Firebase configuration
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;  // Set user email for authentication
    auth.user.password = USER_PASSWORD;  // Set user password for authentication

    // Assign the Realtime Database URL to the Firebase configuration
    config.database_url = DATABASE_URL;

    // Enable automatic reconnection to Wi-Fi
    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096);  // Set the response size for Firebase data
```

### 5. **Firebase Configuration**
This section assigns the API key, user credentials, and database URL to the Firebase configuration. It also enables automatic reconnection to Wi-Fi and sets the response size for Firebase data.

```cpp
    // Assign the callback function for token generation
    config.token_status_callback = tokenStatusCallback;  // Function defined in TokenHelper.h
    config.max_token_generation_retry = 5;  // Set maximum retries for token generation

    // Initialize Firebase with the configuration and authentication
    Firebase.begin(&config, &auth);
    Serial.println("Getting User UID");
```

### 6. **Token Management and Initialization**
The program sets up the token generation callback and initializes Firebase with the provided configuration and authentication settings. It indicates that it is retrieving the user UID.

```cpp
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
```

### 7. **User UID Retrieval and Connection Confirmation**
The program waits until the user UID is available, storing it in the `uid` variable. It prints the user UID and the device's local IP address to confirm a successful connection. The database path is also set based on the user UID.

```cpp
// Variables to hold integer values
int p = 0;  // Variable to store integer value from Firebase
int w = 0;  // Variable for future use
int y = 0;  // Variable for future use
```

### 8. **Variable Declarations for Data Handling**
This section declares integer variables `p`, `w`, and `y` to hold values from Firebase and for potential future use.

```cpp
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
```

### 9. **Main Loop Functionality**
The `loop()` function continuously checks if Firebase is ready and if enough time has passed to send data. It reads an integer value from the database at the path "led". If successful, it prints the path, data type, and the retrieved value. The built-in LED is controlled based on the value of `p`.

```cpp
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
```

### 10. **Serial Input Handling and Data Writing**
The program checks for serial input. If data is available, it reads the incoming string, converts it to an integer, and writes it to the database at the path "led". Success or failure messages are printed to the serial monitor, indicating the status of the write operation.

---

## Review and Discuss
Now that your Firebase Authentication is set up and you have learned how to perform user sign-up, sign-in, and manage authentication state, let's discuss any questions or doubts you may have about the process or Firebase in general. 💬

Feel free to customize the code further to suit your needs! If you have any questions or need assistance, don't hesitate to reach out. Happy coding! 🎉