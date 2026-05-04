#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "Course.h"
using namespace std;

class Admin
{
private : 
	unordered_map<string, Course> courses;
	unordered_map<string, vector<string>> prerequisites;

public :
	void addCourse();
	void editCourse(string code);
	void showCourses();

	void addPrerequisite(string courseCode, string prereq);
	void viewPrerequisites(string courseCode);



	


};

