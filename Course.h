#include <map>
#include <string>
#include<fstream>
#include <vector>
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

    vector<string> getPrerequest();
    void setPrerequest( vector<string> prerequest);

    string getInstructorName();
    void setInstructorName( string instructor_name);



private:
    string name,code;
    string description;
    int creditHours;
    string instructor_name;
    vector<string> prerequest;


};