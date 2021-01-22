#include "airport.h"
#ifndef AEDA_PROJECT_FLIGHT_H
#define AEDA_PROJECT_FLIGHT_H

#include "utils.h"

class Flight;

class MaintenanceCompany{
    string companyName;
    double avaiability;
    int MaintenancesNumber;

public:
    MaintenanceCompany(double avaiability, int MaintenancesNumber, string companyName)
    {
        this->avaiability=avaiability;
        this->MaintenancesNumber=MaintenancesNumber;
        this->companyName=companyName;
    }

    const string &getCompanyName() const {
        return companyName;
    }

    void setCompanyName(const string &companyName) {
        MaintenanceCompany::companyName = companyName;
    }

    double getAvaiability() const {
        return avaiability;
    }

    int getMaintenancesNumber() const {
        return MaintenancesNumber;
    }

    void setAvaiability(double avaiability) {
        MaintenanceCompany::avaiability = avaiability;
    }

    void setMaintenancesNumber(int maintenancesNumber) {
        MaintenancesNumber = maintenancesNumber;
    }

    bool operator<(const MaintenanceCompany &rhs) const {
        if (avaiability > rhs.avaiability)
            return true;
        if (rhs.avaiability > avaiability)
            return false;
        return MaintenancesNumber < rhs.MaintenancesNumber;
    }

};

class Plane{

    string type;
    int capacity;
    vector<Flight*> flights;
    vector<Person *> plane_crew;
    int total_trips;
    float total_hours;
    float op_costs;
    string id;

public:

    Plane() = default;

    Plane(const string &type, int capacity, const vector<Person*> &planeCrew, float opCosts) : type(type),
                                                                                               capacity(capacity),
                                                                                               plane_crew(planeCrew),
                                                                                               op_costs(opCosts) {
        flights = {};
        total_trips = flights.size();
        total_hours = 0;

        id = type.at(type.size() - 1) + to_string(capacity) + type.at(0);
    }

    Plane(const string &type, int capacity, const vector<Flight*> &flights, const vector<Person *> &planeCrew,
          float opCosts):type (type), capacity(capacity), flights(flights), plane_crew(planeCrew), op_costs(opCosts) {
        total_trips = flights.size();
        total_hours = 0;

        id = type.at(type.size() - 1) + to_string(capacity) + type.at(0);
    }

    const string &getType() const {
        return type;
    }

    void setType(const string &type) {
        Plane::type = type;
    }

    int getCapacity() const {
        return capacity;
    }

    void setCapacity(int capacity) {
        Plane::capacity = capacity;
    }

    vector<Flight *> getFlights() const {
        return flights;
    }

    void addVectorFlights(Flight * f){
        this->flights.push_back(f);
    }

    void setFlights(vector<Flight *> flights) {
        Plane::flights = flights;
    }

    vector<Person *> getPlaneCrew() const {
        return plane_crew;
    }

    void setPlaneCrew(const vector<Person *> &pilots) {
        Plane::plane_crew = pilots;
    }

    int getTotalTrips() const {
        return total_trips;
    }

    void setTotalTrips(int totalTrips) {
        total_trips = totalTrips;
    }

    float getTotalHours() const {
        return total_hours;
    }

    void setTotalHours(float totalHours) {
        total_hours = totalHours;
    }

    float getOpCosts() const {
        float op_costs2 = op_costs + 10 * total_trips + 5 * total_hours;
        return op_costs2;
    }

    void setOpCosts(float opCosts) {
        op_costs = opCosts;
    }



    friend ostream &operator<<(ostream &os, const Plane &plane) {

        os << "\tType         : " << plane.getType() << endl;
        os << "\tCapacity     : " << plane.getCapacity() << endl ;
        os << "\tTotal Hours  : " << plane.getTotalHours() << endl;
        os << "\tTotal Flights: " << plane.getTotalTrips() << endl;
        os << "\tOp Costs     : " << plane.getOpCosts() << endl;
        os << "\tPilots       : " << plane.plane_crew.at(0)->getName() << " , " << plane.plane_crew.at(1)->getName() << endl;
        os << "\tCrew         : " << plane.plane_crew.at(2)->getName() << " , " << plane.plane_crew.at(3)->getName() << endl;
        os << "\t------------------" << endl;

        return os;
    }

