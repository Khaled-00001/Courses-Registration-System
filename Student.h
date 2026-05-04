#include <string>
#include <vector>
#include "Course.h"
using namespace std;

#ifndef COURSE_REGESTIRATION_STUDENT_H
#define COURSE_REGESTIRATION_STUDENT_H
struct File {
    ifstream readFile;
    ofstream editFile;
};

class Student {
public:
    // constructors
    Student();
    Student(string name, int id, int level);

    // settes & getters
    string getName();
    void setName(string name);

    int getID();
    void setID(int id);

    int getLevel();
    void setLevel(int level);

    // core functionalities
    void courseRegisteration();
    void viewGrades();
    void addGrade(Course, double);
    void editGrade(Course, double);
    void getGrade(Course);
    bool checkPrerequisites(Course);
    double calculateGPA();
    void generateReport();
private:
    // identifying class attributes
    string name;
    int id;
    int level;
    float gpa;
    vector <Course> registeredCourses;
    vector <Course> passedCourses;
};


#endif //COURSE_REGESTIRATION_STUDENT_H