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
   <script type="module">
     // Import the functions you need from the SDKs you need
     import { initializeApp } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-app.js";
     import { getAnalytics } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-analytics.js";

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

     // Initialize Firebase
     const app = initializeApp(firebaseConfig);
     const analytics = getAnalytics(app);
   </script>
   ```

3. **Paste the Script in Your HTML**: Add the copied script tag to your HTML file, ideally within the `<head>` or at the end of the `<body>` section. This script initializes Firebase with your specific configuration.
<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w5.png)

## Step 4: Continue to Firebase Console

1. **Click Continue to Console**: After pasting the script, click the "Continue to console" button. This will take you back to the Firebase console where you can manage your app and access additional Firebase services.
By following these steps, you will have successfully created a web application and set it up in Firebase. You can now proceed to integrate various Firebase services such as Authentication, Firestore, and Hosting into your web application as needed.
<br><br>![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/w6.png)

