#include <map>
#include <string>
#include<fstream>
using namespace std;

class Course {

public:
    Course();



    //setters and getters
    string getName();
    void setName( string name);
    string getCourse_code() ;
    void setCourse_code( string course_code);

    string getDescription();
    void setDescription( string description);

    int getCredit_hours() ;
    void setCredit_hours(int credit_hours);

    map<string, bool> getPrerequest();
    void setPrerequest( map<string, bool> prerequest);

    string getInstructorName();
    void setInstructorName( string instructor_name);



private:
    string name,code;
    string description;
    int creditHours;
    string instructor_name;
    map<string,bool> prerequest;


};