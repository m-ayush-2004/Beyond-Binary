# Vscode and Firebase Setup 🚀

Welcome to our technical event! In this session, we will guide you through the installation of Visual Studio Code (VS Code), the Live Server extension, and setting up Firebase on your Google account. Let’s get started! 🎉

# Installation of Visual Studio Code (VS Code) 💻

### Step 1: Download VS Code
Click on the link below to install the latest version of VS Code for the project:  
👉 [Download VS Code](https://code.visualstudio.com/download)

### Step 2: Select the Installer
Choose the appropriate installer for your operating system and run the downloaded executable file.

### Step 3: Follow the Prompts
- Follow the installation prompts.
- Make sure to select **"Add to PATH"** and to create a shortcut for easy accessibility.  
- The installation process may take a few moments.

### Step 4: Launch VS Code
Once installed, open VS Code and navigate to the Extensions view by clicking on the box-like icon on the left sidebar.

### Step 5: Search for Live Server
In the Extensions view, search for **"Live Server"**.

### Step 6: Install Live Server
Click on **Install** to add the Live Server extension, which allows you to preview your web pages without needing a separate text editor! 🌐

# Setting Up Firebase ☁️

### What is Firebase?

Firebase is a powerful Backend-as-a-Service (BaaS) platform developed by Google that provides developers with a suite of tools and services to build, manage, and grow applications efficiently. It offers various features, including real-time databases, user authentication, cloud storage, and hosting, making it easier to develop high-quality apps without extensive backend coding.

Firebase is categorized as a NoSQL database, which means it stores data in JSON-like documents. This allows for flexible data structures and real-time synchronization across all connected clients, ensuring that users see the most up-to-date information even when they are offline. Firebase also supports user authentication through various methods, including email/password, Google, Facebook, and more.

### Step 1: Create a Firebase Project
Go to the [Firebase Console](https://console.firebase.google.com).

### Step 2: Log In to Firebase
To log in to Firebase, follow these steps:
1. Go to the [Firebase Console](https://console.firebase.google.com).
2. Click on **"Go to Console"** in the top right corner.
3. If prompted, sign in with your Google account credentials. If you don’t have a Google account, you will need to create one.
4. Once logged in, you will be directed to your Firebase projects dashboard.
![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f1.png)

### Step 3: Name Your Project
Click on create new project to start with the new project.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f2.png)
### Step 4: Name Your Project
For consistency, let’s name our project **"TechnoVIT-PJT"** and click on **Continue**.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f2.png)
### Step 5: Enable Analytics
Check the box to allow Google Analytics for your project and click **Continue**.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f3.png)
### Step 6: Configure Google Analytics
Choose or create a Google Analytics account. If no account is available, create a new one using the pop-up. Then, select **Create Project**.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f4.png)
### Step 7: Project Ready
Your project will be ready and configured in a minute or two, and you can start coding! 🎉

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f5.png)

### Step 8: Explore the new peoject console

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f6.png)
# Setting Up Rules for Database and CRUD Operations 🔒

### Step 1: Access the Database Section
1. Click on the three horizontal bars (☰) in the top left corner of the Firebase console to open the navigation menu.
![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f7.png)

### Step 2: Navigate to Realtime Database
2. Select **Build** from the menu, then click on **Realtime Database**. This will take you to the section where you can manage your database.

### Step 3: Create a Database
3. Click on **Create Database** and choose **Next**. You will be prompted to select a starting mode for your Firebase Security Rules:
![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f8.png)
   - **Test Mode**: This option allows anyone to read and write data to your database. It’s useful for initial testing but should not be used in production.
   - **Locked Mode**: This option denies all reads and writes from mobile and web clients. Only authenticated application servers can access your database.

For now, select **Test Mode** to get started, and then click on **Enable**.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f9.png)

### Step 4: Database Creation Confirmation
4. Your database will be created and ready for use in just a minute or two! 🎉 You will see a dashboard with options for **Data**, **Rules**, **Backups**, and **Usage**.

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f10.png)
### Step 5: Set Database Rules
5. Go to the **Rules** tab. Here, you will define the access permissions for your database. Paste the following code to allow read and write operations for all users:

   ```json
   {
     "rules": {
       ".read": true,
       ".write": true
     }
   }
   ```
![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f11.png)

   This configuration makes your database publicly accessible, which is suitable for testing but not recommended for production applications. 

### Step 6: Add Data to Your Database
6. To add data, hover over the URL of your database, which will look something like this: `https://beyond-binary-2-default-rtdb.firebaseio.com/`. You should see an **Add** option. Click on it to create a new key-value pair:
   - **Key:** `led_status`
   - **Value:** `0`

![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f12.png)
   After entering the key and value, click on **Add**. This action will store the data in your database, and you’re almost done with setting up Firebase for your project! 💪
![alt](https://github.com/m-ayush-2004/TechnoVit-24/blob/main/assets/f13.png)

### Step 7: Review and Discuss
7. Now that your Firebase project is set up, let's discuss any questions or doubts you may have about the process or Firebase in general. 💬
