#include <algorithm>
#include "company.h"
#include <fstream>
#include <sstream>
#include <windows.h>

/// \brief Clear console function
void clear_Console(){
    _getwch();
    system("CLS");
}

/// \brief Company Class Constructor
/// \param name Company Name
Company::Company(const string &name) : name(name){
    readFiles(*this);
}

/// \brief Transforms input line in a string
/// \param string info
/// \return string val
string inputInfo(string info){
    string val;
    do{
        cin.clear();
        cout << '\t' << info ;
        getline(cin,val);
    }while(cin.fail());

    return val;
}

/// \brief Company Class Destructor
Company::~Company(){
    saveFiles(*this);
}

/// \brief Function that adds airport to the vector airports of an object of the class Company
void Company::addAirport() {

    try{
        cout << endl << "\tAdding a new Airport requires setting a Manager and a Location." << endl << endl;
        cout << "\tProceeding to the creation of an Airport..." << endl << endl;

        cout << "\t#-- Manager:" << endl;

        string info = "Name: ";
        string Mname = inputInfo(info);

        info = "Salary (float): ";
        float Msalary = stof(inputInfo(info));

        cout << endl << "\t#-- Birthday:" << endl;

        int d,m,y;
        info = "Day: ";
        d= stoi(inputInfo(info));
        info = "Month: ";
        m = stoi(inputInfo(info));
        info = "Year: ";
        y = stoi(inputInfo(info));

        Date birth = Date(y,m,d);

        Administration *Manager = new Administration(Mname,birth,Msalary,"Manager");
        cout << endl << "\tPress any key to continue...  ";

        clear_Console();

        cout << endl << "\tAdding a new Airport requires setting a Manager and a Location." << endl << endl;
        cout << "\tProceeding to the creation of an Airport..." << endl << endl;

        cout << "\t#-- Location:" << endl ;
        string country, city, GPS;
        info = "Country: ";
        country = inputInfo(info);
        info = "City: ";
        city = inputInfo(info);
        info = "GPS: ";
        GPS = inputInfo(info);

        for(auto i : this->airports){
            if(i->getLocation()->getGps() == GPS){
                cout << endl << "\tAn Airport already exists in this Location." << endl;
                throw invalid_argument("GPS invalid");
            }
        }

        Location *Loc = new Location(country,city,GPS);
        cout << endl << "\tPress any key to continue...  ";

        clear_Console();

        cout << endl << "\tAdding a new Airport requires setting a Manager and a Location." << endl << endl;
        cout << "\tProceeding to the creation of an Airport..." << endl;

        Airport * newAirport = new Airport();
        newAirport->setManager(Manager);
        newAirport->setLocation(Loc);
        newAirport->vectorAddPerson(Manager);

        this->airports.push_back(newAirport);

        cout << endl << *newAirport;
        cout << endl << endl << "\tA new Airport was created. Press any key to return to the previous Menu... ";

        clear_Console();

    }
    catch(invalid_argument &e){
        cout << endl << "\tError : " << e.what();
        cout << endl << "\tCould not add the Airport... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch(...){
        cout << endl << "\tCould not add the Airport... Press any Key to return to the previous Menu...";
        clear_Console();
    }
}

/// \brief Aux Function to Compare Airport s from pointers
bool compareAirports(const Airport* a, const Airport *b){
    return *a < *b;
}

/// \brief Function that shows on console the information of each member of an airport vector from an object of the class Company
void Company::getAirports(){

    if(this->airports.size() == 0){
        cout << endl << "\tThere are no Airports... Press any Key to continue... ";
        clear_Console();
        return;
    }

    vector<Airport *> vAirp = vector<Airport *>(this->airports);
    sort(vAirp.begin(),vAirp.end(),compareAirports);
    cout << endl << "\tShowing all the Airports..." << endl
         << "\t---------------------------" << endl << endl;
    for(auto i : vAirp){
        cout << "\t--- Airport in " << i->getLocation()->getCity() << " , " << i->getLocation()->getCountry() << " ---" << endl;
        cout << *i << endl;
        cout << "\t---------------------------" << endl;
        cout << endl;
    }

    cout << endl << "\tPress any key to continue...  ";
    clear_Console();
};

/// \brief Function that removes a chosen airport of the vector airports from an object of the class Company
void Company::removeAirport() {

    if (this->airports.size() == 0) {
        cout << endl << "\tThere are no Airports to be removed... Press any Key to continue... ";
        clear_Console();
        return;
    }

    cout << endl << "\tShowing all Airports' Locations/Cities:" << endl << endl;
    int index = 0;
    for (auto i : this->airports) {
        cout << "\t" << index << ") " << endl << i->getLocation() << endl << endl << "\t----------" << endl << endl;
        index += 1;
    }
    cout << endl;
    string info = "Choose an Airport(Number) to remove: ";
    string res = inputInfo(info);

    try {
        if (stoi(res) >= 0 && stoi(res) < airports.size()) {
            for (auto i : this->flights) {
                if (i->getDeparture() == airports.at(stoi(res))->getLocation() ||
                    i->getArrival() == airports.at(stoi(res))->getLocation())
                    throw InvalidRemoval(
                            "\tCan not remove this airport. There are flights that arrive/departure from here.");
            }
            this->airports.erase(this->airports.begin() + stoi(res));
            cout << "\tAirport Removed... Press any Key to return to the previous Menu... ";
            clear_Console();
        } else {
            throw invalid_argument("Invalid Number");
        }
    }
    catch (InvalidRemoval &invalidRemoval) {
        cout << endl << invalidRemoval.getMessage();
        cout << endl << "\tCould not remove the Airport... Press any Key to return to the previous Menu...";
        clear_Console();
    }catch(invalid_argument &e){
        cout << endl << "\tError: " << e.what();
        cout << endl << "\tCould not remove the Airport... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch (...){
        cout << endl << "\tCould not remove the Airport... Press any Key to return to the previous Menu...";
        clear_Console();
    }

};

/// \brief Function that updates airport information from an object of the vector airports from the class Company
void Company::updateAirport(){

    if(this->airports.size() == 0){
        cout << endl << "\tThere are no Airports to be updated... Press any Key to continue... ";
        clear_Console();
        return;
    }

    cout << endl << "\tShowing all Airports' Locations/Cities:" << endl << endl;
    int index = 0;
    for(auto i : this->airports){
        cout << "\t" << index << ") " << endl << i->getLocation() << endl << endl << "\t----------" << endl << endl;
        index+=1;
    }

    cout << endl;
    string info = "Choose an Airport(Number) to update: ";
    string res = inputInfo(info);

    try{
        int index = stoi(res);
        if(index >= 0 && index < airports.size()){
            system("CLS");
            Airport *airport = this->airports.at(index);

            char opt;

            cout << "\tField to be updated for Airport in " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << ": "<< endl
                 << "\t--------------------------------------------------------------------" << endl
                 << "\t(A) Manager Info" << endl
                 << "\t(B) Location Info" << endl
                 << "\t-------------------------------" << endl
                 << "\tChoose an action (letter): ";
            cin >> opt;
            cin.ignore(1000,'\n');

            switch (opt)
            {
                case 'A': {
                    cout << endl << "\t#-- Manager:" << endl;

                    string info = "Name: ";
                    string Mname = inputInfo(info);

                    info = "Salary (float): ";
                    float Msalary = stof(inputInfo(info));

                    cout << endl << "\t#-- Birthday:" << endl;

                    int d, m, y;
                    info = "Day: ";
                    d = stoi(inputInfo(info));
                    info = "Month: ";
                    m = stoi(inputInfo(info));
                    info = "Year: ";
                    y = stoi(inputInfo(info));

                    Date birth = Date(y, m, d);

                    Administration *Manager = airport->getManager();
                    Manager->setName(Mname);
                    Manager->setSalary(Msalary);
                    Manager->setBirthday(birth);
                    Manager->setId(Mname.at(0) + to_string(birth.getDay()) + Manager->getCategory().at(0) + to_string(Msalary).at(0));

                    cout << endl << "\tPress any key to continue...  ";
                    break;
                }
                case 'B': {
                    cout << endl << "\t#-- Location:" << endl;
                    string country, city, GPS;
                    info = "Country: ";
                    country = inputInfo(info);
                    info = "City: ";
                    city = inputInfo(info);
                    info = "GPS: ";
                    GPS = inputInfo(info);

                    Location *Loc = airport->getLocation();
                    Loc->setCountry(country);
                    Loc->setCity(city);
                    Loc->setGps(GPS);
                    airport->setLocation(Loc);

                    cout << endl << "\tPress any key to continue...  ";
                    break;
                }
                default:
                    cout << endl << "\tNot a valid option. Press any key to continue...  ";
                    break;
            }
            clear_Console();
        }
        else{
            throw invalid_argument("Invalid Number");
        }
    }
    catch(invalid_argument &e){
        cout << endl << "\tError: " << e.what();
        cout << endl << "\tCould not update the Airport... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch (...){
        cout << endl << "\tCould not update the Airport... Press any Key to return to the previous Menu...";
        clear_Console();
    }

}

