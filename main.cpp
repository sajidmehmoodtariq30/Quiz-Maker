// Header files
#include <iostream> // For cin and cout
#include <windows.h> // For Sleep function

// Namespace for objects like cin and cout and endl
using namespace std;

// Function prototypes
void displayMenu();

// Main function starting point of a cpp program
int main()
{
    system("cls");
    char choice;
    bool flag  = true;
    cout << "Welcome to Quiz Maker" << endl;
    cout << "Created by : Afia, Rehan and Sajid" << endl;
    Sleep(2000);
    do
    {
        // Main Menue
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "Admin" << endl;
            system("pause");
            break;
        case '2':
            cout << "Teacher" << endl;
            system("pause");
            break;
        case '3':
            cout << "Student" << endl;
            system("pause");
            break;
        case '4':
            cout << "Exiting..." << endl;
            flag = false;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (flag);
    return 0;
}

// Function to display the Main menu
void displayMenu()
{
    system("cls");
    cout << "1. TO Enter as an Admin" << endl;
    cout << "2. To Enter as a Teacher" << endl;
    cout << "3. To Enter as a Student" << endl;
    cout << "4. To Exit" << endl;
}