// Header Files
// For input output operations
#include <iostream>
// For sleep function
#include <windows.h>
// For file operations
#include <fstream>
// For string operations
#include <string>

using namespace std;
// Total Courses and Sections
const int totalCourses = 5;
const int totalSections = 3;

// Enum for Courses
enum Courses
{
    MATH = 0,
    PHYSICS,
    CHEMISTRY,
    BIOLOGY,
    CS
};

// Function to convert Courses to string
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

// Enum for Sections
enum Sections
{
    SECTION_A = 0,
    SECTION_B,
    SECTION_C
};

// User Structure
struct User
{
    string username; // Username of the user
    string password; // Password of the user
    string role;     // Role: "Admin", "Teacher", or "Student"
    string name;     // Name of the user
};

// Student Structure
struct Student
{
    string rollNo;                             // Roll Number of the student
    int QuizAttempted;                         // Number of Quizzes Attempted
    int QuizScore;                             // Score of the Quiz
    char grade;                                // Grade of the student
    char section;                              // Section of the student
    bool *coursesPtr = new bool[totalCourses]; // Courses enrolled by the student
    User *studentPtr = new User;               // User pointer for the student
};

// Teacher Structure
struct Teacher
{
    bool *sectionsPtr = new bool[totalSections]; // Sections taught by the teacher
    bool *coursesPtr = new bool[totalCourses];   // Courses taught by the teacher
    User *teacherPtr = new User;                 // User pointer for the teacher
};

struct Question // Quiz Structure
{
    string question;   // Question
    string options[4]; // Options
    int correctOption; // Correct Option
    bool isCorrect;    // Is the answer correct
};

struct Quiz // Quiz Structure
{
    string quizName;             // Name of the Quiz
    string courseName;           // Name of the Course
    int totalQuestions;          // Total Questions
    int totalMarks;              // Total Marks
    Question *quizPtr = nullptr; // Pointer to the Quiz
};

// Function to input username and password
bool login(string role, User &loggedInUser);
// Function to Validate the entered credentials
bool Validation(const string &username, const string &password, const string &role, User &loggedInUser);
// Getting input from file
User *getData(const string &location, int &size);

// Function for admin menu
void adminMenu(const User &loggedInUser);
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