/// \brief Function that adds flight to the vector flights of an object of the class Company
void Company::addFlight() {

    try{

        if(this->airports.size()<2){
            cout << endl << "\tNot enough Airports to create a Flight (At least two needed)." << endl;
            throw invalid_argument("Insufficient number of airports");
        }

        cout << endl << "\tAdding a new Flight requires setting the Date, the Hour, and the Locations." << endl << endl;
        cout << "\tProceeding to the creation of a Flight..." << endl << endl;

        cout << "\t#-- Flight Expected Date:" << endl;

        int Fd,Fm,Fy;
        string info = "Day: ";
        Fd= stoi(inputInfo(info));
        info = "Month: ";
        Fm = stoi(inputInfo(info));
        info = "Year: ";
        Fy = stoi(inputInfo(info));

        Date ExpectedDeparture = Date(Fy,Fm,Fd);

        cout << endl << "\t#-- Flight Expected Hour:" << endl;

        int h,m;
        info = "Hour: ";
        h= stoi(inputInfo(info));
        info = "Minutes: ";
        m = stoi(inputInfo(info));

        Hour ExpectedHour = Hour(h,m);

        info = "Duration (hours): ";
        float duration = stof(inputInfo(info));

        cout << endl << "\tPress any key to continue...  ";

        clear_Console();

        cout << endl << "\tAdding a new Flight requires setting the Date, the Hour, and the Locations." << endl << endl;
        cout << "\tProceeding to the creation of a Flight..." << endl << endl;

        cout << endl << "\t#-- Departure Location:" << endl;

        cout << endl << "\tShowing all Airports' Locations:" << endl << endl;
        int index = 0;
        vector<Airport *> copyAirp = this->airports;
        for(auto i : copyAirp){
            cout << "\t" << index << ") " << i->getLocation()->getCity() << " , " << i->getLocation()->getCountry() << " - " <<  i->getLocation()->getGps();
            cout << endl;
            index+=1;
        }
        cout << endl;
        info = "Choose an Airport(Number) to set as Departure Destination for the flight: ";
        int res = stoi(inputInfo(info));
        int airportDeparture = res;
        Location *DepartureDestination = copyAirp.at(res)->getLocation();
        copyAirp.erase(copyAirp.begin() + res);
        cout << endl << "\tPress any key to continue...  ";

        clear_Console();

        cout << endl << "\tAdding a new Flight requires setting the Date, the Hour, and the Locations." << endl << endl;
        cout << "\tProceeding to the creation of a Flight..." << endl << endl;

        cout << endl << "\t#-- Arrival Location:" << endl;

        cout << endl << "\tShowing all Airports' Locations:" << endl << endl;

        index = 0;

        for(auto i : copyAirp){
            cout << "\t" << index << ") " << i->getLocation()->getCity() << " , " << i->getLocation()->getCountry() << " - " <<  i->getLocation()->getGps();
            cout << endl;
            index+=1;
        }

        cout << endl;
        info = "Choose an Airport(Number) to set as Arrival Destination for the flight: ";
        res = stoi(inputInfo(info));

        Location *ArrivalDestination = copyAirp.at(res)->getLocation();
        cout << endl << "\tPress any key to continue...  ";
        clear_Console();

        if(this->airports.at(airportDeparture)->getPlanes().size() <= 0){
            cout << "\tCan not add a flight without a plane in the Departure Airport" << endl;
            throw invalid_argument("No planes in the departure airport");
        }

        cout << endl << "\tAdding a new Flight requires setting the Date, the Hour, and the Locations." << endl << endl;
        cout << "\tProceeding to the creation of a Flight..." << endl << endl;

        cout << endl << "\t#-- Showing all Planes:" << endl << endl;

        index = 0;

        for(auto p : this->airports.at(airportDeparture)->getPlanes()){
            cout << "\t" << index << ") ------------------" << endl << p;
            cout << endl;
            index+=1;
        }

        cout << endl;
        info = "Choose a Plane(Number): ";
        res = stoi(inputInfo(info));
        Plane * plane =this->airports.at(airportDeparture)->getPlanes().at(res);

        Flight * newFlight = new Flight(ExpectedDeparture,ExpectedHour,DepartureDestination,ArrivalDestination,duration,plane);
        this->flights.push_back(newFlight);
        vector<Flight *> vF = plane->getFlights();
        vF.push_back(newFlight);
        plane->setFlights(vF);

        for(auto person : plane->getPlaneCrew()){
            if(person->getCategory() == "Pilot"){
                Plane_Pilot * planePilot = dynamic_cast<Plane_Pilot *>(person);
                vector<Flight *> vFp = planePilot->getFlights();
                vFp.push_back(newFlight);
                planePilot->setFlights(vFp);
            }
            else if(person->getCategory() == "Crew"){
                Crew_Member * crewMember = dynamic_cast<Crew_Member *>(person);
                vector<Flight *> vFp = crewMember->getFlights();
                vFp.push_back(newFlight);
                crewMember->setFlights(vFp);
            }
        }

        cout << endl << endl << "\tA new Flight was created. Press any key to return to the previous Menu... ";

        clear_Console();

    }
    catch(invalid_argument &e){
        cout << endl << "\tError: " << e.what();
        cout << endl << "\tCould not add the Flight... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch(...){
        cout << endl << "\tCould not add the Flight... Press any Key to return to the previous Menu...";
        clear_Console();
    }

}

/// \brief Aux Function to Compare Flight s from pointers
bool compareFlights(const Flight* a, const Flight *b){
    return *a < *b;
}

/// \brief Function that shows on console the information of each member of a flight's vector from an object of the class Company
void Company::getFlights()
{
    if(this->flights.size() == 0){
        cout << endl << "\tThere are no Flights... Press any Key to continue... ";
        clear_Console();
        return;
    }

    vector<Flight *> vFli = vector<Flight *>(this->flights);
    sort(vFli.begin(),vFli.end(),compareFlights);

    cout << endl << "\tShowing all the Flights..." << endl
         << "\t---------------------------" << endl << endl;
    for(auto i : vFli){
        cout << i;
        cout << "\t---------------------------" << endl;
    }

    cout << endl << "\tPress any key to continue...  ";
    clear_Console();
}

/// \brief Function that removes a chosen flight of the vector flights from an object of the class Company
void Company::removeFlight()
{
    if(this->flights.size() == 0){
        cout << endl << "\tThere are no Flights to be removed... Press any Key to continue... ";
        clear_Console();
        return;
    }

    cout << endl << "\tShowing all existing Flights :" << endl << endl;
    int index = 0;
    for(auto i : this->flights){
        cout << "\t" << index << ") " << endl
             << i << "\t---------------------------" << endl << endl;
        index+=1;
    }
    cout << endl;
    string info = "Choose a Flight(Number) to remove: ";
    string res = inputInfo(info);

    try{
        if(stoi(res) >= 0 && stoi(res) < flights.size()){
            this->flights.erase(this->flights.begin() + stoi(res));
            cout << "\tFlight Removed... Press any Key to return to the previous Menu... ";
            clear_Console();
        }
        else{
            throw invalid_argument("Invalid Number");
        }
    }
    catch(invalid_argument &e){
        cout << endl << "\tError: " << e.what();
        cout << endl << "\tCould not remove the Flight... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch (...){
        cout << endl << "\tCould not remove the Flight... Press any Key to return to the previous Menu...";
        clear_Console();
    }
}

/// \brief Function that updates flight information from an object of the vector flights from the class Company
void Company::updateFlight()
{
    if(this->flights.size() == 0){
        cout << endl << "\tThere are no Flights to be updated... Press any Key to continue... ";
        clear_Console();
        return;
    }

    cout << endl << "\tShowing all existing Flights :" << endl << endl;
    int index = 0;
    for(auto i : this->flights){
        cout << "\t" << index << ") " << endl
             << i << "\t---------------------------" << endl << endl;
        index+=1;
    }

    try{
        cout << endl;
        string info = "Choose a Flight(Number) to update: ";
        string res = inputInfo(info);
        int fligh_index = stoi(res);
        cout << endl << "\tPress any key to continue...  ";
        clear_Console();
        if(fligh_index >= 0 && fligh_index < flights.size()){

            Flight *flight = this->flights.at(fligh_index);

            char opt;
            cout << endl;
            cout << "\tField to be updated for Flight that goes from " << flight->getDeparture()->getCountry() << " to " << flight->getArrival()->getCountry() << " in " << flight->getDate() << " :" << endl
                 << "\t--------------------------------------------------------------------" << endl
                 << endl
                 << "\t(A) Expected Date and Hour" << endl
                 << "\t(B) Departure and Arrival airports" << endl
                 << "\t(C) Plane" << endl
                 << "\t(D) State" << endl
                 << endl
                 << "\t-------------------------------" << endl
                 << "\tChoose an action (letter): ";
            cin >> opt;
            cin.ignore(1000,'\n');

            switch (opt)
            {
                case 'A': {
                    system("CLS");
                    cout << endl << "\t#-- Expected Date:" << endl;

                    int Fd,Fm,Fy;
                    string info = "Day: ";
                    Fd= stoi(inputInfo(info));
                    info = "Month: ";
                    Fm = stoi(inputInfo(info));
                    info = "Year: ";
                    Fy = stoi(inputInfo(info));

                    Date ExpectedDeparture = Date(Fy,Fm,Fd);

                    cout << endl << "\t#-- Expected Hour:" << endl;

                    int h,m;
                    info = "Hour: ";
                    h= stoi(inputInfo(info));
                    info = "Minutes: ";
                    m = stoi(inputInfo(info));

                    Hour ExpectedHour = Hour(h,m);

                    info = "Duration: ";
                    float duration = stof(inputInfo(info));

                    flight->setDate(ExpectedDeparture);
                    flight->setHour(ExpectedHour);
                    flight->setDuration(duration);

                    cout << endl << "\tPress any key to continue...  ";
                    break;
                }
                case 'B': {
                    system("CLS");

                    cout << endl << "\tUpdating the Departure and Arrival Airports of a Flight." << endl << endl;
                    cout << "\tProceeding to the update of a Flight..." << endl << endl;

                    cout << endl << "\t#-- Departure Location:" << endl;

                    cout << endl << "\tShowing all Airports' Locations:" << endl << endl;
                    int index = 0;
                    vector<Airport *> copyAirp = this->airports;
                    for(auto i : copyAirp){
                        cout << "\t" << index << ") " << i->getLocation()->getCity() << " , " << i->getLocation()->getCountry() << " - " <<  i->getLocation()->getGps();
                        cout << endl;
                        index+=1;
                    }
                    cout << endl;
                    info = "Choose an Airport(Number) to set as Departure Destination for the flight: ";
                    int res = stoi(inputInfo(info));

                    Location *DepartureDestination = copyAirp.at(res)->getLocation();
                    copyAirp.erase(copyAirp.begin() + res);
                    cout << endl << "\tPress any key to continue...  ";

                    clear_Console();

                    cout << endl << "\tAdding a new Flight requires setting the Date, the Hour, and the Locations." << endl << endl;
                    cout << "\tProceeding to the creation of a Flight..." << endl << endl;

                    cout << endl << "\t#-- Arrival Location:" << endl;

                    cout << endl << "\tShowing all Airports' Locations:" << endl << endl;

                    index = 0;

                    for(auto i : copyAirp){
                        cout << "\t" << index << ") " << i->getLocation()->getCity() << " , " << i->getLocation()->getCountry() << " - " <<  i->getLocation()->getGps();
                        cout << endl;
                        index+=1;
                    }

                    cout << endl;
                    info = "Choose an Airport(Number) to set as Arrival Destination for the flight: ";
                    res = stoi(inputInfo(info));

                    Location *ArrivalDestination = copyAirp.at(res)->getLocation();

                    cout << endl << "\tPress any key to continue...  ";
                    clear_Console();

                    flight->setDeparture(DepartureDestination);
                    flight->setArrival(ArrivalDestination);

                    break;
                }
                case 'C':
                {
                    system("CLS");
                    cout << endl << "\t#-- Plane:" << endl;

                    for(auto i : this->airports){
                        if(i->getLocation() == flight->getDeparture()){
                            index = 0;

                            for(auto p : i->getPlanes()){
                                cout << "\t" << index << ") ------------------" << endl << p;
                                cout << endl;
                                index+=1;
                            }

                            cout << endl;
                            info = "Choose a Plane(Number): ";
                            long long int resP = stoi(inputInfo(info));
                            Plane * plane = i->getPlanes().at(resP);
                            flight->setPlane(plane);
                            break;
                        }
                    }


                    cout << endl << "\tPress any key to continue...  ";
                    break;
                }
                case 'D':
                {
                    system("CLS");
                    char opt;

                    cout << endl << "\tState of the Flight:" << endl
                         << "\t--------------------------------------------------------------------" << endl
                         << "\t(A) Scheduled" << endl
                         << "\t(B) Done " << endl
                         << "\t(C) Canceled" << endl
                         << "\t-------------------------------" << endl
                         << "\tChoose an action (letter): ";
                    cin >> opt;
                    cin.ignore(1000,'\n');


                    switch (opt)
                    {
                        case 'A': {
                            flight->setState(Scheduled);
                            break;}
                        case 'B': {
                            flight->setState(Done);
                            Plane *plane = flight->getPlane();
                            plane->setTotalTrips(plane->getTotalTrips() + 1);
                            plane->setTotalHours(plane->getTotalHours() + flight->getDuration());
                            for(auto person : plane->getPlaneCrew()){
                                if(person->getCategory() == "Pilot"){
                                    Plane_Pilot * planePilot = dynamic_cast<Plane_Pilot *>(person);
                                    planePilot->setTotalFlights(planePilot->getTotalFlights() + 1);
                                    planePilot->setTotalHours(planePilot->getTotalHours() + flight->getDuration());
                                }
                                else if(person->getCategory() == "Crew"){
                                    Crew_Member * crewMember = dynamic_cast<Crew_Member *>(person);
                                    crewMember->setTotalFlights(crewMember->getTotalFlights() + 1);
                                    crewMember->setTotalHours(crewMember->getTotalHours() + flight->getDuration());

                                }
                            }

                            break;}
                        case 'C': {
                            flight->setState(Canceled);
                            break;}
                        default:
                            throw invalid_argument("Invalid State");
                    }
                    cout << endl << "\tPress any key to continue...  ";
                    break;
                }
                default:
                    cout << endl << "\tNot a valid option. Press any key to continue...  ";
                    break;
            }
            clear_Console();
        }
        else{
            throw invalid_argument("Invalid Number");
        }
    }
    catch(invalid_argument &e){
        cout << endl << "\tError: " << e.what();
        cout << endl << "\tCould not update the Flight... Press any Key to return to the previous Menu...";
        clear_Console();
    }

    catch (...){
        cout << endl << "\tCould not update the Flight... Press any Key to return to the previous Menu...";
        clear_Console();
    }
}

