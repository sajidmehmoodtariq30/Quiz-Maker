// Header files
#include <iostream>  // For cin and cout
#include <windows.h> // For Sleep function
#include <fstream>   // For file handling

// Namespace for objects like cin and cout and endl
using namespace std;

// Structures

struct User
{
    string username;
    string password;
    string role;
    string name;
};

// Function prototypes
void displayMainMenu();
bool login(string designation, User &loggedInUser);
string toLowerCase(string str);
bool Validation(const string &username, const string &password, const string &role, User &loggedInUser);
User *getData(const string &location, int &size);

// Main function starting point of a cpp program
int main()
{
    char choice;        // To store the choice of the user
    bool flag = true;   // To control the loop
    User loggedInUser;  // To store the logged-in user's information
    system("color 0A"); // Changing the color of the console
    system("cls");      // Clearing the console for previous text
    cout << "Welcome to Quiz Maker" << endl;
    cout << "Created by : Afia, Rehan and Sajid" << endl;
    Sleep(2000);
    do
    {
        // Main Menue
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        // Switch case to open the respective menu
        switch (choice)
        {
        case '1': // Admin
            if (login("admin", loggedInUser))
            {
                cout << "Login Successful" << endl;
                Sleep(2000); // To pause the screen for 2 seconds
                // adminMenu(loggedInUser);
            }
            
            system("pause");
            break;
        case '2': // Teacher
            cout << "Please Enter your credentials:" << endl;
            system("pause");
            break;
        case '3': // Student
            cout << "Please Enter your credentials:" << endl;
            system("pause");
            break;
        case '4': // Exit
            cout << "Exiting..." << endl;
            flag = false;
            break;
        default: // In case of a wrong choice
            cout << "Invalid choice" << endl;
        }
    } while (flag);
    return 0;
}

// Function to display the Main menu
void displayMainMenu()
{
    system("cls");
    cout << "1. TO Enter as an Admin" << endl;
    cout << "2. To Enter as a Teacher" << endl;
    cout << "3. To Enter as a Student" << endl;
    cout << "4. To Exit" << endl;
}

// Function to convert a string to lower case
string toLowerCase(string str)
{
    for (int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}

bool login(string role, User &loggedInUser)
{
    string username, password;
    bool flag = true;
    while (flag) // A while loop to get the username and password untill user enters correct credentials or exits by pressing 1
    {
        cout << "Press 1 to exit" << endl;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        username = toLowerCase(username); // Converting the username to lower case in order to avoid case sensitivity
        password = toLowerCase(password); // Converting the username to lower case in order to avoid case sensitivity
        if (username == "1" || password == "1")
            flag = false;
        else if (Validation(username, password, role, loggedInUser))
            return true;
        else
            cout << "Wrong Credentials" << endl;
        Sleep(2000); // To pause the screen for 2 seconds
    }

    return false;
}

// Function to Validate the entered credentials
bool Validation(const string &username, const string &password, const string &role, User &loggedInUser)
{
    bool isValid = false;
    int size = 0;
    // Getting data from file and storing it in a User pointer
    User *data = getData("Data/users.txt", size);

    // Checking if the entered credentials are correct
    for (int i = 0; i < size; i++)
    {
        if (data[i].username == username && data[i].password == password && data[i].role == role)
        {
            isValid = true;
            loggedInUser = data[i]; // Store the logged-in user's information
            break;
        }
    }
    // Deleting the dynamic data pointer
    delete[] data;
    return isValid;
}

// Getting User data from file
User *getData(const string &location, int &size)
{
    // Loading the File
    ifstream file(location);

    // Count the number of lines
    size = 0;
    // A temporary string created to calculate number of lines
    string temp;
    while (getline(file, temp))
        size++;

    // Reset the file stream to the beginning
    file.clear();
    file.seekg(0, ios::beg);

    // Allocate memory for User array
    User *data = new User[size];

    // Read the data from the file
    for (int i = 0; i < size; i++)
    {
        file >> data[i].username >> data[i].password >> data[i].role >> data[i].name; // Similar to using single cin ad getting multiple inputs in multiple variables
        data[i].username = toLowerCase(data[i].username);
        data[i].password = toLowerCase(data[i].password);
    }

    return data;
}
