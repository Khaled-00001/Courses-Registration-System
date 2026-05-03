//
// Created by mostafa-medhat-jr on 5/3/26.
//

#include "Course.h"
#include<fstream>

Course::Course() {

    this->setCredit_hours(0);
    this->setDescription(" ");
    this->setInstructorName("");
    this->setPrerequest(map<string, bool>());
    this->setCourse_code("");
    this->setName("");

}

string Course::getName() {
    return this->name;
}

void Course::setName(string name) {
    this->name = name;
}

string Course::getCourse_code() {
    return this->code;
}

int Course::getCredit_hours() {
    return this->creditHours;
}

string Course::getDescription() {
    return this->description;
}

map<string, bool> Course::getPrerequest() {
    return this->prerequest;
}

void Course::setCourse_code(string course_code) {
    this->code = course_code;
}

void Course::setCredit_hours(int credit_hours) {
    this->creditHours = credit_hours;
}

void Course::setDescription(string description) {
    this->description = description;
}

void Course::setPrerequest(map<string, bool> prerequest) {
    this->prerequest = prerequest;
}

string Course::getInstructorName() {
    return this->instructor_name;
}

void Course::setInstructorName(string instructor_name) {
    this->instructor_name = instructor_name;
}







