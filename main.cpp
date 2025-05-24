#include <iostream> //Basic input output stream library
#include <string> //For using string and string related functions
#include <fstream> //For file handling
#include <iomanip> //For displaying formatted output
#include <windows.h> //For colors 
using namespace std;

const int MAX = 100; // Define a constant MAX with value 100 for the maximum number of students.
int rollNumbers[MAX]; //Integer array to store roll numbers.
string names[MAX]; //Array to store names
int ages[MAX]; //Array to store ages
int s_count = 0; //Initializing student count with 0.

const string PASSWORD = "admin123"; // A predefined password

// Function to set console text color
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

char toLowerChar(char c) //Converts uppercase into lowercase and lowercase remains same
{
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

string toLowerCase(const string& str) //The lowercase character from above function are converted to a whole string.
{
    string lower;
    for (char c : str) //Loop ranges over the string str one character at a time.
        lower += toLowerChar(c);
    return lower;
}

void printHeader() //Function that is simply printing the header containing names, age and roll number.
{
    setColor(11); // Light cyan for header
    cout << left << setw(10) << "Roll"
        << setw(25) << "Name"
        << setw(5) << "Age" << endl;
    cout << string(40, '-') << endl;
    setColor(7);
}

void printStudent(int i) //Function that prints the students information.
{
    setColor(14); // Yellow for student data
    cout << left << setw(10) << rollNumbers[i]
        << setw(25) << names[i]
        << setw(5) << ages[i] << endl;
    setColor(7);
}

bool login() //A simple function that validates our login. 
{
    string input;
    int attempts = 3;
    while (attempts--) {
        setColor(9); // Blue prompt
        cout << "Enter password (" << attempts + 1 << " attempts left): ";
        setColor(7);
        cin >> input;
        if (input == PASSWORD)
        {
            setColor(10); // Green success
            cout << "Access granted.\n";
            setColor(7);
            return true;
        }
        else
        {
            setColor(12); // Red error
            cout << "Wrong password.\n";
            setColor(7);
        }
    }
    return false;
}

bool isFull() //Helper function to see if the student count is greater than or equal to 100.
{
    return s_count >= MAX;
}

bool isEmpty() //Helper function that tells us if we donot have any student list/data available.
{
    return s_count == 0;
}

int getStudentIndex(int roll) //Function that gets the students index if their roll number exists.
{
    for (int i = 0; i < s_count; i++)
        if (rollNumbers[i] == roll)
            return i;
    return -1;
}

int inputRollNumber() //Function that inputs and validates the students roll number.
{
    int roll;
    while (true)
    {
        setColor(9);
        cout << "Enter Roll Number: ";
        setColor(7);
        cin >> roll;
        if (cin.fail()) //If the user enters invalid input for example an alphabet then cin.fail() will take place.
        {
            cin.clear();
            cin.ignore(1000, '\n');
            setColor(12);
            cout << "Invalid input. Please enter a valid integer roll number.\n";
            setColor(7);
            continue;
        }
        if (getStudentIndex(roll) != -1) //This checks if roll number already exists or not
        {
            setColor(12);
            cout << "Roll number already exists. Try again.\n";
            setColor(7);
        }
        else
        {
            cin.ignore(1000, '\n'); // clear newline for getline later
            return roll; //returns the roll number.
        }
    }
}

string inputName() //Function that inputs the students name
{
    string name;
    setColor(9);
    cout << "Enter Name: ";
    setColor(7);
    getline(cin, name);
    while (name.empty()) //.empty is a string function and checks if a string is empty. While loop here will keep asking name until we write an unempty string.
    {
        setColor(12);
        cout << "Name cannot be empty. Enter Name: ";
        setColor(7);
        getline(cin, name);
    }
    return name; //Returns the name
}

int inputAge() //Function that inputs the students age.
{
    int age;
    while (true)
    {
        setColor(9);
        cout << "Enter Age: ";
        setColor(7);
        cin >> age;
        if (cin.fail() || age <= 0) //If we do not write a number for a age or write a negative number for age, the loop will keep asking us to write a proper age.
        {
            cin.clear();
            cin.ignore(1000, '\n');
            setColor(12);
            cout << "Invalid age. Please enter a positive integer.\n";
            setColor(7);
        }
        else
        {
            cin.ignore(1000, '\n'); // clear newline for next getline
            return age; //Simply returns the age
        }
    }
}

void inputStudent(int i) //Function takes index i and stores roll number , names and ages at the index i.
{
    rollNumbers[i] = inputRollNumber();
    names[i] = inputName();
    ages[i] = inputAge();
}

void loadFromFile() //Function that loads student information from the text file into the arrays.
{
    ifstream fin("students.txt"); //reads from file
    s_count = 0; //resets the student count
    if (!fin)
    {
        return;
    }
    while (s_count < MAX && fin >> rollNumbers[s_count]) //loop is going to run until we have EOF or we reach maximum students (100).
    {
        fin.ignore();
        getline(fin, names[s_count]); //name from the file 
        fin >> ages[s_count]; //ages from the file
        fin.ignore();
        s_count++;
    }
    fin.close();
}

void saveToFile() //Function that saves the student data into the files.
{
    ofstream fout("students.txt");
    for (int i = 0; i < s_count; i++)
    {
        fout << rollNumbers[i] << endl;
        fout << names[i] << endl;
        fout << ages[i] << endl;
    }
    fout.close();
}

void saveToCSV() //Function that allows us to save the student data in MS-EXCEL (CSV) file.
{
    ofstream fout("students.csv");
    fout << "Roll Num,Name,Age\n";
    for (int i = 0; i < s_count; i++)
    {
        fout << rollNumbers[i] << "," << names[i] << "," << ages[i] << "\n";
    }
    fout.close();
    setColor(10);
    cout << "Saved to students.csv successfully.\n";
    setColor(7);
}

void addStudent() //Function that allows us to add students
{
    if (isFull()) //isFull is the utility function defined above which tells us if our file contains 100(max) students.
    {
        setColor(12);
        cout << "Database full. Cannot add more students.\n";
        setColor(7);
        return;
    }
    inputStudent(s_count); //Function defined above that allows us to cin the students name age and roll num against an index.
    s_count++; //incrementing the student count.
    saveToFile(); //saving the students info in the file.
    setColor(10);
    cout << "Student added successfully.\n";
    setColor(7);
}

void viewStudents() //Function that allows us to view the students which are already saved.
{
    if (isEmpty()) //isEmpty is another helper function defined above. If there are no students saved then it will give us the message.
    {
        setColor(12);
        cout << "No students found.\n";
        setColor(7);
        return;
    }
    printHeader(); //Defined above and prints the output format.
    for (int i = 0; i < s_count; i++)
        printStudent(i);  //Prints the student info for that index.
}

void updateStudent() //Allows us to update student info w the help of roll num.
{
    int roll;
    setColor(9);
    cout << "Enter roll number to update: ";
    setColor(7);
    cin >> roll;
    if (cin.fail()) //If we input anything other than a number.
    {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(12);
        cout << "Invalid input.\n";
        setColor(7);
        return;
    }
    int index = getStudentIndex(roll); //If the roll number doesnt exist then we cant update the student.
    if (index == -1)
    {
        setColor(12);
        cout << "Student not found.\n";
        setColor(7);
        return;
    }
    cin.ignore(); // clear newline before getline
    setColor(9);
    cout << "Enter new name: ";
    setColor(7);
    getline(cin, names[index]); //Stores the name at the FOUND index.
    while (names[index].empty()) //If you write an empty string then the program keeps asking until you write an unempty string.
    {
        setColor(12);
        cout << "Name cannot be empty. Enter new name: ";
        setColor(7);
        getline(cin, names[index]);
    }
    ages[index] = inputAge(); //At the index replace the users age by calling the inputAge function and write the new age.
    saveToFile(); //Changes are saved to the file.
    setColor(10);
    cout << "Student updated.\n";
    setColor(7);
}

void deleteStudent() //Function to delete a student and relevant information.
{
    int roll;
    setColor(9);
    cout << "Enter roll number to delete: "; //Inputs the roll number to be deleted 
    setColor(7);
    cin >> roll;
    if (cin.fail()) //Incase of invalid input
    {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(12);
        cout << "Invalid input.\n";
        setColor(7);
        return;
    }
    int index = getStudentIndex(roll);
    if (index == -1) //If the roll number does not exist
    {
        setColor(12);
        cout << "Student not found.\n";
        setColor(7);
        return;
    }

    char confirm;
    setColor(12);
    cout << "Are you sure you want to delete student with Roll No " << roll << "? (y/n): ";
    setColor(7);
    cin >> confirm;
    cin.ignore(1000, '\n');
    if (confirm == 'y' || confirm == 'Y')
    {
        for (int i = index; i < s_count - 1; i++) //Shifting the records one position up
        {
            rollNumbers[i] = rollNumbers[i + 1]; //Moving the roll numbers , names and ages a position back.
            names[i] = names[i + 1];
            ages[i] = ages[i + 1];
        }
        s_count--; //This removes the one duplicate left at the end.
        saveToFile(); //Changes are saved 
        setColor(10);
        cout << "Student deleted.\n";
        setColor(7);
    }
    else //If any key except y or Y is pressend deletion is cancelled.
    {
        setColor(14);
        cout << "Delete operation canceled.\n";
        setColor(7);
    }
}


void searchStudent() //Searches student by roll number.
{
    int roll;
    setColor(9);
    cout << "Enter roll number to search: "; //Enter roll num
    setColor(7);
    cin >> roll;
    if (cin.fail()) //Incase of invalid roll num
    {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(12);
        cout << "Invalid input.\n";
        setColor(7);
        return;
    }
    int index = getStudentIndex(roll); //Index is found against which roll num is stored

    if (index == -1) //If index is -1 it means that the roll number isnt there hence the student isnt there.
    {
        setColor(12);
        cout << "Student not found.\n";
        setColor(7);
    }
    else
    {
        setColor(10);             //If student index exists
        cout << "Student found:\n";
        setColor(7);
        printHeader(); //Header is printed
        printStudent(index); //Information stored against that index is printed
    }
}

void searchByName() //Function that searches students by name
{
    cin.ignore();
    string name;
    setColor(9);
    cout << "Enter full name to search: "; //Enter name
    setColor(7);
    getline(cin, name);
    if (name.empty()) //Incase name string is empty
    {
        setColor(12);
        cout << "Name cannot be empty.\n";
        setColor(7);
        return;
    }
    bool found = false;
    string searchNameLower = toLowerCase(name); //The function here converts the name here into lowercase letters. Its usecase is there lets say that if a name is stored as Ahmed then even if we search AHmEd the name will show up
    printHeader(); //Prints header
    for (int i = 0; i < s_count; i++)
    {
        if (toLowerCase(names[i]) == searchNameLower)
        {
            printStudent(i);  //If the name is found then print the information stored against that name.
            found = true;
        }
    }
    if (!found) //If the name isnt found
    {
        setColor(12);
        cout << "No student found with the name \"" << name << "\".\n";
        setColor(7);
    }
}

void countStudents() //Functiont that simply keep track of number of students with variable s_count
{
    setColor(10);
    cout << "Total students: " << s_count << endl;
    setColor(7);
}

void averageAge() //Function to find the average age of student.
{
    if (isEmpty()) //If no students are there
    {
        setColor(12);
        cout << "No students to calculate average age.\n";
        setColor(7);
        return;
    }
    int total = 0;
    for (int i = 0; i < s_count; i++) //loop to sum the ages of all students
    {
        total += ages[i];
    }
    double avg = static_cast<double>(total) / s_count; //Simply avg is calculated.
    setColor(10);
    cout << fixed << setprecision(2);
    cout << "Average age: " << avg << endl;
    setColor(7);
}

void oldestStudent() //Function to find the oldest student
{
    if (isEmpty()) //If there are no students. 
    {
        setColor(12);
        cout << "No students available.\n";
        setColor(7);
        return;
    }
    int maxAge = ages[0];
    for (int i = 1; i < s_count; i++) //A simple bubble sort to find the maximum age.
        if (ages[i] > maxAge)
            maxAge = ages[i];

    setColor(10);
    cout << "Oldest student(s):\n";
    setColor(7);
    printHeader(); //Prints the header
    for (int i = 0; i < s_count; i++)
        if (ages[i] == maxAge)
            printStudent(i); //Prints the maximum age student and their details.
}

void youngestStudent() //Function to find the youngest student.
{
    if (isEmpty()) //If there are no students
    {
        setColor(12);
        cout << "No students available.\n";
        setColor(7);
        return;
    }
    int minAge = ages[0];
    for (int i = 1; i < s_count; i++) //A simple bubble sort to find the minimum age.
        if (ages[i] < minAge)
            minAge = ages[i];
    setColor(10);
    cout << "Youngest student(s):\n";
    setColor(7);
    printHeader(); //Prints header
    for (int i = 0; i < s_count; i++)
        if (ages[i] == minAge)
            printStudent(i); //Prints the information of youngest aged student.
}

void sortStudents()  //Function that sorts by roll number ascending (bubble sort)
{
    for (int i = 0; i < s_count - 1; i++) //A simple bubble sort to swap the information of two students based on roll numbers.
    {
        for (int j = 0; j < s_count - i - 1; j++)
        {
            if (rollNumbers[j] > rollNumbers[j + 1])
            {
                swap(rollNumbers[j], rollNumbers[j + 1]);  //Here swap() is a function of iostream library and switches the information of two students.
                swap(names[j], names[j + 1]);
                swap(ages[j], ages[j + 1]);
            }
        }
    }
    setColor(10);
    cout << "Students sorted by roll number.\n";
    setColor(7);
    saveToFile(); //Changes are saved to file meaning in file roll numbers are in ascending order.
    viewStudents(); //Sorted information is displayed.
}

void reverseDisplay() //Function to display students in a reverse order
{
    if (isEmpty()) //If we have no students. 
    {
        setColor(12);
        cout << "No students to display.\n";
        setColor(7);
        return;
    }
    printHeader(); //Header is printed
    for (int i = s_count - 1; i >= 0; i--)
    {
        printStudent(i);  //A reverse loop is implemented to print the students and their info in a reverse order.
    }
}

void searchByAgeRange() //Function to search students within an age range.
{
    int minAge, maxAge;
    setColor(9);
    cout << "Enter minimum age: ";
    setColor(7);
    cin >> minAge;
    setColor(9);
    cout << "Enter maximum age: ";
    setColor(7);
    cin >> maxAge;
    if (cin.fail() || minAge > maxAge || minAge < 0) //If you write invalid ages.
    {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(12);
        cout << "Invalid age range.\n";
        setColor(7);
        return;
    }
    bool found = false;
    printHeader();
    for (int i = 0; i < s_count; i++)
    {
        if (ages[i] >= minAge && ages[i] <= maxAge) //If ages are greater than equal to minimum age and less than equal to maximum age
        {
            printStudent(i); //Students within the age range are printed.
            found = true;
        }
    }
    if (!found) //If no students lie within that age range.
    {
        setColor(12);
        cout << "No students found in age range " << minAge << " to " << maxAge << ".\n";
        setColor(7);
    }
}


void clearData() //Function to delete all the user data
{
    char confirm;
    setColor(12); // Red for warning
    cout << "Are you sure you want to clear ALL student data? This action cannot be undone. (y/n): ";
    setColor(7);
    cin >> confirm;
    cin.ignore(1000, '\n');
    if (confirm == 'y' || confirm == 'Y')
    {
        s_count = 0;                 //If you choose y or Y then s_count ages names roll numbers everything is reset.
        for (int i = 0; i < MAX; i++)
        {
            rollNumbers[i] = 0;
            names[i].clear();
            ages[i] = 0;
        }
        ofstream fout("students.txt", ios::trunc); // clear file
        fout.close();

        setColor(10);
        cout << "All student data cleared successfully.\n";
        setColor(7);
    }
    else //If choose anything else than y or Y then clear data is cancelled.
    {
        setColor(14);
        cout << "Clear data operation canceled.\n";
        setColor(7);
    }
}

void menu() //Function that simply prints the menu.
{
    setColor(11); // Light cyan header
    cout << "\n=== STUDENT MANAGEMENT SYSTEM ===\n";
    setColor(14); // Yellow options
    cout << "1. Add Student\n";
    cout << "2. View Students\n";
    cout << "3. Update Student\n";
    cout << "4. Delete Student\n";
    cout << "5. Search Student by Roll\n";
    cout << "6. Search Student by Name\n";
    cout << "7. Count Students\n";
    cout << "8. Average Age\n";
    cout << "9. Oldest Student\n";
    cout << "10. Youngest Student\n";
    cout << "11. Sort Students by Roll\n";
    cout << "12. Reverse Display Order\n";
    cout << "13. Search Students by Age Range\n";
    cout << "14. Save to CSV\n";
    cout << "15. Exit\n";
    cout << "16. Clear All Data\n";
    setColor(7);
    setColor(14);
    cout << "Enter your choice: ";
    setColor(7);
}

int main() //Main Function
{
    loadFromFile(); //Load students info from the file

    if (!login()) //If you fail to login meaning you write incorrect password 3 times.
    {
        setColor(12);
        cout << "Access denied. Exiting...\n";
        setColor(7);
        return 0;
    }

    int choice;
    do {
        menu(); //Menu is printed.
        cin >> choice;
        if (cin.fail()) //If you write anything else than a number.
        {
            cin.clear();
            cin.ignore(1000, '\n');
            setColor(12);
            cout << "Invalid input. Please enter a number.\n";
            setColor(7);
            continue;
        }
        cin.ignore(1000, '\n'); // clear newline for getline in input functions

        switch (choice) //Choice and selection to be made from the different options.
        {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            searchStudent();
            break;
        case 6:
            searchByName();
            break;
        case 7:
            countStudents();
            break;
        case 8:
            averageAge();
            break;
        case 9:
            oldestStudent();
            break;
        case 10:
            youngestStudent();
            break;
        case 11:
            sortStudents();
            break;
        case 12:
            reverseDisplay();
            break;
        case 13:
            searchByAgeRange();
            break;
        case 14:
            saveToCSV();
            break;
        case 16:
            clearData();
            break;
        case 15:
            setColor(11);
            cout << "Exiting program. Goodbye!\n";
            setColor(7);
            break;
        default:
            setColor(12);
            cout << "Invalid choice. Please select from the menu.\n";
            setColor(7);
        }
    } while (choice != 15);

    return 0;
}
