#include "System.h"
#include "Student.h"
#include "Course.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <cctype>
#include <QMessageBox>
// REMOVED: #include <iostream> — System no longer uses cout/cin anywhere.

// ─────────────────────────────────────────────
// FIX 1 (Constructor): readRegisterFile() was never called.
// WHY: Registered courses were lost on every restart because the file was
//      never read back. Added call alongside the other two readers.
// ─────────────────────────────────────────────
System::System() {
    readingCourseFile();
    readingStudentFile();
    readingRegisterFile();   // <-- ADDED
}

// ─────────────────────────────────────────────
// Course Searching — unchanged logic, still correct.
// ─────────────────────────────────────────────
Course System::searchCourseByName(string courseName) {
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));
    return courses[courseName];
}

Course System::searchCourseByCode(string courseCode) {
    courseCode = handleSpaceToUnderScore(toUpperCase(courseCode));
    for (auto& c : courses) {
        if (c.second.getCourse_code() == courseCode) {
            return courses[c.second.getName()];
        }
    }
    return Course();
}

// ─────────────────────────────────────────────
// Helpers — unchanged
// ─────────────────────────────────────────────
string System::toUpperCase(string str) {
    string s;
    for (auto& c : str) {
        c = toupper(c);
        s += c;
    }
    return s;
}

string System::handleSpaceToUnderScore(string str) {
    for (int i = 0; i < (int)str.size(); i++) {
        if (str[i] == ' ') str[i] = '_';
    }
    return str;
}

// ─────────────────────────────────────────────
// FIX 2 (readingCourseFile): Key normalisation.
// WHY: The map key must be uppercase+underscore (e.g. "DATA_STRUCTURES")
//      to match what searchCourseByName() produces when the GUI calls it.
//      Before, the raw name from the file was used as-is, so searches missed.
// ─────────────────────────────────────────────
void System::readingCourseFile() {
    courseFile.readFile.open("course.txt");
    string line;
    while (getline(courseFile.readFile, line)) {
        stringstream ss(line);
        string code, name, description, instructor_name;
        int creditHours;
        ss >> code >> name >> description >> instructor_name >> creditHours;

        vector<string> prereq;
        string req;
        while (ss >> req) {
            prereq.push_back(req);
        }

        Course c;
        c.setName(name);
        c.setCourse_code(code);
        c.setCredit_hours(creditHours);
        c.setDescription(description);
        c.setInstructorName(instructor_name);
        c.setPrerequest(prereq);

        // FIX: normalise the key so searches always find their course.
        // BEFORE: courses[name] = c;
        // AFTER:
        string key = handleSpaceToUnderScore(toUpperCase(name));
        courses[key] = c;
    }
    courseFile.readFile.close();
}

// ─────────────────────────────────────────────
// FIX 3 (readingStudentFile): File name mismatch.
// WHY: addStudent() wrote to "students.txt" (with an 's') but this
//      function opened "student.txt" — saved students never reloaded.
//      Unified to "students.txt" everywhere (also fixed in addStudent below).
// ─────────────────────────────────────────────
void System::readingStudentFile()
{
    studentFile.readFile.open("students.txt");

    string name, password;
    int ID, level;

    while (studentFile.readFile >> ID >> name >> level >> password)
    {
        Student s;
        s.setName(name);
        s.setID(ID);
        s.setLevel(level);
        s.setPassword(password);


        students[ID] = s;
    }

    studentFile.readFile.close();
}
void System::readingRegisterFile() {
    registerFile.readFile.open("register.txt");
    string line;
    while (getline(registerFile.readFile, line)) {
        stringstream ss(line);
        string code, name, instructorName;
        int studentId, creditHours;
        ss >> studentId >> code >> name >> creditHours >> instructorName;
        Course c;
        c.setName(name);
        c.setCourse_code(code);
        c.setCredit_hours(creditHours);
        c.setInstructorName(instructorName);
        registeredCourses[studentId].push_back(c);
    }
    registerFile.readFile.close();
}

// ─────────────────────────────────────────────
// FIX 4 (printAllStudents): Return string instead of cout.
// WHY: GUI cannot read console output. The function now builds and returns
//      the full text so the Qt widget can display it in a label or text area.
// ─────────────────────────────────────────────
string System::printAllStudents() {
    string result;
    for (auto& p : students) {
        Student& s = p.second;
        result += "Student Name: " + s.getName() + "\n";
        result += "Student ID: " + to_string(s.getID()) + "\n";
        result += "Student Level: " + to_string(s.getLevel()) + "\n\n";
        result += "------------------------------\n";
    }
    return result;
}

