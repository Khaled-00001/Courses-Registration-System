#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("Course Registration System");
    ui->stackedWidget->setCurrentIndex(0); // always start at login
}

MainWindow::~MainWindow() {
    delete ui;
}

// ─── LOGIN ───────────────────────────────────────────────────────────────────

void MainWindow::on_btnLoginAdmin_clicked() {
    string user = ui->txtUsername->text().toStdString();
    string pass = ui->txtPassword->text().toStdString();

    if (admin.login(user, pass)) {
        isAdminLogged = true;
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

void MainWindow::on_btnLoginStudent_clicked()
{
    bool ok;
    int id = ui->txtUsername->text().toInt(&ok);
    string password = ui->txtPassword->text().toStdString();

    if (!ok || !system.studentExists(id))
    {
        QMessageBox::warning(this, "Login Failed", "Student ID not found.");
        return;
    }

    Student s = system.getStudent(id);

    if (s.getPassword() != password)
    {
        QMessageBox::warning(this, "Login Failed", "Incorrect password.");
        return;
    }

    currentStudentID = id;
    ui->stackedWidget->setCurrentIndex(7);
}

// ─── STUDENT DASHBOARD ───────────────────────────────────────────────────────

void MainWindow::on_btnSearchCourse_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_btnRegisterCourse_clicked() {
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_btnViewGrades_clicked() {
    string grades = system.viewGrades(currentStudentID);
    double gpa    = system.calculateGPA(currentStudentID);
    ui->txtGradesDisplay->setText(QString::fromStdString(grades));
    ui->lblGPA->setText("GPA: " + QString::number(gpa, 'f', 2));
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_btnViewGPA_clicked() {
    double gpa = system.calculateGPA(currentStudentID);
    QMessageBox::information(this, "Your GPA",
                             "GPA: " + QString::number(gpa, 'f', 2));
}

void MainWindow::on_btnStudentLogout_clicked() {
    currentStudentID = -1;
    ui->txtUsername->clear();
    ui->txtPassword->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

// ─── COURSE SEARCH PAGE ──────────────────────────────────────────────────────

void MainWindow::on_btnSearch_clicked() {
    string input = ui->txtSearchInput->text().toStdString();
    Course result;

    if (ui->radioByCode->isChecked()) {
        result = system.searchCourseByCode(input);
    } else {
        result = system.searchCourseByName(input);
    }

    if (result.getName().empty()) {
        ui->txtSearchResult->setText("Course not found.");
        return;
    }

    QString info;
    info += "Name:        " + QString::fromStdString(result.getName())           + "\n";
    info += "Code:        " + QString::fromStdString(result.getCourse_code())    + "\n";
    info += "Credits:     " + QString::number(result.getCredit_hours())          + "\n";
    info += "Instructor:  " + QString::fromStdString(result.getInstructorName()) + "\n";
    info += "Description: " + QString::fromStdString(result.getDescription());
    ui->txtSearchResult->setText(info);
}

void MainWindow::on_btnBackFromSearch_clicked() {
    ui->stackedWidget->setCurrentIndex(isAdminLogged ? 0 : 1);
}

// ─── REGISTER COURSE PAGE ────────────────────────────────────────────────────

void MainWindow::on_btnRegister_clicked() {
    string courseName = ui->txtRegisterCourseName->text().toStdString();

    if (!system.checkPrerequesites(currentStudentID, courseName)) {
        ui->lblRegisterResult->setText("Prerequisites not met.");
        return;
    }

    string result = system.courseRegisteration(currentStudentID, courseName);
    ui->lblRegisterResult->setText(QString::fromStdString(result));
}

void MainWindow::on_btnBackFromRegister_clicked() {
    ui->stackedWidget->setCurrentIndex(7);
}

// ─── GRADES PAGE ─────────────────────────────────────────────────────────────

void MainWindow::on_btnBackFromGrades_clicked() {
    ui->stackedWidget->setCurrentIndex(7);
}

// ─── ADMIN DASHBOARD ─────────────────────────────────────────────────────────

void MainWindow::on_btnManageCourses_clicked() {
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btnManageStudents_clicked() {
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_btnViewAllStudents_clicked() {
    string all = system.printAllStudents();
    QMessageBox::information(this, "All Students",
                             QString::fromStdString(all));
}

void MainWindow::on_btnAddGrade_clicked() {
    bool ok;

    QString idStr = QInputDialog::getText(this, "Add Grade", "Enter Student ID:");
    int id = idStr.toInt(&ok);
    if (!ok) return;

    QString course = QInputDialog::getText(this, "Add Grade", "Enter Course Name:");
    if (course.isEmpty()) return;

    QString gradeStr = QInputDialog::getText(this, "Add Grade", "Enter Grade (0-100):");
    double grade = gradeStr.toDouble(&ok);
    if (!ok) return;

    string result = system.addGrade(id, course.toStdString(), grade);
    QMessageBox::information(this, "Result", QString::fromStdString(result));
}

void MainWindow::on_btnAdminLogout_clicked() {
    isAdminLogged = false;
    ui->txtUsername->clear();
    ui->txtPassword->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

// ─── ADMIN: MANAGE COURSES ───────────────────────────────────────────────────

void MainWindow::on_btnAddCourse_clicked() {
    string name       = ui->txtCourseName->text().toStdString();
    string code       = ui->txtCourseCode->text().toStdString();
    string desc       = ui->txtCourseDesc->text().toStdString();
    string instructor = ui->txtCourseInstructor->text().toStdString();
    int    ch         = ui->spinCreditHours->value();

    if (name.empty() || code.empty()) {
        ui->lblCourseResult->setText("Name and Code are required.");
        return;
    }

    string result = system.addCourse(name, code, desc, instructor, ch);
    ui->lblCourseResult->setText(QString::fromStdString(result));
}

void MainWindow::on_btnEditCourse_clicked() {
    string code       = ui->txtEditCode->text().toStdString();
    string name       = ui->txtEditName->text().toStdString();
    string desc       = ui->txtEditDesc->text().toStdString();
    string instructor = ui->txtEditInstructor->text().toStdString();
    int    ch         = ui->spinEditCH->value();

    if (code.empty()) {
        ui->lblCourseResult->setText("Course code is required.");
        return;
    }

    string result = system.editCourse(code, name, desc, ch, instructor);
    ui->lblCourseResult->setText(QString::fromStdString(result));
}

void MainWindow::on_btnBackFromCourses_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}

// ─── ADMIN: MANAGE STUDENTS ──────────────────────────────────────────────────

void MainWindow::on_btnAddStudent_clicked() {
    string name  = ui->txtStudentName->text().toStdString();
    int    id    = ui->spinStudentID->value();
    int    level = ui->spinStudentLevel->value();
    string password = ui->txtPassword->text().toStdString();
    if (name.empty()) {
        ui->lblStudentResult->setText("Student name is required.");
        return;
    }

    string result = system.addStudent(name, id, level,password);
    ui->lblStudentResult->setText(QString::fromStdString(result));
}

void MainWindow::on_btnDeleteStudent_clicked() {
    int id = ui->spinDeleteID->value();
    string result = system.deleteStudent(id);
    ui->lblStudentResult->setText(QString::fromStdString(result));
}

void MainWindow::on_btnViewStudents_clicked() {
    string all = system.printAllStudents();
    ui->txtStudentsDisplay->setText(QString::fromStdString(all));
}

void MainWindow::on_btnBackFromStudents_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}