/// \brief Function that calculates Expenses value of a company
/// \return CompanyValue - Expenses value of a company
float Company::ExpensesValue()
{
    float CompanyValue=0;
    for (auto i : airports)
        CompanyValue += i->AirportExpensesValue();
    return CompanyValue;
}

///\brief Function that shows Expenses value of a company
void Company::showFinances()
{
    float pilot=0,crew=0,admin=0,employee=0,A319=0,A320=0,A330=0,B737=0;
    int i_pilot=0,i_crew=0,i_admin=0,i_employee=0,i_A319=0,i_A320=0,i_A330=0,i_B737=0;
    for (auto i: airports)
    {
        for (auto j: i->getPeople())
        {
            if (j->getCategory()=="Pilot")
            {
                i_pilot++;
                pilot+=j->getSalary();
            }
            if (j->getCategory()=="Crew")
            {
                i_crew++;
                crew+=j->getSalary();
            }
            if (j->getCategory()=="Admin")
            {
                i_admin++;
                admin+=j->getSalary();
            }
            if (j->getCategory()=="Employee")
            {
                i_employee++;
                employee+=j->getSalary();
            }
        }
        for (auto j: i->getPlanes())
        {
            if (j->getType()=="Airbus A319")
            {
                i_A319++;
                A319+=j->getOpCosts();
            }
            if (j->getType()=="Airbus A320")
            {
                i_A320++;
                A320+=j->getOpCosts();
            }
            if (j->getType()=="Airbus A330")
            {
                i_A330++;
                A330+=j->getOpCosts();
            }
            if (j->getType()=="Boeing 737")
            {
                i_B737++;
                B737+=j->getOpCosts();
            }
        }
    }
    float PilotMean= (i_pilot==0) ? 0 : pilot/i_pilot;
    float CrewMean= (i_crew==0) ? 0 : crew/i_crew;
    float AdminMean= (i_admin==0) ? 0 : admin/i_admin;
    float EmployeeMean= (i_employee==0) ? 0 : employee/i_employee;
    float A319Mean= (i_A319==0) ? 0 : A319/i_A319;
    float A320Mean= (i_A320==0) ? 0 : A320/i_A320;
    float A330Mean= (i_A330==0) ? 0 : A330/i_A330;
    float B737Mean= (i_B737==0) ? 0 : B737/i_B737;
    system("CLS");
    cout << endl << "\tCompany Finances \n"
         << "\t_______________________________" << endl <<
        "\n\tWorkers Salary: " << endl <<
        "\t-------------------------------" << endl <<
        "\n\tPilot mean: " << PilotMean <<
        "\n\tCrew Members mean: " << CrewMean <<
        "\n\tAdministrator mean: " << AdminMean <<
        "\n\tEmployee mean: " << EmployeeMean << endl <<
        "\n\tNumber of workers: " << i_admin+i_crew+i_employee+i_pilot << endl <<
        "\n\tPlanes Operation Costs: " << endl <<
        "\t-------------------------------" << endl <<
        "\n\tAirbus A319 mean: " << A319Mean <<
        "\n\tAirbus A320 mean: " << A320Mean <<
        "\n\tAirbus A330 mean: " << A330Mean <<
        "\n\tBoeing 737 mean: " << B737Mean << endl <<
        "\n\tNumber of planes: " << i_A319+i_A320+i_A330+i_B737 << endl <<
        "\t-------------------------------" << endl <<
        "\n\tTotal Company Expenses: " << ExpensesValue() << endl <<
        endl << "\tPress any key to return to main menu.";
    clear_Console();
}

/// \brief Function that adds a MaintenanceCompany to the priority_queue
void Company::addMaintenanceCompany(){

    try{
        cout << endl << "\tAdding a new Company requires setting a Name, an availability and the corresponding Maintenances executed." << endl << endl;
        cout << "\tProceeding to the creation of a Maintenance Company..." << endl << endl;

        string info = "Company Name: ";
        string Mname = inputInfo(info);

        info = "Availability (minutes): ";
        float Availability = stof(inputInfo(info));

        info = "Maintenances previously executed: ";
        int Maintenances = stoi(inputInfo(info));

        MaintenanceCompany *M = new MaintenanceCompany(Availability,Maintenances,Mname);
        cout << endl << "\tPress any key to continue...  ";

        MaintenanceCompanies.push(*M);

        clear_Console();

    }
    catch(invalid_argument &e){
        cout << endl << "\tError : " << e.what();
        cout << endl << "\tCould not add the Company... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch(...){
        cout << endl << "\tCould not add the Company... Press any Key to return to the previous Menu...";
        clear_Console();
    }
}

/// \brief Function that removes a MaintenanceCompany from the priority_queue
void Company::removeMaintenanceCompany()
{
    if(MaintenanceCompanies.size() == 0){
        cout << endl << "\n\tThere are no Companies available... Press any Key to continue... ";
        clear_Console();
        return ;
    }

    vector<MaintenanceCompany> used;

    while(!MaintenanceCompanies.empty())
    {
        used.push_back(MaintenanceCompanies.top());
        MaintenanceCompanies.pop();
    }


    int res;
    try {
        int index=0;
        for (auto i : used) {
            cout << "\n\t" << index << ") " << i.getCompanyName() << " , available in " << i.getAvaiability() << " minutes" << endl;
            cout << "\t---------------------------" << endl;
            index += 1;
        }
        string info = "Choose a Company(index): ";
        res = stoi(inputInfo(info));

        if (used.size() - 1 < res)
            cout << endl << "\tCould not find the Company... ";
        else{
            cout << "\n\tCompany Name: " << used.at(res).getCompanyName() << endl;
            cout << "\tAvailability (minutes): " << used.at(res).getAvaiability() << endl;
            cout << "\tNumber of Maintenances in record: " << used.at(res).getMaintenancesNumber() << endl;;
            cout << "\t-------------------------\n" << endl;
            cout << endl << "\tCompany removed successfully... Press any Key to continue... ";
        }

        int count=0;
        for (auto i:used)
        {
            if (count!=res) {
                MaintenanceCompanies.push(i);
            }
            count++;
        }
    }catch (...){
        cout << endl << "\tInvalid index... Press any Key to return to the previous Menu...";
        for (auto i:used)
        {
            MaintenanceCompanies.push(i);
        }
        clear_Console();
        return ;
    }

    clear_Console();
    return ;
}