    friend ostream &operator<<(ostream &os, const Plane *plane) {

        os << "\tType         : " << plane->getType() << endl;
        os << "\tCapacity     : " << plane->getCapacity() << endl ;
        os << "\tTotal Hours  : " << plane->getTotalHours() << endl;
        os << "\tTotal Flights: " << plane->getTotalTrips() << endl;
        os << "\tOp Costs     : " << plane->getOpCosts() << endl;
        os << "\tPilots       : " << plane->plane_crew.at(0)->getName() << " , " << plane->plane_crew.at(1)->getName() << endl;
        os << "\tCrew         : " << plane->plane_crew.at(2)->getName() << " , " << plane->plane_crew.at(3)->getName() << endl;
        os << "\t------------------" << endl;

        return os;
    }

    const string &getId() {
        id = type.at(type.size() - 1) + to_string(capacity) + type.at(0);
        return id;
    }

    void setId(const string &id) {
        Plane::id = id;
    }
};

enum State {Scheduled, Done , Canceled};

class Flight{

    Date date;
    Hour hour;
    Location *departure;
    Location *arrival;
    Plane *plane;
    State state;
    float duration;
    string id;

public:
    Flight(){};
    Flight(Date date, Hour hour, Location *departure, Location *arrival, float duration, Plane *plane)
    {
        this->date = date;
        this->hour = hour;
        this->departure = departure;
        this->arrival = arrival;
        this->plane = plane;
        this->state = Scheduled;
        this->duration = duration;
        this->id = this->departure->getCity().at(0) + to_string(this->date.getDay()) + this->arrival->getCity().at(0) + to_string(int(this->duration));
    };

    const Date &getDate() const {
        return date;
    }

    void setDate(const Date &date) {
        Flight::date = date;
    }

    const Hour &getHour() const {
        return hour;
    }

    void setHour(const Hour &hour) {
        Flight::hour = hour;
    }

    Location *getDeparture() const {
        return departure;
    }

    void setDeparture(Location *departure) {
        Flight::departure = departure;
    }

    Location *getArrival() const {
        return arrival;
    }

    void setArrival(Location *arrival) {
        Flight::arrival = arrival;
    }

    Plane *getPlane() const {
        return plane;
    }

    void setPlane(Plane *plane) {
        Flight::plane = plane;
    }

    string getStringState() const {
        string states[] = {"Scheduled","Done", "Canceled", "Rescheduled"};
        return states[this->state];
    }

    State getState() const {
        return state;
    }

    void setState(const State &state) {
        Flight::state = state;
    }

    float getDuration() const {
        return duration;
    }

    void setDuration(float duration) {
        Flight::duration = duration;
    }

    bool operator<(const Flight &rhs) const {
        if (date < rhs.date)
            return true;
        if (rhs.date < date)
            return false;
        return hour < rhs.hour;
    }

    friend ostream &operator<<(ostream &os, const Flight &flight) {
        os << "\tDate     : " << flight.date << endl;
        os << "\tHour     : " << flight.hour << endl;
        os << "\tDuration : " << flight.duration << endl << endl;
        os << "\tDeparture: " << flight.departure->getCity() << " , " << flight.departure->getCountry() << endl;
        os << "\tArrival  : " << flight.arrival->getCity() << " , " << flight.arrival->getCountry() << endl;
        os << "\tPlane    : " << flight.getPlane()->getType() << endl;
        os << "\tState    : " << flight.getStringState() << endl;
        return os;
    }

    friend ostream &operator<<(ostream &os, const Flight *flight) {
        os << "\tDate     : " << flight->date << endl;
        os << "\tHour     : " << flight->hour << endl;
        os << "\tDuration : " << flight->duration << endl << endl;
        os << "\tDeparture: " << flight->departure->getCity() << " , " << flight->departure->getCountry() << endl;
        os << "\tArrival  : " << flight->arrival->getCity() << " , " << flight->arrival->getCountry() << endl;
        os << "\tPlane    : " << flight->getPlane()->getType() << endl;
        os << "\tState    : " << flight->getStringState() << endl;
        return os;
    }

    const string &getId() const {
        return id;
    }

    void setId(const string &id) {
        Flight::id = id;
    }
};

class Plane_Pilot: public Person {

    vector<Flight *> flights;
    string plane_type;
    float total_hours;
    int total_flights;
    float baseSalary;
public:

    Plane_Pilot(){
        category = "Pilot";
    };

