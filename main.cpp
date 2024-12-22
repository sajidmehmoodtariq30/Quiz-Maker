// Header files
#include <iostream>  // For cin and cout
#include <windows.h> // For Sleep function
#include <fstream>   // For file handling

// Namespace for objects like cin and cout and endl
using namespace std;

int totalCourses = 5;
int totalSections = 3;

// Structures

struct User
{
    string username;
    string password;
    string role;
    string name;
};

struct Student
{
    string rollNo;
    string name;
    char section;
    int quizAttempted = 0;
    int *makrsPtr = new int[quizAttempted];
    char Grade = 'F';
    int *coursesPtr = new int[5];
};

struct Teacher
{
    string teacherId;
    string name;
    bool *coursesPtr = new bool[totalCourses];
    bool *sectionsPtr = new bool[totalSections];
};

// Enumerations
enum Courses // Enum for Courses
{
    MATH = 0,
    PHYSICS,
    CHEMISTRY,
    BIOLOGY,
    CS
};

enum Sections // Enum for Sections
{
    SECTION_A = 0,
    SECTION_B,
    SECTION_C
};

// Function prototypes
void displayMainMenu();
bool login(string designation, User &loggedInUser);
string toLowerCase(string str);
bool Validation(const string &username, const string &password, const string &role, User &loggedInUser);
User *getData(const string &location, int &size);
void adminMenu(const User &loggedInUser);
void studentMenu(const User &loggedInUser);
void teacherMenu(const User &loggedInUser);
void addUser();
bool validateUsername(const string &location, const string &username);
void writeUser(User *user);
Teacher *inputTeacterData(Teacher *teacherptr, string username);
string sectionsToString(Sections section);
string courseToString(Courses course);
void writeTeacher(Teacher *teacherptr);
Student *inputStudentData(Student *studentptr, string username);
void writeStudent(Student *studentptr);

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
            cout << "Please Enter your credentials ";
            if (login("admin", loggedInUser))
            {
                cout << "Login Successful" << endl;
                Sleep(2000); // To pause the screen for 2 seconds
                adminMenu(loggedInUser);
            }
            system("pause");
            break;
        case '2': // Teacher
            cout << "Please Enter your credentials ";
            if (login("teacher", loggedInUser))
            {
                cout << "Login Successful" << endl;
                Sleep(2000); // To pause the screen for 2 seconds
                teacherMenu(loggedInUser);
            }
            system("pause");
            break;
        case '3': // Student
            cout << "Please Enter your credentials ";
            if (login("student", loggedInUser))
            {
                cout << "Login Successful" << endl;
                Sleep(2000); // To pause the screen for 2 seconds
                studentMenu(loggedInUser);
            }
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
    cout << "1. To Enter as an Admin" << endl;
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

// Getting username and password from the user
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

    if (data == nullptr)
    {
        cout << "Enter you name: ";
        string name;
        cin.ignore(); // To ignore the previous newline character
        getline(cin, name);
        ofstream file("Data/users.txt");
        file << username << " " << password << " " << role << " " << name << endl;
        file.close();
        data = getData("Data/users.txt", size);
    }

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
    fstream file(location);

    // Count the number of lines
    size = 0;
    // A temporary string created to calculate number of lines
    string temp;
    while (getline(file, temp))
        size++;
    // checking if the file is empty
    if (size == 0)
        return nullptr;
    // Reset the file stream to the beginning
    file.clear();
    file.seekg(0, ios::beg);

    // Allocate memory for User array
    User *data = new User[size];

    // Read the data from the file
    for (int i = 0; i < size; i++)
    {
        file >> data[i].username >> data[i].password >> data[i].role; // Similar to using single cin ad getting multiple inputs in multiple variables
        getline(file, data[i].name);                                  // To get the name of the user
        data[i].username = toLowerCase(data[i].username);
        data[i].password = toLowerCase(data[i].password);
    }

    return data;
}

