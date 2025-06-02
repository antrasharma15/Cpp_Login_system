#include <iostream>
#include <fstream>
#include <string>
#include <functional>  // for std::hash

using namespace std;

// Function prototypes
void registerUser();
void loginUser();
string hashPassword(const string &password);

int main() {
    int choice;

    cout << "==============================" << endl;
    cout << "   Login and Registration System" << endl;
    cout << "==============================" << endl;

    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}

// Hashing function using std::hash
string hashPassword(const string &password) {
    hash<string> hasher;
    size_t hashed = hasher(password);
    return to_string(hashed);  // convert hash to string
}

// Register function
void registerUser() {
    string username, password;
    cout << "\nEnter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    ofstream userFile(username + ".txt");
    userFile << username << endl;
    userFile << hashPassword(password) << endl;  // save hashed password
    userFile.close();

    cout << "Registration successful!" << endl;
}

// Login function
void loginUser() {
    string username, password, storedUser, storedHashedPass;
    cout << "\nEnter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream userFile(username + ".txt");
    if (userFile.is_open()) {
        getline(userFile, storedUser);
        getline(userFile, storedHashedPass);

        string inputHashedPass = hashPassword(password);

        if (storedUser == username && storedHashedPass == inputHashedPass) {
            cout << "Login successful! Welcome, " << username << "." << endl;
        } else {
            cout << "Invalid username or password." << endl;
        }

        userFile.close();
    } else {
        cout << "User not found. Please register first." << endl;
    }
}