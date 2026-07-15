#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct Student {
    string ID, Name;
    int Age , NSubjects;
    vector<double> Grades;
    double Total = 0 , Avg = 0;

    static void Valid_Age(int &age) {
        while (age < 0 || age > 100 || cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Age\nTry Again\n";
            cin >> age;
        }
    }

    static void Valid_NGrades(int &Number) {
        while (Number < 0 || cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Number Of Subjects\nTry Again";
            cin >> Number;
        }
    }

    static void Valid_Grades(double &Grade) {
        while (Grade < 0 || cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Grade\nTry Again";
            cin >> Grade;
          }
    }
};

int Choice_Read() {
    int C = 0;
    cout << "\nChoose A Number\n";
    cout << "1-Search Student\n";
    cout << "2-Add Student\n";
    cout << "3-Edit Student Grades\n";
    cout << "4-Delete Student\n";
    cout << "5-Top Student\n";
    cout << "6-Exit\n";
    cin >> C;
    return C;
}

int Read_ID(const vector<Student> &Stud, const size_t S) {
    string id;
    cout << "Enter Student ID\n";
    cin >> id;

    while (true) {
        for (int i = 0; i < S; i++) {
            if (id == Stud[i].ID) {
                return i;
            }
        }
        cout << "ID Not Found\nTry Again\n";
        cin >> id;
    }
}

void Grade_Total(Student &Stud, const int NSubjects) {
    double Sum = 0;
    for (int i = 0; i < NSubjects; i++)
        Sum += Stud.Grades[i];
    Stud.Total = Sum;
}

void Grade_Avg(Student &Stud, const int NSubjects) {
    Stud.Avg = Stud.Total / NSubjects;
}

void Search_Student(const Student &Stud) {
    cout << "Name: " << Stud.Name << endl;
    cout << "Age: " << Stud.Age << endl;

    const int NSubjects = Stud.NSubjects;
    cout << "Grades: ";
    for (int i = 0; i < NSubjects; i++)
        cout << Stud.Grades[i] << ' ';

    cout << "\nTotal Of Grades: " << Stud.Total << endl;
    cout << "Average Of Grades: " << Stud.Avg << endl;
}

void Read_Grades(Student &Stud, const int NSubjects) {
    cout << "Enter Student Grades\n";
    for (int c = 0; c < NSubjects; c++) {
        cin >> Stud.Grades[c];
        Student::Valid_Grades(Stud.Grades[c]);
    }
}

void Add_Student(Student &Stud, const size_t S) {
    cout << "Enter Student Name\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, Stud.Name);

    cout << "Enter Student Age\n";
    cin >> Stud.Age;
    Student::Valid_Age(Stud.Age);

    cout << "Enter Number Of Subjects Of The Student\n";
    cin >> Stud.NSubjects;
    Student::Valid_NGrades(Stud.NSubjects);
    Stud.Grades.resize(Stud.NSubjects);

    Read_Grades(Stud , Stud.NSubjects);

    if (Stud.NSubjects) {
         Grade_Total(Stud, Stud.NSubjects);
        Grade_Avg(Stud, Stud.NSubjects);
    }

    Stud.ID = "#" + Stud.Name.substr(0,min<size_t>(2,Stud.Name.length())) + to_string(Stud.Age) + "_" + to_string(S);
    cout << "Student ID Is " << Stud.ID << endl;
}

void Edit_Grades(Student &Stud) {
    const int NGrades = Stud.NSubjects;
    Read_Grades(Stud , NGrades);

    Grade_Total(Stud, NGrades);
    Grade_Avg(Stud, NGrades);
}

void Delete_Student(vector<Student> &student , const int i) {
    student.erase(student.begin() + i);
}

void Top_Student(const vector<Student> &student, const size_t S) {
    double Max = -1;
    int C = 0;
    string id;
    for (int i = 0; i < S; i++) {
        if (Max < student[i].Avg) {
            Max = student[i].Avg;
            id = student[i].ID;
            C = i;
        }
    }
    cout << "Student ID: " << id << endl;
    Search_Student(student[C]);
}

int main() {
    int Choice = 0;
    vector<Student> Students;
    cout << "Welcome To Student Management System\n";

    while (true) {
        int Index = 0;
        Choice = Choice_Read();
        switch (Choice) {
            case 1:
                if (empty(Students)) {
                    cout << "There Isn't Any Added Student To Search For\n";
                    break;
                }
                Index = Read_ID(Students, size(Students));
                Search_Student(Students[Index]);
                break;
            case 2:
                Students.push_back(Student{});
                Add_Student(Students.back(), size(Students));
                break;
            case 3:
                if (empty(Students)) {
                    cout << "There Isn't Any Added Student To Edit His Grades\n";
                    break;
                }
                Index = Read_ID(Students, size(Students));
                Edit_Grades(Students[Index]);
                break;
            case 4:
                if (empty(Students)) {
                    cout << "There Isn't Any Added Student To Delete Him\n";
                    break;
                }
                Index = Read_ID(Students, size(Students));
                Delete_Student(Students , Index);
                break;
            case 5:
                if (empty(Students)) {
                    cout << "There Isn't Any Added Student To Find The Top One\n";
                    break;
                }
                Top_Student(Students, size(Students));
                break;
            case 6:
                cout << "#Program Ended#";
                return 0;
            default:
                cout << "Invalid Choice\n";
                break;
        }
    }
}
