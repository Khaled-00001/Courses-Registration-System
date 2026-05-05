
#include "System.h"
#include "Student.h"
#include <iostream>
#include<fstream>
#include <vector>
#include <sstream>
#include <cctype>
#include "Course.h"



System::System() {
    readingCourseFile();
    readingStudentFile();
    readingRegisterFile();
}

// ------------------------ Course Searching ------------------------ //
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

// -------------- Reading Files -------------- //
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

void System::readingRegisterFile() {
    registerFile.readFile.open("register.txt");
    string line;
    while (getline(registerFile.readFile, line)) {
        stringstream ss(line);
        string code, name, intructorName;
        int studentId, creditHours;
        ss >> studentId >> code >> name >> creditHours >> intructorName;
        Course c;
        c.setName(name);
        c.setCourse_code(code);
        c.setCredit_hours(creditHours);
        c.setInstructorName(intructorName);
        registeredCourses[studentId].push_back(c);
    }
    registerFile.readFile.close();
}


void System:: readingStudentFile() {
    studentFile.readFile.open("student.txt");

    string line;

    while (getline(studentFile.readFile, line)) {
        stringstream ss(line);

        string name;
        int ID, level;

        ss >> ID >> name >> level;


        Student s;
        s.setName(name);
        s.setID(ID);
        s.setLevel(level);


        students[ID] = s;
    }

    studentFile.readFile.close();
}

// -------------- Print Data -------------- //
void System::printAllStudents() {
    for (auto& p: students) {
        Student& s = p.second;
        cout << "Student Name: " << s.getName() << endl;
        cout << "Student ID: " << s.getID() << endl;
        cout << "Student Level: " << s.getLevel() << endl;
        cout << endl;
        cout << "------------------------------\n";
    }
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

// converting to uppercase cuz all course names are Capitalized //
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

// ----------------------- Grades Section ----------------------- //


// adding grades to regestired course and making vector of pairs<Course, Grade>
void System::addGrade(int studentID, string courseName, double grade) {
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));
    // check the existance of the course in the map
    if (courses.find(courseName) == courses.end()) {
        cout << "Course is Not Exist\n";
        return;
    }

    bool found = false;
    string targetCode = courses[courseName].getCourse_code();
    // check the existance of the course in student registered courses
    for (int i = 0; i < registeredCourses[studentID].size(); i++) {
        if (courses[courseName].getCourse_code() == registeredCourses[studentID][i].getCourse_code()) {
            found = true;
        }
    }
    if (!found) {
        cout << "Can't add grade for " << courseName << ", because this course is not assigned to you!\n";
        return;
    }
    bool alreadyAdded = false;

    for (auto & addedGrade: grades[studentID]) {
        if (targetCode == addedGrade.first.getCourse_code()) {
            alreadyAdded = true;
            break;
        }
    }
    if (!alreadyAdded) {
        grades[studentID].push_back(make_pair(courses[courseName], grade));
    }
}

// editing grades
void System::editGrade(int studentID, string courseName, double newGrade) {
    bool found = false;
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));
    string targetCode = courses[toUpperCase(courseName)].getCourse_code();
    for (int i = 0; i < grades[studentID].size(); i++){
        if (targetCode == grades[studentID][i].first.getCourse_code()) {
            grades[studentID][i].second = newGrade;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Can't edit grade for " << courseName << ", because there is no previous grades!\n";

}


// getting grades by course name
void System::getGrade(int studentID,string courseName) {
    bool found = false;
    double courseGrade;
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));
    string courseCode, cName;
    string studentName = students[studentID].getName();
    for (auto& c: grades[studentID]) {
        if (c.first.getName() == courseName) {
            found = true;
            c.second;
            courseCode = c.first.getCourse_code();
            cName = c.first.getName();
            break;
        }
    }
    if (found) {
        cout << "Student Name: " << studentName << endl;
        cout << "Subject Name: " << cName << ", " << "& Code: " << courseCode << endl;
        cout << "Your degree is: " << courseGrade << endl;
    }
    else {
        cout << "Check your ID & Course Name!\n";
    }

}

// view all grades for specific student
void System::viewGrades(int studentID) {
    for (auto& c: grades[studentID]) {
        cout << "Course: " << c.first.getName() << endl;
        cout << "Grade: " << c.second << endl;
    }
}

// calculate gpa for specific student
double System::calculateGPA(int studentID) {
    double totalCreditHours = 0, totalGrades = 0;
    for (auto& c: grades[studentID]) {
        totalCreditHours += c.first.getCredit_hours();
        totalGrades += c.second;
    }
    double gpa = totalGrades/totalCreditHours;
    return gpa;
}

