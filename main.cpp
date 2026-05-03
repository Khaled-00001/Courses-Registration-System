#include <iostream>
#include <unordered_map>
#include<fstream>


#include "Course.h"
using namespace std;




struct File {
    ifstream readFile;
    ofstream editFile;
};

//fns
Course searchCourseByName(string courseName);
pair<Course,bool> searchCourseByCode(string courseCode);
void readingCourseFile(File &f);
void printCourses(); //made chat do it cuz i am bored to do it

//init ds var
unordered_map<string, Course> courses;


int main() {
    File courseFile;

    readingCourseFile(courseFile);
    printCourses();

    return 0;
}

Course searchCourse(string courseName) {
    return courses[courseName];
}

pair<Course,bool> searchCourseByCode(string courseCode) {
    pair<Course,bool> result;
    for (auto& c : courses) {
        if (c.second.getCourse_code() == courseCode) {
            result.second=true;
            result.first=courses[c.second.getName()];
            return result;
        }

    }
    Course cempty;
    result.second=false;
    result.first=cempty;

    return result;
}

void readingCourseFile(File &f) {
    f.readFile.open("course.txt");

    string code,name,description,instructor_name,request;
    int creditHours;

    while (f.readFile>> code>> name >>description>>instructor_name >> creditHours>>request) {
        Course c;
        map<string,bool>p1;
        p1[request]=false;
        c.setName(name);
        c.setCourse_code(code);
        c.setCredit_hours(creditHours);
        c.setDescription(description);
        c.setInstructorName(instructor_name);
        c.setPrerequest(p1);
        courses[name]=c;

    }
}

void printCourses() {

    for ( auto& pair : courses) {
        Course& c = pair.second;

        cout << "Course Name: " << c.getName() << endl;
        cout << "Code: " << c.getCourse_code() << endl;
        cout << "Credit Hours: " << c.getCredit_hours() << endl;
        cout << "Description: " << c.getDescription() << endl;
        cout << "Instructor: " << c.getInstructorName() << endl;

        cout << "Prerequisite(s): ";
        for (auto & pre : c.getPrerequest()) {
            cout << pre.first << " ";
        }
        cout << endl;

        cout << "------------------------" << endl;
    }
}
