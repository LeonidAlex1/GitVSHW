#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    string genre;
    int year;
    bool available;
    double rating;
};

class Library {
private:
    vector<Book> books;
    int nextId;

public:
    Library() : nextId(1) {}

    void addBook(const string& title, const string& author, const string& genre, int year, bool available, double rating) {
        books.push_back({ nextId++, title, author, genre, year, available, rating });
    }

    void removeBook(int id) {
        books.erase(remove_if(books.begin(), books.end(), [id](const Book& b) { return b.id == id; }), books.end());
    }

    void updateBook(int id, const string& title, const string& author, const string& genre, int year, bool available, double rating) {
        for (auto& book : books) {
            if (book.id == id) {
                book.title = title;
                book.author = author;
                book.genre = genre;
                book.year = year;
                book.available = available;
                book.rating = rating;
                break;
            }
        }
    }


    void displayBooks() {
        for (const auto& book : books) {
            cout << "ID: " << book.id << " Title: " << book.title << " Author: " << book.author
                << " Genre: " << book.genre << " Year: " << book.year << " Available: "
                << (book.available ? "Yes" : "No") << " Rating: " << book.rating << endl;
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const auto& book : books) {
            file << book.id << "," << book.title << "," << book.author << "," << book.genre << ","
                << book.year << "," << book.available << "," << book.rating << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Book book;
            string available;
            getline(ss, line, ','); book.id = stoi(line);
            getline(ss, book.title, ',');
            getline(ss, book.author, ',');
            getline(ss, book.genre, ',');
            getline(ss, line, ','); book.year = stoi(line);
            getline(ss, available, ','); book.available = (available == "1");
            getline(ss, line, ','); book.rating = stod(line);
            books.push_back(book);
        }
    }


};



