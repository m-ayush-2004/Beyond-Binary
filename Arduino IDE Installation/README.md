# Arduino Installation Guide 🚀

Follow these steps to install the Arduino IDE, which we'll use for programming our NodeMCU device.

## Step 1: Download the Arduino IDE

Choose the appropriate version for your operating system:

- **Windows:** [Download Arduino 1.8.19 for Windows](https://downloads.arduino.cc/arduino-1.8.19-windows.exe)
- **macOS:** [Download Arduino 1.8.19 for macOS](https://downloads.arduino.cc/arduino-1.8.19-macosx.zip)

## Step 2: Install the Arduino IDE

1. **Run the Installer:**
   - After downloading, run the installer for your operating system.
   
2. **Follow the Installation Prompts:**
   - Continue through the installation process by clicking `Next` on each prompt.
   - **Tip:** Ensure you select the option to "Add shortcut to desktop" for easier access.

## Step 3: Launch the Arduino IDE

Once the installation is complete:

1. **Open the Arduino IDE:**
   - Locate the Arduino shortcut on your desktop or find it in your applications folder.
   - This is where we will be coding for our NodeMCU device.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/a1.png)

## Step 4: Customize the Arduino IDE for ESP8266 Boards 🛠️

Before we start with our IoT journey, we need to customize the software to integrate the ESP8266 series of boards into the Arduino IDE.

### Follow these steps:

1. **Open Preferences:**
   - Go to `File` > `Preferences` in the Arduino IDE, or use the shortcut `Ctrl + ,` to open the Preferences window.
![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/a2.png)
   
2. **Add ESP8266 Board Manager URL:**
   - In the Preferences window, locate the `Additional Boards Manager URLs` text box.
   - Paste the following link into the text box:
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - This URL allows the Arduino IDE to integrate the ESP8266 board series, enabling you to download the NodeMCU board along with its libraries and packages.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/a3.png)

3. **Apply Changes:**
   - Click `OK` to close the Preferences window.
   - Restart the Arduino IDE to apply the changes.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/a3.png)

## Step 5: Install ESP8266 Packages 📦

To select the ESP8266 Wi-Fi module as our operational board, you first need to install all the necessary packages.

### Follow these steps:

1. **Open Boards Manager:**
   - Navigate to `Tools` > `Board` > `Boards Manager...` in the Arduino IDE.
   
![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/a4.png)

2. **Search for ESP8266:**
   - In the Boards Manager window that pops up, type "esp8266" in the search bar at the top.
   
3. **Install ESP8266 Packages:**
   - From the search results, locate the boards by "ESP8266 Community."
   - Click `Install` to download and install the necessary packages.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/a5.png)
## Step 6: Select the ESP8266 Board

1. **Choose Your Board:**
   - After installation, go back to `Tools` > `Board`, and select the specific ESP8266 board (e.g., NodeMCU 1.0) that you are working with.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/a6.png)
You are now ready to start programming your NodeMCU and dive into the world of IoT! 🌟
