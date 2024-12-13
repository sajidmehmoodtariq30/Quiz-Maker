// Header Files
#include <iostream>
#include <windows.h>

using namespace std;

// Function to input username and password
bool login(string role);
// Function to Validate the entered credentials
bool Validation(string username, string password, string role);

// Main Function
int main()
{
    bool flag = true;        // To strore user choice
    char choice;              // To store user choice
    bool passwordValidation; // To store password validation
    while (flag)
    {
        // To clear the screen
        system("cls");
        // Menue
        cout << "To Enter as an Admin press 1" << endl;
        cout << "To Enter as a Teacher Press 2" << endl;
        cout << "To Enter as a Student Press 3" << endl;
        cout << "To Exit Press 4" << endl;
        cout << "Enter Your Choice: ";
        // User Choice
        cin >> choice;

        switch (choice)
        {
        case '1':
            system("cls");
            cout << "Welcome to Admin Panel Please Enter your Credentials or ";
            if (login("admin"))
                cout << "Login Successfull" << endl;
            else
                cout << "Login Failed" << endl;
            break;
        case '2':
            cout << "Teacher" << endl;
            break;
        case '3':
            cout << "Student" << endl;
            break;
        case '4':
            flag = false;
            break;
        default:
            cout << "Invalid Choice" << endl;
            break;
        }
    }
    return 0;
}

// Function to input username and password
bool login(string role)
{
    string username, password;
    bool flag = true;
    while (flag)
    {
        cout << "Press 1 to exit" << endl;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        if (username == "1" || password == "1")
            flag = false;
        else if (Validation(username, password, role))
            return true;
        else
            cout << "Wrong Credentials" << endl;
        Sleep(2000);
    }

    return false;
}
// Function to Validate the entered credentials
bool Validation(string username, string password, string role)
{
    if (role == "admin")
        if (username == "admin" && password == "admin")
            return true;
    return false;
}