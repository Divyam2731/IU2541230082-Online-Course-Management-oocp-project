#pragma once
#include "Common.h"

class Course {
private:
    int id;
    string title;
    double fee;
public:
    Course() : id(0), title(""), fee(0) {}
    Course(int i, const string& t, double f) : id(i), title(t), fee(f) {}
    int getId() const { return id; }
    string getTitle() const { return title; }
    double getFee() const { return fee; }
    void setDetails(const string& t, double f) { title=t; fee=f; }
    void display() const { cout << "Course ID: " << id << " | Title: " << title << " | Fee: Rs. " << fee << "\n"; }
};