/// \brief Function that shows MaintenanceCompany Menu
/// \param Company company
/// \return 0 upon success, 1 otherwise
int showMaintenanceCompanies(Company &company){
    char opt2;
    cout << endl << "\tSearch for Maintenance Companies:" << endl
         << "\t--------------" << endl
         << endl
         << "\t(A) Add Company" << endl
         << "\t(B) Remove Company" << endl
         << "\t(C) Show Companies" << endl
         << "\t(D) Schedule Maintenance" <<endl
         << "\t(X) Exit" << endl
         << endl
         << "\t-------------------------------" << endl
         << "\tChoose an action (letter): ";
    cin >> opt2;
    cin.ignore(1000,'\n');
    cout << endl;


    switch (opt2)
    {
        case 'A':{
            system("CLS");
            company.addMaintenanceCompany();
            return 0;
        }
        case 'B': {
            system("CLS");
            company.removeMaintenanceCompany();
            return 0;
        }

        case 'C':{
            system("CLS");
            if(company.MaintenanceCompanies.size() == 0){
                cout << endl << "\tThere are no Companies available... Press any Key to continue... ";
                clear_Console();
                return 1;
            }

            cout << endl << "\tMaintenance Companies:" << endl;
            cout << "\t----------------------------------------------" << endl;

            char opt;

            cout << endl << "\tSearch for Maintenance Companies:" << endl
                 << "\t--------------" << endl
                 << endl
                 << "\t(A) In Order" << endl
                 << "\t(B) Reverse Order" << endl
                 << "\t(C) Specific Company" << endl
                 << "\t(X) Exit" << endl
                 << endl
                 << "\t-------------------------------" << endl
                 << "\tChoose an action (letter): ";
            cin >> opt;
            cin.ignore(1000,'\n');
            cout << endl;

            switch (opt)
            {
                case 'A':{
                    system("CLS");
                    vector<MaintenanceCompany> used;

                    while(!company.MaintenanceCompanies.empty())
                    {
                        used.push_back(company.MaintenanceCompanies.top());
                        cout << "\n\tCompany Name : " << company.MaintenanceCompanies.top().getCompanyName() << endl;
                        cout << "\tAvailability(minutes) : " << company.MaintenanceCompanies.top().getAvaiability() << endl;
                        cout << "\tNumber of Maintenances in record  : " << company.MaintenanceCompanies.top().getMaintenancesNumber() << endl;;
                        cout << "\t-------------------------" << endl;
                        company.MaintenanceCompanies.pop();
                    }
                    for (auto i:used)
                    {
                        company.MaintenanceCompanies.push(i);
                    }

                    cout << endl << "\tPress any key to return to the main menu... ";
                    clear_Console();
                    return 1;
                }
                case 'B':{
                    system("CLS");
                    vector<MaintenanceCompany> used;

                    while(!company.MaintenanceCompanies.empty())
                    {
                        used.push_back(company.MaintenanceCompanies.top());
                        company.MaintenanceCompanies.pop();
                    }

                    reverse(used.begin(),used.end());

                    for (auto i:used)
                    {
                        cout << "\n\tCompany Name : " << i.getCompanyName() << endl;
                        cout << "\tAvailability(minutes) : " << i.getAvaiability() << endl;
                        cout << "\tNumber of Maintenances in record  : " << i.getMaintenancesNumber() << endl;;
                        cout << "\t-------------------------" << endl;
                        company.MaintenanceCompanies.push(i);
                    }

                    cout << endl << "\tPress any key to return to the main menu... ";
                    clear_Console();
                    return 1;
                }
                case 'C':{
                    system("CLS");
                    MaintenanceCompany *mc1;
                    vector<MaintenanceCompany> used;

                    while(!company.MaintenanceCompanies.empty())
                    {
                        used.push_back(company.MaintenanceCompanies.top());
                        company.MaintenanceCompanies.pop();
                    }
                    for (auto i:used)
                    {
                        company.MaintenanceCompanies.push(i);
                    }

                    int res;

                    try {
                        int index=0;
                        cout << endl;
                        for (auto i : used) {
                            cout << "\t" << index << " " << i.getCompanyName() << " , available in " << i.getAvaiability() << " minutes" << endl;
                            cout << "\t---------------------------" << endl;
                            index += 1;
                        }
                        string info = "Choose a Company(index): ";
                        res = stoi(inputInfo(info));
                    }catch (...){
                        cout << endl << "\tCould not choose the Company... Press any Key to return to the previous Menu...";
                        clear_Console();
                        return 1;
                    }

                    if (used.size()-1<res)
                        cout << endl << "\tCould not find the Company... ";
                    else{
                        cout << endl;
                        cout << "\tCompany Name " << used.at(res).getCompanyName() << endl;
                        cout << "\tAvailability(minutes) : " << used.at(res).getAvaiability() << endl;
                        cout << "\tNumber of Maintenances in record  : " << used.at(res).getMaintenancesNumber() << endl;;
                        cout << "\t-------------------------" << endl;
                    }


                    cout << endl << "\tPress any key to return to the main menu... ";
                    clear_Console();
                    return 1;
                }
                case 'X':
                    system("CLS");
                    return 0;
                default:
                    system("CLS");
                    return 0;
            }
        }
        case 'D':{
            if(company.airports.size() == 0){
                cout << endl << "\tThere are no Airports... Press any Key to continue... ";
                clear_Console();
                return 1;
            }
            int res;
            Airport *airport;
            try {
                vector<Airport *> vAirp = vector<Airport *>(company.airports);
                sort(vAirp.begin(), vAirp.end());
                int index = 0;
                for (auto i : vAirp) {
                    cout << "\t" << index << ") --- Airport in " << i->getLocation()->getCity() << " , "
                         << i->getLocation()->getCountry() << " ---" << endl << endl;
                    cout << *i << endl;
                    cout << "\t---------------------------" << endl << endl;
                    index += 1;
                }
                string info = "Choose an Airport(index): ";
                res = stoi(inputInfo(info));
                airport = vAirp.at(res);
            }catch (...){
                cout << endl << "\tCould not choose the Airport... Press any Key to return to the previous Menu...";
                clear_Console();
                return 1;
            }

            system("CLS");
            cout << endl;
            int index=0;
            for (auto i : company.airports.at(res)->getPlanes())
            {
                //cout << "\t" <<index << ") " << i->getId() << ", " << i->getCapacity() << endl;
                cout << "\t" << index << ") ------------------------------" << endl;
                cout << i << endl;
                index++;
            }
            try {
                string info = "\n\tChoose a Plane to schedule repairing: ";
                res = stoi(inputInfo(info));
                if (res > index-1) {
                    throw invalid_argument("Invalid Index");
                }
                vector<MaintenanceCompany> used;

                info = "Choose the number of minimal maintenances the company should have: ";
                int minM;
                minM = stoi(inputInfo(info));
                bool value=false;

                while(!company.MaintenanceCompanies.empty())
                {
                    if (company.MaintenanceCompanies.top().getMaintenancesNumber()>=minM)
                    {
                        MaintenanceCompany mc1 = company.MaintenanceCompanies.top();
                        mc1.setAvaiability(mc1.getAvaiability()+180.0);
                        mc1.setMaintenancesNumber(mc1.getMaintenancesNumber()+1);
                        used.push_back(mc1);
                        company.MaintenanceCompanies.pop();
                        value=true;
                        break;
                    }
                    else
                    {
                        used.push_back(company.MaintenanceCompanies.top());
                        company.MaintenanceCompanies.pop();
                    }
                }
                if (value==false)
                    cout << "\tNo such company exists";
                else{
                    cout << endl << "\tA company was successfully hired to repair the plane" << endl;
                }

                for (auto i:used)
                {
                    company.MaintenanceCompanies.push(i);
                }
            }catch (...){
                cout << endl << "\tInvalid information... Press any Key to return to the previous Menu...";
                clear_Console();
                return 1;
            }

            cout << endl << "\tPress any key to return to the main menu... ";
            clear_Console();
        }
        case 'X':
            system("CLS");
            return 0;
        default:
            system("CLS");
            return 0;
    }
    system("CLS");
    return 0;
}

/// \brief Shows Company banner
/// \param company - Object from class Company
/// \param onlyBanner
void showBanner(Company &company, bool onlyBanner){

    cout << "\t" << company.banner << endl;
    cout << "\t" << company.name << endl << endl;
    if(onlyBanner){
        cout << "\tThis is a Cpp OOP Project for AEDA Class." << endl << "\tDeveloped by:" << endl;
        cout << "\tEduardo Brito  - up201806271" << endl;
        cout << "\tPedro Ferreira - up201806506" << endl;
        cout << "\tPedro Ponte    - up201809694" << endl;
        cout << endl << "\tPress any key to return to main menu.";
        clear_Console();
    }

}

/// \brief Shows CRUD Menu
/// \param company - Object from class Company
/// \return 0 upon success, 1 upon failure
int showCRUDMenu(Company &company){
    char opt;

    cout << endl << "\t  ___ ___ _   _ ___    __  __ ___ _  _ _   _ \n"
                    "\t / __| _ \\ | | |   \\  |  \\/  | __| \\| | | | |\n"
                    "\t| (__|   / |_| | |) | | |\\/| | _|| .` | |_| |\n"
                    "\t \\___|_|_\\\\___/|___/  |_|  |_|___|_|\\_|\\___/ "<< endl
         << "\t--------------------------------------------------------------------" << endl
         << endl
         << "\t(A) Add Airport" << endl
         << "\t(B) Add Flight" << endl
         << "\t(C) Remove Airport" << endl
         << "\t(D) Remove Flight" << endl
         << "\t(E) Update Airport" << endl
         << "\t(F) Update Flight" << endl
         << "\t(G) View all Airports" << endl
         << "\t(H) View all Flights" << endl
         << "\t(X) Exit" << endl
         << endl
         << "\t-------------------------------" << endl
         << "\tChoose an action (letter): ";
    cin >> opt;
    cin.ignore(1000,'\n');

    switch (opt)
    {
        case 'A':
            system("CLS");
            company.addAirport();
            break;
        case 'B':
            system("CLS");
            company.addFlight();
            break;
        case 'C':
            system("CLS");
            company.removeAirport();
            break;
        case 'D':
            system("CLS");
            company.removeFlight();
            break;
        case 'E':
            system("CLS");
            company.updateAirport();
            break;
        case 'F':
            system("CLS");
            company.updateFlight();
            break;
        case 'G':
            system("CLS");
            company.getAirports();
            break;
        case 'H':
            system("CLS");
            company.getFlights();
            break;
        case 'X':
            system("CLS");
            return 0;
        default:
            system("CLS");
            break;
    }
    return 0;
}