// Teacher Menu
void teacherMenu(const User &loggedInUser);
// Function to accomodate quiz creation
void createQuiz(const string &location);
// Student Menu
void studentMenu(const User &loggedInUser);
// Function to accomodate quiz attempt
void attemptQuiz(const string &quizLocation, const string &studentDataLocation, const string &username);

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
        // Calling appropriate functions depending upon the choice of user
        switch (choice)
        {
        case '1': // Admin
            // For clearing previous output
            system("cls");
            cout << "Please Enter your Credentials or ";
            if (login("admin", loggedInUser))
            {
                cout << "Login Successful" << endl;
                // To pause the screen for 2 seconds bcz the menue functions uses clrscreen

                Sleep(2000);
                adminMenu(loggedInUser);
            }
            break;
        case '2': // Teacher
            system("cls");
            cout << "Welcome to Teacher Panel Please Enter your Credentials or ";
            if (login("teacher", loggedInUser))
            {
                cout << "Login Successful" << endl;
                // To pause the screen for 2 seconds bcz the next functions uses clrscreen
                Sleep(2000);
                teacherMenu(loggedInUser);
            }
            break;
        case '3': // Student
            system("cls");
            cout << "Welcome to Student Panel Please Enter your Credentials or ";
            if (login("student", loggedInUser))
            {
                cout << "Login Successful" << endl;
                // To pause the screen for 2 seconds bcz the next functions uses clrscreen
                Sleep(2000);
                studentMenu(loggedInUser);
            }
            break;
        case '4': // Exit
            flag = false;
            break;
        default: // Invalid Case
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
    // A while loop to get the username and password untill user enters correct credentials or exits
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
        // To pause the screen for 2 seconds bcz the next functions uses clrscreen
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
    int size = 0;
    // Creating a new User
    User newUser;
    bool check = false;
    // opening the file to append data
    ofstream file(location, ios::app);
    system("cls");
    // Getting the user details
    cout << "Enter User Details:" << endl;
    // Making sure the username is unique
    do
    {
        cout << "Enter Username: ";
        cin >> newUser.username;
        // Getting data from file and storing it in a User pointer
        User *data = getData("Data/users.data", size);

        // Checking if the entered credentials are correct
        for (int i = 0; i < size; i++)
        {
            if (data[i].username == newUser.username)
            {
                cout << "Username already exists!" << endl;
                check = true;
                break;
            }
        }
        delete[] data;
    } while (check);
    cout << "Enter Password: ";
    cin >> newUser.password;
    cout << "Enter Role (Admin/Teacher/Student): ";
    cin >> newUser.role;
    cout << "Enter Name: ";
    cin >> newUser.name;
    // Writing the user details to the file
    file << endl
         << newUser.username << " " << newUser.password << " " << newUser.role << " " << newUser.name;
    file.close();

    // Handle Teacher-Specific Data
    if (newUser.role == "teacher")
    {
        // Openening the file to append data
        ofstream teacherFile("Data/teacher.data", ios::app);
        teacherFile << newUser.username << " ";
        // Creating arrays for courses and sections
        bool courses[totalCourses];
        bool sections[totalSections];
        // Getting the courses and sections the teacher teaches
        cout << "Assign Courses to Teacher (1 for Yes, 0 for No):\n";
        for (int i = 0; i < totalCourses; i++)
        {
            cout << "Teach " << courseToString((Courses)i) << "? ";
            cin >> courses[i];
            teacherFile << courses[i] << " ";
        }

        cout << "Assign Sections to Teacher (1 for Yes, 0 for No):\n";
        for (int i = 0; i < totalSections; i++)
        {
            cout << "Teach " << (Sections)i << "? ";
            cin >> sections[i];
            teacherFile << sections[i] << " ";
        }

        teacherFile << endl;
        teacherFile.close();
    }

    // Handle Student-Specific Data
    else if (newUser.role == "student")
    {
        char section;
        bool courses[totalCourses];
        // Openening the file to append data
        ofstream studentFile("Data/student.data", ios::app);
        // Getting the section and courses the student is enrolled in
        cout << "Assign Section to Student (A/B/C): ";
        cin >> section;
        // Writing the student details to the file
        studentFile << newUser.username << " " << section << " ";
        cout << "Enroll Student in Courses (1 for Yes, 0 for No):\n";
        for (int i = 0; i < totalCourses; i++)
        {
            cout << "Enroll in " << courseToString((Courses)i) << "? ";
            cin >> courses[i];
            studentFile << courses[i] << " ";
        }

        // Save student-specific data
        studentFile << endl;
        studentFile.close();
    }

    cout << "User added successfully!" << endl;
    Sleep(1000);
}

