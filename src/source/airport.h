#ifndef AEDA_PROJECT_AIRPORT_H
#define AEDA_PROJECT_AIRPORT_H

#include "airport_objects.h"
#include "flight.h"
#include <unordered_set>

using namespace std;

class PersonRecord{

    string state;
    Person * person;

public:

    PersonRecord(const string &state, Person *person) : state(state), person(person) {}

    const string &getState() const {
        return state;
    }

    void setState(const string &state) {
        PersonRecord::state = state;
    }

    Person *getPerson() const {
        return person;
    }

    void setPerson(Person *person) {
        PersonRecord::person = person;
    }

    ostream & printInfo(ostream &os) const{
        if(this->person->getCategory() == "Employee"){
            os << "\tName      : " << this->person->getName() << endl
               << "\tBirth     : " << this->person->getBirthday() << endl
               << "\tCategory  : " << this->person->getCategory()<< endl
               << "\tSalary    : " << this->person->getSalary() << endl
               << "\tSchedule  : " << dynamic_cast<Employee *>(person)->getSchedule() << endl
               << "\tState     : " << this->getState() << endl
               << "\t---------------------------" << endl;
        }
        if(this->person->getCategory() == "Admin"){
            os << "\tName      : " << this->person->getName() << endl
               << "\tBirth     : " << this->person->getBirthday() << endl
               << "\tCategory  : " << this->person->getCategory() << endl
               << "\tSalary    : " << this->person->getSalary() << endl
               << "\tDepartment: " << dynamic_cast<Administration *>(person)->getDepartment() << endl
               << "\tState     : " << this->getState() << endl
               << "\t---------------------------" << endl;
            return os;
        }
        if(this->person->getCategory() == "Pilot"){
            os << "\tName         : " << this->person->getName() << endl
               << "\tBirth        : " << this->person->getBirthday() << endl
               << "\tCategory     : " << this->person->getCategory() << endl
               << "\tSalary       : " << this->person->getSalary() << endl
               << "\tTotal Hours  : " << dynamic_cast<Plane_Pilot *>(person)->getTotalHours() << endl
               << "\tTotal Flights: " << dynamic_cast<Plane_Pilot *>(person)->getTotalFlights() << endl
               << "\tPlane Type   : " << dynamic_cast<Plane_Pilot *>(person)->getPlaneType() << endl
               << "\tState        : " << this->getState() << endl
               << "\t---------------------------" << endl;
        }
        if(this->person->getCategory() == "Crew"){
            os << "\tName         : " << this->person->getName() << endl
               << "\tBirth        : " << this->person->getBirthday() << endl
               << "\tCategory     : " << this->person->getCategory() << endl
               << "\tSalary       : " << this->person->getSalary() << endl
               << "\tTotal Hours  : " << dynamic_cast<Crew_Member *>(person)->getTotalHours() << endl
               << "\tTotal Flights: " << dynamic_cast<Crew_Member *>(person)->getTotalFlights() << endl
               << "\tState        : " << this->getState() << endl
               << "\t---------------------------" << endl;
        }
        return os;
    }
};

struct peopleHash{
    int operator()(const PersonRecord &p1) const {
        int hash = 7;
        for (int i = 0; i < p1.getPerson()->getName().size(); i++) {
            hash = hash*31 + (int)p1.getPerson()->getName().at(i);
        }
        return hash;
    }

    bool operator()(const PersonRecord &p1, const PersonRecord &p2) const{
        return p1.getPerson()->getId() == p2.getPerson()->getId();
    }
};

typedef unordered_set<PersonRecord, peopleHash, peopleHash> tabHPeople;

class Airport{

    Administration *manager;
    Location *location;
    vector<Person *> people;
    vector<Plane *> planes;
    tabHPeople allWorkers;

public:

    Airport() = default;

    Administration *getManager() const {
        return manager;
    }

    void setManager(Administration *manager) {
        Airport::manager = manager;
    }

    Location *getLocation() const {
        return location;
    }

    void setLocation(Location *location) {
        Airport::location = location;
    }

    void vectorAddPerson(Person *p){
        this->people.push_back(p);
        this->allWorkers.insert(PersonRecord("Employed",p));
    }

    void tableAddOldPerson(Person *p){
        this->allWorkers.insert(PersonRecord("Unemployed",p));
    }

    void vectorAddPlane(Plane *p){
        this->planes.push_back(p);
    }

    const vector<Person *> &getPeople() const{
        return people;
    }

    const vector<Plane *> &getPlanes() const{
        return planes;
    }

    const tabHPeople &getAllWorkers() const {
        return allWorkers;
    }

    void setAllWorkers(const tabHPeople &allWorkers) {
        Airport::allWorkers = allWorkers;
    }

    bool operator<(const Airport &rhs) const {
        return location < rhs.location;
    }

    friend ostream &operator<<(ostream &os, const Airport &airport) {
        os << "\tManager: " << endl;
        airport.manager->printInfo(os) << "\tLocation: " << endl << *airport.location;
        return os;
    }

    friend ostream &operator<<(ostream &os, const Airport *airport) {
        os << "\tManager: " << endl;
        airport->manager->printInfo(os) << "\tLocation: " << endl << *airport->location;
        return os;
    }
    
    void addPerson();
    void removePerson();
    void updatePerson();
    void getAllPeople();

    void addPlane();
    void removePlane();
    void updatePlane();
    void getAllPlanes();

    float ShowFinancesWorkers(string cat)
    {
        float Financial_Value=0;
        for (auto i : people)
        {
            if (i->getCategory()==cat)
                Financial_Value+=i->getSalary();
            if (cat=="total")
                Financial_Value+=i->getSalary();
        }
        return Financial_Value;
    }

    float ShowFinancesPlanes(string t)
    {
        float Financial_Value=0;
        for (auto i : planes)
        {
            if (i->getType()==t)
                Financial_Value+=i->getOpCosts();
            if (t=="total")
                Financial_Value+=i->getOpCosts();
        }
        return Financial_Value;
    }

    float AirportExpensesValue()
    {
        return ShowFinancesPlanes("total") + ShowFinancesWorkers("total");
    }

    int showWorkersRecord();
};

class AirportRecord{

    Airport * airport;
    string id;
    int count;
    double track_hours;
    double average_track_time;

public:
    AirportRecord(Airport *airport) : airport(airport) {
        this->id = airport->getLocation()->getGps() + "_" + airport->getManager()->getName();
        this->count = 0;
        this->track_hours = 0;
        this->average_track_time = 0;
    }

    Airport *getAirport() const;

    void setAirport(Airport *airport);

    const string &getId() const;

    void setId(const string &id);

    int getCount() const;

    void setCount(int count);

    double getTrackHours() const;

    void setTrackHours(double tracksHours);

    void addTrackHours(double trackHours);

    void addTrackHours(double flightTime, int unused);

    double getAverageTrackHours() const;

    bool operator<(const AirportRecord &rhs) const;

    bool operator==(const AirportRecord &rhs) const;

    bool operator!=(const AirportRecord &rhs) const;
};

#endif //AEDA_PROJECT_AIRPORT_H
