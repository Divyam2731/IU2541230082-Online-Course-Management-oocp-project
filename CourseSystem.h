#pragma once
#include "Common.h"
#include "Student.h"
#include "Course.h"
#include "Instructor.h"
#include "Enrollment.h"
#include "FileManager.h"

class CourseSystem {
private:
    static const int CAPACITY = 100;
    Student* students;
    Course* courses;
    Enrollment* enrollments;
    int studentCount, courseCount, enrollmentCount;
    int nextStudent, nextCourse, nextEnrollment;
    int readInt(const string& prompt) {
        int value;
        while(true) {
            cout << prompt;
            if(cin >> value) { cin.ignore(numeric_limits<streamsize>::max(), '\n'); return value; }
            cout << "Please enter a valid whole number.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    string readText(const string& prompt) {
        string value; cout << prompt; getline(cin,value);
        if(value.find('|') != string::npos) { cout << "The | character is not allowed; using a hyphen instead.\n"; for(char& c:value) if(c=='|') c='-'; }
        return value;
    }
    int findStudent(int value) const { for(int i=0;i<studentCount;i++) if(students[i].getId()==value) return i; return -1; }
    int findCourse(int value) const { for(int i=0;i<courseCount;i++) if(courses[i].getId()==value) return i; return -1; }
    int findEnrollment(int value) const { for(int i=0;i<enrollmentCount;i++) if(enrollments[i].getId()==value) return i; return -1; }
    void saveAll() { FileManager::saveStudents(students,studentCount); FileManager::saveCourses(courses,courseCount); FileManager::saveEnrollments(enrollments,enrollmentCount); }
public:
    CourseSystem() : students(new Student[CAPACITY]), courses(new Course[CAPACITY]), enrollments(new Enrollment[CAPACITY]),
        studentCount(0),courseCount(0),enrollmentCount(0),nextStudent(1),nextCourse(1),nextEnrollment(1) {
        studentCount=FileManager::loadStudents(students,CAPACITY);
        courseCount=FileManager::loadCourses(courses,CAPACITY);
        enrollmentCount=FileManager::loadEnrollments(enrollments,CAPACITY);
        for(int i=0;i<studentCount;i++) if(students[i].getId()>=nextStudent) nextStudent=students[i].getId()+1;
        for(int i=0;i<courseCount;i++) if(courses[i].getId()>=nextCourse) nextCourse=courses[i].getId()+1;
        for(int i=0;i<enrollmentCount;i++) if(enrollments[i].getId()>=nextEnrollment) nextEnrollment=enrollments[i].getId()+1;
    }
    ~CourseSystem() { saveAll(); delete[] students; delete[] courses; delete[] enrollments; }
    void addStudent() {
        if(studentCount>=CAPACITY) { cout<<"Student limit reached.\n"; return; }
        string n=readText("Student name: "), e=readText("Student email: ");
        students[studentCount++]=Student(nextStudent++,n,e); saveAll(); cout<<"Student added successfully.\n";
    }
    void addCourse() {
        if(courseCount>=CAPACITY) { cout<<"Course limit reached.\n"; return; }
        string t=readText("Course title: "); double fee;
        cout<<"Course fee (Rs.): ";
        while(!(cin>>fee) || fee<0) { cout<<"Enter a valid non-negative fee: "; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        courses[courseCount++]=Course(nextCourse++,t,fee); saveAll(); cout<<"Course added successfully.\n";
    }
    void displayAll() const {
        cout<<"\n--- STUDENTS ---\n";
        if(studentCount==0) cout<<"No students yet.\n";
        for(int i=0;i<studentCount;i++) { const Person* p=&students[i]; p->display(); }
        cout<<"--- COURSES ---\n";
        if(courseCount==0) cout<<"No courses yet.\n";
        for(int i=0;i<courseCount;i++) courses[i].display();
        cout<<"--- ENROLLMENTS ---\n";
        if(enrollmentCount==0) cout<<"No enrollments yet.\n";
        for(int i=0;i<enrollmentCount;i++) enrollments[i].display();
    }
    void searchRecord() const {
        int type=const_cast<CourseSystem*>(this)->readInt("Search 1=Student, 2=Course, 3=Enrollment: ");
        int idValue=const_cast<CourseSystem*>(this)->readInt("Enter ID: ");
        if(type==1) { int i=findStudent(idValue); if(i>=0) students[i].display(); else cout<<"Student not found.\n"; }
        else if(type==2) { int i=findCourse(idValue); if(i>=0) courses[i].display(); else cout<<"Course not found.\n"; }
        else if(type==3) { int i=findEnrollment(idValue); if(i>=0) enrollments[i].display(); else cout<<"Enrollment not found.\n"; }
        else cout<<"Invalid record type.\n";
    }
    void updateRecord() {
        int type=readInt("Update 1=Student, 2=Course, 3=Enrollment progress: ");
        int idValue=readInt("Enter ID: ");
        if(type==1) { int i=findStudent(idValue); if(i<0){cout<<"Student not found.\n";return;} string n=readText("New name: "),e=readText("New email: "); students[i].setDetails(n,e); }
        else if(type==2) { int i=findCourse(idValue); if(i<0){cout<<"Course not found.\n";return;} string t=readText("New title: "); double f; cout<<"New fee: "; while(!(cin>>f)||f<0){cout<<"Enter non-negative fee: ";cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');} cin.ignore(numeric_limits<streamsize>::max(),'\n'); courses[i].setDetails(t,f); }
        else if(type==3) { int i=findEnrollment(idValue); if(i<0){cout<<"Enrollment not found.\n";return;} int p=readInt("New progress (0-100): "); if(p<0||p>100){cout<<"Progress must be from 0 to 100.\n";return;} enrollments[i].setProgress(p); }
        else {cout<<"Invalid record type.\n";return;}
        saveAll(); cout<<"Record updated successfully.\n";
    }
    void deleteRecord() {
        int type=readInt("Delete 1=Student, 2=Course, 3=Enrollment: ");
        int idValue=readInt("Enter ID: ");
        if(type==1) { int i=findStudent(idValue); if(i<0){cout<<"Student not found.\n";return;} for(int j=i;j<studentCount-1;j++)students[j]=students[j+1]; studentCount--; }
        else if(type==2) { int i=findCourse(idValue); if(i<0){cout<<"Course not found.\n";return;} for(int j=i;j<courseCount-1;j++)courses[j]=courses[j+1]; courseCount--; }
        else if(type==3) { int i=findEnrollment(idValue); if(i<0){cout<<"Enrollment not found.\n";return;} for(int j=i;j<enrollmentCount-1;j++)enrollments[j]=enrollments[j+1]; enrollmentCount--; }
        else {cout<<"Invalid record type.\n";return;}
        saveAll(); cout<<"Record deleted successfully.\n";
    }
    void enrollStudent() {
        if(enrollmentCount>=CAPACITY){cout<<"Enrollment limit reached.\n";return;}
        int s=readInt("Student ID: "), c=readInt("Course ID: ");
        if(findStudent(s)<0 || findCourse(c)<0){cout<<"Please add a valid student and course first.\n";return;}
        enrollments[enrollmentCount++]=Enrollment(nextEnrollment++,s,c,0); saveAll();
        cout<<"Enrollment completed. Progress starts at 0%.\n";
    }
    void report() const {
        cout<<"\n=== COURSE MANAGEMENT REPORT ===\nStudents: "<<studentCount<<"\nCourses: "<<courseCount<<"\nEnrollments: "<<enrollmentCount<<"\n";
        double total=0; for(int i=0;i<courseCount;i++) total+=courses[i].getFee();
        cout<<"Combined listed course fees: Rs. "<<total<<"\n";
    }
    void menu() {
        int choice;
        do {
            cout<<"\n===== ONLINE COURSE MANAGEMENT =====\n1. Add Student\n2. Add Course\n3. Display Records\n4. Search Record\n5. Update Record\n6. Delete Record\n7. Enroll Student\n8. Report\n9. Save and Exit\n";
            choice=readInt("Choose option: ");
            switch(choice) {
                case 1:addStudent();break; case 2:addCourse();break; case 3:displayAll();break;
                case 4:searchRecord();break; case 5:updateRecord();break; case 6:deleteRecord();break;
                case 7:enrollStudent();break; case 8:report();break; case 9:saveAll();cout<<"Data saved. Goodbye!\n";break;
                default:cout<<"Choose an option from 1 to 9.\n";
            }
        } while(choice!=9);
    }
};
