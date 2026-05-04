#include "Admin.h"
#include <string>
#include <iostream>
using namespace std;

void Admin::addCourse() {

	Course c;
	string name, courseCode, descreption, instructorName;
	int ch;
	cout << "Enter course title \n ";
    cin.ignore();
    getline(cin, name);
	cout << "Enter course code \n ";
	cin >> courseCode;
    if (courses.find(courseCode) != courses.end()) {
        cout << "Course already exists!\n";
        return;
    }
	cout << "Enter course descreption \n ";
	cin >> descreption;
	cout << "Enter course credit hours \n ";
	cin >> ch;
	cout << "Enter course instructor name\n ";
	cin >> instructorName;

	c.setName(name);
	c.setCourse_code(courseCode);
	c.setCredit_hours(ch);
	c.setDescription(descreption);
	c.setInstructorName(instructorName);
    courses[courseCode] = c;

    cout << " Enter the number of prerequisites \n ";
    int prereqNum;
    cin >> prereqNum;
    string prereqcode;
    for (int i = 0; i < prereqNum; i++) {
        cout << "enter the " << i + 1 << "prerequisite \n ";
        cin >> prereqcode;
        prerequisites[courseCode].push_back(prereqcode);
    }

}
void Admin::editCourse(string code) {
        if (courses.find(code) == courses.end()) {
            cout << "Course not found!\n";
            return;
        }


        
        int choice;

        while (true) {
            cout << "\nEditing course: " << courses[code].getName() << endl;

            cout << "1. Edit Name\n";
            cout << "2. Edit Description\n";
            cout << "3. Edit Credit Hours\n";
            cout << "4. Edit Instructor\n";
            cout << "5. add prerequisite\n";
            cout << "6. delete prerequisite\n";
            cout << "7. Exit\n";

            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) {
                string name;
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, name);
                courses[code].setName(name);
            }
            else if (choice == 2) {
                string desc;
                cout << "Enter new description: ";
                cin.ignore();
                getline(cin, desc);
                courses[code].setDescription(desc);
            }
            else if (choice == 3) {
                int ch;
                cout << "Enter new credit hours: ";
                cin >> ch;
                courses[code].setCredit_hours(ch);
            }
            else if (choice == 4) {
                string instructor;
                cout << "Enter instructor name: ";
                cin.ignore();
                getline(cin, instructor);
                courses[code].setInstructorName(instructor);
            }
            else if (choice == 5) {
                cout << "Current prerequisites : \n ";
                for (int i = 0; i < prerequisites[code].size(); i++) {
                    cout << i << ": " << prerequisites[code][i] << endl;
                }
                cout << "\n Enter prerequisite \n";
                string prereq;
                cin >> prereq;
                prerequisites[code].push_back(prereq);
                break;
            }
            else if (choice == 6) {
                cout << "Current prerequisites \n ";
                for (int i = 0; i < prerequisites[code].size(); i++) {
                    cout << i << ": " << prerequisites[code][i] << endl;
                }

                cout << "Enter index of prerequisite  \n";
                int index;
                cin >> index;
                if (index > prerequisites[code].size()) {
                    cout << "invalid index \n ";
                    break;
                }
                else {
                    prerequisites[code].erase((prerequisites[code].begin() + index));

                    break;
                }
            }
            else if (choice == 7) {
                cout << "Exiting edit menu...\n";
                break;
            }
            else {
                cout << "Invalid choice!\n";
            }
        }

        cout << "Course updated successfully!\n";

        
 }

void Admin::showCourses() {
    for (auto& c : courses) {
        cout << c.first << "  " << c.second.getName() << "\n";
    }
}


void Admin::addPrerequisite(string courseCode, string prereq) {
   
    if (courses.find(courseCode) == courses.end()) {
        cout << "Course not found!\n";
        return;
    }
    prerequisites[courseCode].push_back(prereq);

}



void Admin::viewPrerequisites(string courseCode) {
    if (courses.find(courseCode) == courses.end()) {
        cout << "Course not found!\n";
        return;
    }
    
    cout << "To registre " << courseCode << " you have to pass : ";
    
    if (!prerequisites[courseCode].empty()) {
        for (auto it : prerequisites[courseCode]) {
            cout << it << " ";

        }
    }
    else
        cout << "No prerequisites ";
    cout << endl;
}