// Admin Menu
void adminMenu(const User &loggedInUser)
{
    bool flag = true;
    char choice;
    while (flag)
    {
        system("cls");
        // Admin Menu
        cout << "Hello " << loggedInUser.name << " Welcome to Admin Panel" << endl;
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
        case '1': // Add User
            addUser();
            break;
        case '2': // Search User
        {
            string username;
            cout << "Enter username to search: ";
            cin >> username;
            // searchUser("Data/users.txt", username);
            system("pause");
            break;
        }
        case '3': // List Users
            // listUsers("Data/users.txt");
            system("pause");
            break;
        case '4': // Delete User
        {
            // deleteUser("Data/users.txt");
            system("pause");
            break;
        }
        case '5': // Update User
        {
            // editUser("Data/users.txt");
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

// Teacher Menue
void teacherMenu(const User &loggedInUser)
{
    bool flag = true;
    char choice;
    while (flag)
    {
        system("cls");
        cout << "Hello " << loggedInUser.name << " Welcome to Teacher Panel" << endl;
        cout << "Teacher Menu:" << endl;
        cout << "1. Create Quiz" << endl;
        cout << "2. Edit Quiz" << endl;
        cout << "3. Preview Quiz" << endl;
        cout << "4. Assign Quiz" << endl;
        cout << "5. Assign Grades" << endl;
        cout << "6. View Grades" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1': // Create Quiz
            // createQuiz("Data/quizez.txt", loggedInUser.username);
            system("pause");
            break;
        case '2':
            // editQuiz("Data/quizez.txt", loggedInUser.username);
            system("pause");
            break;
        case '3':
            // previewQuiz("Data/quizez.txt" , loggedInUser.username);
            system("pause");
            break;
        case '4': // Assign Quiz
            // assignQuiz("Data/quizez.txt", "Data/students.txt", "Data/assigned.txt", loggedInUser.username);
            Sleep(2000);
            break;
        case '5':
            // assignGrades( "Data/grades.txt","Data/results.txt", loggedInUser.username);
            Sleep(2000);
            break;
        case '6':
            // viewResults("Data/results.txt", "Data/students.txt");
            Sleep(2000);
            break;
        case '7':
            flag = false;
            break;
        default:
            cout << "Invalid choice!" << endl;
            Sleep(1000);
            break;
        }
    }
}

// Student Menue
void studentMenu(const User &loggedInUser)
{
    bool flag = true;
    char choice;
    while (flag)
    {
        system("cls");
        cout << "Hello " << loggedInUser.name << " Welcome to Admin Panel" << endl;
        cout << "Student Menu:" << endl;
        cout << "1. Attempt Quiz" << endl;
        cout << "2. View Grades" << endl;
        cout << "3. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            // attemptQuiz("Data/quizez.txt", "Data/assigned.txt", loggedInUser.username, "Data/results.txt");
            system("pause");
            break;
        case '2':
            // viewGrades("Data/results.txt", loggedInUser.username);
            Sleep(2000); // To pause the screen for 2 seconds
            break;
        case '3':
            flag = false;
            break;
        default:
            cout << "Invalid choice!" << endl;
            Sleep(1000);
            break;
        }
    }
}

// AddUser function
void addUser()
{
    User *userptr = new User;
    Teacher *teacherptr = new Teacher;
    Student *studentptr = new Student;
    do
    {
        cout << "Enter username: ";
        cin >> (*userptr).username;
    } while (!validateUsername("Data/users.txt", (*userptr).username));
    cout << "Enter password: ";
    cin >> (*userptr).password;
    cout << "Enter role: ";
    do
    {
        cin >> (*userptr).role;
        cout << "Enter name: ";
    } while (!((*userptr).role == "admin" || (*userptr).role == "teacher" || (*userptr).role == "student"));
    cin.ignore();
    getline(cin, (*userptr).name);
    writeUser(userptr);
    if ((*userptr).role == "teacher")
    {
        teacherptr = inputTeacterData(teacherptr, (*userptr).username);
        writeTeacher(teacherptr);
    }
    else if ((*userptr).role == "student")
    {
        studentptr = inputStudentData(studentptr, (*userptr).username);
        writeStudent(studentptr);
    }
    delete userptr;
    delete teacherptr;
    delete studentptr;
}

// Validate if the username already exists
bool validateUsername(const string &location, const string &username)
{
    int size = 0;
    User *data = getData(location, size);
    for (int i = 0; i < size; i++)
    {
        if (data[i].username == username)
        {
            delete[] data;
            return false;
        }
    }
    delete[] data;
    return true;
}

// Writing user data to file
void writeUser(User *user)
{
    ofstream file("Data/Users.txt", ios::app);
    file << (*user).username << " " << (*user).password << " " << (*user).role << " " << (*user).name << endl;
    file.close();
}

Teacher *inputTeacterData(Teacher *teacherptr, string username)
{
    teacherptr->teacherId = username;
    cout << "Enter your Name: ";
    getline(cin, teacherptr->name);
    cout << "Assign Courses to Teacher (1 for Yes, 0 for No):\n";
    for (int i = 0; i < totalCourses; i++)
        do
        {
            cout << "Teach " << courseToString((Courses)i) << "? ";
            cin >> teacherptr->coursesPtr[i];
        } while (teacherptr->coursesPtr[i] != 0 && teacherptr->coursesPtr[i] != 1);

    for (int i = 0; i < totalSections; i++)
        do
        {
            cout << "Teach " << sectionsToString((Sections)i) << "?";
            cin >> teacherptr->sectionsPtr[i];
        } while (teacherptr->sectionsPtr[i] != 0 && teacherptr->sectionsPtr[i] != 1);
    return teacherptr;
}

// Function to convert Courses to string bcz the enum was giving index while printing
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

// Function to convert Courses to string bcz enum was giving index while printing
string sectionsToString(Sections section)
{
    switch (section)
    {
    case SECTION_A:
        return "A";
    case SECTION_B:
        return "B";
    case SECTION_C:
        return "C";
    default:
        return "Unknown";
    }
}

// Writing Teacher data to file
void writeTeacher(Teacher *teacherptr)
{
    ofstream teacherFile("Data/teachers.txt", ios::app);
    teacherFile << endl
                << teacherptr->teacherId << " ";
    for (int i = 0; i < totalCourses; i++)
        teacherFile << teacherptr->coursesPtr[i] << " ";
    for (int i = 0; i < totalSections; i++)
        teacherFile << teacherptr->sectionsPtr[i] << " ";
    teacherFile << endl;
    teacherFile.close();
}

// Getting Student Information
Student *inputStudentData(Student *studentptr, string username)
{
    studentptr->rollNo = username;
    do
    {
        cout << "Enter your Section (A, B, C): ";
        cin >> studentptr->section;
    } while (studentptr->section != 'A' && studentptr->section != 'B' && studentptr->section != 'C');
    for (int i = 0; i < totalCourses; i++)
    {
        do
        {
            cout << "Enroll in " << courseToString((Courses)i) << "? ";
            cin >> studentptr->coursesPtr[i];
        } while (studentptr->coursesPtr[i] != 0 && studentptr->coursesPtr[i] != 1);
    }
    return studentptr;
}

// Writing Student data to file
void writeStudent(Student *studentptr)
{
    ofstream studentFile("Data/students.txt", ios::app);
    studentFile
        << studentptr->rollNo << " " << studentptr->section << " " << studentptr->quizAttempted << " ";
    for (int i = 0; i < studentptr->quizAttempted; i++)
        studentFile << studentptr->makrsPtr[i] << " ";
    studentFile << studentptr->Grade << " ";
    for (int i = 0; i < totalCourses; i++)
        studentFile << studentptr->coursesPtr[i] << " ";
    studentFile << endl;
    studentFile.close();
}
