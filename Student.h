#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student {
private:
    string name;
    int id;
    int level;
    string password;

public:
    Student();
    Student(string name, int id, int level);

    void setName(string name);
    string getName();

    void setID(int id);
    int getID();
    void setPassword(string pass);
    string getPassword();
    void setLevel(int level);
    int getLevel();
};

#endif
