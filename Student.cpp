#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string first_name, last_name, course;
    int section;
};

// Function prototypes
void addRecord(fstream &file);
void listRecords(fstream &file);
void modifyRecord(fstream &file);
void deleteRecord(fstream &file);
void searchRecord(fstream &file);

const string filename = "students.dat";

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
        cout << "\t\t====== STUDENT DATABASE MANAGEMENT SYSTEM ======";
        cout << "\n\n";
        cout << "\t1. Add Record\n";
        cout << "\t2. List Records\n";
        cout << "\t3. Modify Record\n";
        cout << "\t4. Delete Record\n";
        cout << "\t5. Search Record\n";
        cout << "\t6. Exit\n";
        cout << "\n\tSelect an option: ";
        cin >> choice;

        switch (choice) {
            case '1': addRecord(file); break;
            case '2': listRecords(file); break;
            case '3': modifyRecord(file); break;
            case '4': deleteRecord(file); break;
            case '5': searchRecord(file); break;
            case '6': 
                file.close();
                cout << "\nThank you for using the Student Database Management System!\n";
                return 0;
            default: 
                cout << "Invalid choice. Please try again.\n";
                system("pause");
        }
    }

    return 0;
}

void addRecord(fstream &file) {
    Student student;
    char another = 'Y';

    file.seekp(0, ios::end);

    while (toupper(another) == 'Y') {
        system("cls");
        cout << "Enter First Name: ";
        cin >> student.first_name;
        cout << "Enter Last Name: ";
        cin >> student.last_name;
        cout << "Enter Course: ";
        cin >> student.course;
        cout << "Enter Section: ";
        cin >> student.section;

        file.write(reinterpret_cast<char*>(&student), sizeof(student));
        cout << "\nAdd another record? (Y/N): ";
        cin >> another;
    }
}

void listRecords(fstream &file) {
    Student student;

    file.seekg(0, ios::beg);

    system("cls");
    cout << "\n\t=== List of Students ===\n\n";
    cout << left << setw(20) << "First Name" 
         << setw(20) << "Last Name" 
         << setw(30) << "Course" 
         << setw(10) << "Section" 
         << endl;
    cout << string(80, '-') << endl;

    while (file.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        cout << left << setw(20) << student.first_name 
             << setw(20) << student.last_name 
             << setw(30) << student.course 
             << setw(10) << student.section 
             << endl;
    }

    file.clear(); // Clear EOF flag
    system("pause");
}

void modifyRecord(fstream &file) {
    Student student;
    string last_name_to_modify;
    bool found = false;

    cout << "\nEnter the last name of the student to modify: ";
    cin >> last_name_to_modify;

    file.seekg(0, ios::beg);

    while (file.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        if (student.last_name == last_name_to_modify) {
            found = true;
            cout << "\nEnter new First Name: ";
            cin >> student.first_name;
            cout << "Enter new Last Name: ";
            cin >> student.last_name;
            cout << "Enter new Course: ";
            cin >> student.course;
            cout << "Enter new Section: ";
            cin >> student.section;

            file.seekp(-static_cast<int>(sizeof(student)), ios::cur);
            file.write(reinterpret_cast<char*>(&student), sizeof(student));
            cout << "\nRecord modified successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "\nRecord not found.\n";
    }

    file.clear();
    system("pause");
}

void deleteRecord(fstream &file) {
    Student student;
    string last_name_to_delete;
    vector<Student> temp_data;

    cout << "\nEnter the last name of the student to delete: ";
    cin >> last_name_to_delete;

    file.seekg(0, ios::beg);

    while (file.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        if (student.last_name != last_name_to_delete) {
            temp_data.push_back(student);
        }
    }

    file.close();
    file.open(filename, ios::out | ios::binary | ios::trunc);

    for (const auto& s : temp_data) {
        file.write(reinterpret_cast<const char*>(&s), sizeof(s));
    }

    file.clear();
    cout << "\nRecord deleted successfully.\n";
    system("pause");
}

void searchRecord(fstream &file) {
    Student student;
    string last_name_to_search;
    bool found = false;

    cout << "\nEnter the last name of the student to search: ";
    cin >> last_name_to_search;

    file.seekg(0, ios::beg);

    while (file.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        if (student.last_name == last_name_to_search) {
            found = true;
            cout << "\nRecord Found:\n";
            cout << "First Name: " << student.first_name << endl;
            cout << "Last Name: " << student.last_name << endl;
            cout << "Course: " << student.course << endl;
            cout << "Section: " << student.section << endl;
            break;
        }
    }

    if (!found) {
        cout << "\nRecord not found.\n";
    }

    file.clear();
    system("pause");
}
