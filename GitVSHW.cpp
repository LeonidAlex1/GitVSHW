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








};