/// \brief Shows Airport Management Menu
/// \param company - Object from class Company
/// \return 0 upon success, 1 upon failure
int showAPManagement(Company &company){

    if(company.airports.size() == 0){
        cout << endl << "\tThere are no Airports... Press any Key to continue... ";
        clear_Console();
        return 1;
    }
    Airport *airport;
    try {
        vector<Airport *> vAirp = vector<Airport *>(company.airports);
        sort(vAirp.begin(), vAirp.end());
        int index = 0;
        for (auto i : vAirp) {
            cout << "\t" << index << ") --- Airport in " << i->getLocation()->getCity() << " , "
                 << i->getLocation()->getCountry() << " ---" << endl << endl;
            cout << *i << endl << endl;
            cout << "\t---------------------------" << endl << endl;
            index += 1;
        }
        string info = "Choose an Airport (index): ";
        int res = stoi(inputInfo(info));
        airport = vAirp.at(res);
    }catch (...){
        cout << endl << "\tCould not choose the Airport... Press any Key to return to the previous Menu...";
        clear_Console();
        return 1;
    }
    while(true){
        system("CLS");
        char opt;
        cout << endl << "\tAirport Management -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
             << "\t--------------------------------------------------------------------" << endl
             << endl
             << "\t(A) Add Person" << endl
             << "\t(B) Add Plane" << endl
             << "\t(C) Remove Person" << endl
             << "\t(D) Remove Plane" << endl
             << "\t(E) Update Person" << endl
             << "\t(F) Update Plane" << endl
             << "\t(G) View all People" << endl
             << "\t(H) View all Planes" << endl
             << "\t(I) View all time Workers" << endl
             << "\t(X) Exit" << endl
             << endl
             << "\t-------------------------------" << endl
             << "\tChoose an action (letter): ";
        cin >> opt;
        cin.ignore(1000,'\n');

        switch (opt)
        {
            case 'A':
                system("CLS");
                airport->addPerson();
                break;
            case 'B':
                system("CLS");
                airport->addPlane();
                break;
            case 'C':
                system("CLS");
                airport->removePerson();
                break;
            case 'D':
                system("CLS");
                airport->removePlane();
                break;
            case 'E':
                system("CLS");
                airport->updatePerson();
                break;
            case 'F':
                system("CLS");
                airport->updatePlane();
                break;
            case 'G':
                system("CLS");
                airport->getAllPeople();
                break;
            case 'H':
                system("CLS");
                airport->getAllPlanes();
                break;
            case 'I':
                system("CLS");
                airport->showWorkersRecord();
            case 'X':
                system("CLS");
                return 0;
            default:
                system("CLS");
                break;
        }
    }
}

/// \brief Shows Airports Records in a BST
/// \param company - Object from class Company
/// \return 0 upon success, 1 upon failure
int showAirportsRecords(Company &company){
    if(company.airports.size() == 0){
        cout << endl << "\tThere are no Airports... Press any Key to continue... ";
        clear_Console();
        return 1;
    }

    try{
        for(auto ap : company.airports){
            AirportRecord airportRecord = AirportRecord(ap);

            for(auto f : company.flights){
                if(*f->getArrival() == *ap->getLocation()){
                    airportRecord.addTrackHours(f->getDuration(),0);
                }
            }
            company.AirportRecords.insert(airportRecord);
        }
    }catch(...){
        cout << endl << "\tCould not show Airports Records... Press any Key to continue... ";
        clear_Console();
        return 1;
    }

    cout << endl << "\tAirports Records:" << endl;
    cout << "\t----------------------------------------------" << endl;

    char opt;

    cout << endl << "\tSearch for Airports Records:" << endl
         << "\t--------------" << endl
         << endl
         << "\t(A) In Order" << endl
         << "\t(B) Reverse Order" << endl
         << "\t(C) Specific Airport" << endl
         << "\t(X) Exit" << endl
         << endl
         << "\t-------------------------------" << endl
         << "\tChoose an action (letter): ";
    cin >> opt;
    cin.ignore(1000,'\n');
    cout << endl;

    switch (opt)
    {
        case 'A':{
            for(auto i : company.AirportRecords){
                cout << "\tAirport in " << endl << i.getAirport()->getLocation() << endl;
                cout << "\tNumber of Arrivals in : " << i.getCount() << endl;
                cout << "\tTotal Hours on Track  : " << i.getTrackHours() << endl;;
                cout << "\tAverage Hours on Track: " << i.getAverageTrackHours() << endl;
                cout << "\t-------------------------" << endl;
            }
            cout << endl << "\tPress any key to return to the main menu... ";
            clear_Console();
            return 1;
        }
        case 'B':{
            set<AirportRecord>::reverse_iterator it = company.AirportRecords.rbegin();
            while(it != company.AirportRecords.rend()){
                cout << "\tAirport in " << endl << it->getAirport()->getLocation() << endl;
                cout << "\tNumber of Arrivals in : " << it->getCount() << endl;
                cout << "\tTotal Hours on Track  : " << it->getTrackHours() << endl;;
                cout << "\tAverage Hours on Track: " << it->getAverageTrackHours() << endl;
                cout << "\t-------------------------" << endl;
                it++;
            }
            cout << endl << "\tPress any key to return to the main menu... ";
            clear_Console();
            return 1;
        }
        case 'C':{
            Airport *airport;
            try {
                vector<Airport *> vAirp = vector<Airport *>(company.airports);
                sort(vAirp.begin(), vAirp.end());
                int index = 0;
                for (auto i : vAirp) {
                    cout << "\t" << index << ") Airport in " << i->getLocation()->getCity() << " , " << i->getLocation()->getCountry() << endl;
                    cout << "\t---------------------------" << endl;
                    index += 1;
                }
                string info = "Choose an Airport(index): ";
                int res = stoi(inputInfo(info));
                airport = vAirp.at(res);
            }catch (...){
                cout << endl << "\tCould not choose the Airport... Press any Key to return to the previous Menu...";
                clear_Console();
                return 1;
            }
            auto it = company.AirportRecords.begin();
            bool found = false;
            cout << endl;
            while(it != company.AirportRecords.end()){
                if(*it == AirportRecord(airport)){
                    cout << "\tAirport in " << endl << it->getAirport()->getLocation() << endl;
                    cout << "\tNumber of Arrivals in : " << it->getCount() << endl;
                    cout << "\tTotal Hours on Track  : " << it->getTrackHours() << endl;;
                    cout << "\tAverage Hours on Track: " << it->getAverageTrackHours() << endl;
                    cout << "\t-------------------------" << endl;
                    found = true;
                    break;
                }
                it++;
            }
            if(!found){
                cout << endl << "\tCould not find the airport... ";
            }
            cout << endl << "\tPress any key to return to the main menu... ";
            clear_Console();
            return 1;
        }
        case 'X':
            system("CLS");
            return 0;
        default:
            system("CLS");
            return 0;
    }

    return 0;
}

