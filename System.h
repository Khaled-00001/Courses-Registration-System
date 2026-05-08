#ifndef UNTITLED3_SYSTEM_H
#define UNTITLED3_SYSTEM_H
#include <unordered_map>
#include<fstream>
#include <vector>
#include "Admin.h"

class Student;
class Course;
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
    unordered_map<int, vector<pair<Course, double>>> grades;
    unordered_map<int, vector<Course>> registeredCourses;
    unordered_map<int, vector<Course>> passedCourses;
    Admin admin;
    unordered_map<string, vector<string>> prerequisites; // courseCode -> prereqCodes

public:
    System();
    Course searchCourseByName(string courseName);
    Course searchCourseByCode(string courseCode);
    void courseRegisteration();
    void viewGrades(int);
    void addGrade(int ,string, double);
    void editGrade(int ,string, double);
    void checkPrerequesites(string);
    double calculateGPA(int);
    void generateReport(int);
    void getGrade(int ,string);
    void readingCourseFile();
    void readingStudentFile();
    void printCourses(); //made chat do it cuz i am bored to do it
    string toUpperCase(string str);
    string handleSpaceToUnderScore(string str);
    vector<Course> getCourses();
    void setCourses(vector<Course> courses);
    void printAllStudents();
    void showSpecificCourse();
    void readingRegisterFile();
    bool studentExists(int id);
    bool courseExists(string code);
    void addCourse();
    void editCourse(string code);

    //void deleteCourse(string code);
    void addStudent();
    void deleteStudent(int id);
    void registerStudentInCourse(int studentID, string courseCode);
    void addPrerequisite(string courseCode, string prereq);
    void viewPrerequisites(string courseCode);
 // integration
    void run();
    bool loginAdmin();
    void studentMenu(int id) ;
    void adminMenu() ;
    void saveStudents();
    void saveCourses();
    void saveRegistrations();

};



#endif