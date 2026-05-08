#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
using namespace std;

class Course {
private:
    string name;
    string code;
    string description;
    string instructor_name;
    int creditHours;
    vector<string> prerequest;

public:
    Course();

    string getName();
    void setName(string name);

    string getCourse_code();
    void setCourse_code(string course_code);

    int getCredit_hours();
    void setCredit_hours(int credit_hours);

    string getDescription();
    void setDescription(string description);

    string getInstructorName();
    void setInstructorName(string instructor_name);

    vector<string> getPrerequest();
    void setPrerequest(vector<string> prerequest);
};

#endif
