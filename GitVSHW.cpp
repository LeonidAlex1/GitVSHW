#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct User {
    string login;
    string password;
    string name;
    string address;
    string phone;
};

struct Test {
    string category;
    string name;
    vector<string> questions;
    vector<string> answers;
};

struct TestResult {
    string userLogin;
    string testName;
    int correctAnswers;
    int totalQuestions;
    double score;
};

map<string, User> users;

map<string, Test> tests;

map<string, vector<TestResult>> testResults;

string adminLogin = "";
string adminPassword = "";

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

    if (users.find(user.login) != users.end()) {
        cout << "Login is already taken. Please choose another one.\n";
        return;
    }

    users[user.login] = user;
    cout << "Registration successful!\n";
}

void takeTest() {
    string userLogin;
    cout << "Enter your login: ";
    cin >> userLogin;

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

    if (tests.find(testName) == tests.end()) {
        cout << "Test not found.\n";
        return;
    }

    Test test = tests[testName];
    int correctAnswers = 0;

    for (int i = 0; i < test.questions.size(); i++) {
        string answer;
        cout << "Question " << i + 1 << ": " << test.questions[i] << "\n";
        cout << "Enter your answer: ";
        cin >> answer;
        if (answer == test.answers[i]) {
            correctAnswers++;
        }
    }

    double score = (double)correctAnswers / test.questions.size() * 100;

    TestResult result;
    result.userLogin = userLogin;
    result.testName = testName;
    result.correctAnswers = correctAnswers;
    result.totalQuestions = test.questions.size();
    result.score = score;
    testResults[userLogin].push_back(result);

    cout << "Test completed! Your score is " << score << "%\n";
}

void viewTestResults() {
    string userLogin;
    cout << "Enter the login of the user: ";
    cin >> userLogin;

    if (testResults.find(userLogin) == testResults.end()) {
        cout << "No test results found for this user.\n";
        return;
    }

    for (TestResult result : testResults[userLogin]) {
        cout << "Test Name: " << result.testName << "\n";
        cout << "Correct Answers: " << result.correctAnswers << "\n";
        cout << "Total Questions: " << result.totalQuestions << "\n";
        cout << "Score: " << result.score << "%\n";
    }
}

void addTest() {
    Test test;
    cout << "Enter the category of the test: ";
    cin >> test.category;
    cout << "Enter the name of the test: ";
    cin >> test.name;

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

void viewStatistics() {
    cout << "-----------------------------------------------\n";
    cout << "              View Statistics Menu            \n";
    cout << "-----------------------------------------------\n";
    cout << "1. View statistics by test\n";
    cout << "2. Exit\n";
    cout << "-----------------------------------------------\n";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        for (auto& test : tests) {
            int totalCorrectAnswers = 0;
            int totalQuestions = 0;
            for (auto& result : testResults) {
                for (auto& testResult : result.second) {
                    if (testResult.testName == test.first) {
                        totalCorrectAnswers += testResult.correctAnswers;
                        totalQuestions += testResult.totalQuestions;
                    }
                }
            }
            double averageScore = (double)totalCorrectAnswers / totalQuestions * 100;
            cout << "Test Name: " << test.first << "\n";
            cout << "Average Score: " << averageScore << "%\n";
        }
        break;
    case 2:
        return;
    default:
        cout << "Invalid choice.\n";
    }
}

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

void changeUserLoginAndPassword() {
    string userLogin, newLogin, newPassword;
    cout << "Enter the login of the user: ";
    cin >> userLogin;
    cout << "Enter new login: ";
    cin >> newLogin;
    cout << "Enter new password: ";
    cin >> newPassword;

    if (users.find(userLogin) == users.end()) {
        cout << "User not found.\n";
        return;
    }

    users[userLogin].login = newLogin;
    users[userLogin].password = newPassword;
    cout << "User login and password changed successfully!\n";
}

void deleteUser();
void modifyUser();

void manageUsers() {
    cout << "-----------------------------------------------\n";
    cout << "              Manage Users Menu              \n";
    cout << "-----------------------------------------------\n";
    cout << "1. Create user\n";
    cout << "2. Delete user\n";
    cout << "3. Modify user\n";
    cout << "4. Exit\n";
    cout << "-----------------------------------------------\n";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        registerUser();
        break;
    case 2:
        deleteUser();
        break;
    case 3:
        modifyUser();
        break;
    case 4:
        return;
    default:
        cout << "Invalid choice.\n";
    }
}

void deleteUser() {
    string userLogin;
    cout << "Enter the login of the user to delete: ";
    cin >> userLogin;

    if (users.find(userLogin) == users.end()) {
        cout << "User not found.\n";
        return;
    }

    users.erase(userLogin);
    cout << "User deleted successfully!\n";
}

void modifyUser() {
    string userLogin;
    cout << "Enter the login of the user to modify: ";
    cin >> userLogin;

    if (users.find(userLogin) == users.end()) {
        cout << "User not found.\n";
        return;
    }

    cout << "Enter new name: ";
    cin >> users[userLogin].name;
    cout << "Enter new address: ";
    cin >> users[userLogin].address;
    cout << "Enter new phone number: ";
    cin >> users[userLogin].phone;
    cout << "Enter new login: ";
    cin >> users[userLogin].login;
    cout << "Enter new password: ";
    cin >> users[userLogin].password;

    cout << "User modified successfully!\n";
}

void generateQuestions() {
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
        cout << "-----------------------------------------------\n";
        cout << "              Main Menu                      \n";
        cout << "-----------------------------------------------\n";
        cout << "1. Login as admin\n";
        cout << "2. Login as user\n";
        cout << "3. Exit\n";
        cout << "-----------------------------------------------\n";

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
                    cout << "-----------------------------------------------\n";
                    cout << "              Admin Menu                     \n";
                    cout << "-----------------------------------------------\n";
                    cout << "1. Manage users\n";
                    cout << "2. View statistics\n";
                    cout << "3. Change login and password\n";
                    cout << "4. Exit\n";
                    cout << "-----------------------------------------------\n";

                    int adminChoice;
                    cin >> adminChoice;

                    switch (adminChoice) {
                    case 1:
                        manageUsers();
                        break;
                    case 2:
                        viewStatistics();
                        break;
                    case 3:
                        cout << "-----------------------------------------------\n";
                        cout << "              Change Login and Password Menu  \n";
                        cout << "-----------------------------------------------\n";
                        cout << "1. Change admin login and password\n";
                        cout << "2. Change user login and password\n";
                        cout << "3. Exit\n";
                        cout << "-----------------------------------------------\n";

                        int changeChoice;
                        cin >> changeChoice;

                        switch (changeChoice) {
                        case 1:
                            changeAdminLoginAndPassword();
                            break;
                        case 2:
                            changeUserLoginAndPassword();
                            break;
                        case 3:
                            return;
                        default:
                            cout << "Invalid choice.\n";
                        }
                        break;
                    case 4:
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
            cout << "-----------------------------------------------\n";
            cout << "              User Menu                      \n";
            cout << "-----------------------------------------------\n";
            cout << "1. Register\n";
            cout << "2. Take test\n";
            cout << "3. View test results\n";
            cout << "4. Exit\n";
            cout << "-----------------------------------------------\n";

            int userChoice;
            cin >> userChoice;

            switch (userChoice) {
            case 1:
                registerUser();
                break;
            case 2:
                takeTest();
                break;
            case 3:
                viewTestResults();
                break;
            case 4:
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
