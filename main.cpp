#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QMessageBox>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // This makes the program read/write files from the SOURCE folder
    // so you only create course.txt / students.txt / register.txt once
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    a.setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #1e1e2e;
            color: #cdd6f4;
            font-family: 'Segoe UI';
            font-size: 14px;
        }
        QPushButton {
            background-color: #89b4fa;
            color: #1e1e2e;
            border: none;
            border-radius: 8px;
            padding: 10px 24px;
            font-weight: bold;
            min-width: 140px;
        }
        QPushButton:hover {
            background-color: #b4befe;
        }
        QPushButton:pressed {
            background-color: #74c7ec;
        }
        QLineEdit, QTextEdit, QSpinBox {
            background-color: #313244;
            border: 1px solid #45475a;
            border-radius: 6px;
            padding: 6px 10px;
            color: #cdd6f4;
        }
        QLineEdit:focus, QTextEdit:focus, QSpinBox:focus {
            border: 1px solid #89b4fa;
        }
        QLabel {
            color: #cdd6f4;
        }
        QRadioButton {
            color: #cdd6f4;
            spacing: 6px;
        }
        QRadioButton::indicator {
            width: 14px;
            height: 14px;
            border-radius: 7px;
            border: 2px solid #89b4fa;
            background: transparent;
        }
        QRadioButton::indicator:checked {
            background-color: #89b4fa;
        }
    )");

    MainWindow w;
    w.setMinimumSize(900, 650);
    w.show();
    return a.exec();
}