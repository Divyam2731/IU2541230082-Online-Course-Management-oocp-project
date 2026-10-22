#pragma once
#include "Common.h"

class Student : public Person {
private:
    string email;
public:
    Student() : Person(), email("") {}
    Student(int i, const string& n, const string& e) : Person(i,n), email(e) {}
    string getEmail() const { return email; }
    void setDetails(const string& n, const string& e) { name=n; email=e; }
    void display() const override { cout << "Student ID: " << id << " | Name: " << name << " | Email: " << email << "\n"; }
};
