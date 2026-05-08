#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "System.h"
#include "Admin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Login
    void on_btnLoginAdmin_clicked();
    void on_btnLoginStudent_clicked();

    // Student dashboard
    void on_btnSearchCourse_clicked();
    void on_btnRegisterCourse_clicked();
    void on_btnViewGrades_clicked();
    void on_btnViewGPA_clicked();
    void on_btnStudentLogout_clicked();

    // Course search page
    void on_btnSearch_clicked();
    void on_btnBackFromSearch_clicked();

    // Register course page
    void on_btnRegister_clicked();
    void on_btnBackFromRegister_clicked();

    // Grades page
    void on_btnBackFromGrades_clicked();

    // Admin dashboard
    void on_btnManageCourses_clicked();
    void on_btnManageStudents_clicked();
    void on_btnAddGrade_clicked();
    void on_btnViewAllStudents_clicked();
    void on_btnAdminLogout_clicked();

    // Admin manage courses page
    void on_btnAddCourse_clicked();
    void on_btnEditCourse_clicked();
    void on_btnBackFromCourses_clicked();

    // Admin manage students page
    void on_btnAddStudent_clicked();
    void on_btnDeleteStudent_clicked();
    void on_btnViewStudents_clicked();
    void on_btnBackFromStudents_clicked();

private:
    Ui::MainWindow *ui;
    System system;
    Admin  admin;
    int    currentStudentID = -1;
    bool   isAdminLogged    = false;
};

#endif