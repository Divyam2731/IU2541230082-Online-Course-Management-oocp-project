#pragma once
#include "Common.h"
#include "Student.h"
#include "Course.h"
#include "Enrollment.h"

class FileManager {
public:
    // Simple delimiter-based storage for this classroom project.
    static void saveStudents(Student* items, int count) {
        ofstream out("Data/students.txt");
        if (!out) { cerr << "Warning: could not save students. Check the Data folder.\n"; return; }
        for(int i=0;i<count;i++) out << items[i].getId() << "|" << items[i].getName() << "|" << items[i].getEmail() << "\n";
    }
    static int loadStudents(Student* items, int capacity) {
        ifstream in("Data/students.txt"); if(!in) return 0;
        string line; int count=0;
        while(getline(in,line) && count<capacity) {
            stringstream ss(line); string a,b,c;
            if(getline(ss,a,'|') && getline(ss,b,'|') && getline(ss,c,'|')) {
                try { items[count++] = Student(stoi(a),b,c); } catch(...) {}
            }
        }
        return count;
    }
    static void saveCourses(Course* items, int count) {
        ofstream out("Data/courses.txt");
        if (!out) { cerr << "Warning: could not save courses. Check the Data folder.\n"; return; }
        for(int i=0;i<count;i++) out << items[i].getId() << "|" << items[i].getTitle() << "|" << items[i].getFee() << "\n";
    }
    static int loadCourses(Course* items, int capacity) {
        ifstream in("Data/courses.txt"); if(!in) return 0;
        string line; int count=0;
        while(getline(in,line) && count<capacity) {
            stringstream ss(line); string a,b,c;
            if(getline(ss,a,'|') && getline(ss,b,'|') && getline(ss,c,'|')) {
                try { items[count++] = Course(stoi(a),b,stod(c)); } catch(...) {}
            }
        }
        return count;
    }
    static void saveEnrollments(Enrollment* items, int count) {
        ofstream out("Data/enrollments.txt");
        if (!out) { cerr << "Warning: could not save enrollments. Check the Data folder.\n"; return; }
        for(int i=0;i<count;i++) out << items[i].getId() << "|" << items[i].getStudentId() << "|" << items[i].getCourseId() << "|" << items[i].getProgress() << "\n";
    }
    static int loadEnrollments(Enrollment* items, int capacity) {
        ifstream in("Data/enrollments.txt"); if(!in) return 0;
        string line; int count=0;
        while(getline(in,line) && count<capacity) {
            stringstream ss(line); string a,b,c,d;
            if(getline(ss,a,'|') && getline(ss,b,'|') && getline(ss,c,'|') && getline(ss,d,'|')) {
                try { items[count++] = Enrollment(stoi(a),stoi(b),stoi(c),stoi(d)); } catch(...) {}
            }
        }
        return count;
    }
};