    Plane_Pilot(const string &name, const Date &birthday, float salary, const string &planeType)
            : Person(name, birthday, salary), plane_type(planeType) {
        baseSalary = salary;
        this->setSalary(baseSalary);
        this->total_flights = 0;
        this->total_hours = 0;
        this->flights = {};

        category = "Pilot";
        string idP = name.at(0) + to_string(birthday.getDay()) + category.at(0) +  to_string(birthday.getYear());
        this->setId(idP);

    }

    Plane_Pilot(const string &name, const Date &birthday, float salary, const string &planeType, float totalHours,
                int totalFlights) : Person(name, birthday, salary), plane_type(planeType), total_hours(totalHours),
                                    total_flights(totalFlights) {
        baseSalary = salary;
        this->setSalary(baseSalary);
        category = "Pilot";
        string idP = name.at(0) + to_string(birthday.getDay()) + category.at(0) +  to_string(birthday.getYear());
        this->setId(idP);
    }

    vector<Flight*> getFlights() const{
        return flights;
    }

    void setFlights(vector<Flight*> flightsTaken) {
        flights = flightsTaken;
    }

    const string &getPlaneType() const {
        return plane_type;
    }

    void setPlaneType(int index) {
        if(index < 0 || index >= PlaneTypes->size()) throw invalid_argument("Invalid index.");

        plane_type = PlaneTypes[index];
    }

    float getTotalHours() const {
        return total_hours;
    }

    void setTotalHours(float totalHours) {
        total_hours = totalHours;
    }

    int getTotalFlights() const {
        return total_flights;
    }

    void setTotalFlights(int totalFlights) {
        total_flights = totalFlights;
    }

    void setSalary(float BaseSalary){
        this->salary = BaseSalary * (1 + log(total_hours + 1) + log(total_flights + 1));
    };

    ostream &printInfo(ostream &os) const{
        os << "\tName         : " << this->getName() << endl
           << "\tBirth        : " << this->getBirthday() << endl
           << "\tCategory     : " << this->getCategory() << endl
           << "\tSalary       : " << this->getSalary() << endl
           << "\tTotal Hours  : " << this->getTotalHours() << endl
           << "\tTotal Flights: " << this->getTotalFlights() << endl
           << "\tPlane Type   : " << this->getPlaneType() << endl
           << "\t---------------------------" << endl;
        return os;
    }

};

class Crew_Member: public Person
{
    vector<Flight *> flights;
    float total_hours;
    int total_flights;
    float baseSalary;

public:

    Crew_Member(){
        category = "Crew";
    };

    Crew_Member(const string &name, const Date &birthday, float salary) : Person(name, birthday, salary){
        this->baseSalary = salary;
        this->setSalary(baseSalary);
        this->total_flights = 0;
        this->total_hours = 0;
        this->flights = {};
        category = "Crew";
        string idP = name.at(0) + to_string(birthday.getDay()) + category.at(0) +  to_string(birthday.getYear());
        this->setId(idP);

    }

    Crew_Member(const string &name, const Date &birthday, float salary, float totalHours, int totalFlights) : Person(
            name, birthday, salary), total_hours(totalHours), total_flights(totalFlights) {
        baseSalary = salary;
        this->setSalary(baseSalary);
        category = "Crew";
        string idP = name.at(0) + to_string(birthday.getDay()) + category.at(0) +  to_string(birthday.getYear());
        this->setId(idP);
    }

    const vector<Flight*> &getFlights() const {
        return flights;
    }

    void setFlights(const vector<Flight*> &flights) {
        Crew_Member::flights = flights;
    }

    float getTotalHours() const {
        return total_hours;
    }

    void setTotalHours(float totalHours) {
        total_hours = totalHours;
        setSalary(this->salary);
    }

    int getTotalFlights() const {
        return total_flights;
    }

    void setTotalFlights(int totalFlights) {
        total_flights = totalFlights;
        setSalary(this->salary);
    }

    void setSalary(float BaseSalary){
        this->salary = BaseSalary * (1 + log(total_hours + 1) + log(total_flights + 1));
    };

    ostream &printInfo(ostream &os) const{
        os << "\tName         : " << this->getName() << endl
           << "\tBirth        : " << this->getBirthday() << endl
           << "\tCategory     : " << this->getCategory() << endl
           << "\tSalary       : " << this->getSalary() << endl
           << "\tTotal Hours  : " << this->getTotalHours() << endl
           << "\tTotal Flights: " << this->getTotalFlights() << endl
           << "\t---------------------------" << endl;
        return os;
    }
};

#endif //AEDA_PROJECT_FLIGHT_H