// Function to search for a user by username
void searchUser(const string &location, const string &username)
{
    int size = 0;
    // Getting data from file
    User *data = getData(location, size);
    bool found = false;
    // Searching for the user
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
    ifstream file(location);
    string choice;
    cout << "Choose an option:\n";
    cout << "1. List All Users\n";
    cout << "2. List Users with the Same Name\n";
    cout << "3. List Students Enrolled in a Specific Course\n";
    cout << "4. List Students in a Specific Section\n";
    cout << "5. List Teachers in a Specific Section\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == "1") // Listing all users
    {
        User user;
        while (file >> user.username >> user.password >> user.role >> user.name)
            cout << "Username: " << user.username << ", Role: " << user.role << ", Name: " << user.name << endl;
    }
    else if (choice == "2") // Listing users with the same name
    {
        string name;
        cout << "Enter the name to filter by: ";
        cin >> name;

        User user;
        // Searching for the user with the same name
        while (file >> user.username >> user.password >> user.role >> user.name)
            if (user.name == name)
                cout << "Username: " << user.username << ", Role: " << user.role << ", Name: " << user.name << endl;
    }
    else if (choice == "3") // Listing students enrolled in a specific course
    {
        int course;
        cout << "Choose a course:\n";
        for (int i = 0; i < totalCourses; i++)
            cout << i << ". " << courseToString((Courses)i) << endl;
        cin >> course;

        ifstream studentFile("Data/student.data");
        string username, section;
        bool courses[totalCourses];

        while (studentFile >> username >> section)
        {
            for (int i = 0; i < totalCourses; i++)
                studentFile >> courses[i];

            if (courses[course])
                cout << "Username: " << username << ", Section: " << section << endl;
        }
        studentFile.close();
    }
    else if (choice == "4") // Listing students in a specific section
    {
        char section;
        cout << "Enter the section (A/B/C): ";
        cin >> section;

        ifstream studentFile("Data/student.data");
        string username;
        char studentSection;

        while (studentFile >> username >> studentSection)
            if (studentSection == section)
                cout << "Username: " << username << ", Section: " << studentSection << endl;

        studentFile.close();
    }
    else if (choice == "5") // Listing teachers in a specific section
    {
        char section;
        // Making sure that the sections are A, B, or C
        do
        {
            cout << "Enter the section (A/B/C): ";
            cin >> section;
        } while (section != 'A' && section != 'B' && section != 'C');

        ifstream teacherFile("Data/teacher.data");
        string username;
        bool sections[totalSections];

        while (teacherFile >> username)
        {
            for (int i = 0; i < totalSections; i++)
                teacherFile >> sections[i];

            if (sections[section - 'A']) // bcz section is a character
                cout << "Username: " << username << endl;
        }
        teacherFile.close();
    }
    else
    {
        cout << "Invalid choice!" << endl;
    }

    file.close();
    system("pause");
}

// Function to delete a user by username
void deleteUser(const string &location, const string &username, const User &loggedInUser)
{
    // Checking if the user is trying to delete himself
    if (username == loggedInUser.username)
    {
        cout << "Error: You cannot delete yourself!" << endl;
        Sleep(1000);
        return;
    }

    int size = 0;
    User *data = getData(location, size);
    bool found = false;
    int index = -1;
    // Searching for the user
    for (int i = 0; i < size; i++)
        if (data[i].username == username)
        {
            found = true;
            index = i;
            break;
        }
    // Deleting the user
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
    ifstream inFile(location);
    ofstream outFile("temp.data");
    string usernameToUpdate;
    bool found = false;

    cout << "Enter the username of the user to update: ";
    cin >> usernameToUpdate;
    // Getting the user details
    User user;
    while (inFile >> user.username >> user.password >> user.role >> user.name)
    {
        // Checking if the user is the one to update
        if (user.username == usernameToUpdate)
        {
            // if found then update the details
            found = true;
            cout << "Updating details for user: " << usernameToUpdate << endl;

            cout << "Enter New Password (current: " << user.password << "): ";
            cin >> user.password;
            cout << "Enter New Name (current: " << user.name << "): ";
            cin >> user.name;

            // Role-specific updates
            if (user.role == "Teacher")
            {
                bool courses[totalCourses];
                bool sections[totalSections];

                cout << "Update Assigned Courses (1 for Yes, 0 for No):\n";
                for (int i = 0; i < totalCourses; i++)
                {
                    cout << "Teach " << (Courses)i << "? ";
                    cin >> courses[i];
                }

                cout << "Update Assigned Sections (1 for Yes, 0 for No):\n";
                for (int i = 0; i < totalSections; i++)
                {
                    cout << "Teach " << (Sections)i << "? ";
                    cin >> sections[i];
                }

                // Update teacher-specific file
                ofstream teacherFile("Data/teacher.data", ios::app);
                teacherFile << user.username << " ";
                for (int i = 0; i < totalCourses; i++)
                    teacherFile << courses[i] << " ";
                for (int i = 0; i < totalSections; i++)
                    teacherFile << sections[i] << " ";
                teacherFile << endl;
                teacherFile.close();
                cout << "Teacher-specific data updated successfully!" << endl;
            }
            else if (user.role == "Student")
            {
                bool courses[totalCourses];
                char section;

                cout << "Update Enrolled Courses (1 for Yes, 0 for No):\n";
                for (int i = 0; i < totalCourses; i++)
                {
                    cout << "Enroll in " << (Courses)i << "? ";
                    cin >> courses[i];
                }

                cout << "Update Assigned Section (A/B/C): ";
                cin >> section;

                // Update student-specific file
                ofstream studentFile("Data/student.data", ios::app);
                studentFile << user.username << " " << section << " ";
                for (int i = 0; i < totalCourses; i++)
                    studentFile << courses[i] << " ";
                studentFile << endl;
                studentFile.close();
                cout << "Student-specific data updated successfully!" << endl;
            }
        }
        // If not found then write the data to the file
        outFile << user.username << " " << user.password << " " << user.role << " " << user.name << endl;
    }

    inFile.close();
    outFile.close();
    // Remove the old file and rename the new file
    remove(location.c_str());
    rename("temp.data", location.c_str());

    if (found)
        cout << "User updated successfully!" << endl;
    else
        cout << "User not found!" << endl;

    Sleep(1000);
}

