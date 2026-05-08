#include "Student.h"
// REMOVED: #include <fstream>  — not used in Student.cpp
// FIX: Removed stray global `Course myCourses;` declared here.
// WHY: It was unused, caused an unnecessary Course construction on startup,
//      and pollutes the global namespace. It belongs nowhere in Student.cpp.

Student::Student() {
    this->setID(0);
    this->setName("");
    this->setLevel(0);
}

Student::Student(string name, int id, int level) {
    this->name = name;
    this->id = id;
    this->level = level;
}

void Student::setName(string name) {
    this->name = name;
}
string Student::getName() {
    return name;
}
void Student::setID(int id) {
    this->id = id;
}
int Student::getID() {
    return id;
}
void Student::setLevel(int level) {
    this->level = level;
}
int Student::getLevel() {
    return level;
}
void Student::setPassword(string pass) {
    password = pass;
}

string Student::getPassword() {
    return password;
}