/// \brief Shows Airport Finances Menu
/// \param company - Object from class Company
/// \return 0 upon success, 1 upon failure
int showAirportFinances(Company &company){

    if(company.airports.size() == 0){
        cout << endl << "\tThere are no Airports... Press any Key to continue... ";
        clear_Console();
        return 1;
    }
    Airport *airport;
    try {
        vector<Airport *> vAirp = vector<Airport *>(company.airports);
        sort(vAirp.begin(), vAirp.end());
        int index = 0;
        for (auto i : vAirp) {
            cout << "\t" << index << ") --- Airport in " << i->getLocation()->getCity() << " , "
                 << i->getLocation()->getCountry() << " ---" << endl << endl;
            cout << *i << endl;
            cout << "\t---------------------------" << endl << endl;
            index += 1;
        }
        string info = "Choose an Airport(index): ";
        int res = stoi(inputInfo(info));
        airport = vAirp.at(res);
    }catch (...){
        cout << endl << "\tCould not choose the Airport... Press any Key to return to the previous Menu...";
        clear_Console();
        return 1;
    }

    while(true){
        system("CLS");
        char opt;
        cout << endl << "\tAirport Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
             << "\t--------------------------------------------------------------------" << endl
             << endl
             << "\t(A) Workers" << endl
             << "\t(B) Planes" << endl
             << "\t(C) Total" << endl
             << "\t(X) Exit" << endl
             << endl
             << "\t-------------------------------" << endl
             << endl
             << "\tChoose an action (letter): ";
        cin >> opt;
        cin.ignore(1000,'\n');
        float total_expenses_value = 0;
        switch (opt)
        {
            case 'A':
                system("CLS");
                char opt;

                cout << endl << "\tWorkers Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                     << "\t--------------------------------------------------------------------" << endl
                     << endl
                     << "\t(A) Administrator" << endl
                     << "\t(B) Employee" << endl
                     << "\t(C) Crew Member" << endl
                     << "\t(D) Pilot" << endl
                     << "\t(E) Total" << endl
                     << endl
                     << "\t-------------------------------" << endl
                     << endl
                     << "\tChoose a Person Type (letter): ";
                cin >> opt;
                cin.ignore(1000,'\n');

                if(opt != 'A' && opt != 'B' && opt != 'C' && opt != 'D' && opt != 'E'){
                    cout << endl << endl << "\tCould not see Workers Finances. Press any key to return to the previous Menu... ";
                    clear_Console();
                    return 1;
                }
                switch (opt)
                {
                    case 'A':
                        //system("CLS");
                        cout << endl << "\tAdministrators Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                        << "\t-------------------------------" << endl <<
                        "\n\tSalary Costs: " << airport->ShowFinancesWorkers("Admin") << endl <<
                        endl << "\tPress any key to return to main menu.";
                        clear_Console();
                        break;
                    case 'B':
                        //system("CLS");
                        cout << endl << "\tEmployees Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                        << "\t-------------------------------" << endl <<
                        "\n\tSalary Costs: " << airport->ShowFinancesWorkers("Employee") << endl <<
                        endl << "\tPress any key to return to main menu.";
                        clear_Console();
                        break;
                    case 'C':
                        //system("CLS");
                        cout << endl << "\tCrew Members Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                        << "\t-------------------------------" << endl <<
                        "\n\tSalary Costs: " << airport->ShowFinancesWorkers("Crew") << endl <<
                        endl << "\tPress any key to return to main menu.";
                        clear_Console();
                        break;
                    case 'D':
                        //system("CLS");
                        cout << endl << "\tPilots Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                        << "\t-------------------------------" << endl <<
                        "\n\tSalary Costs: " << airport->ShowFinancesWorkers("Pilot") << endl <<
                        endl << "\tPress any key to return to main menu.";
                        clear_Console();
                        break;
                    case 'E':
                        //system("CLS");
                        cout << endl << "\tAll Staff Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                        << "\t-------------------------------" << endl <<
                        "\n\tSalary Costs: " << airport->ShowFinancesWorkers("total") << endl <<
                        endl << "\tPress any key to return to main menu.";
                        clear_Console();
                        break;
                }
                break;
            case 'B':
                system("CLS");
                opt;
                cout << endl << "\tPlanes Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl;
                cout << endl
                     << "\t(A) Airbus A319" << endl
                     << "\t(B) Airbus A320" << endl
                     << "\t(C) Airbus A330" << endl
                     << "\t(D) Boeing 737" << endl
                     << "\t(E) Total" << endl
                     << endl
                     << "\t-------------------------------" << endl
                     << endl
                     << "\tChoose a Plane Type (letter): ";
                cin >> opt;
                cin.ignore(1000,'\n');

                if(opt != 'A' && opt != 'B' && opt != 'C' && opt != 'D' && opt != 'E'){
                    cout << endl << endl << "\tCould not see Workers Finances. Press any key to return to the previous Menu... ";
                    clear_Console();
                    return 1;
                }
                switch (opt)
                {
                    case 'A':
                        //system("CLS");
                        cout << endl << "\tAirbus A319 Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                        << "\t-------------------------------" << endl <<
                        "\n\tOperation Costs: " << airport->ShowFinancesPlanes("Airbus A319") << endl <<
                        endl << "\tPress any key to return to main menu.";
                        clear_Console();
                        break;
                    case 'B':
                        //system("CLS");
                        cout << endl << "\tAirbus A320 Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                        << "\t-------------------------------" << endl <<
                        "\n\tOperation Costs: " << airport->ShowFinancesPlanes("Airbus A320") << endl <<
                        endl << "\tPress any key to return to main menu.";
                        clear_Console();
                        break;
                    case 'C':
                        //system("CLS");
                        cout << endl << "\tAirbus A330 Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                        << "\t-------------------------------" << endl <<
                        "\n\tOperation Costs: " << airport->ShowFinancesPlanes("Airbus A330") << endl <<
                        endl << "\tPress any key to return to main menu.";
                        clear_Console();
                        break;
                    case 'D':
                        //system("CLS");
                        cout << endl << "\tBoeing 737 Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                        << "\t-------------------------------" << endl <<
                        "\n\tOperation Costs: " << airport->ShowFinancesPlanes("Boeing 737") << endl <<
                        endl << "\tPress any key to return to main menu.";
                        clear_Console();
                        break;
                    case 'E':
                        //system("CLS");
                        cout << endl << "\tAll Planes Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                        << "\t-------------------------------" << endl <<
                        "\n\tOperation Costs: " << airport->ShowFinancesPlanes("total") << endl <<
                        endl << "\tPress any key to return to main menu.";
                        clear_Console();
                        break;
                }
                break;
            case 'C':
                //system("CLS");
                total_expenses_value = airport->AirportExpensesValue();
                cout << endl << "\tAirport Finances -- " << airport->getLocation()->getCity() << " , " << airport->getLocation()->getCountry() << endl
                << "\t-------------------------------" << endl <<
                "\n\tTotal Expenses Costs: " << total_expenses_value << endl <<
                endl << "\tPress any key to return to main menu.";
                clear_Console();
                break;
            case 'X':
                system("CLS");
                return 0;
            default:
                system("CLS");
                break;
        }
    }
}

/// \brief Shows Finances Menu
/// \param company - Object from class Company
/// \return 0 upon success, 1 upon failure
int showFinancesMenu(Company &company)
{
    char opt;

    cout << endl << "\t  ___ ___ _  _   _   _  _  ___ ___ ___ \n"
                    "\t | __|_ _| \\| | /_\\ | \\| |/ __| __/ __|\n"
                    "\t | _| | || .` |/ _ \\| .` | (__| _|\\__ \\\n"
                    "\t |_| |___|_|\\_/_/ \\_\\_|\\_|\\___|___|___/"<< endl
         << "\t--------------------------------------------------------------------" << endl
         << endl
         << "\t(A) Company " << endl
         << "\t(B) Airport" << endl
         << "\t(X) Exit" << endl
         << endl
         << "\t-------------------------------" << endl
         << "\tChoose an action (letter): ";
    cin >> opt;
    cin.ignore(1000,'\n');

    switch (opt)
    {
        case 'A':
            system("CLS");
            company.showFinances();
            break;
        case 'B':
            system("CLS");
            showAirportFinances(company);
            break;
        case 'X':
            system("CLS");
            return 0;
        default:
            system("CLS");
            break;
    }
    return 0;
}

