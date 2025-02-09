To create a web application and set it up in Firebase, follow these detailed steps:

## Step 1: Access Firebase Project Settings

1. **Go to Project Settings in Firebase**: Open the Firebase console and navigate to your project. Click on the settings gear icon located in the top left corner of the Firebase console.

2. **Navigate to the General Section**: In the Project Settings menu, select the "General" tab. This section contains all the necessary configurations for your project.
<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w1.png)

## Step 2: Register Your Web App

1. **Locate Your App**: Scroll down to the "Your apps" section where you can see existing applications linked to your Firebase project.
<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w2.png)

2. **Click on Web App Icon**: Click on the web icon (</>) to start the process of adding a new web application.
<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w2.png)

3. **Name Your Application**: Enter a name for your application. Note that Firebase Hosting is optional at this stage, so you can choose to enable it later if desired.
<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w3.png)

4. **Click on Register App**: After naming your app, click the "Register App" button. This action will initiate the setup process for your Firebase web application, which may take a few moments.
<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w4.png)

## Step 3: Set Up Firebase Configuration

1. **Select Use a Script**: Once the app is registered, you will be prompted to select how you want to add Firebase to your web application. Choose the option to use a script.
<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w5.png)

2. **Copy the Script Tag**: A script tag will be generated containing your Firebase configuration details. This includes important information such as your API key, Auth domain, Database URL, Project ID, Storage bucket, Messaging sender ID, App ID, and Measurement ID. 

   Example script to be copied (note that your values will differ):

   ```html
     // Your web app's Firebase configuration
     const firebaseConfig = {
       apiKey: "AIzaSyAxrJCnE9B2MSC7Vp31bgYbGcxPe5I__Qo",
       authDomain: "technovit-24.firebaseapp.com",
       databaseURL: "https://technovit-24-default-rtdb.firebaseio.com",
       projectId: "technovit-24",
       storageBucket: "technovit-24.appspot.com",
       messagingSenderId: "534890112185",
       appId: "1:534890112185:web:01dd39bda5a2f77293a768",
       measurementId: "G-77NY3D7ZTM"
     };
   ```

3. **Paste the Script in Your Java Script File**: Add the copied script tag to your HTML file, ideally within the `<head>` or at the end of the `<body>` section. This script initializes Firebase with your specific configuration.
<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w5.png)

## Step 4: Continue to Firebase Console

1. **Click Continue to Console**: After pasting the script, click the "Continue to console" button. This will take you back to the Firebase console where you can manage your app and access additional Firebase services.
By following these steps, you will have successfully created a web application and set it up in Firebase. You can now proceed to integrate various Firebase services such as Authentication, Firestore, and Hosting into your web application as needed.
<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w6.png)


## Create Real-Time Database Structure

1. **Go to the Real-Time Database**: In the Firebase console, navigate to the "Realtime Database" section.

2. **Create the Structure**: Create the structure as shown in the image. You need to set up the following paths:
   - `https://technovit-24-default-rtdb.firebaseio.com/distance/id/x`
   - `https://technovit-24-default-rtdb.firebaseio.com/distance/id/y`

<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w7.png)
   The steps to create this structure can be demonstrated on the projector.

---

## Implement Live Area Graphs with Chart.js

### What is Chart.js?

Chart.js is a powerful open-source JavaScript library that allows developers to create interactive and visually appealing charts and graphs using HTML5 canvas elements. It provides a simple API for creating various types of charts, including line, bar, pie, and area charts, making it an excellent choice for data visualization in web applications.

### What is npm?

npm (Node Package Manager) is a package manager for JavaScript that allows developers to easily install, manage, and share libraries and dependencies for their projects. It is widely used in the JavaScript ecosystem, particularly for projects that use Node.js. With npm, you can install Chart.js and other libraries with a simple command, streamlining the development process.

### Fetching Data from Firebase

In our application, we will fetch data from the Firebase Realtime Database to update our area graph dynamically. The following JavaScript code demonstrates how to initialize Firebase, create a Chart.js instance, and update the chart with data fetched from Firebase.

#### HTML File for Web Page

