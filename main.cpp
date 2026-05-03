#include <iostream>
#include <unordered_map>
#include<fstream>
#include <vector>
#include<sstream>
#include <cctype>

#include "Course.h"
using namespace std;

struct File {
    ifstream readFile;
    ofstream editFile;
};

//fns
Course searchCourseByName(string courseName);
Course searchCourseByCode(string courseCode);
void readingCourseFile(File &f);
void printCourses(); //made chat do it cuz i am bored to do it
string toUpperCase(string str);

//init ds var
unordered_map<string, Course> courses;


int main() {
    File courseFile;

    /*readingCourseFile(courseFile);
    printCourses();
    cout<<"Hereeeeeeeee\n";
    cout<<searchCourseByCode("cs304").getName()<<endl;
    cout<<searchCourseByName("artificial_intelligence").getCourse_code()<<endl;*/

    return 0;
}

Course searchCourseByName(string courseName) {
    courseName = toUpperCase(courseName);
    return courses[courseName];
}

Course searchCourseByCode(string courseCode) {
    courseCode = toUpperCase(courseCode);

    for (auto& c : courses) {
        if (c.second.getCourse_code() == courseCode) {
          return courses[c.second.getName()];

        }
    }
    Course cempty = Course();

    return cempty;
}

void readingCourseFile(File &f) {
    f.readFile.open("course.txt");

    string line;

    while (getline(f.readFile, line)) {
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

    f.readFile.close();
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
        for (int i=0 ; i<c.getPrerequest().size(); i++) {
            cout << c.getPrerequest().at(i) << " ";
        }
        cout << endl;

        cout << "------------------------" << endl;
    }
}

string toUpperCase(string str) {
    string s;
    for (auto& c : str) {
        c = toupper(c);
        s+=c;
    }
    return s;
}