// Function for admin menu
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
            addUser("Data/users.data");
            break;
        case '2': // Search User
        {
            string username;
            cout << "Enter username to search: ";
            cin >> username;
            searchUser("Data/users.data", username);
            system("pause");
            break;
        }
        case '3': // List Users
            listUsers("Data/users.data");
            system("pause");
            break;
        case '4': // Delete User
        {
            string username;
            cout << "Enter username to delete: ";
            cin >> username;
            deleteUser("Data/users.data", username, loggedInUser);
            system("pause");
            break;
        }
        case '5': // Update User
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

// Teacher Menu
void teacherMenu(const User &loggedInUser)
{
    bool flag = true;
    char choice;
    while (flag)
    {
        system("cls");
        cout << "Hello " << loggedInUser.name << "Welcome to Teacher Panel" << endl;
        cout << "Teacher Menu:" << endl;
        cout << "1. Create Quiz" << endl;
        cout << "2. View Results" << endl;
        cout << "3. Edit Quiz" << endl;
        cout << "4. Assign Quiz" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1': // Create Quiz
            createQuiz("Data/quizzes.data");
            break;
        case '2': // View Results
            viewResults("Data/student.data");
            break;
        case '3': // Edit Quiz
            editQuiz("Data/quizzes.data");
            break;
        default:
            cout << "Invalid choice!" << endl;
            Sleep(1000);
            break;
        }
    }
}

void viewResults(const string &studentDataLocation)
{
    ifstream file(studentDataLocation);
    if (!file.is_open())
    {
        cout << "No results available!" << endl;
        Sleep(2000);
        return;
    }

    string username, quizName;
    char Grade;
    int score;

    cout << "Results:" << endl;
    while (file >> username >> quizName >> score >> Grade)
        cout << "Username: " << username << ", Quiz: " << quizName << ", Score: " << score << "/" << ", Grade: " << Grade << endl;

    file.close();
    system("pause");
}

