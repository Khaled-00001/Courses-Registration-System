#include<iostream>
#include<vector>
#include<fstream>
#include<assert.h>
#include "Student.h"

using namespace std;

vector <Course> registeredCourses;
vector<pair<Course, double>> courseGradesPair;
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

// adding grades to regestired course and making vector of pairs<Course, Grade>
void Student::addGrade(Course course, double grade) {
    for (int i = 0; i < registeredCourses.size(); i++) {
        if (registeredCourses[i].getCourse_code() != course.getCourse_code()) {
            assert("This Course is not registered for you\n");
        }
        else {
            courseGradesPair.push_back(make_pair(course, grade));
        }
    }
}

// editing grades
void Student::editGrade(Course course, double newGrade) {
    for (int i = 0; i < courseGradesPair.size(); i++) {
        if (course.getCourse_code() != courseGradesPair[i].first.getCourse_code()) {
            assert("You can't edit grade on this course because you don't add it's grade before\n");
        }
        else {
            courseGradesPair[i].second = newGrade;
        }
    }
}

// getting grades by course name
void Student::getGrade(Course course) {
    for (int i = 0; i < courseGradesPair.size(); i++) {
        if (course.getName() == courseGradesPair[i].first.getName()) {
            cout << "Your degree in " << course.getName() << " is " << courseGradesPair[i].second << endl;
        }
    }
}


void Student::viewGrades() {
    for (int i = 0; i < courseGradesPair.size(); i++) {
        cout << "Course: " << courseGradesPair[i].first.getName() << endl;
        cout << "Grade: " << courseGradesPair[i].second << endl;
    }
}

double Student::calculateGPA() {
    double totalCreditHours, totalGrades;
    for (int i = 0; i < courseGradesPair.size(); i++) {
        totalCreditHours += courseGradesPair[i].first.getCredit_hours();
        totalGrades += courseGradesPair[i].second;
    }
    double gpa = totalGrades/totalCreditHours;
    return gpa;
}

void Student::generateReport() {
    cout << "--------- Student Report ---------\n";
    cout << "Name: " << getName() << endl;
    cout << "ID: " << getID() << endl ;
    cout << "--- Grades ---\n";
    viewGrades();
    cout << "------\n";
    cout << "GPA: " << calculateGPA() << endl;
    cout << "----------------------------------\n";
}

void Student::courseRegisteration() {}



