#include "Admin.h"
#include <iostream>

using namespace std;

Admin::Admin() {
    username = "admin";
    password = "1234";
}

Admin::Admin(string user, string pass) {
    username = user;
    password = pass;
}

void Admin::setUsername(string user) {
    username = user;
}

string Admin::getUsername() {
    return username;
}

void Admin::setPassword(string pass) {
    password = pass;
}

string Admin::getPassword() {
    return password;
}

bool Admin::login(string user, string pass) {

    if (user == username && pass == password) {
        cout << "Login successful!\n";
        return true;
    }

    cout << "Invalid username or password!\n";
    return false;
}