void editQuiz(const string &location)
{
    ifstream file(location);
    if (!file.is_open())
    {
        cout << "No quizzes available!" << endl;
        Sleep(2000);
        return;
    }

    string quizName;
    cout << "Enter Quiz Name to Edit: ";
    cin >> quizName;

    int size = 0; // Number of quizzes in the file
    file.seekg(0, ios::beg); // Ensure the file is at the start for counting
    Quiz tempQuiz;

    // Count quizzes
    while (file >> tempQuiz.quizName >> tempQuiz.courseName >> tempQuiz.totalQuestions)
    {
        file.ignore(); // Skip to next line
        for (int i = 0; i < tempQuiz.totalQuestions; i++)
        {
            string dummy;
            getline(file, dummy); // Question
            for (int j = 0; j < 4; j++)
            {
                getline(file, dummy); // Options
            }
            file >> dummy; // Correct answer
        }
        size++;
    }
    file.clear();
    file.seekg(0, ios::beg); // Reset to the beginning for actual reading

    if (size == 0)
    {
        cout << "No quizzes found!" << endl;
        Sleep(2000);
        return;
    }

    Quiz *quizzes = new Quiz[size];
    bool found = false;

    // Load quizzes into dynamic array
    for (int i = 0; i < size; i++)
    {
        file >> quizzes[i].quizName >> quizzes[i].courseName >> quizzes[i].totalQuestions;
        quizzes[i].quizPtr = new Question[quizzes[i].totalQuestions];
        for (int j = 0; j < quizzes[i].totalQuestions; j++)
        {
            file.ignore();
            getline(file, quizzes[i].quizPtr[j].question);
            for (int k = 0; k < 4; k++)
            {
                getline(file, quizzes[i].quizPtr[j].options[k]);
            }
            file >> quizzes[i].quizPtr[j].correctOption;
        }

        if (quizzes[i].quizName == quizName)
        {
            found = true;
        }
    }
    file.close();

    if (!found)
    {
        cout << "Quiz not found!" << endl;
        for (int i = 0; i < size; i++)
        {
            delete[] quizzes[i].quizPtr;
        }
        delete[] quizzes;
        Sleep(2000);
        return;
    }

    // Edit the selected quiz
    for (int k = 0; k < size; k++)
    {
        if (quizzes[k].quizName == quizName)
        {
            cout << "Editing Quiz: " << quizzes[k].quizName << endl;
            for (int i = 0; i < quizzes[k].totalQuestions; i++)
            {
                cout << "Question " << i + 1 << ": " << quizzes[k].quizPtr[i].question << endl;
                for (int j = 0; j < 4; j++)
                {
                    cout << j + 1 << ". " << quizzes[k].quizPtr[i].options[j] << endl;
                }
                cout << "Enter new question (leave blank to keep current): ";
                string newQuestion;
                cin.ignore();
                getline(cin, newQuestion);
                if (!newQuestion.empty())
                {
                    quizzes[k].quizPtr[i].question = newQuestion;
                }

                for (int j = 0; j < 4; j++)
                {
                    cout << "Enter new option " << j + 1 << " (leave blank to keep current): ";
                    string newOption;
                    getline(cin, newOption);
                    if (!newOption.empty())
                    {
                        quizzes[k].quizPtr[i].options[j] = newOption;
                    }
                }

                cout << "Enter new correct option (1-4, leave blank to keep current): ";
                string newCorrectOption;
                getline(cin, newCorrectOption);
                if (!newCorrectOption.empty())
                {
                    quizzes[k].quizPtr[i].correctOption = stoi(newCorrectOption);
                }
            }
            break;
        }
    }

    // Save the updated quizzes back to the file
    ofstream outFile(location);
    for (int k = 0; k < size; k++)
    {
        outFile << quizzes[k].quizName << " " << quizzes[k].courseName << " " << quizzes[k].totalQuestions << endl;
        for (int i = 0; i < quizzes[k].totalQuestions; i++)
        {
            outFile << quizzes[k].quizPtr[i].question << endl;
            for (int j = 0; j < 4; j++)
                outFile << quizzes[k].quizPtr[i].options[j] << endl;

            outFile << quizzes[k].quizPtr[i].correctOption << endl;
        }
    }
    outFile.close();

    // Free memory
    for (int i = 0; i < size; i++)
    {
        delete[] quizzes[i].quizPtr;
    }
    delete[] quizzes;

    cout << "Quiz edited successfully!" << endl;
    Sleep(2000);
}

