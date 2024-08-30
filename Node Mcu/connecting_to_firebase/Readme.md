
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
 

## Review and Discuss
Now that your Firebase Authentication is set up and you have learned how to perform user sign-up, sign-in, and manage authentication state, let's discuss any questions or doubts you may have about the process or Firebase in general. 💬
