#pragma once
#include "Common.h"

class Enrollment {
private:
    int id, studentId, courseId, progress;
public:
    Enrollment() : id(0), studentId(0), courseId(0), progress(0) {}
    Enrollment(int i,int s,int c,int p) : id(i),studentId(s),courseId(c),progress(p) {}
    int getId() const { return id; }
    int getStudentId() const { return studentId; }
    int getCourseId() const { return courseId; }
    int getProgress() const { return progress; }
    void setProgress(int p) { progress=p; }
    void display() const { cout << "Enrollment ID: " << id << " | Student ID: " << studentId << " | Course ID: " << courseId << " | Progress: " << progress << "%\n"; }
};