// ─────────────────────────────────────────────
// FIX 5 (printCourses): Return string instead of cout.
// ─────────────────────────────────────────────
string System::printCourses() {
    string result;
    for (auto& pair : courses) {
        Course& c = pair.second;
        result += "Course Name: " + c.getName() + "\n";
        result += "Code: " + c.getCourse_code() + "\n";
        result += "Credit Hours: " + to_string(c.getCredit_hours()) + "\n";
        result += "Description: " + c.getDescription() + "\n";
        result += "Instructor: " + c.getInstructorName() + "\n";
        result += "Prerequisite(s): ";
        for (int i = 0; i < (int)c.getPrerequest().size(); i++) {
            result += c.getPrerequest().at(i) + " ";
        }
        result += "\n------------------------\n";
    }
    return result;
}

vector<Course> System::getCourses() {
    vector<Course> course;
    for (auto& c : courses) {
        course.push_back(c.second);
    }
    return course;
}

void System::setCourses(vector<Course> course) {
    for (int i = 0; i < (int)course.size(); i++) {
        string key = handleSpaceToUnderScore(toUpperCase(course[i].getName()));
        courses[key] = course[i];
    }
}

// ─────────────────────────────────────────────
// FIX 6 (addGrade): Return string status instead of cout.
// WHY: GUI needs to display the result in a message box or label.
//      Kept all original validation logic — only replaced cout with return.
// ─────────────────────────────────────────────
string System::addGrade(int studentID, string courseName, double grade) {
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));

    if (courses.find(courseName) == courses.end()) {
        // BEFORE: cout << "Course is Not Exist\n"; return;
        return "Course does not exist.";
    }

    string targetCode = courses[courseName].getCourse_code();
    bool found = false;
    for (int i = 0; i < (int)registeredCourses[studentID].size(); i++) {
        if (targetCode == registeredCourses[studentID][i].getCourse_code()) {
            found = true;
        }
    }
    if (!found) {
        // BEFORE: cout << "Can't add grade for ..." << endl; return;
        return "Can't add grade for " + courseName + ": not registered for this course.";
    }

    bool alreadyAdded = false;
    for (auto& addedGrade : grades[studentID]) {
        if (targetCode == addedGrade.first.getCourse_code()) {
            alreadyAdded = true;
            break;
        }
    }
    if (!alreadyAdded) {
        grades[studentID].push_back(make_pair(courses[courseName], grade));
    }
    return "Grade added successfully.";
}

// ─────────────────────────────────────────────
// FIX 7 (editGrade): Consistent key normalisation + return string.
// WHY 1: The original code called toUpperCase() then accessed
//         courses[toUpperCase(courseName)] — double-normalising an already
//         normalised string. The lookup then used a key without underscores,
//         missing the course entirely.
// WHY 2: cout replaced with return string for GUI.
// ─────────────────────────────────────────────
string System::editGrade(int studentID, string courseName, double newGrade) {
    // BEFORE: courseName = handleSpaceToUnderScore(toUpperCase(courseName));
    //         string targetCode = courses[toUpperCase(courseName)].getCourse_code();
    //         (double-uppercase, and no underscore conversion on the second lookup)
    // AFTER: normalise once, use the same key for both.
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));
    string targetCode = courses[courseName].getCourse_code();

    for (int i = 0; i < (int)grades[studentID].size(); i++) {
        if (targetCode == grades[studentID][i].first.getCourse_code()) {
            grades[studentID][i].second = newGrade;
            return "Grade updated successfully.";
        }
    }
    // BEFORE: cout << "Can't edit grade ..." << endl;
    return "Can't edit grade for " + courseName + ": no previous grade found.";
}

// ─────────────────────────────────────────────
// FIX 8 (getGrade): Uninitialized variable + return value for GUI.
// WHY 1: `courseGrade` was declared but never assigned — `c.second;` is a
//         no-op expression. The printed grade was garbage memory.
//         Fixed: courseGrade = c.second;
// WHY 2: cout replaced — returns a string the GUI can show.
// ─────────────────────────────────────────────
string System::getGrade(int studentID, string courseName) {
    bool found = false;
    double courseGrade = 0.0;
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));
    string courseCode, cName;
    string studentName = students[studentID].getName();

    for (auto& c : grades[studentID]) {
        if (c.first.getName() == courseName) {
            found = true;
            courseGrade = c.second;   // BEFORE: c.second;  (no-op — unread)
            courseCode = c.first.getCourse_code();
            cName = c.first.getName();
            break;
        }
    }

    if (found) {
        return "Student: " + studentName +
               "\nCourse: " + cName + " (" + courseCode + ")" +
               "\nGrade: " + to_string(courseGrade);
    }
    // BEFORE: cout << "Check your ID & Course Name!\n";
    return "No grade found. Check student ID and course name.";
}

