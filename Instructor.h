#pragma once
#include "Common.h"

class Instructor : public Person {
private:
    string specialization;
public:
    Instructor() : Person(), specialization("") {}
    Instructor(int i, const string& n, const string& s) : Person(i,n), specialization(s) {}
    void display() const override { cout << "Instructor ID: " << id << " | Name: " << name << " | Specialization: " << specialization << "\n"; }
};
