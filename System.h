#ifndef UNTITLED3_SYSTEM_H
#define UNTITLED3_SYSTEM_H
#include <unordered_map>
#include<fstream>
#include <vector>

class Course;
using namespace std;

struct File {
    ifstream readFile;
    ofstream editFile;
};

class System {
private:
    unordered_map<string, Course> courses;
    File courseFile;


public:
    System();
    Course searchCourseByName(string courseName);
    Course searchCourseByCode(string courseCode);
    void readingCourseFile();
    void printCourses(); //made chat do it cuz i am bored to do it
    string toUpperCase(string str);
    string handleSpaceToUnderScore(string str);
    vector<Course> getCourses();
    void setCourses(vector<Course> courses);

};


#endif