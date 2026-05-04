#include<iostream>
#include<vector>
#include <sstream>
#include<fstream>
#include<assert.h>
#include "Student.h"

using namespace std;
Course myCourses;

// default constructor
Student::Student() {
    this->setID(0);
    this->setName("");
    this->setLevel(0);
}
// parameterized constructor
Student::Student(string name, int id, int level) {
    this->name = name;
    this->id = id;
    this->level= level;
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