void studentMenu(const User &loggedInUser)
{
    bool flag = true;
    char choice;
    while (flag)
    {
        system("cls");
        cout << "Hello " << loggedInUser.name << "Welcome to Admin Panel" << endl;
        cout << "Student Menu:" << endl;
        cout << "1. Attempt Quiz" << endl;
        cout << "2. View Grades" << endl;
        cout << "3. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            attemptQuiz("Data/quizzes.data", "Data/student.data", loggedInUser.username);
            break;
        case '2':
            cout << "Viewing grades is not implemented yet." << endl;
            // To pause the screen for 2 seconds bcz the next functions uses clrscreen
            Sleep(2000);
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

void createQuiz(const string &location)
{
    ofstream file(location, ios::app);
    Quiz newQuiz;

    cout << "Enter Quiz Name: ";
    cin >> newQuiz.quizName;
    cout << "Enter Course Name: ";
    cin >> newQuiz.courseName;
    cout << "Enter Total Questions: ";
    cin >> newQuiz.totalQuestions;

    newQuiz.quizPtr = new Question[newQuiz.totalQuestions];
    for (int i = 0; i < newQuiz.totalQuestions; i++)
    {
        cout << "Enter Question " << i + 1 << ": ";
        cin.ignore();
        getline(cin, newQuiz.quizPtr[i].question);
        cout << "Enter 4 Options:" << endl;
        for (int j = 0; j < 4; j++)
        {
            cout << "Option " << j + 1 << ": ";
            getline(cin, newQuiz.quizPtr[i].options[j]);
        }
        cout << "Enter Correct Option (1-4): ";
        cin >> newQuiz.quizPtr[i].correctOption;
    }

    file << newQuiz.quizName << " " << newQuiz.courseName << " " << newQuiz.totalQuestions << endl;
    for (int i = 0; i < newQuiz.totalQuestions; i++)
    {
        file << newQuiz.quizPtr[i].question << endl;
        for (int j = 0; j < 4; j++)
        {
            file << newQuiz.quizPtr[i].options[j] << endl;
        }
        file << newQuiz.quizPtr[i].correctOption << endl;
    }

    delete[] newQuiz.quizPtr;
    file.close();
    cout << "Quiz created successfully!" << endl;
    // To pause the screen for 2 seconds bcz the next functions uses clrscreen
    Sleep(2000);
}

void attemptQuiz(const string &quizLocation, const string &studentDataLocation, const string &username)
{
    ifstream file(quizLocation);
    if (!file.is_open())
    {
        cout << "No quizzes available!" << endl;
        // To pause the screen for 2 seconds bcz the next functions uses clrscreen
        Sleep(2000);
        return;
    }

    string quizName;
    cout << "Enter Quiz Name to Attempt: ";
    cin >> quizName;

    Quiz quiz;
    bool found = false;
    while (file >> quiz.quizName >> quiz.courseName >> quiz.totalQuestions)
    {
        quiz.quizPtr = new Question[quiz.totalQuestions];
        for (int i = 0; i < quiz.totalQuestions; i++)
        {
            file.ignore();
            getline(file, quiz.quizPtr[i].question);
            for (int j = 0; j < 4; j++)
            {
                getline(file, quiz.quizPtr[i].options[j]);
            }
            file >> quiz.quizPtr[i].correctOption;
        }

        if (quiz.quizName == quizName)
        {
            found = true;
            break;
        }
        delete[] quiz.quizPtr;
    }
    file.close();

    if (!found)
    {
        cout << "Quiz not found!" << endl;
        // To pause the screen for 2 seconds bcz the next functions uses clrscreen
        Sleep(2000);
        return;
    }

    int score = 0;

    cout << "Attempting Quiz: " << quiz.quizName << endl;
    for (int i = 0; i < quiz.totalQuestions; i++)
    {
        cout << "Question " << i + 1 << ": " << quiz.quizPtr[i].question << endl;
        for (int j = 0; j < 4; j++)
        {
            cout << j + 1 << ". " << quiz.quizPtr[i].options[j] << endl;
        }
        int answer;
        cout << "Enter your answer (1-4): ";
        cin >> answer;

        if (answer == quiz.quizPtr[i].correctOption)
        {
            score++;
        }
    }

    cout << "You scored " << score << " out of " << quiz.totalQuestions << "!" << endl;

    // Save the student's result
    ofstream studentFile(studentDataLocation, ios::app);
    if (studentFile.is_open())
    {
        studentFile << username << " " << quiz.quizName << " " << score << " " << quiz.totalQuestions << endl;
        studentFile.close();
        cout << "Your result has been saved!" << endl;
    }
    else
    {
        cout << "Failed to save your result." << endl;
    }

    delete[] quiz.quizPtr;
    // To pause the screen for 2 seconds bcz the next functions uses clrscreen
    Sleep(2000);
}