/// \brief Read Airports' and Flights' Files from "data" directory
/// \param company - Object from class Company
void readFiles(Company &company){

    CreateDirectory("data", NULL);

    string airports_dir = "data\\airports";
    ifstream airports(airports_dir);

    if (!airports.good() || airports.peek() == ifstream::traits_type::eof() || airports.peek() == '\0')
    {
        airports.close();
        std::ofstream output(airports_dir,ios::out);
        output.close();
    }
    else {
        try{
            string line;
            while (getline(airports, line)){
                stringstream ss(line);
                Administration *manager = new Administration();
                Location *location = new Location();
                Date birth = Date();
                string res;
                getline(ss,res,';');
                manager->setName(res);

                getline(ss,res,';');
                birth.setYear(stoi(res));
                getline(ss,res,';');
                birth.setMonth(stoi(res));
                getline(ss,res,';');
                birth.setDay(stoi(res));
                manager->setBirthday(birth);

                getline(ss,res,';');
                manager->setSalary(stof(res));
                getline(ss,res,';'); // Category
                getline(ss,res,';');
                manager->setDepartment(res);

                getline(ss,res,';');
                location->setCountry(res);
                getline(ss,res,';');
                location->setCity(res);
                getline(ss,res,';');
                location->setGps(res);

                manager->setId(manager->getName().at(0) + to_string(manager->getBirthday().getDay()) + manager->getCategory().at(0) + to_string(manager->getSalary()).at(0));

                Airport *airport = new Airport();
                airport->setManager(manager);
                airport->setLocation(location);
                airport->vectorAddPerson(manager);
                company.airports.push_back(airport);

                string dir = "data\\" + airport->getLocation()->getCity() + "_" + airport->getLocation()->getCountry();
                string people_dir = dir + "\\people";
                ifstream people(people_dir);
                string line2;
                while(getline(people, line2)){
                    stringstream ss(line2);
                    Person *p = new Person();
                    Date birth2;
                    getline(ss,res,';');
                    p->setName(res);
                    getline(ss,res,';');
                    birth2.setYear(stoi(res));
                    getline(ss,res,';');
                    birth2.setMonth(stoi(res));
                    getline(ss,res,';');
                    birth2.setDay(stoi(res));
                    p->setBirthday(birth2);

                    getline(ss,res,';');
                    p->setSalary(stof(res));
                    getline(ss,res,';'); // Category
                    if(res == "Admin"){
                        getline(ss,res,';');
                        p = new Administration(p->getName(),p->getBirthday(),p->getSalary(),res);
                    }
                    else if(res == "Employee"){
                        getline(ss,res,';');
                        p = new Employee(p->getName(),p->getBirthday(),p->getSalary(),res);
                    }
                    else if(res == "Crew"){
                        string Total_Hours, Total_Flights;
                        getline(ss,Total_Hours,';');
                        getline(ss,Total_Flights,';');
                        p = new Crew_Member(p->getName(),p->getBirthday(),p->getSalary(),stof(Total_Hours),stoi(Total_Flights));

                    }
                    else if(res == "Pilot"){
                        string Plane_Type,Total_Hours, Total_Flights;
                        getline(ss,Plane_Type,';');
                        getline(ss,Total_Hours,';');
                        getline(ss,Total_Flights,';');
                        p = new Plane_Pilot(p->getName(),p->getBirthday(),p->getSalary(),Plane_Type,stof(Total_Hours),stoi(Total_Flights));
                    }
                    airport->vectorAddPerson(p);
                }

                people.close();

                dir = "data\\" + airport->getLocation()->getCity() + "_" + airport->getLocation()->getCountry();
                string old_people_dir = dir + "\\old_people";
                ifstream old_people(old_people_dir);
                line2 = "";
                while(getline(old_people, line2)){
                    stringstream ss(line2);
                    Person *p = new Person();
                    Date birth2;
                    getline(ss,res,';');
                    p->setName(res);
                    getline(ss,res,';');
                    birth2.setYear(stoi(res));
                    getline(ss,res,';');
                    birth2.setMonth(stoi(res));
                    getline(ss,res,';');
                    birth2.setDay(stoi(res));
                    p->setBirthday(birth2);

                    getline(ss,res,';');
                    p->setSalary(stof(res));
                    getline(ss,res,';'); // Category
                    if(res == "Admin"){
                        getline(ss,res,';');
                        p = new Administration(p->getName(),p->getBirthday(),p->getSalary(),res);
                    }
                    else if(res == "Employee"){
                        getline(ss,res,';');
                        p = new Employee(p->getName(),p->getBirthday(),p->getSalary(),res);
                    }
                    else if(res == "Crew"){
                        string Total_Hours, Total_Flights;
                        getline(ss,Total_Hours,';');
                        getline(ss,Total_Flights,';');
                        p = new Crew_Member(p->getName(),p->getBirthday(),p->getSalary(),stof(Total_Hours),stoi(Total_Flights));

                    }
                    else if(res == "Pilot"){
                        string Plane_Type,Total_Hours, Total_Flights;
                        getline(ss,Plane_Type,';');
                        getline(ss,Total_Hours,';');
                        getline(ss,Total_Flights,';');
                        p = new Plane_Pilot(p->getName(),p->getBirthday(),p->getSalary(),Plane_Type,stof(Total_Hours),stoi(Total_Flights));
                    }
                    airport->tableAddOldPerson(p);
                }

                old_people.close();

                string planes_dir = dir + "\\planes";
                ifstream planes(planes_dir);
                string line3;
                while(getline(planes, line3)){
                    stringstream ss(line3);
                    Plane *p = new Plane();
                    getline(ss,res,';');
                    p->setType(res);
                    getline(ss,res,';');
                    p->setCapacity(stoi(res));
                    getline(ss,res,';');
                    p->setOpCosts(stof(res));
                    getline(ss,res,';');
                    p->setTotalHours(stof(res));
                    getline(ss,res,';');
                    p->setTotalTrips(stoi(res));
                    vector<string> ids;
                    while(getline(ss,res,';')){
                        ids.push_back(res);
                    }
                    vector<Person *> Pp;
                    for(const auto id : ids){
                        for(auto prson : airport->getPeople()){
                            if(prson->getId() == id){
                                Pp.push_back(prson);
                            }
                        }
                    }
                    p->setPlaneCrew(Pp);
                    airport->vectorAddPlane(p);
                }

                planes.close();

                //cout << endl << *airport;
                //cout << endl << endl << "\tA new Airport was created. Press any key to move on... ";
                //clear_Console();
            }
            airports.close();

        }catch(...){
            throw (string("\tFailed to read Airports' files... "));
        }
    }

    string flights_dir = "data\\flights";
    ifstream flights(flights_dir);

    if (!flights.good() || flights.peek() == ifstream::traits_type::eof() || flights.peek() == '\0')
    {
        flights.close();
        std::ofstream output(flights_dir,ios::out);
        output.close();
    }
    else {
        try{
            string line;
            while (getline(flights, line)){
                stringstream ss(line);
                Date expectedD = Date();
                string res;
                getline(ss,res,';');
                expectedD.setYear(stoi(res));
                getline(ss,res,';');
                expectedD.setMonth(stoi(res));
                getline(ss,res,';');
                expectedD.setDay(stoi(res));

                Hour expectedH = Hour();

                getline(ss,res,';');
                expectedH.setHour(stoi(res));
                getline(ss,res,';');
                expectedH.setMinute(stoi(res));

                getline(ss,res,';');
                float duration(stof(res));

                Location depLoc = Location();

                getline(ss,res,';');
                depLoc.setCountry(res);
                getline(ss,res,';');
                depLoc.setCity(res);
                getline(ss,res,';');
                depLoc.setGps(res);

                Location arrLoc = Location();

                getline(ss,res,';');
                arrLoc.setCountry(res);
                getline(ss,res,';');
                arrLoc.setCity(res);
                getline(ss,res,';');
                arrLoc.setGps(res);

                Flight *flight = new Flight();
                flight->setDate(expectedD);
                flight->setHour(expectedH);
                flight->setDuration(duration);

                bool foundD = false, foundA = false;
                for(auto i : company.airports){
                    if(*(i->getLocation()) == depLoc){
                        foundD = true;
                        flight->setDeparture(i->getLocation());
                    }
                    else if(*(i->getLocation()) == arrLoc){
                        foundA = true;
                        flight->setArrival(i->getLocation());
                    }
                }

                if(!foundA || !foundD) throw invalid_argument("Airport Not Found");

                getline(ss,res,';');
                flight->setState(State(stoi(res)));
                string planeId; bool found = false;
                getline(ss,planeId,';');
                for(auto airp : company.airports){
                    if(*(airp->getLocation()) == *(flight->getDeparture())){

                        for(auto p : airp->getPlanes()){

                            if(p->getId() == planeId){
                                found = true;
                                flight->setPlane(p);
                                p->addVectorFlights(flight);

                                break;
                            }
                        }

                        if(!found) throw invalid_argument("No Plane Matching");

                    }
                }

                company.flights.push_back(flight);
                //cout << endl << *flight;
                //cout << endl << endl << "\tA new Flight was created. Press any key to move on... ";
                //clear_Console();
            }
            flights.close();

        }
        catch(invalid_argument &e){
            cout << endl << "\tError: " << e.what();
            throw (string("\tFailed to read Flights' file... "));
        }
        catch(...){
            throw (string("\tFailed to read Flights' file... "));
        }
    }

    string mc_dir = "data\\mcompanies";
    ifstream mc(mc_dir);

    if (!mc.good() || mc.peek() == ifstream::traits_type::eof() || mc.peek() == '\0')
    {
        mc.close();
        std::ofstream output(mc_dir,ios::out);
        output.close();
    }
    else {
        try{
            string line;
            while (getline(mc, line)){
                string companyName;
                double avaiability;
                int MaintenancesNumber;
                stringstream ss(line);

                string res;
                getline(ss,res,';');
                companyName = res;

                getline(ss,res,';');
                avaiability = stod(res);

                getline(ss,res,';');
                MaintenancesNumber = stoi(res);

                MaintenanceCompany MCp = MaintenanceCompany(avaiability,MaintenancesNumber,companyName);
                company.MaintenanceCompanies.push(MCp);
            }
            mc.close();

        }
        catch(invalid_argument &e){
            cout << endl << "\tError: " << e.what();
            throw (string("\tFailed to read Maintenance Companies' file... "));
        }
        catch(...){
            throw (string("\tFailed to read Maintenance Companies' file... "));
        }
    }

}

/// \brief Show a Panel with all the flights in order of Schedule
/// \param company - Object from class Company
int showFlightsPanel(Company &company) {
    if(company.flights.size() == 0){
        cout << endl << "\tThere are no Flights. Press any key to return to the main menu... ";
        clear_Console();
        return 0;
    }
    
    vector<Flight *> fl = vector<Flight *>(company.flights);
    sort(fl.begin(),fl.end(),compareFlights);
    cout << endl << "\tFlights Panel:" << endl;
    cout << "\t----------------------------------------------" << endl;

    char opt;

    cout << endl << "\tSearch for Flights by:" << endl
         << "\t--------------" << endl
         << endl
         << "\t(A) Date" << endl
         << "\t(B) Location" << endl
         << "\t(C) State" << endl
         << "\t(D) Show All" << endl
         << "\t(X) Exit" << endl
         << endl
         << "\t-------------------------------" << endl
         << "\tChoose an action (letter): ";
    cin >> opt;
    cin.ignore(1000,'\n');
    cout << endl;
    switch (opt)
    {
        case 'A':{
            try{
                cout << endl << "\t#-- Beginning After:" << endl;
                int Fd,Fm,Fy;
                string info = "Day: ";
                Fd = stoi(inputInfo(info));
                info = "Month: ";
                Fm = stoi(inputInfo(info));
                info = "Year: ";
                Fy = stoi(inputInfo(info));

                Date date1 = Date(Fy,Fm,Fd);

                int h,m;
                info = "Hour: ";
                h= stoi(inputInfo(info));
                info = "Minutes: ";
                m = stoi(inputInfo(info));

                Hour hour1 = Hour(h,m);

                cout << endl << "\t#-- Ending Before:" << endl;
                info = "Day: ";
                Fd= stoi(inputInfo(info));
                info = "Month: ";
                Fm = stoi(inputInfo(info));
                info = "Year: ";
                Fy = stoi(inputInfo(info));

                Date date2 = Date(Fy,Fm,Fd);

                info = "Hour: ";
                h = stoi(inputInfo(info));
                info = "Minutes: ";
                m = stoi(inputInfo(info));

                Hour hour2 = Hour(h,m);
                cout << endl;
                for(auto f : fl){
                    bool show = false;
                    if(date1 < f->getDate() && f->getDate() < date2)
                        show = true;
                    else if(date1 == f->getDate()){
                        if(hour1 < f->getHour())
                            show = true;
                    }
                    else if(date2 == f->getDate()){
                        if(f->getHour() < hour2)
                            show = true;
                    }
                    if(show){
                        cout << "\tDate     : " << f->getDate() << " , " << f->getHour() << endl;
                        cout << "\tDeparture: " << f->getDeparture()->getCity() << " , " << f->getDeparture()->getCountry() << endl;
                        cout << "\tArrival  : " << f->getArrival()->getCity() << " , " << f->getArrival()->getCountry()<< endl;
                        cout << "\tState    : " << f->getStringState() << endl;
                        cout << "\t----------------------------------------------" << endl;
                    }
                }

            }
            catch(string &e){
                cout << endl << "\tError: " << e;
                cout << endl << "\tPress any key to return to the main menu... ";
                clear_Console();
                return 1;
            }
            catch(...){
                cout << endl << "\tPress any key to return to the main menu... ";
                clear_Console();
                return 1;
            }

            cout << endl << "\tPress any key to return to the main menu... ";
            clear_Console();
            return 1;
        }
        case 'B':{
            cout << "\tSearch for: ";
            string search;
            cin >> search;
            for(auto f : fl){
                string Loc = f->getArrival()->getCity() + "_" + f->getArrival()->getCountry() + "_";
                Loc +=  f->getDeparture()->getCity() + "_" + f->getDeparture()->getCountry();

                if(Loc.find(search) != std::string::npos){
                    cout << "\tDate     : " << f->getDate() << " , " << f->getHour() << endl;
                    cout << "\tDeparture: " << f->getDeparture()->getCity() << " , " << f->getDeparture()->getCountry() << endl;
                    cout << "\tArrival  : " << f->getArrival()->getCity() << " , " << f->getArrival()->getCountry()<< endl;
                    cout << "\tState    : " << f->getStringState() << endl;
                    cout << "\t----------------------------------------------" << endl;
                }
            }
            cout << endl << "\tPress any key to return to the main menu... ";
            clear_Console();
            return 1;
        }
        case 'C':{

            char opt;

            cout << endl << "\tState of the Flights:" << endl
                 << "\t--------------------------------------------------------------------" << endl
                 << "\t(A) Scheduled" << endl
                 << "\t(B) Done " << endl
                 << "\t(C) Canceled" << endl
                 << "\t-------------------------------" << endl
                 << "\tChoose a state (letter): ";
            cin >> opt;
            cin.ignore(1000,'\n');
            State state;
            cout << endl;
            if(opt == 'A') state = Scheduled;
            else if(opt == 'B') state = Done;
            else if (opt == 'C') state = Canceled;
            else{
                cout << endl <<"\tPress any key to return to the main menu... ";
                clear_Console();
                return 1;
            }
            for(auto f : fl){

                if(f->getState() == state){
                    cout << "\tDate     : " << f->getDate() << " , " << f->getHour() << endl;
                    cout << "\tDeparture: " << f->getDeparture()->getCity() << " , " << f->getDeparture()->getCountry() << endl;
                    cout << "\tArrival  : " << f->getArrival()->getCity() << " , " << f->getArrival()->getCountry()<< endl;
                    cout << "\tState    : " << f->getStringState() << endl;
                    cout << "\t----------------------------------------------" << endl;
                }
            }
            cout << endl << "\tPress any key to return to the main menu... ";
            clear_Console();
            return 1;
        }
        case 'D':{

            for(auto i : fl){
                cout << "\tDate     : " << i->getDate() << " , " << i->getHour() << endl;
                cout << "\tDeparture: " << i->getDeparture()->getCity() << " , " << i->getDeparture()->getCountry() << endl;
                cout << "\tArrival  : " << i->getArrival()->getCity() << " , " << i->getArrival()->getCountry()<< endl;
                cout << "\tState    : " << i->getStringState() << endl;
                cout << "\t----------------------------------------------" << endl;
            }
            cout << endl << "\tPress any key to return to the main menu... ";
            clear_Console();
            return 1;
        }
        case 'X':
            system("CLS");
            return 0;
        default:
            system("CLS");
            return 0;
    }

    return 0;
}

