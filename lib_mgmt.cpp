#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Book structure to hold book details
struct Book {
    string title;
    string author;
    string publisher;
    int year;
    int copies;
};

// Function prototypes
void addBook(fstream &file);
void listBooks(fstream &file);
void searchBook(fstream &file);
void modifyBook(fstream &file);
void deleteBook(fstream &file);

const string filename = "library.dat";

int main() {
    fstream file;
    char choice;

    file.open(filename, ios::in | ios::out | ios::binary);

    if (!file) {
        // If the file doesn't exist, create it
        file.open(filename, ios::out);
        file.close();
        file.open(filename, ios::in | ios::out | ios::binary);
    }

    while (true) {
        system("cls");
        cout << "\t\t====== LIBRARY MANAGEMENT SYSTEM ======";
        cout << "\n\n";
        cout << "\t1. Add Book\n";
        cout << "\t2. List All Books\n";
        cout << "\t3. Search Book by Title\n";
        cout << "\t4. Modify Book Details\n";
        cout << "\t5. Delete Book\n";
        cout << "\t6. Exit\n";
        cout << "\n\tSelect an option: ";
        cin >> choice;

        switch (choice) {
            case '1': addBook(file); break;
            case '2': listBooks(file); break;
            case '3': searchBook(file); break;
            case '4': modifyBook(file); break;
            case '5': deleteBook(file); break;
            case '6': 
                file.close();
                cout << "\nThank you for using the Library Management System!\n";
                return 0;
            default: 
                cout << "Invalid choice. Please try again.\n";
                system("pause");
        }
    }

    return 0;
}

void addBook(fstream &file) {
    Book book;
    char another = 'Y';

    file.seekp(0, ios::end);

    while (toupper(another) == 'Y') {
        system("cls");
        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin, book.title);
        cout << "Enter Author Name: ";
        getline(cin, book.author);
        cout << "Enter Publisher Name: ";
        getline(cin, book.publisher);
        cout << "Enter Publication Year: ";
        cin >> book.year;
        cout << "Enter Number of Copies: ";
        cin >> book.copies;

        file.write(reinterpret_cast<char*>(&book), sizeof(book));
        cout << "\nAdd another book? (Y/N): ";
        cin >> another;
    }
}

void listBooks(fstream &file) {
    Book book;

    file.seekg(0, ios::beg);

    system("cls");
    cout << "\n\t=== List of Books ===\n\n";
    cout << left << setw(30) << "Title" 
         << setw(20) << "Author" 
         << setw(20) << "Publisher" 
         << setw(10) << "Year" 
         << setw(10) << "Copies" 
         << endl;
    cout << string(90, '-') << endl;

    while (file.read(reinterpret_cast<char*>(&book), sizeof(book))) {
        cout << left << setw(30) << book.title 
             << setw(20) << book.author 
             << setw(20) << book.publisher 
             << setw(10) << book.year 
             << setw(10) << book.copies 
             << endl;
    }

    file.clear(); // Clear EOF flag
    system("pause");
}

void searchBook(fstream &file) {
    Book book;
    string title_to_search;
    bool found = false;

    cout << "\nEnter the title of the book to search: ";
    cin.ignore();
    getline(cin, title_to_search);

    file.seekg(0, ios::beg);

    while (file.read(reinterpret_cast<char*>(&book), sizeof(book))) {
        if (book.title == title_to_search) {
            found = true;
            cout << "\nBook Found:\n";
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Publisher: " << book.publisher << endl;
            cout << "Year: " << book.year << endl;
            cout << "Copies: " << book.copies << endl;
            break;
        }
    }

    if (!found) {
        cout << "\nBook not found.\n";
    }

    file.clear();
    system("pause");
}

void modifyBook(fstream &file) {
    Book book;
    string title_to_modify;
    bool found = false;

    cout << "\nEnter the title of the book to modify: ";
    cin.ignore();
    getline(cin, title_to_modify);

    file.seekg(0, ios::beg);

    while (file.read(reinterpret_cast<char*>(&book), sizeof(book))) {
        if (book.title == title_to_modify) {
            found = true;
            cout << "\nEnter new details for the book:\n";
            cout << "Enter Book Title: ";
            getline(cin, book.title);
            cout << "Enter Author Name: ";
            getline(cin, book.author);
            cout << "Enter Publisher Name: ";
            getline(cin, book.publisher);
            cout << "Enter Publication Year: ";
            cin >> book.year;
            cout << "Enter Number of Copies: ";
            cin >> book.copies;

            file.seekp(-static_cast<int>(sizeof(book)), ios::cur);
            file.write(reinterpret_cast<char*>(&book), sizeof(book));
            cout << "\nBook details updated successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "\nBook not found.\n";
    }

    file.clear();
    system("pause");
}

void deleteBook(fstream &file) {
    Book book;
    string title_to_delete;
    vector<Book> temp_data;

    cout << "\nEnter the title of the book to delete: ";
    cin.ignore();
    getline(cin, title_to_delete);

    file.seekg(0, ios::beg);

    while (file.read(reinterpret_cast<char*>(&book), sizeof(book))) {
        if (book.title != title_to_delete) {
            temp_data.push_back(book);
        }
    }

    file.close();
    file.open(filename, ios::out | ios::binary | ios::trunc);

    for (const auto& b : temp_data) {
        file.write(reinterpret_cast<const char*>(&b), sizeof(b));
    }

    file.clear();
    cout << "\nBook deleted successfully.\n";
    system("pause");
}
