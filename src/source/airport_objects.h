#ifndef AEDA_PROJECT_AIRPORT_OBJECTS_H
#define AEDA_PROJECT_AIRPORT_OBJECTS_H

#include "utils.h"
#include <cmath>

static string PlaneTypes[] = {"Airbus A319","Airbus A320","Airbus A330","Boeing 737"};
static float PlaneCostsPerType[] = {500.99,750.50,1250.25,800.99};

class Person{

    string name;
    Date birthday;
    string id;

protected:
    float salary;
    string category;

public:

    Person() = default;
    Person(const string &name, const Date &birthday, float salary) : name(name), birthday(birthday), salary(salary) {
    }

    const string &getName() const{
        return this->name;
    };

    void setName(const string &name){
        this->name = name;
    };

    const Date &getBirthday() const{
        return this->birthday;
    };

    void setBirthday(const Date &birthday){
        this->birthday = birthday;
    };

    float getSalary() const{
        return this->salary;
    };

    virtual void setSalary(float salary){
        this->salary = salary;
    };

    virtual ostream &printInfo(ostream &os) const{
        os << "\tName      : " << this->name << endl
        << "\tBirth     : " << this->birthday << endl
        << "\tSalary    : " << this->salary << endl
        << "\t---------------------------" << endl;
        return os;
    }

    const string &getId() const {
        return id;
    }

    void setId(const string &id) {
        Person::id = id;
    }

    const string &getCategory() const {
        return category;
    }
};

class Employee: public Person
{
    string schedule;

public:

    Employee(){
        category = "Employee";
    };

    Employee(const string &name, const Date &birthday, float salary, const string &schedule)
            : Person(name, birthday, salary), schedule(schedule) {
        category = "Employee";
        string idP = name.at(0) + to_string(birthday.getDay()) + category.at(0) + to_string(salary).at(0);
        this->setId(idP);
    }

    const string &getSchedule() const {
        return schedule;
    }

    void setSchedule(const string &schedule) {
        Employee::schedule = schedule;
    }

    ostream &printInfo(ostream &os) const{
        os << "\tName      : " << this->getName() << endl
           << "\tBirth     : " << this->getBirthday() << endl
           << "\tCategory  : " << this->getCategory()<< endl
           << "\tSalary    : " << this->getSalary() << endl
           << "\tSchedule  : " << this->getSchedule() << endl
           << "\t---------------------------" << endl;
        return os;
    }

};

class Administration: public Person
{
    string department;
public:

    Administration(){
        category = "Admin";
    };

    Administration(const string &name, const Date &birthday, float salary,
                   const string &department) : Person(name, birthday, salary), department(department) {
        category = "Admin";
        string idP = name.at(0) + to_string(birthday.getDay()) + category.at(0) + to_string(salary).at(0);
        this->setId(idP);
    }

    const string &getDepartment() const {
        return this->department;
    }

    void setDepartment(const string &department) {
        Administration::department = department;
    }

    ostream & printInfo(ostream &os) const {
        os << "\tName      : " << this->getName() << endl
           << "\tBirth     : " << this->getBirthday() << endl
           << "\tCategory  : " << this->getCategory() << endl
           << "\tSalary    : " << this->getSalary() << endl
           << "\tDepartment: " << this->department << endl
           << "\t---------------------------" << endl;
        return os;
    }
};


#endif //AEDA_PROJECT_AIRPORT_OBJECTS_H
