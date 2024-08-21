
// Import necessary functions from Firebase SDK
import { initializeApp } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-app.js";
import { getAnalytics } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-analytics.js";

// Firebase configuration object containing the project's credentials
const firebaseConfig = {
    apiKey: "AIzaSyAxrJCnE9B2MSC7Vp31bgYbGcxPe5I__Qo", // API key for Firebase project
    authDomain: "technovit-24.firebaseapp.com", // Auth domain for Firebase authentication
    databaseURL: "https://technovit-24-default-rtdb.firebaseio.com", // URL for the Firebase Realtime Database
    projectId: "technovit-24", // Unique identifier for the Firebase project
    storageBucket: "technovit-24.appspot.com", // Cloud Storage bucket for the project
    messagingSenderId: "534890112185", // Sender ID for Firebase Cloud Messaging
    appId: "1:534890112185:web:01dd39bda5a2f77293a768", // Unique identifier for the app
    measurementId: "G-77NY3D7ZTM" // Measurement ID for Google Analytics
};
// Your web app's Firebase configuration
// var firebaseConfig = {
//     apiKey: "<API_KEY>",
//     authDomain: "<AUTH_DOMAIN>",
//     databaseURL: "<DATABASE_URL>",
//     projectId: "<PROJECT_ID>",
//     storageBucket: "<STORAGE_BUCKET>",
//     messagingSenderId: "<MESSAGING_SENDER_ID>",
//     appId: "<APP_ID>"
// };
// Initialize Firebase with the provided configuration
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
