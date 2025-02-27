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

struct BorrowedBook {
    int bookId;
    string borrower;
    string borrowDate;
    string returnDate;
    string condition;
};

class Library {
private:
    vector<Book> books;
    vector<BorrowedBook> borrowedBooks;
    int nextId;

public:
    Library() : nextId(1) {}

    void addBook() {
        string title, author, genre;
        int year;
        double rating;
        bool available = true;

        cout << "Enter title: "; cin.ignore(); getline(cin, title);
        cout << "Enter author: "; getline(cin, author);
        cout << "Enter genre: "; getline(cin, genre);
        cout << "Enter year: "; cin >> year;
        cout << "Enter rating: "; cin >> rating;

        books.push_back({ nextId++, title, author, genre, year, available, rating });
    }

    void removeBook() {
        int id;
        cout << "Enter book ID to remove: "; cin >> id;
        books.erase(remove_if(books.begin(), books.end(), [id](const Book& b) { return b.id == id; }), books.end());
    }

    void updateBook() {
        int id;
        cout << "Enter book ID to update: "; cin >> id;
        for (auto& book : books) {
            if (book.id == id) {
                cout << "Enter new title: "; cin.ignore(); getline(cin, book.title);
                cout << "Enter new author: "; getline(cin, book.author);
                cout << "Enter new genre: "; getline(cin, book.genre);
                cout << "Enter new year: "; cin >> book.year;
                cout << "Enter new rating: "; cin >> book.rating;
                return;
            }
        }
        cout << "Book not found\n";
    }

    void displayBooks() {
        for (const auto& book : books) {
            cout << "ID: " << book.id << " Title: " << book.title << " Author: " << book.author
                << " Genre: " << book.genre << " Year: " << book.year << " Available: "
                << (book.available ? "Yes" : "No") << " Rating: " << book.rating << "\n";
        }
    }

    void borrowBook() {
        int id;
        string borrower, borrowDate;
        cout << "Enter book ID to borrow: "; cin >> id;
        cout << "Enter borrower name: "; cin.ignore(); getline(cin, borrower);
        cout << "Enter borrow date: "; getline(cin, borrowDate);

        for (auto& book : books) {
            if (book.id == id && book.available) {
                book.available = false;
                borrowedBooks.push_back({ id, borrower, borrowDate, "", "" });
                cout << "Book borrowed successfully\n";
                return;
            }
        }
        cout << "Book not available\n";
    }

    void returnBook() {
        int id;
        string returnDate, condition;
        cout << "Enter book ID to return: "; cin >> id;
        cout << "Enter return date: "; cin.ignore(); getline(cin, returnDate);
        cout << "Enter book condition: "; getline(cin, condition);

        for (auto& borrow : borrowedBooks) {
            if (borrow.bookId == id && borrow.returnDate.empty()) {
                borrow.returnDate = returnDate;
                borrow.condition = condition;

                for (auto& book : books) {
                    if (book.id == id) {
                        book.available = true;
                        break;
                    }
                }
                cout << "Book returned successfully\n";
                return;
            }
        }
        cout << "Borrowed record not found\n";
    }

    void menu() {
        int choice;
        do {
            cout << "\nLibrary Management System\n";
            cout << "1. Add Book\n";
            cout << "2. Remove Book\n";
            cout << "3. Update Book\n";
            cout << "4. Display Books\n";
            cout << "5. Borrow Book\n";
            cout << "6. Return Book\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
            case 1: addBook(); break;
            case 2: removeBook(); break;
            case 3: updateBook(); break;
            case 4: displayBooks(); break;
            case 5: borrowBook(); break;
            case 6: returnBook(); break;
            case 7: break;
            default: cout << "Invalid choice\n";
            }
        } while (choice != 7);
    }
};

int main() {
    Library lib;
    lib.menu();
    return 0;
}
