//
// Created by mostafa-medhat-jr on 5/4/26.
//

#include "System.h"
#include <iostream>
#include<fstream>
#include <vector>
#include<sstream>
#include <cctype>
#include "Course.h"

System::System() {
    readingCourseFile();
}

Course System:: searchCourseByName(string courseName) {
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));
    return courses[courseName];
}

Course System::searchCourseByCode(string courseCode) {
    courseCode = handleSpaceToUnderScore(toUpperCase(courseCode));

    for (auto& c : courses) {
        if (c.second.getCourse_code() == courseCode) {
          return courses[c.second.getName()];

        }
    }
    Course cempty = Course();

    return cempty;
}

void System:: readingCourseFile() {
    courseFile.readFile.open("course.txt");

    string line;

    while (getline(courseFile.readFile, line)) {
        stringstream ss(line);

        string code, name, description, instructor_name;
        int creditHours;

        ss >> code >> name >> description >> instructor_name >> creditHours;

        vector<string> prereq;
        string req;


        while (ss >> req) {
            prereq.push_back(req);
        }

        Course c;
        c.setName(name);
        c.setCourse_code(code);
        c.setCredit_hours(creditHours);
        c.setDescription(description);
        c.setInstructorName(instructor_name);
        c.setPrerequest(prereq);

        courses[name] = c;
    }

    courseFile.readFile.close();
}

void System::printCourses() {

    for ( auto& pair : courses) {
        Course& c = pair.second;

        cout << "Course Name: " << c.getName() << endl;
        cout << "Code: " << c.getCourse_code() << endl;
        cout << "Credit Hours: " << c.getCredit_hours() << endl;
        cout << "Description: " << c.getDescription() << endl;
        cout << "Instructor: " << c.getInstructorName() << endl;

        cout << "Prerequisite(s): ";
        for (int i=0 ; i<c.getPrerequest().size(); i++) {
            cout << c.getPrerequest().at(i) << " ";
        }
        cout << endl;

        cout << "------------------------" << endl;
    }
}

string System::toUpperCase(string str) {
    string s;
    for (auto& c : str) {
        c = toupper(c);
        s+=c;
    }
    return s;
}

string System::handleSpaceToUnderScore(string str) {

    for (int i=0;i<str.size();i++) {
        if (str[i] == ' ') {
            str[i] = '_';
        }
    }
return str;
}

vector<Course> System::getcoursesWeHave() {
    vector<Course> course;
    for (auto &c : courses) {
        course.push_back(c.second);
    }
    return course;
}

void System::setCoursesWeHave(vector<Course> course) {
    for (int i=0;i<course.size();i++) {
        courses [course[i].getName()] = course[i];

    }
}