// getting full report on specific student
void System::generateReport(int studentID) {
    cout << "--------- Student Report ---------\n";
    cout << "Name: " << students[studentID].getName() << endl;
    cout << "ID: " << students[studentID].getID() << endl ;
    cout << "--- Grades ---\n";
    viewGrades(studentID);
    cout << "------\n";
    cout << "GPA: " << calculateGPA(studentID) << endl;
    cout << "----------------------------------\n";
}

// showCourses for students before regesteration
void System::showSpecificCourse() {
    cout << "Welcome to Course Registration :)\n";
    cout << "How do you want to search for Courses?\n";
    cout << "Press 1 to search by Course Code & 2 to search by Course Name: ";
    string input; cin >> input; // passing code or name
    if (input == "1") {
        string code;
        cout << "Enter the code of Course you want: ";
        cin >> code;
        code = handleSpaceToUnderScore(toUpperCase(code));
        bool found = false;
        // handling typo & ensuring that the course exist
        for (auto& c: courses) {
            if (c.second.getCourse_code() == code) {
                found = true;
                break;
            }
        }
        // printing the course info by code passed by the user
        if (found) {
            cout << "---------- Course Found ----------\n";
            cout << "Course Name: ";
            cout << searchCourseByCode(code).getName();
            cout <<"\nCourse Credit Hours: ";
            cout << searchCourseByCode(code).getCredit_hours();
            cout << "\nCourse Credit Hours: ";
            cout << searchCourseByCode(code).getCredit_hours();
            cout << "\nCourse Instructor: ";
            cout << searchCourseByCode(code).getInstructorName();
            cout << "\nCourse Description: ";
            cout << searchCourseByCode(code).getDescription();
            cout << "------------------------\n";
        // handling conditions
        }else {
            cout << "Course Not Found!\n";
        }
        // if the user need courses info by pass course name
    }else if (input == "2") {
        string name;
        cout << "Enter Course Name: ";
        cin >> name;
        // to be sure that the name is similar to courseName written in the file
        name = handleSpaceToUnderScore(toUpperCase(name));
        bool found = false;
        for (auto& c: courses) {
            if (c.second.getName() == name) {
                found = true;
                break;
            }
            // printing course info by pass it's name
        }if (found) {
            cout << "---------- Course Found ----------\n";
            cout << "Course Name: ";
            cout << searchCourseByName(name).getName();
            cout << "Course Code: ";
            cout << searchCourseByName(name).getCourse_code();
            cout <<"\nCourse Credit Hours: ";
            cout << searchCourseByName(name).getCredit_hours();
            cout << "\nCourse Credit Hours: ";
            cout << searchCourseByName(name).getCredit_hours();
            cout << "\nCourse Instructor: ";
            cout << searchCourseByName(name).getInstructorName();
            cout << "\nCourse Description: ";
            cout << searchCourseByName(name).getDescription();
            cout << "------------------------\n";
        }else {
            cout << "Course Not Found!\n";
        }
    }else {
        cout << "Invalid Option :(\n";
    }
    cout << "Do you want to Register Specific Course ?(y / n)\n";
    char ans; cin >> ans;
    if (ans == 'y') {
        courseRegisteration();
    }
    else {
        cout << "Thanks for Coming!\n";
    }
}
void System::courseRegisteration() {
    int studentID;
    string courseName;
    cout << "Enter your ID: ";
    cin >> studentID;
    cout << "Enter course you want to register: ";
    cin >> courseName;
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));
    bool found = false;
    for (auto& c: courses) {
        if (c.second.getName() == courseName) {
            found = true;
            break;
        }
    }
    if (found && checkPrerequesites(studentID ,courseName)) {
        registeredCourses[studentID].push_back(courses[courseName]);
        cout << "Congrats :)\nCourse have been Registered Successfully!\n";
    }


}

bool System::checkPrerequesites(int studentID,string courseName) {
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));
    bool found = 0;
    vector<string>& prereq = courses[courseName].getPrerequest();
    vector<Course>& passed = passedCourses[studentID];
    if (prereq.empty()) {
        cout << "You can register this course\n";
        return true;
    }
    for (auto& req: prereq) {
        found = false;
        for (auto& p: passed) {
            if (req == p.getName()) {
                found = true;
                break;
            }
        }
    }
    if (!found) {
        cout << "You can't register this course\n";
        return false;
    }
    cout << "You can regiseter this course\n";
    return true;
}