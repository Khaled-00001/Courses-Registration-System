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



private:
    // identifying class attributes
    string name;
    int id;
    int level;
    float gpa;

};


#endif //COURSE_REGESTIRATION_STUDENT_H