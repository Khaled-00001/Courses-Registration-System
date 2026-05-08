#ifndef SYSTEM_H
#define SYSTEM_H

#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>
#include "Course.h"
#include "Student.h"

using namespace std;

struct File {
    ifstream readFile;
    ofstream editFile;
};

class System {
private:
    File courseFile;
    File studentFile;
    File registerFile;

    unordered_map<string, Course> courses;
    unordered_map<int, Student> students;
    unordered_map<int, vector<pair<Course,double>>> grades;
    unordered_map<int, vector<Course>> registeredCourses;
    unordered_map<int, vector<Course>> passedCourses;
    unordered_map<string, vector<string>> prerequisites;

    string toUpperCase(string str);
    string handleSpaceToUnderScore(string str);

    void readingCourseFile();
    void readingStudentFile();
    void readingRegisterFile();

public:
    System();

    Course searchCourseByName(string courseName);
    Course searchCourseByCode(string courseCode);

    string printAllStudents();
    string printCourses();

    vector<Course> getCourses();
    void setCourses(vector<Course> courses);

    string addGrade(int studentID, string courseName, double grade);
    string editGrade(int studentID, string courseName, double newGrade);
    string getGrade(int studentID, string courseName);
    string viewGrades(int studentID);
    string generateReport(int studentID);
    double calculateGPA(int studentID);

    bool checkPrerequesites(int studentID, string courseName);
    void addPrerequisite(string courseCode, string prereq);
    string viewPrerequisites(string courseCode);

    string addCourse(string name, string code, string desc,
                     string instructor, int ch);

    string editCourse(string code, string newName, string newDesc,
                      int newCH, string newInstructor);

    string addStudent(string name, int id, int level, string password);
    string deleteStudent(int id);

    string courseRegisteration(int studentID, string courseName);
    string registerStudentInCourse(int studentID, string courseCode);

    bool studentExists(int id);
    bool courseExists(string code);
    Student getStudent(int id);
};

#endif