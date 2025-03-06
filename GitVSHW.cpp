#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Structure to represent a user
struct User {
    string login;
    string password;
    string name;
    string address;
    string phone;
};

// Structure to represent a test
struct Test {
    string category;
    string name;
    vector<string> questions;
    vector<string> answers;
};

// Structure to represent a test result
struct TestResult {
    string userLogin;
    string testName;
    int correctAnswers;
    int totalQuestions;
    double score;
};

// Map to store users
map<string, User> users;

// Map to store tests
map<string, Test> tests;

// Map to store test results
map<string, vector<TestResult>> testResults;

// Admin login and password
string adminLogin = "";
string adminPassword = "";

// Function to register a new user
void registerUser() {
    User user;
    cout << "Enter your name: ";
    cin >> user.name;
    cout << "Enter your address: ";
    cin >> user.address;
    cout << "Enter your phone number: ";
    cin >> user.phone;
    cout << "Enter your login: ";
    cin >> user.login;
    cout << "Enter your password: ";
    cin >> user.password;

    // Check if the login is already taken
    if (users.find(user.login) != users.end()) {
        cout << "Login is already taken. Please choose another one.\n";
        return;
    }

    users[user.login] = user;
    cout << "Registration successful!\n";
}

// Function to login a user
void loginUser() {
    string login, password;
    cout << "Enter your login: ";
    cin >> login;
    cout << "Enter your password: ";
    cin >> password;

    // Check if the user exists and the password is correct
    if (users.find(login) == users.end() || users[login].password != password) {
        cout << "Invalid login or password.\n";
        return;
    }

    cout << "Login successful!\n";
}

// Function to take a test
void takeTest() {
    string userLogin;
    cout << "Enter your login: ";
    cin >> userLogin;

    // Check if the user exists
    if (users.find(userLogin) == users.end()) {
        cout << "User not found.\n";
        return;
    }

    cout << "Choose a test:\n";
    cout << "1. Math Test\n";
    cout << "2. History Test\n";
    int choice;
    cin >> choice;

    string testName;
    switch (choice) {
    case 1:
        testName = "Math Test";
        break;
    case 2:
        testName = "History Test";
        break;
    default:
        cout << "Invalid choice.\n";
        return;
    }

    // Check if the test exists
    if (tests.find(testName) == tests.end()) {
        cout << "Test not found.\n";
        return;
    }

    Test test = tests[testName];
    int correctAnswers = 0;

    // Ask the user the questions and check the answers
    for (int i = 0; i < test.questions.size(); i++) {
        string answer;
        cout << "Question " << i + 1 << ": " << test.questions[i] << "\n";
        cout << "Enter your answer: ";
        cin >> answer;
        if (answer == test.answers[i]) {
            correctAnswers++;
        }
    }

    // Calculate the score
    double score = (double)correctAnswers / test.questions.size() * 100;

    // Save the test result
    TestResult result;
    result.userLogin = userLogin;
    result.testName = testName;
    result.correctAnswers = correctAnswers;
    result.totalQuestions = test.questions.size();
    result.score = score;
    testResults[result.userLogin].push_back(result);

    cout << "Test completed! Your score is " << score << "%\n";
}

// Function to view test results
void viewTestResults() {
    string userLogin;
    cout << "Enter the login of the user: ";
    cin >> userLogin;

    // Check if the user exists
    if (testResults.find(userLogin) == testResults.end()) {
        cout << "No test results found for this user.\n";
        return;
    }

    // Display the test results
    for (TestResult result : testResults[userLogin]) {
        cout << "Test Name: " << result.testName << "\n";
        cout << "Correct Answers: " << result.correctAnswers << "\n";
        cout << "Total Questions: " << result.totalQuestions << "\n";
        cout << "Score: " << result.score << "%\n";
    }
}

