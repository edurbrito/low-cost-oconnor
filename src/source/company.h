#ifndef AEDA_PROJECT_COMPANY_H
#define AEDA_PROJECT_COMPANY_H

#include "airport.h"
#include <set>
#include <queue>

class Company{

private:

    string name;
    vector<Airport *> airports = vector<Airport *>();
    vector<Flight *> flights = vector<Flight *>();
    set<AirportRecord> AirportRecords;
    priority_queue<MaintenanceCompany> MaintenanceCompanies;
    string banner = "";

public:

    Company(const string &name);
    ~Company();

    const string &getName() const { return name; }
    void setName(const string &name) { Company::name = name; }

    const string &getBanner() const{ return banner; }
    void setBanner(const string &Banner){ banner = Banner; }

    void addAirport();
    void addFlight();

    void updateAirport();
    void updateFlight();

    void getAirports();
    void getFlights();

    void removeAirport();
    void removeFlight();

    void showFinances();
    float ExpensesValue();

    void addMaintenanceCompany();
    void removeMaintenanceCompany();

    friend void readFiles(Company &company);
    friend void showBanner(Company &company, bool onlyBanner);
    friend int showMenu(Company &company);
    friend int showCRUDMenu(Company &company);
    friend int showAPManagement(Company &company);
    friend int showAirportsRecords(Company &company);
    friend int showAirportFinances(Company &company);
    friend int showFlightsPanel(Company &company);
    friend int showMaintenanceCompanies(Company &company);
    friend void saveFiles(Company &company);

};

void clear_Console();
string inputInfo(string info);

#endif //AEDA_PROJECT_COMPANY_H
