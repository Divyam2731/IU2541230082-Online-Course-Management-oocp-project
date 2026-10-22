#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <exception>
using namespace std;


// Common abstract base class used by the record types.
class Person {
protected:
    int id;
    string name;
public:
    Person() : id(0), name("") {}
    Person(int i, const string& n) : id(i), name(n) {}
    virtual ~Person() {}
    int getId() const { return id; }
    string getName() const { return name; }
    virtual void display() const = 0; // virtual function for runtime polymorphism
};