// Function to manage users
void manageUsers() {
    cout << "1. Create user\n";
    cout << "2. Delete user\n";
    cout << "3. Modify user\n";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        registerUser();
        break;
    case 2:
        // Delete user
        break;
    case 3:
        // Modify user
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

// Function to add a test
void addTest() {
    Test test;
    cout << "Enter the category of the test: ";
    cin >> test.category;
    cout << "Enter the name of the test: ";
    cin >> test.name;

    // Add questions and answers to the test
    int numQuestions;
    cout << "Enter the number of questions: ";
    cin >> numQuestions;
    for (int i = 0; i < numQuestions; i++) {
        string question, answer;
        cout << "Enter question " << i + 1 << ": ";
        cin >> question;
        cout << "Enter answer " << i + 1 << ": ";
        cin >> answer;
        test.questions.push_back(question);
        test.answers.push_back(answer);
    }

    tests[test.name] = test;
    cout << "Test added successfully!\n";
}

// Function to view statistics
void viewStatistics() {
    cout << "1. View statistics by category\n";
    cout << "2. View statistics by test\n";
    cout << "3. View statistics by user\n";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        // View statistics by category
        break;
    case 2:
        // View statistics by test
        break;
    case 3:
        // View statistics by user
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

// Function to change admin login and password
void changeAdminLoginAndPassword() {
    string newLogin, newPassword;
    cout << "Enter new login: ";
    cin >> newLogin;
    cout << "Enter new password: ";
    cin >> newPassword;

    adminLogin = newLogin;
    adminPassword = newPassword;
    cout << "Admin login and password changed successfully!\n";
}

// Function to generate questions for math and history tests
void generateQuestions() {
    // Math questions
    Test mathTest;
    mathTest.category = "Math";
    mathTest.name = "Math Test";
    mathTest.questions.push_back("What is the value of x in the equation 2x + 5 = 11?");
    mathTest.answers.push_back("3");
    mathTest.questions.push_back("What is the value of y in the equation y - 3 = 7?");
    mathTest.answers.push_back("10");
    mathTest.questions.push_back("What is the value of z in the equation z / 2 = 9?");
    mathTest.answers.push_back("18");
    tests[mathTest.name] = mathTest;

    // History questions
    Test historyTest;
    historyTest.category = "History";
    historyTest.name = "History Test";
    historyTest.questions.push_back("Who was the first president of the United States?");
    historyTest.answers.push_back("George Washington");
    historyTest.questions.push_back("What year did the American Revolution start?");
    historyTest.answers.push_back("1775");
    historyTest.questions.push_back("Who was the leader of the Soviet Union during World War II?");
    historyTest.answers.push_back("Joseph Stalin");
    tests[historyTest.name] = historyTest;
}

int main() {
    generateQuestions();

    if (adminLogin.empty()) {
        cout << "Enter admin login: ";
        cin >> adminLogin;
        cout << "Enter admin password: ";
        cin >> adminPassword;
    }

    while (true) {
        cout << "1. Login as admin\n";
        cout << "2. Login as user\n";
        cout << "3. Exit\n";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string login, password;
            cout << "Enter admin login: ";
            cin >> login;
            cout << "Enter admin password: ";
            cin >> password;

            if (login == adminLogin && password == adminPassword) {
                cout << "Login successful!\n";

                while (true) {
                    cout << "1. Manage users\n";
                    cout << "2. Add test\n";
                    cout << "3. View statistics\n";
                    cout << "4. Change admin login and password\n";
                    cout << "5. Exit\n";
                    int adminChoice;
                    cin >> adminChoice;

                    switch (adminChoice) {
                    case 1:
                        manageUsers();
                        break;
                    case 2:
                        addTest();
                        break;
                    case 3:
                        viewStatistics();
                        break;
                    case 4:
                        changeAdminLoginAndPassword();
                        break;
                    case 5:
                        return 0;
                    default:
                        cout << "Invalid choice.\n";
                    }
                }
            }
            else {
                cout << "Invalid login or password.\n";
            }
            break;
        }
        case 2: {
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "3. Take test\n";
            cout << "4. View test results\n";
            cout << "5. Exit\n";
            int userChoice;
            cin >> userChoice;

            switch (userChoice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                takeTest();
                break;
            case 4:
                viewTestResults();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 3:
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