// ─────────────────────────────────────────────
// FIX 9 (viewGrades): Return string instead of cout.
// ─────────────────────────────────────────────
string System::viewGrades(int studentID) {
    string result;
    for (auto& c : grades[studentID]) {
        result += "Course: " + c.first.getName() + "\n";
        result += "Grade: " + to_string(c.second) + "\n";
    }
    if (result.empty()) result = "No grades recorded.";
    return result;
}

double System::calculateGPA(int studentID) {
    double totalCreditHours = 0, totalGrades = 0;
    for (auto& c : grades[studentID]) {
        totalCreditHours += c.first.getCredit_hours();
        totalGrades += c.second;
    }
    if (totalCreditHours == 0) return 0.0;
    return totalGrades / totalCreditHours;
}

// ─────────────────────────────────────────────
// FIX 10 (generateReport): Return string instead of cout.
// ─────────────────────────────────────────────
string System::generateReport(int studentID) {
    string result;
    result += "--------- Student Report ---------\n";
    result += "Name: " + students[studentID].getName() + "\n";
    result += "ID: " + to_string(students[studentID].getID()) + "\n";
    result += "--- Grades ---\n";
    result += viewGrades(studentID);
    result += "------\n";
    result += "GPA: " + to_string(calculateGPA(studentID)) + "\n";
    result += "----------------------------------\n";
    return result;
}

// ─────────────────────────────────────────────
// FIX 11 (checkPrerequesites): Missing return + wrong function name.
// WHY: Function declared bool but had zero logic and no return — undefined
//      behaviour / crash. Also called viewPrerequesites() which doesn't exist.
//      Now implements actual prerequisite checking against completed grades.
// ─────────────────────────────────────────────
bool System::checkPrerequesites(int studentID, string courseName) {
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));

    if (courses.find(courseName) == courses.end()) {
        return false;
    }

    vector<string> prereqs = courses[courseName].getPrerequest();

    // No prerequisites → student is always eligible
    if (prereqs.empty()) return true;

    // Build set of course codes the student has already passed (grade >= 50)
    for (auto& prereqCode : prereqs) {
        bool passed = false;
        for (auto& g : grades[studentID]) {
            if (g.first.getCourse_code() == prereqCode && g.second >= 50.0) {
                passed = true;
                break;
            }
        }
        if (!passed) return false;   // missing at least one prerequisite
    }
    return true;
}

// ─────────────────────────────────────────────
// FIX 12 (addCourse): cin/cout replaced with parameters.
// WHY: GUI passes the values directly — no console interaction needed.
//      Duplicate-check now uses the normalised name key (not code), which
//      matches how courses[] is actually keyed.
//      Returns a string result the GUI can show in a message box.
// ─────────────────────────────────────────────
string System::addCourse(string name, string code, string desc, string instructor, int ch) {
    string key = handleSpaceToUnderScore(toUpperCase(name));

    // BEFORE: if (courses.find(code) != courses.end()) — wrong key type
    // AFTER: check by normalised name key
    if (courses.find(key) != courses.end()) {
        return "Course already exists.";
    }

    Course c;
    c.setName(name);
    c.setCourse_code(code);
    c.setDescription(desc);
    c.setCredit_hours(ch);
    c.setInstructorName(instructor);

    courses[key] = c;

    courseFile.editFile.open("course.txt", ios::app);
    courseFile.editFile << code << " " << name << " "
                        << desc << " " << instructor << " " << ch << "\n";
    courseFile.editFile.close();

    return "Course added successfully.";
}

// ─────────────────────────────────────────────
// FIX 13 (editCourse): cin/cout loop replaced with individual setters.
// WHY: GUI sends the new values directly. Each field is optional — pass
//      an empty string to leave it unchanged.
//      Returns a string result for the GUI.
// ─────────────────────────────────────────────
string System::editCourse(string code, string newName, string newDesc, int newCH, string newInstructor) {
    // Find course by code (iterate map — map is keyed by name, not code)
    string foundKey;
    for (auto& pair : courses) {
        if (pair.second.getCourse_code() == code) {
            foundKey = pair.first;
            break;
        }
    }
    if (foundKey.empty()) {
        return "Course not found.";
    }

    if (!newName.empty())       courses[foundKey].setName(newName);
    if (!newDesc.empty())       courses[foundKey].setDescription(newDesc);
    if (newCH > 0)              courses[foundKey].setCredit_hours(newCH);
    if (!newInstructor.empty()) courses[foundKey].setInstructorName(newInstructor);

    return "Course updated successfully.";
}

