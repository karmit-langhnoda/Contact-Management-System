#include<bits/stdc++.h>
using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

vector<Contact> contacts;

void loadContacts();
void saveContacts();
void createContact();
void editContact();
void searchContact();
void deleteContact();
void displayAllContacts();
void backupContacts();
void restoreBackup();

int main() {
    loadContacts();
    int choice;

    do {
        cout << "\nContact Management System\n";
        cout << "1. Create Contact\n";
        cout << "2. Edit Contact\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Display All Contacts\n";
        cout << "6. Backup Contacts\n";
        cout << "7. Restore Backup\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                createContact();
                break;
            case 2:
                editContact();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                displayAllContacts();
                break;
            case 6:
                backupContacts();
                break;
            case 7:
                restoreBackup();
                break;
            case 0:
                saveContacts();
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}

void loadContacts() {
    ifstream file("contacts.txt");
    Contact temp;
    while (file >> temp.name >> temp.phone >> temp.email) {
        contacts.push_back(temp);
    }
    file.close();
}

void saveContacts() {
    ofstream file("contacts.txt");
    for (const auto &c : contacts) {
        file << c.name << " " << c.phone << " " << c.email << "\n";
    }
    file.close();
}

void createContact() {
    Contact temp;
    cout << "Enter Name: ";
    cin >> temp.name;
    cout << "Enter Phone: ";
    cin >> temp.phone;
    cout << "Enter Email: ";
    cin >> temp.email;
    contacts.push_back(temp);
    saveContacts();
    cout << "Contact created successfully!\n";
}

void editContact() {
    string searchName;
    cout << "Enter the name of the contact to edit: ";
    cin >> searchName;
    for (auto &c : contacts) {
        if (c.name == searchName) {
            cout << "Enter new Name: ";
            cin >> c.name;
            cout << "Enter new Phone: ";
            cin >> c.phone;
            cout << "Enter new Email: ";
            cin >> c.email;
            saveContacts();
            cout << "Contact edited successfully!\n";
            return;
        }
    }
    cout << "Contact not found.\n";
}

void searchContact() {
    string searchName;
    cout << "Enter the name of the contact to search: ";
    cin >> searchName;
    for (const auto &c : contacts) {
        if (c.name == searchName) {
            cout << "Contact found:\n";
            cout << "Name: " << c.name << "\nPhone: " << c.phone << "\nEmail: " << c.email << "\n";
            return;
        }
    }
    cout << "Contact not found.\n";
}

void deleteContact() {
    string searchName;
    cout << "Enter the name of the contact to delete: ";
    cin >> searchName;
    auto it = remove_if(contacts.begin(), contacts.end(), [&](const Contact &c) { return c.name == searchName; });
    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        saveContacts();
        cout << "Contact deleted successfully!\n";
    } else {
        cout << "Contact not found.\n";
    }
}

void displayAllContacts() {
    if (contacts.empty()) {
        cout << "No contacts available.\n";
        return;
    }
    cout << "All Contacts:\n";
    for (const auto &c : contacts) {
        cout << "Name: " << c.name << "\nPhone: " << c.phone << "\nEmail: " << c.email << "\n--------------------\n";
    }
}

void backupContacts() {
    saveContacts();
    system("cp contacts.txt backup_contacts.txt");
    cout << "Backup created successfully!\n";
}

void restoreBackup() {
    system("cp backup_contacts.txt contacts.txt");
    contacts.clear();
    loadContacts();
    cout << "Backup restored successfully!\n";
}
