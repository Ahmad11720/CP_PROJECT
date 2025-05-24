
Student Management System (C++ Project)
--------------------------------------

Overview:
This project is a console-based Student Management System built in C++ using procedural programming and file handling. It allows users to manage student records, including adding, viewing, updating, deleting, sorting, and exporting data. The project emphasizes modular design and input validation using arrays and functions.

Requirements:
- Visual Studio 2019/2022 or later (or any C++ IDE)
- A C++17-compatible compiler
- Windows OS (for colored console output using <windows.h>)

Setup Instructions:
1. Clone or Download the Project
   - Ensure all source files are present (main.cpp, students.txt if available, etc.)

2. Open the Project in Visual Studio
   - Double-click the solution file (.sln) if available
   - Or open Visual Studio > File > Open > Project/Solution

3. Build the Project
   - Build > Build Solution or press Ctrl+Shift+B

Run Instructions:
- From Visual Studio:
  - Press F5 (Debug) or Ctrl+F5 (Run without debugging)
- From Executable:
  - Navigate to ./Debug/ or ./Release/ folder and run StudentManagementSystem.exe

Data Handling:
- Uses 'students.txt' for data storage
- Optionally exports to 'students.csv' for Excel-compatible viewing

Features:
- Add Student
- View Students (Read)
- Update Student Details
- Delete Student Record
- Search by Roll Number or Name
- Count Total Students
- Calculate Average Age
- Find Oldest/Youngest Students
- Sort by Roll Number
- Reverse Display Order
- Search by Age Range
- Export to CSV
- Clear All Data (with confirmation)

Notes:
- All input is validated to avoid crashes or invalid data
- File handling ensures persistent storage
- Uses text colors via <windows.h> to enhance console UI

Developer:
Ahmad Qureshi
Roll Number: 01-134251-011