void System::addPrerequisite(string code, string prereq) {
    if (courses.find(code) == courses.end()) return;
    prerequisites[code].push_back(prereq);
}

string System::viewPrerequisites(string code) {
    string result = "Prerequisites: ";
    if (courses.find(code) == courses.end()) {
        return "Course not found.";
    }
    if (prerequisites[code].empty()) {
        result += "None";
    } else {
        for (auto& p : prerequisites[code]) {
            result += p + " ";
        }
    }
    return result;
}

// ─────────────────────────────────────────────
// FIX 14 (): cin/cout replaced with parameters + file name fix.
// WHY 1: GUI passes values directly.
// WHY 2: File was "students.txt" here but reader opened "student.txt" — now
//         both consistently use "students.txt".
// ─────────────────────────────────────────────
string System::addStudent(string name, int id, int level, string password)
{
    if (students.find(id) != students.end())
        return "Student already exists.";

    Student s(name, id, level);
    s.setPassword(password);

    students[id] = s;

    studentFile.editFile.open("students.txt", ios::app);
    studentFile.editFile << id << " " << name << " " << level << " " << password << "\n";
    studentFile.editFile.close();

    return "Student added successfully.";
}
string System::deleteStudent(int id) {
    if (students.find(id) == students.end()) {
        return "Student not found.";
    }
    students.erase(id);
    grades.erase(id);
    registeredCourses.erase(id);
    return "Student deleted successfully.";
}

// ─────────────────────────────────────────────
// FIX 15 (studentExists / courseExists): These were called but never defined.
// WHY: registerStudentInCourse() called them → linker error.
//      Added as simple map-lookup helpers.
// ─────────────────────────────────────────────
bool System::studentExists(int id) {
    return students.find(id) != students.end();
}

bool System::courseExists(string code) {
    for (auto& pair : courses) {
        if (pair.second.getCourse_code() == code) return true;
    }
    return false;
}

// ─────────────────────────────────────────────
// FIX 16 (registerStudentInCourse): Type mismatch + validation + return string.
// WHY: Original pushed `code` (a string) into `vector<Course>` — compile error.
//      Now looks up the Course object by code and pushes that instead.
//      Also saves to register.txt for persistence.
// ─────────────────────────────────────────────
string System::registerStudentInCourse(int id, string code) {
    if (!studentExists(id)) return "Student not found.";
    if (!courseExists(code)) return "Course not found.";

    // FIX: find the actual Course object (map is keyed by name, not code)
    Course found;
    bool courseFound = false;
    for (auto& pair : courses) {
        if (pair.second.getCourse_code() == code) {
            found = pair.second;
            courseFound = true;
            break;
        }
    }
    if (!courseFound) return "Course not found.";

    // Prevent duplicate registration
    for (auto& c : registeredCourses[id]) {
        if (c.getCourse_code() == code) return "Already registered in this course.";
    }

    registeredCourses[id].push_back(found);

    registerFile.editFile.open("register.txt", ios::app);
    registerFile.editFile << id << " " << found.getCourse_code() << " "
                          << found.getName() << " " << found.getCredit_hours() << " "
                          << found.getInstructorName() << "\n";
    registerFile.editFile.close();

    return "Registered successfully.";
}

// ─────────────────────────────────────────────
// FIX 17 (courseRegisteration): Uninitialized bool + cin/cout removed.
// WHY: `bool found` was not initialised — undefined behaviour on the if(found)
//      check if the loop body never ran. Refactored to accept parameters so
//      the GUI can call it directly. Returns a status string.
// ─────────────────────────────────────────────
string System::courseRegisteration(int studentID, string courseName) {
    courseName = handleSpaceToUnderScore(toUpperCase(courseName));

    // BEFORE: bool found;  ← uninitialised
    // AFTER:
    bool found = false;
    for (auto& c : courses) {
        if (c.second.getName() == courseName) {
            found = true;
            break;
        }
    }

    if (found) {
        registeredCourses[studentID].push_back(courses[courseName]);
        return "Course registered successfully.";
    }
    return "Course not found.";
}Student System::getStudent(int id)
{
    return students[id];
}
