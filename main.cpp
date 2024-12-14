// Header Files
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

const int totalCourses = 5;
const int totalSections = 3;

enum Courses
{
    MATH = 0,
    PHYSICS,
    CHEMISTRY,
    BIOLOGY,
    CS
};

string courseToString(Courses course)
{
    switch (course)
    {
    case MATH:
        return "Math";
    case PHYSICS:
        return "Physics";
    case CHEMISTRY:
        return "Chemistry";
    case BIOLOGY:
        return "Biology";
    case CS:
        return "Computer Science";
    default:
        return "Unknown";
    }
}

enum Sections
{
    SECTION_A = 0,
    SECTION_B,
    SECTION_C
};

struct User
{
    string username; // Username of the user
    string password; // Password of the user
    string role;     // Role: "Admin", "Teacher", or "Student"
    string name;     // Name of the user
};

struct Student
{
    string rollNo;
    int QuizAttempted;
    int QuizScore;
    char grade;
    char section;
    bool *coursesPtr = new bool[totalCourses];
    User *studentPtr = new User;
};

struct Teacher
{
    bool *sectionsPtr = new bool[totalSections];
    bool *coursesPtr = new bool[totalCourses];
    User *teacherPtr = new User;
};

struct Question
{
    string question;
    string options[4];
    int correctOption;
    bool isCorrect;
};

struct Quiz
{
    string quizName;
    string courseName;
    int totalQuestions;
    int totalMarks;
    Question *quizPtr = nullptr;
};

// Function to input username and password
bool login(string role, User &loggedInUser);
// Function to Validate the entered credentials
bool Validation(const string &username, const string &password, const string &role, User &loggedInUser);
// Getting input from file
User *getData(const string &location, int &size);

// Function to add a new user
void addUser(const string &location);
// Function to search for a user by username
void searchUser(const string &location, const string &username);
// Function to list users based on different criteria
void listUsers(const string &location);
// Function to delete a user by username
void deleteUser(const string &location, const string &username, const User &loggedInUser);
// Function to update user details
void updateUser(const string &location, const string &username);
// Function for admin menu
void adminMenu(const User &loggedInUser);

// Main Function
int main()
{
    bool flag = true;        // To store user choice
    char choice;             // To store user choice
    bool passwordValidation; // To store password validation
    User loggedInUser;       // To store the logged-in user's information

    while (flag)
    {
        // To clear the screen
        system("cls");
        // Menu
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
            if (login("admin", loggedInUser))
            {
                cout << "Login Successful" << endl;
                cout << "Welcome, " << loggedInUser.name << "!" << endl;
                adminMenu(loggedInUser);
            }
            break;
        case '2':
            system("cls");
            cout << "Welcome to Teacher Panel Please Enter your Credentials or ";
            if (login("teacher", loggedInUser))
            {
                cout << "Login Successful" << endl;
                cout << "Welcome, " << loggedInUser.name << "!" << endl;
                // teacherMenu(loggedInUser);
            }
            break;
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
bool login(string role, User &loggedInUser)
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
        else if (Validation(username, password, role, loggedInUser))
            return true;
        else
            cout << "Wrong Credentials" << endl;
        Sleep(2000);
    }

    return false;
}

// Function to Validate the entered credentials
bool Validation(const string &username, const string &password, const string &role, User &loggedInUser)
{
    bool isValid = false;
    int size = 0;
    // Getting data from file and storing it in a User pointer
    User *data = getData("Data/users.data", size);

    for (int i = 0; i < size; i++)
    {
        if (data[i].username == username && data[i].password == password && data[i].role == role)
        {
            isValid = true;
            loggedInUser = data[i]; // Store the logged-in user's information
            break;
        }
    }
    delete[] data;
    return isValid;
}

// Getting input from file
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
        file >> data[i].username >> data[i].password >> data[i].role >> data[i].name;

    return data;
}

// Function to add a new user
void addUser(const string &location)
{
    ofstream file(location, ios::app);
    User newUser;
    system("cls");
    cout << "Enter Username: ";
    cin >> newUser.username;
    cout << "Enter Password: ";
    cin >> newUser.password;
    cout << "Enter Role (Admin/Teacher/Student): ";
    cin >> newUser.role;
    cout << "Enter Name: ";
    cin >> newUser.name;
    file << endl
         << newUser.username << " " << newUser.password << " " << newUser.role << " " << newUser.name;
    file.close();

    // Handle Teacher-Specific Data
    if (newUser.role == "teacher")
    {
        bool courses[totalCourses];
        bool sections[totalSections];
        cout << "Assign Courses to Teacher (1 for Yes, 0 for No):\n";
        for (int i = 0; i < totalCourses; i++)
        {
            cout << "Teach " << courseToString((Courses)i) << "? ";
            cin >> courses[i];
        }

        cout << "Assign Sections to Teacher (1 for Yes, 0 for No):\n";
        for (int i = 0; i < totalSections; i++)
        {
            cout << "Teach " << (Sections)i << "? ";
            cin >> sections[i];
        }

        // Save teacher-specific data
        ofstream teacherFile("Data/teacher.data", ios::app);
        teacherFile << newUser.username << " ";
        for (int i = 0; i < totalCourses; i++)
            teacherFile << courses[i] << " ";
        for (int i = 0; i < totalSections; i++)
            teacherFile << sections[i] << " ";
        teacherFile << endl;
        teacherFile.close();
        cout << "Teacher-specific data saved successfully!" << endl;
    }

    // Handle Student-Specific Data
    else if (newUser.role == "student")
    {
        bool courses[totalCourses];
        char section;
        cout << "Enroll Student in Courses (1 for Yes, 0 for No):\n";
        for (int i = 0; i < totalCourses; i++)
        {
            cout << "Enroll in " << courseToString((Courses)i) << "? ";
            cin >> courses[i];
        }

        cout << "Assign Section to Student (A/B/C): ";
        cin >> section;

        // Save student-specific data
        ofstream studentFile("Data/student.data", ios::app);
        studentFile << newUser.username << " " << section << " ";
        for (int i = 0; i < totalCourses; i++)
            studentFile << courses[i] << " ";
        studentFile << endl;
        studentFile.close();
        cout << "Student-specific data saved successfully!" << endl;
    }

    cout << "User added successfully!" << endl;
    Sleep(1000);
}

