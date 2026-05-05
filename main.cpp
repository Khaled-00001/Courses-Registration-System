#include <iostream>
#include<fstream>
#include <cctype>
#include "Course.h"
#include "System.h"
using namespace std;



int main() {
    System system;


    vector<Course> co=system.getCourses();
    Course c1;

    c1.setName("3elm nafs");
    co.push_back(c1);
    system.setCourses(co);
    system.printCourses();
    /*cout<<"Hereeeeeeeee\n";
    cout<<system.searchCourseByCode("cS304").getName()<<endl;
    cout<<system.searchCourseByName("oop").getCourse_code()<<endl;*/

    return 0;
}
