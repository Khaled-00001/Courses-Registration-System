# 🎓 Course Registration System

> A robust, dual-interface C++ application engineered with a user-first perspective, bridging core backend software engineering with intuitive UI/UX design to provide seamless academic management.

---

## 📖 Project Overview

The **Course Registration System** is a comprehensive academic management solution designed to handle student enrollments, course prerequisites, and grading. Built entirely in C++, the architecture emphasizes clean data persistence through custom file handlers and offers two distinct user experiences: a feature-rich graphical interface powered by the **Qt Framework** and a lightweight, high-performance **Terminal/CLI** version.

Whether you are an administrator managing the curriculum or a student mapping out your semester, this system provides the tools necessary for efficient, error-free registration.

---

## ✨ Key Features

### 👨‍🎓 Student Portal

- **Course Registration:** Seamlessly enroll in available subjects.
- **Prerequisite Checking:** Automatically view required foundational courses before registration.
- **Grade Tracking:** Access overall academic standing or query grades for specific subjects.
- **Personalized Dashboard:** View currently registered courses linked securely to the student ID.

### 🛡️ Administrator Panel

- **Student Management:** Add new students to the database and edit existing profiles (Seat Number, Name, Level).
- **Course Management:** Create, update, and manage course offerings (Code, Name, Prerequisites, and Specifications).
- **Grade Administration:** Input and update student grades securely.

### 🔍 Core System Capabilities

- **Advanced Search:** Locate courses instantly using Course Code or Course Name.
- **Persistent File Handling:**
  - `Students Database:` Stores comprehensive student details securely.
  - `Registration Ledger:` Maps Student IDs to their respective registered course codes.

---

## 🖥️ System Interfaces & Walkthrough

To accommodate different environments and user preferences, the system is deployed in two versions. Replace the placeholder paths below with the actual paths to your screenshots (e.g., `./images/login.png`).

### 🎨 1. Graphical User Interface (Qt Version)

The GUI version focuses on accessibility and clean navigation, ensuring a modern user experience.

#### **Authentication**

Secure entry point for both Admins and Students.

![Login Page GUI](/Images/GUI_version/login_page.png)

#### **Admin Experience**

The central hub for managing the system's data.

![Admin Dashboard GUI](/Images/GUI_version/Admin_Dashboard.png)

Managing the curriculum requires precision. This module allows admins to define course codes, names, and prerequisites.

![Add & Edit Course GUI](/Images/GUI_version/Add_Edit_Course.png)

#### **Student Experience**

A clear, intuitive overview of the student's academic journey and enrolled subjects.

![Student Dashboard GUI](/Images/GUI_version/Student_Dashboard.png)

Students and Admins can rapidly find subjects using the search utility.

![Search for Courses GUI](/Images/GUI_version/Search_for_Course.png)

---

### 💻 2. Terminal / Command Line Interface

The CLI version strips away the graphical overhead, offering rapid execution and a deep dive into the core C++ logic.

#### **Admin Access & Control**

Secure terminal login for system administrators.

![Admin Login Terminal](/Images/terminal_version/admin_login.png)

The main control view for terminal administrators to execute commands.

![Admin View Terminal](/Images/terminal_version/admin_view_courses.png)

Executing course modifications directly via command line prompts.

![Edit Courses View Terminal](/Images/terminal_version/edit_course.png)

#### **Student Access**

A clean, text-based output displaying the student's registered curriculum and academic standing.

![Student Courses View Terminal](/Images/terminal_version/student_view_courses.png)

---

## 🗄️ Data Architecture & File Handling

The system relies on a custom flat-file database approach to ensure data remains persistent between sessions:

1. **`students.txt`**: Stores the core demographics `[Seat Number | Name | Level]`.
2. **`courses.txt`**: Stores course blueprints `[Course Code | Name | Prerequisites | Specs]`.
3. **`registry.txt`**: The relational ledger bridging the data, storing `[Student ID -> Array of Registered Course Codes]`.

---

## 🛠️ Technology Stack

- **Core Language:** C++
- **GUI Framework:** Qt
- **Data Storage:** File I/O (File Streams)
- **Architecture:** Modular Object-Oriented Programming (OOP)

## 🚀 Getting Started

1. Clone the repository.
2. Compile the CLI version using standard `g++` or your preferred C++ compiler.