// Function to search for a user by username
void searchUser(const string &location, const string &username)
{
    int size = 0;
    User *data = getData(location, size);
    bool found = false;
    for (int i = 0; i < size; i++)
        if (data[i].username == username)
        {
            cout << "User found!" << endl;
            cout << "Username: " << data[i].username << endl;
            cout << "Role: " << data[i].role << endl;
            cout << "Name: " << data[i].name << endl;
            found = true;
            break;
        }

    if (!found)
        cout << "User not found!" << endl;
    delete[] data;
}

// Function to list users based on different criteria
void listUsers(const string &location)
{
    system("cls");
    int size = 0;
    User *data = getData(location, size);
    char choice;
    cout << "List Users Menu:" << endl;
    cout << "1. List all users" << endl;
    cout << "2. List user by username" << endl;
    cout << "3. List user by role" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case '1':
        for (int i = 0; i < size; i++)
            cout << "Username: " << data[i].username << ", Role: " << data[i].role << ", Name: " << data[i].name << endl;
        break;
    case '2':
    {
        string username;
        cout << "Enter username: ";
        cin >> username;
        bool found = false;
        for (int i = 0; i < size; i++)
            if (data[i].username == username)
            {
                cout << "Username: " << data[i].username << ", Role: " << data[i].role << ", Name: " << data[i].name << endl;
                found = true;
                break;
            }

        if (!found)
            cout << "User not found!" << endl;
        break;
    }
    case '3':
    {
        string role;
        cout << "Enter role (Admin/Teacher/Student): ";
        cin >> role;
        bool found = false;
        for (int i = 0; i < size; i++)
            if (data[i].role == role)
            {
                cout << "Username: " << data[i].username << ", Role: " << data[i].role << ", Name: " << data[i].name << endl;
                found = true;
            }

        if (!found)
            cout << "No users found with the role " << role << "!" << endl;
        break;
    }
    default:
        cout << "Invalid choice!" << endl;
        break;
    }
    delete[] data;
}

// Function to delete a user by username
void deleteUser(const string &location, const string &username, const User &loggedInUser)
{
    if (username == loggedInUser.username)
    {
        cout << "Error: You cannot delete yourself!" << endl;
        return;
    }

    int size = 0;
    User *data = getData(location, size);
    bool found = false;
    int index = -1;

    for (int i = 0; i < size; i++)
        if (data[i].username == username)
        {
            found = true;
            index = i;
            break;
        }

    if (found)
    {
        for (int i = index; i < size - 1; i++)
            data[i] = data[i + 1];

        size--;
        ofstream file(location);
        for (int i = 0; i < size; i++)
            file << data[i].username << " " << data[i].password << " " << data[i].role << " " << data[i].name << endl;
        file.close();
        cout << "User deleted successfully!" << endl;
        Sleep(1000);
    }
    else
        cout << "User not found!" << endl;

    delete[] data;
}

// Function to update user details
void updateUser(const string &location, const string &username)
{
    int size = 0;
    User *data = getData(location, size);
    bool found = false;

    for (int i = 0; i < size; i++)
    {
        if (data[i].username == username)
        {
            cout << "Enter New Password: ";
            cin >> data[i].password;
            cout << "Enter New Role: ";
            cin >> data[i].role;
            cout << "Enter New Name: ";
            cin >> data[i].name;
            break;
        }
    }

    ofstream file("Data/Users.dat");
    for (int i = 0; i < size; i++)
        file << data[i].username << " " << data[i].password << " " << data[i].role << " " << data[i].name << endl;

    delete[] data;
    file.close();
}

// Function for admin menu
void adminMenu(const User &loggedInUser)
{
    bool flag = true;
    char choice;
    while (flag)
    {
        system("cls");
        cout << "Admin Menu:" << endl;
        cout << "1. Add User" << endl;
        cout << "2. Search User" << endl;
        cout << "3. List Users" << endl;
        cout << "4. Delete User" << endl;
        cout << "5. Update User" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            addUser("Data/users.data");
            break;
        case '2':
        {
            string username;
            cout << "Enter username to search: ";
            cin >> username;
            searchUser("Data/users.data", username);
            system("pause");
            break;
        }
        case '3':
            listUsers("Data/users.data");
            system("pause");
            break;
        case '4':
        {
            string username;
            cout << "Enter username to delete: ";
            cin >> username;
            deleteUser("Data/users.data", username, loggedInUser);
            system("pause");
            break;
        }
        case '5':
        {
            string username;
            cout << "Enter username to update: ";
            cin >> username;
            updateUser("Data/users.data", username);
            system("pause");
            break;
        }
        case '6':
            flag = false;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }
}