/// \brief Save Airports' and Flights' Files to "data" directory
/// \param company - Object from class Company
void saveFiles(Company &company){
    string airports_dir = "data\\airports";
    ofstream airports_file(airports_dir, ios::trunc);
    string res;
    ostringstream ss(res);
    for(auto i : company.airports){
        ss << i->getManager()->getName() << ";"
        << i->getManager()->getBirthday().getYear() << ";"
        << i->getManager()->getBirthday().getMonth() << ";"
        << i->getManager()->getBirthday().getDay() << ";"
        << i->getManager()->getSalary() << ";"
        << i->getManager()->getCategory() << ";"
        << i->getManager()->getDepartment() << ";"
        << i->getLocation()->getCountry() << ";"
        << i->getLocation()->getCity() << ";"
        << i->getLocation()->getGps()
        << endl;

        string base_dir = "data\\" + i->getLocation()->getCity() + "_" + i->getLocation()->getCountry();
        auto dir = base_dir.c_str();
        CreateDirectory(dir, NULL);

        string people_dir = base_dir + "\\people";
        ofstream people_file(people_dir, ios::trunc);
        vector<Person *> vPeople = i->getPeople();
        string people;
        ostringstream ssPeople(people);
        for(int index = 1 ; index < vPeople.size(); index++){

            Person *p = vPeople.at(index);
            ssPeople << p->getName() << ";"
            << p->getBirthday().getYear() << ";"
            << p->getBirthday().getMonth() << ";"
            << p->getBirthday().getDay() << ";"
            << p->getSalary() << ";"
            << p->getCategory() << ";";
            if(p->getCategory() == "Admin"){
                ssPeople <<  dynamic_cast<Administration *>(p)->getDepartment();
            }
            else if(p->getCategory() == "Employee"){
                ssPeople <<  dynamic_cast<Employee *>(p)->getSchedule();
            }
            else if(p->getCategory() == "Crew"){
                ssPeople <<  dynamic_cast<Crew_Member *>(p)->getTotalHours() << ";"
                << dynamic_cast<Crew_Member *>(p)->getTotalFlights();
            }
            else if(p->getCategory() == "Pilot"){
                ssPeople << dynamic_cast<Plane_Pilot *>(p)->getPlaneType() << ";"
                << dynamic_cast<Plane_Pilot *>(p)->getTotalHours() << ";"
                << dynamic_cast<Plane_Pilot *>(p)->getTotalFlights();
            }
            ssPeople << endl;

        }
        people = ssPeople.str();
        people = people.substr(0, people.size()-1);

        people_file << people;
        people_file.close();

        string old_people_dir = base_dir + "\\old_people";
        ofstream old_people_file(old_people_dir, ios::trunc);
        tabHPeople ToldPeople = i->getAllWorkers();
        string old_people;
        ostringstream ssOldPeople(old_people);
        for(auto p : ToldPeople){
            if(p.getState() != "Employed"){
                ssOldPeople << p.getPerson()->getName() << ";"
                                                << p.getPerson()->getBirthday().getYear() << ";"
                                                << p.getPerson()->getBirthday().getMonth() << ";"
                                                << p.getPerson()->getBirthday().getDay() << ";"
                                                << p.getPerson()->getSalary() << ";"
                                                << p.getPerson()->getCategory() << ";";
                if(p.getPerson()->getCategory() == "Admin"){
                    ssOldPeople <<  dynamic_cast<Administration *>(p.getPerson())->getDepartment();
                }
                else if(p.getPerson()->getCategory() == "Employee"){
                    ssOldPeople <<  dynamic_cast<Employee *>(p.getPerson())->getSchedule();
                }
                else if(p.getPerson()->getCategory() == "Crew"){
                    ssOldPeople <<  dynamic_cast<Crew_Member *>(p.getPerson())->getTotalHours() << ";"
                                << dynamic_cast<Crew_Member *>(p.getPerson())->getTotalFlights();
                }
                else if(p.getPerson()->getCategory() == "Pilot"){
                    ssOldPeople << dynamic_cast<Plane_Pilot *>(p.getPerson())->getPlaneType() << ";"
                                << dynamic_cast<Plane_Pilot *>(p.getPerson())->getTotalHours() << ";"
                                << dynamic_cast<Plane_Pilot *>(p.getPerson())->getTotalFlights();
                }
                ssOldPeople << endl;
            }
        }
        old_people = ssOldPeople.str();
        old_people = old_people.substr(0, old_people.size()-1);

        old_people_file << old_people;
        old_people_file.close();

        string planes_dir = base_dir + "\\planes";
        ofstream planes_file(planes_dir, ios::trunc);
        vector<Plane *> vPlanes = i->getPlanes();
        string planes;
        ostringstream ssPlanes(planes);
        for(int index = 0 ; index < vPlanes.size(); index++){

            Plane *p = vPlanes.at(index);
            ssPlanes << p->getType() << ";"
                     << p->getCapacity() << ";"
                     << p->getOpCosts() << ";"
                     << p->getTotalHours() << ";"
                     << p->getTotalTrips() << ";";
            for(int i = 0 ; i < p->getPlaneCrew().size() - 1; i++){

                ssPlanes << p->getPlaneCrew().at(i)->getId() << ";";
            }
            ssPlanes << p->getPlaneCrew().at(p->getPlaneCrew().size()-1)->getId();
            ssPlanes << endl;
        }
        planes += ssPlanes.str();
        planes = planes.substr(0, planes.size()-1);
        planes_file << planes;
        planes_file.close();

    }
    res = ss.str();
    res = res.substr(0, res.size()-1);
    airports_file << res;
    airports_file.close();

    string flights_dir = "data\\flights";
    ofstream flights_file(flights_dir, ios::trunc);
    res = "";
    ostringstream ss2(res);
    for(auto i : company.flights){
        ss2 << i->getDate().getYear() << ";"
        << i->getDate().getMonth() << ";"
        << i->getDate().getDay() << ";"
        << i->getHour().getHour() << ";"
        << i->getHour().getMinute() << ";"
        << i->getDuration() << ";"
        << i->getDeparture()->getCountry() << ";"
        << i->getDeparture()->getCity() << ";"
        << i->getDeparture()->getGps() << ";"
        << i->getArrival()->getCountry() << ";"
        << i->getArrival()->getCity() << ";"
        << i->getArrival()->getGps() << ";"
        << i->getState() << ";"
        << i->getPlane()->getId()
        << endl;
    }
    res = ss2.str();
    res = res.substr(0, res.size()-1);
    flights_file << res;
    flights_file.close();

    string mc_dir = "data\\mcompanies";
    ofstream mc_file(mc_dir, ios::trunc);
    res = "";
    ostringstream ss3(res);
    while(!company.MaintenanceCompanies.empty()){

        ss3 << company.MaintenanceCompanies.top().getCompanyName() << ";"
            << company.MaintenanceCompanies.top().getAvaiability() << ";"
            << company.MaintenanceCompanies.top().getMaintenancesNumber()
            << endl;
        company.MaintenanceCompanies.pop();

    }
    res = ss3.str();
    res = res.substr(0, res.size()-1);
    mc_file << res;
    mc_file.close();
}

/// \brief Shows initial Menu
/// \param company - Object from class Company
/// \return 0 upon success, 1 upon failure
int showMenu(Company &company){
    showBanner(company, false);

    char opt;

    cout << "\tWelcome to the Application Menu. Please select an action:" << endl
         << "\t--------------------------------------------------------------------" << endl
         << endl
         << "\t(A) CRUD Operations" << endl
         << "\t(B) Airports Management" << endl
         << "\t(C) Airports Records" << endl
         << "\t(D) Finances" << endl
         << "\t(E) Flights Panel" << endl
         << "\t(F) Maintenance Companies" << endl
         << "\t(G) Credits" << endl
         << "\t(X) Exit" << endl
         << endl
         << "\t-------------------------------" << endl
         << "\tChoose an action (letter): ";
    cin >> opt;
    cin.ignore(1000,'\n');

    switch (opt)
    {
        case 'A':
            system("CLS");
            showCRUDMenu(company);
            break;
        case 'B':
            system("CLS");
            showAPManagement(company);
            break;
        case 'C':
            system("CLS");
            showAirportsRecords(company);
            break;
        case 'D':
            system("CLS");
            showFinancesMenu(company);
            break;
        case 'E':
            system("CLS");
            showFlightsPanel(company);
            break;
        case 'F':
            system("CLS");
            showMaintenanceCompanies(company);
            break;
        case 'G':
            system("CLS");
            showBanner(company, true);
            break;
        case 'X':
            return 1;
        default:
            system("CLS");
            break;
    }
    return 0;
}
