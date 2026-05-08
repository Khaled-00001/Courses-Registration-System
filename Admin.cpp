#include "Admin.h"
// REMOVED: #include <iostream>  — Admin has no console output; GUI reads the return value.
#include <fstream>
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

// FIX: Removed cout lines. The caller (GUI) reads the bool return value directly.
// BEFORE:
//   cout << "Login successful!\n";
//   cout << "Invalid username or password!\n";
// AFTER: just return the bool — no console output.
bool Admin::login(string user, string pass)
{
    std::ifstream file("admin.txt");

    string u, p;
    while (file >> u >> p)
    {
        if (u == user && p == pass)
            return true;
    }

    return false;
}