```html
<!DOCTYPE html>
<html>

<head>
    <title>Area Graph</title>
    <style>
        body {
            background-color: #000000; /* Sets the background color of the body to black */
        }
    </style>
    <!-- Include the CanvasJS library for creating charts -->
    <script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>
    <!-- Include Firebase SDK for using Firebase services -->
    <script src="https://www.gstatic.com/firebasejs/8.2.1/firebase.js"></script>
    <!-- Include Chart.js library for creating charts -->
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
</head>

<body>
    <!-- Canvas element where the chart will be rendered -->
    <canvas id="myChart"></canvas>
    <script src="graph.js" type="module"></script> <!-- Link to the JavaScript file for chart logic -->
</body>

</html>
```

#### JavaScript File for Web Page (graph.js)

```javascript
// Import necessary functions from Firebase SDK
import { initializeApp } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-app.js";
import { getAnalytics } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-analytics.js";

// Firebase configuration object containing the project's credentials
const firebaseConfig = {
    apiKey: "AIzaSyAxrJCnE9B2MSC7Vp31bgYbGcxPe5I__Qo",
    authDomain: "technovit-24.firebaseapp.com",
    databaseURL: "https://technovit-24-default-rtdb.firebaseio.com",
    projectId: "technovit-24",
    storageBucket: "technovit-24.appspot.com",
    messagingSenderId: "534890112185",
    appId: "1:534890112185:web:01dd39bda5a2f77293a768",
    measurementId: "G-77NY3D7ZTM"
};

// Initialize Firebase
firebase.initializeApp(firebaseConfig);
const database = firebase.database(); // Reference to the Firebase Realtime Database

// Get the context of the canvas element to draw the chart
const ctx = document.getElementById('myChart').getContext('2d');
let chart; // Variable to hold the chart instance
let dataPoints = []; // Array to store data points fetched from Firebase
let dataArray = []; // Array to temporarily hold data points
let xValues = []; // Array to hold x-axis values
let yValues = []; // Array to hold y-axis values

// Create a new Chart instance using Chart.js
chart = new Chart(ctx, {
    type: 'line', // Specifies the type of chart (line chart)
    data: {
        labels: xValues, // Labels for the x-axis
        datasets: [{
            fill: { // Configuration for filling the area under the line
                target: 'origin', // Fill area from the line to the origin
                above: 'rgb(255, 0, 0,0.2)',   // Color for the area above the line (red with transparency)
                below: 'rgb(0, 0, 255,0.7)'    // Color for the area below the line (blue with transparency)
            },
            label: 'Data Points', // Label for the dataset
            data: yValues, // Data for the y-axis
            backgroundColor: 'rgba(255, 99, 132, 0.8)', // Background color of the area under the line
            borderColor: 'rgba(255, 99, 132, 1)', // Color of the line
            borderWidth: 1 // Width of the line
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true // Ensures the y-axis starts at zero
            }
        }
    }
});

// Set an interval to update the chart data every 9 seconds
setInterval(() => {
    // Listen for changes in the "distance" reference in the Firebase database
    database.ref("distance").on("value", (snapshot) => {
        dataPoints = snapshot.val(); // Get the current value of the "distance" reference

        // Clear the arrays to prepare for new data
        dataArray.length = 0; // Clear dataArray
        xValues.length = 0; // Clear xValues
        yValues.length = 0; // Clear yValues

        // Populate the dataArray with the values from the snapshot
        for (const key in dataPoints) {
            dataArray.push(dataPoints[key]); // Push each data point into dataArray
        }

        // Populate xValues and yValues arrays with corresponding data
        dataArray.forEach((dataPoint) => {
            xValues.push(dataPoint.x); // Push x value to xValues
            yValues.push(dataPoint.y); // Push y value to yValues
        });

        // Update the chart with the new data
        chart.data.datasets[0].data = yValues; // Update the dataset with new y values
        chart.data.labels = xValues; // Update the labels with new x values
        chart.update(); // Refresh the chart to reflect the new data
    });
}, 9000); // Repeat the above process every 9000 milliseconds (9 seconds)
```

##Results of what we just created
---
<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w8.png)


an area graph that updates every 9 seconds taking data fromglobally hosted firebase system

isnt it amazing?

## Conclusion

By following the steps outlined in this README, you will have successfully set up a web application that utilizes Firebase for real-time data storage and Chart.js for dynamic data visualization. This project serves as a foundation for building more complex applications that require real-time data handling and interactive graphical representations. Happy coding!

Feel free to customize the code further to suit your needs! If you have any questions or need assistance, don't hesitate to reach out. Happy coding! 🎉
