#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Функция для простого шифрования пароля
string encryptPassword(const string& password) {
    string encrypted = password;
    for (char& c : encrypted) c += 3;
    return encrypted;
}

string decryptPassword(const string& encrypted) {
    string decrypted = encrypted;
    for (char& c : decrypted) c -= 3;
    return decrypted;
}

// Класс пользователя
class User {
public:
    string login, password, name, address, phone;
    vector<string> testResults;

    User(string l, string p, string n, string a, string ph)
        : login(l), password(encryptPassword(p)), name(n), address(a), phone(ph) {
    }

    void addTestResult(const string& result) {
        testResults.push_back(result);
    }
};

// Класс администратора
class Admin {
private:
    string adminLogin = "admin";
    string adminPassword = encryptPassword("admin123");

public:
    bool verifyAdmin(const string& login, const string& password) {
        return (login == adminLogin && encryptPassword(password) == adminPassword);
    }
    void changeAdminCredentials(const string& newLogin, const string& newPassword) {
        adminLogin = newLogin;
        adminPassword = encryptPassword(newPassword);
    }
};

// Класс тестов
class Test {
public:
    string category;
    string title;
    vector<pair<string, string>> questions;

    Test(string c, string t) : category(c), title(t) {}

    void addQuestion(const string& question, const string& answer) {
        questions.push_back({ question, answer });
    }
};

// Класс системы тестирования
class TestingSystem {
private:
    map<string, User> users;
    vector<Test> tests;
    Admin admin;
    string userFile = "users.txt";
    string testFile = "tests.txt";

public:
    void registerUser();
    void loginUser();
    void adminMenu();
    void userMenu(const string& login);
    void takeTest(const string& login);
    void saveUsersToFile();
    void loadUsersFromFile();
    void saveTestsToFile();
    void loadTestsFromFile();
};

void TestingSystem::registerUser() {
    string login, password, name, address, phone;
    cout << "Enter login: "; cin >> login;
    if (users.find(login) != users.end()) {
        cout << "Login already exists!\n";
        return;
    }
    cout << "Enter password: "; cin >> password;
    cout << "Enter full name: "; cin.ignore(); getline(cin, name);
    cout << "Enter address: "; getline(cin, address);
    cout << "Enter phone: "; cin >> phone;

    users[login] = User(login, password, name, address, phone);
    saveUsersToFile();
    cout << "Registration successful!\n";
}

void TestingSystem::saveUsersToFile() {
    ofstream file(userFile);
    if (!file) {
        cout << "Error: Unable to open file for saving users.\n";
        return;
    }
    try {
        for (const auto& pair : users) {
            const string& login = pair.first;
            const User& user = pair.second;
            file << login << " " << user.password << "\n"
                << user.name << "\n"
                << user.address << "\n"
                << user.phone << "\n";
        }
    }
    catch (const exception& e) {
        cout << "Error writing to file: " << e.what() << "\n";
    }
    file.close();
}

void TestingSystem::loadUsersFromFile() {
    ifstream file(userFile);
    if (!file) return;
    string login, password, name, address, phone;
    while (getline(file, login) && getline(file, password) &&
        getline(file, name) && getline(file, address) &&
        getline(file, phone)) {
        users[login] = User(login, decryptPassword(password), name, address, phone);
    }
    file.close();
}

int main() {
    TestingSystem system;
    system.loadUsersFromFile();
    int choice;
    do {
        cout << "1. Register\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) system.registerUser();
        else if (choice == 2) system.loginUser();
    } while (choice != 3);

    return 0;
}
