#include "airport.h"
#include "company.h"
#include <algorithm>

/// \brief Function that adds a Person to the vector people of an object of the class Airport
void Airport::addPerson(){
    char opt;

    cout << endl << "\tAirport Management -- " << this->getLocation()->getCity() << " , " << this->getLocation()->getCountry() << endl
         << "\t--------------------------------------------------------------------" << endl
         << endl
         << "\t(A) Administrator" << endl
         << "\t(B) Employee" << endl
         << "\t(C) Crew Member" << endl
         << "\t(D) Pilot" << endl
         << endl
         << "\t-------------------------------" << endl
         << endl
         << "\tChoose a Person Type (letter): ";
    cin >> opt;
    cin.ignore(1000,'\n');

    if(opt != 'A' && opt != 'B' && opt != 'C' && opt != 'D'){
        cout << endl << endl << "\tCould not add a new Person. Press any key to return to the previous Menu... ";
        clear_Console();
        return;
    }

    system("CLS");

    Person *new_person;
    string info, Pname, Pcategory;
    float Psalary;
    int d,m,y;
    Date birth;

    try{
        cout << endl << "\tAdding a new Person to the Airport:" << endl << endl;

        info = "Name: ";
        Pname = inputInfo(info);

        info = "Salary (float): ";
        Psalary = stof(inputInfo(info));

        cout << endl << "\tBirthday:" << endl;

        info = "Day: ";
        d= stoi(inputInfo(info));
        info = "Month: ";
        m = stoi(inputInfo(info));
        info = "Year: ";
        y = stoi(inputInfo(info));

        birth = Date(y,m,d);

    }catch(...){
        cout << "\tCould not add the Person... Press any Key to return to the previous Menu...";
        clear_Console();
        return;
    }

    cout << endl;

    if(opt == 'A'){
        info = "Department: ";
        string department = inputInfo(info);
        new_person = new Administration(Pname,birth,Psalary,department);
        cout << endl << endl << "\tA new Administrator was created. Press any key to return to the previous Menu... ";
    }
    else if(opt == 'B'){
        info = "Schedule: ";
        string schedule = inputInfo(info);
        new_person = new Employee(Pname,birth,Psalary,schedule);
        cout << endl << endl << "\tA new Employee was created. Press any key to return to the previous Menu... ";
    }
    else if(opt == 'C'){
        new_person = new Crew_Member(Pname,birth,Psalary);
        cout << endl << endl << "\tA new Crew Member was created. Press any key to return to the previous Menu... ";
    }
    else if(opt == 'D'){
        try{
            int type;

            cout << "\tPlane Type: " << endl
                 << "\t-------------------------------" << endl
                 << "\t(0) Airbus A319" << endl
                 << "\t(1) Airbus A320" << endl
                 << "\t(2) Airbus A330" << endl
                 << "\t(3) Boeing 737" << endl
                 << "\t-------------------------------" << endl
                 << "\tChoose a Plane Type (number): ";
            cin >> type;
            cin.ignore(1000,'\n');

            if(type < 0 || type > 3) throw invalid_argument("Invalid Type.");

            new_person = new Plane_Pilot(Pname,birth,Psalary,PlaneTypes[type]);
            cout << endl << endl << "\tA new Pilot was created. Press any key to return to the previous Menu... ";

        }
        catch (invalid_argument &e){
            cout << "\tError: " << e.what() << endl;
            cout << "\tCould not add the Person... Press any Key to return to the previous Menu...";
            clear_Console();
            return;
        }
        catch(...){
            cout << "\tCould not add the Person... Press any Key to return to the previous Menu...";
            clear_Console();
            return;
        }
    }
    this->people.push_back(new_person);
    this->allWorkers.insert(PersonRecord("Employed",new_person));
    clear_Console();
}

/// \brief Function that shows on console the information of each member of People vector from an object of the class Airport
void Airport::removePerson() {
    if(this->people.size() <= 1){
        cout << endl << "\tThere are no People... Press any Key to continue... ";
        clear_Console();
        return;
    }
    cout << endl << "\tShowing all the People:" << endl << endl;
    for(int i = 1 ; i < people.size(); i++){
        cout << "\t" << i << ") ------------" << endl
             << "\tName     : " << people[i]->getName() << endl
             << "\tCategory : " << people[i]->getCategory()<< endl << endl;
    }
    cout << endl;
    string info = "Choose a Person(Number) to remove: ";
    string res = inputInfo(info);

    try{
        if(stoi(res) >= 1 && stoi(res) < this->people.size()){
            if(this->people.at(stoi(res))->getCategory() == "Pilot" || this->people.at(stoi(res))->getCategory() == "Crew"){
                for(auto i : this->planes){
                    vector<Person *> pp = i->getPlaneCrew();
                    if(find(pp.begin(),pp.end(),this->people.at(stoi(res))) != pp.end()){
                        throw InvalidRemoval("\tThere are planes associated with this person. First remove this person from the plane.");
                    }
                }
            }
            auto itr = allWorkers.begin();
            while(itr != allWorkers.end()){
                if(itr->getPerson()->getId() == people.at(stoi(res))->getId()){
                    break;
                }
                itr++;
            }
            this->allWorkers.erase(itr);
            this->allWorkers.insert(PersonRecord("Unemployed",this->people.at(stoi(res))));
            this->people.erase(this->people.begin() + stoi(res));
            cout << endl << "\tPerson Removed... Press any Key to return to the previous Menu... ";
            clear_Console();
        }
        else{
            throw invalid_argument("Invalid Number");
        }
    }
    catch (invalid_argument &e){
        cout << endl  << "\tError: " << e.what();
        cout << endl << "\tCould not remove the Person... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch(InvalidRemoval &invalidRemoval){
        cout << endl << invalidRemoval.getMessage();
        cout << endl << "\tCould not remove the Person... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch (...){
        cout << endl << "\tCould not remove the Person... Press any Key to return to the previous Menu...";
        clear_Console();
    }

}

/// \brief Function that removes a chosen Person of the vector People from an object of the class Airport
void Airport::updatePerson() {
    if(this->people.size() <= 1){
        cout << endl << "\tThere are no People... Press any Key to continue... ";
        clear_Console();
        return;
    }
    cout << endl << "\tShowing all the People:" << endl << endl;
    for(int i = 1 ; i < people.size(); i++){
        cout << "\t" << i << ") ------------" << endl
             << "\tName     : " << people[i]->getName() << endl
             << "\tCategory : " << people[i]->getCategory() << endl << endl;
    }
    cout << endl;
    string info = "Choose a Person(Number) to update: ";
    string res = inputInfo(info);
    system("CLS");
    try{
        if(stoi(res) >= 1 && stoi(res) < this->people.size()){
            Person * person = people[stoi(res)];

            string Pname, Pcategory;
            float Psalary;
            int d,m,y;
            Date birth;

            cout << endl << "\tUpdating the Person:" << endl << endl;

            info = "Name: ";
            Pname = inputInfo(info);

            info = "Salary (float): ";
            Psalary = stof(inputInfo(info));

            cout << endl << "\tBirthday:" << endl;

            info = "Day: ";
            d= stoi(inputInfo(info));
            info = "Month: ";
            m = stoi(inputInfo(info));
            info = "Year: ";
            y = stoi(inputInfo(info));

            birth = Date(y,m,d);

            cout << endl;

            if(person->getCategory() == "Admin"){
                info = "Department: ";
                string department = inputInfo(info);
                person = new Administration(Pname,birth,Psalary,department);
                }
            else if(person->getCategory() == "Employee"){
                info = "Schedule: ";
                string schedule = inputInfo(info);
                person = new Employee(Pname,birth,Psalary,schedule);
                }
            else if(person->getCategory() == "Crew"){
                info = "Total Hours: ";
                float hours = stof(inputInfo(info));
                info = "Total Flights: ";
                int flights = stoi(inputInfo(info));
                person = new Crew_Member(Pname,birth,Psalary,hours,flights);
                }
            else if(person->getCategory() == "Pilot"){
                int type;

                cout << "\tPlane Type: " << endl
                     << "\t-------------------------------" << endl
                     << "\t(0) Airbus A319" << endl
                     << "\t(1) Airbus A320" << endl
                     << "\t(2) Airbus A330" << endl
                     << "\t(3) Boeing 737" << endl
                     << "\t-------------------------------" << endl
                     << endl
                     << "\tChoose a Plane Type (number): ";
                cin >> type;
                cin.ignore(1000,'\n');

                if(type < 0 || type > 3) throw invalid_argument("Invalid Type.");

                info = "Total Hours: ";
                float hours = stof(inputInfo(info));
                info = "Total Flights: ";
                int flights = stoi(inputInfo(info));
                person = new Plane_Pilot(Pname,birth,Psalary,PlaneTypes[type],hours,flights);
                }
            auto itr = allWorkers.begin();
            while(itr != allWorkers.end()){
                if(itr->getPerson()->getId() == people.at(stoi(res))->getId()){
                    break;
                }
                itr++;
            }
            this->allWorkers.erase(itr);
            this->allWorkers.insert(PersonRecord("Employed",person));
            people.at(stoi(res)) = person;
            cout << endl << "\tPerson Updated... Press any Key to return to the previous Menu... ";
            clear_Console();
        }
        else{
            throw invalid_argument("Invalid Number");
        }
    }
    catch (invalid_argument &e){
        cout << "\tError: " << e.what();
        cout << endl << "\tCould not update the Person... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch (...){
        cout << endl << "\tCould not update the Person... Press any Key to return to the previous Menu...";
        clear_Console();
    }
}

/// \brief Function that compares two people by his name
/// \param a - first person to be compared
/// \param b - second person to be compared
/// \return true if a is alphabetically first compared to b, false otherwise
bool comparePerson(const Person* a, const Person *b){
    return a->getName() < b->getName();
}

/// \brief Function that updates person information from an object of the vector People from the class Airport
void Airport::getAllPeople() {

    if(this->people.size() == 0){
        cout << endl << "\tThere are no People... Press any Key to continue... ";
        clear_Console();
        return;
    }
    cout << endl << "\tShowing all the People..." << endl
         << "\t---------------------------" << endl << endl;

    vector<Person *> vPeople = vector<Person *>(this->people);
    sort(vPeople.begin(),vPeople.end(),comparePerson);
    for(auto i : vPeople){
        i->printInfo(cout);
    }

    cout << endl << "\tPress any key to continue...  ";
    clear_Console();
}

/// \brief Function that adds plane to the vector planes of an object of the class Airport
void Airport::addPlane() {
    int capacity = 0;
    Plane *new_plane;
    Person *pilot1, *pilot2, *crew_member1, *crew_member2;
    string info;

    try{

        cout << "\tPlane Type: " << endl
             << "\t-------------------------------" << endl
             << endl
             << "\t(0) Airbus A319" << endl
             << "\t(1) Airbus A320" << endl
             << "\t(2) Airbus A330" << endl
             << "\t(3) Boeing 737" << endl
             << endl
             << "\t-------------------------------" << endl
             << endl
             << "\tChoose a Plane Type (letter): ";
        int type;
        cin >> type;
        cin.ignore(1000,'\n');

        if(type < 0 || type > 3){
            throw invalid_argument("Invalid type");
        }
        vector<Person *> pilots;
        vector<Person *>crew_members;
        for(auto i : people){
            if(i->getCategory()== "Pilot" && dynamic_cast<Plane_Pilot*>(i)->getPlaneType() == PlaneTypes[type]){
                pilots.push_back(i);
            }
            if(i->getCategory() == "Crew"){
                crew_members.push_back(i);
            }
        }

        if(crew_members.size() < 2 || pilots.size()< 2){
            cout << endl << "\tNot enough Pilots or Crew Members to add a Plane (At least two for each needed)." << endl;
            throw invalid_argument("Insufficient Pilots or Crew Members");
        }

        info = "Capacity: ";
        capacity = stoi(inputInfo(info));

        system("CLS");
        cout << endl << "\tAdding a new plane requires setting two Pilots and two Crew Members." << endl;
        cout << "\tProceeding to add a Plane..." << endl << endl;
        cout << "\t#--Pilot 1:" << endl;
        cout << endl << "\tShowing all pilots:" << endl << endl;
        int index = 0;

        for(auto i : pilots){
            cout << "\t" << index << ") " << i->getName() << endl << endl << "\t----------" << endl;
            cout << endl;
            index += 1;
        }
        cout << endl;
        info = "Choose a Pilot (Number): ";
        int res = stoi(inputInfo(info));
        pilot1 = pilots.at(res);
        pilots.erase(pilots.begin()+res);

        system("CLS");
        cout << "\tProceeding to add a Plane..." << endl << endl;

        cout << "\t#--Pilot 2:" << endl;
        cout << endl << "\tShowing all pilots:" << endl << endl;

        index = 0;
        for(auto i : pilots){
            cout << "\t" << index << ") " << i->getName() << endl << endl << "\t----------" << endl;
            cout << endl;
            index += 1;
        }
        cout << endl;
        info = "Choose a Pilot (Number): ";
        res = stoi(inputInfo(info));
        pilot2 = pilots.at(res);

        system("CLS");
        cout << "\tProceeding to add a Plane..." << endl << endl;
        cout << "\t#--Crew Member 1:" << endl;
        cout << endl << "\tShowing all Crew Members:" << endl << endl;

        index = 0;
        for(auto i : crew_members) {
            cout << "\t" << index << ") " << i->getName() << endl << endl << "\t----------" << endl;
            cout << endl;
            index+=1;
        }
        cout << endl;
        info = "Choose a Crew Member (Number): ";
        res = stoi(inputInfo(info));
        crew_member1 = crew_members.at(res);
        crew_members.erase(crew_members.begin() + res);

        system("CLS");
        cout << "\tProceeding to add a Plane..." << endl << endl;

        cout << "\t#--Crew Member 2: " << endl;
        cout << endl << "\tShowing all Crew Members:" << endl << endl;
        index = 0;
        for(auto i : crew_members){
            cout << "\t" << index << ") " << i->getName() << endl << endl << "\t----------" << endl;
            cout << endl;
            index += 1;
        }
        cout << endl;
        info = "Choose a Crew Member (Number): ";
        res = stoi(inputInfo(info));
        crew_member2 = crew_members.at(res);

        new_plane = new Plane(PlaneTypes[type], capacity, {pilot1, pilot2, crew_member1, crew_member2}, PlaneCostsPerType[type]);
        this->planes.push_back(new_plane);

        cout << endl << endl << "\tA new Plane was added. Press any key to return to the previous Menu... ";

        clear_Console();
    }
    catch (invalid_argument &e){
        cout << "\tError: " << e.what();
        cout << endl << "\tCould not add the Plane... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch(...){
        cout << endl << "\tCould not add the Plane... Press any Key to return to the previous Menu...";
        clear_Console();
    }
}

/// \brief Function that removes a chosen plane of the vector planes from an object of the class Airport
void Airport::removePlane() {
    if(this->planes.size() == 0){
        cout << endl << "\tThere are no Planes... Press any Key to continue... ";
        clear_Console();
        return;
    }
    cout << endl << "\tShowing all the Planes:" << endl << endl;
    for(int i = 0; i < planes.size(); i++){
        cout << "\t" << i << ") ------------" << endl
        << planes[i] << endl;

    }
    cout << endl;
    string info = "Choose a Plane(Number) to remove: ";
    string res = inputInfo(info);

    try{
        if(stoi(res) >= 0 && stoi(res) < this->planes.size()){
            if(this->planes.at(stoi(res))->getFlights().size() > 0){
                throw InvalidRemoval("\tCan not remove this plane because there are flights associated. First remove the plane from the flights.");
            }

            this->planes.erase(this->planes.begin() + stoi(res));
            cout << endl << "\tPlane Removed... Press any Key to return to the previous Menu... ";
            clear_Console();
        }
        else{
            throw invalid_argument("Invalid Number");
        }
    }
    catch(invalid_argument &e){
        cout << endl << "Error: " << e.what();
        cout << endl << "\tCould not remove the Plane... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch(InvalidRemoval &invalidRemoval){
        cout << endl << invalidRemoval.getMessage();
        cout << endl << "\tCould not remove the Plane... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch(...){
        cout << endl << "\tCould not remove the Plane... Press any Key to return to the previous Menu...";
        clear_Console();
    }
}

/// \brief Function that shows on console the information of each member of planes vector from an object of the class Airport
void Airport::getAllPlanes()
{
    if(this->planes.size() == 0){
        cout << endl << "\tThere are no Planes... Press any Key to continue... ";
        clear_Console();
        return;
    }
    cout << endl << "\tShowing all planes..." << endl
         << "\t------------------" << endl << endl;
    for(auto i : this->planes){
        cout << i << endl;
    }

    cout << endl << "\tPress any key to continue...  ";
    clear_Console();

}

/// \brief Function that updates plane information from an object of the vector planes from the class Airport
void Airport::updatePlane()
{
    if(this->planes.size() < 1){
        cout << endl << "\tThere are no Planes... Press any Key to continue... ";
        clear_Console();
        return;
    }
    cout << endl << "\tShowing all the Planes:" << endl << endl;
    for(int i = 0 ; i < planes.size(); i++){
        cout << "\t" << i << ") ------------" << endl
             << "\tType     : " << planes[i]->getType() << endl
             << "\tCapacity : " << planes[i]->getCapacity() << endl;

    }
    cout << endl;
    string info = "Choose a Plane(Number) to update: ";
    string res = inputInfo(info);
    try{
        if(stoi(res) >= 0 && stoi(res) < this->planes.size()){
            Plane * plane = planes[stoi(res)];

            char opt;
            cout << endl;
            cout << "\tField to be updated for this " << plane->getType() << endl
                 << "\t--------------------------------------------------------------------" << endl
                 << endl
                 << "\t(A) Capacity" << endl
                 << "\t(B) Crew Members" << endl
                 << endl
                 << "\t-------------------------------" << endl
                 << "\tChoose an action (letter): ";
            cin >> opt;
            cin.ignore(1000,'\n');


            switch (opt)
            {
                case 'A': {
                    int Pcapacity;

                    cout << endl << "\tUpdating the Plane:" << endl << endl;

                    info = "Capacity: ";
                    Pcapacity = stoi(inputInfo(info));
                    plane->setCapacity(Pcapacity);
                    cout << "\tPlane Updated... Press any Key to return to the previous Menu... ";
                    break;
                }
                case 'B': {
                    Person * pilot1, *pilot2, *crew_member1, *crew_member2;
                    vector<Person *> pilots;
                    vector<Person *>crew_members;
                    for(auto i : people){
                        if(i->getCategory() == "Pilot" && dynamic_cast<Plane_Pilot*>(i)->getPlaneType() == plane->getType()){
                            pilots.push_back(i);
                        }
                        if(i->getCategory() == "Crew"){
                            crew_members.push_back(i);
                        }
                    }

                    if(crew_members.size() < 2 || pilots.size()< 2){
                        cout << endl << "\tNot enough Pilots or Crew Members to update a Plane (At least two for each needed)." << endl;
                        throw invalid_argument("Insufficient Pilots or Crew Members");
                    }

                    system("CLS");
                    cout << endl << "\tUpdating a plane requires setting two Pilots and two Crew Members." << endl;
                    cout << "\tProceeding to update a Plane..." << endl << endl;
                    cout << "\t#--Pilot 1:" << endl;
                    cout << endl << "\tShowing all pilots:" << endl << endl;
                    int index = 0;

                    for(auto i : pilots){
                        cout << "\t" << index << ") " << i->getName() << endl << endl << "\t----------" << endl;
                        cout << endl;
                        index += 1;
                    }
                    cout << endl;
                    info = "Choose a Pilot(Number): ";
                    int res = stoi(inputInfo(info));
                    pilot1 = pilots.at(res);
                    pilots.erase(pilots.begin()+res);

                    system("CLS");
                    cout << "\tProceeding to add a Plane..." << endl << endl;

                    cout << "\t#--Pilot 2:" << endl;
                    cout << endl << "\tShowing all pilots:" << endl << endl;

                    index = 0;
                    for(auto i : pilots){
                        cout << "\t" << index << ") " << i->getName() << endl << endl << "\t----------" << endl;
                        cout << endl;
                        index += 1;
                    }
                    cout << endl;
                    info = "Choose a Pilot(Number): ";
                    res = stoi(inputInfo(info));
                    pilot2 = pilots.at(res);

                    system("CLS");
                    cout << "\tProceeding to add a Plane..." << endl << endl;
                    cout << "\t#--Crew Member 1:" << endl;
                    cout << endl << "\tShowing all Crew Members:" << endl << endl;

                    index = 0;
                    for(auto i : crew_members) {
                        cout << "\t" << index << ") " << i->getName() << endl << endl << "\t----------" << endl;
                        cout << endl;
                        index+=1;
                    }
                    cout << endl;
                    info = "Choose a Crew Member(Number): ";
                    res = stoi(inputInfo(info));
                    crew_member1 = crew_members.at(res);
                    crew_members.erase(crew_members.begin() + res);

                    system("CLS");
                    cout << "\tProceeding to add a Plane..." << endl << endl;

                    cout << "\t#--Crew Member 2: " << endl;
                    cout << endl << "\tShowing all Crew Members:" << endl << endl;
                    index = 0;
                    for(auto i : crew_members){
                        cout << "\t" << index << ") " << i->getName() << endl << endl << "\t----------" << endl;
                        cout << endl;
                        index += 1;
                    }
                    cout << endl;
                    info = "Choose a Crew Member(Number):";
                    res = stoi(inputInfo(info));
                    crew_member2 = crew_members.at(res);

                    plane->setPlaneCrew({pilot1,pilot2,crew_member1,crew_member2});
                    cout << "\tPlane Updated... Press any Key to return to the previous Menu... ";
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
        cout << endl << "Error: " << e.what();
        cout << endl << "\tCould not update the Plane... Press any Key to return to the previous Menu...";
        clear_Console();
    }
    catch (...){
        cout << "\tCould not update the Plane... Press any Key to return to the previous Menu...";
        clear_Console();
    }
}

Airport *AirportRecord::getAirport() const {
    return airport;
}

void AirportRecord::setAirport(Airport *airport) {
    AirportRecord::airport = airport;
}

const string &AirportRecord::getId() const {
    return id;
}

void AirportRecord::setId(const string &id) {
    AirportRecord::id = id;
}

int AirportRecord::getCount() const {
    return count;
}

void AirportRecord::setCount(int count) {
    AirportRecord::count = count;
}

double AirportRecord::getTrackHours() const {
    return track_hours;
}

void AirportRecord::setTrackHours(double trackHours) {
    track_hours = trackHours;
}

/// \brief Add track hours to the total track hours for the Airport
/// \param trackHours - to be added to the total hours
void AirportRecord::addTrackHours(double trackHours){
    track_hours += trackHours;
    count += 1;
    average_track_time = track_hours/count;
}

/// \brief Add track hours to the total track hours for the Airport
/// \param flightTime - flight time to calculate the time spent on track
/// \param unused - to differenciate from the other implementation
void AirportRecord::addTrackHours(double flightTime, int unused){
    track_hours += flightTime/10;
    count += 1;
    average_track_time = track_hours/count;
}

double AirportRecord::getAverageTrackHours() const {
    return average_track_time;
}

bool AirportRecord::operator<(const AirportRecord &rhs) const {
    if (count < rhs.count)
        return true;
    if (rhs.count < count)
        return false;
    return average_track_time < rhs.average_track_time;
}

bool AirportRecord::operator==(const AirportRecord &rhs) const {
    return (airport->getLocation()->getCountry() == rhs.airport->getLocation()->getCountry()) && (airport->getLocation()->getCity() == rhs.airport->getLocation()->getCity()) && (airport->getLocation()->getGps() == rhs.airport->getLocation()->getGps());
}

bool AirportRecord::operator!=(const AirportRecord &rhs) const {
    return !(rhs == *this);
}

/// \brief Shows Workers Records in a Hash Table
/// \return 0 upon success, 1 upon failure
int Airport::showWorkersRecord() {
    if(this->allWorkers.size() == 0){
        cout << endl << "\tThere are no People... Press any key to continue...";
        clear_Console();
        return 1;
    }

    char opt;

    cout << endl << "\tSearch for Workers Records:" << endl
         << "\t--------------" << endl
         << endl
         << "\t(A) In Order" << endl
         << "\t(B) Reverse Order" << endl
         << "\t(C) Only Unemployed" << endl
         << "\t(X) Exit" << endl
         << endl
         << "\t-------------------------------" << endl
         << "\tChoose an action (letter): ";
    cin >> opt;
    cin.ignore(1000,'\n');
    cout << endl;

    switch(opt){
        case 'A':{
            for(auto i : this->allWorkers){
                i.printInfo(cout);
            }
            cout << endl << "\tPress any key to return to the main menu... ";
            clear_Console();
            return 0;
        }
        case 'B':{
            vector<PersonRecord> workers;
            for(auto i : this->allWorkers){
                workers.push_back(i);
            }
            reverse(workers.begin(), workers.end());
            for(auto i: workers){
                i.printInfo(cout);
            }
            cout << endl << "\tPress any key to return to the main menu... ";
            clear_Console();
            return 0;
        }
        case 'C':{
            vector<PersonRecord> workers;
            for(auto i : this->allWorkers){
                if(i.getState() != "Employed")
                    workers.push_back(i);
            }
            if(workers.size() != 0){
                int count = 1;
                for(auto i: workers){
                    cout << "\t" << count << ")" << endl;
                    i.printInfo(cout);
                    count++;
                }
                try{
                    string info = "Choose a Person to Employ (index): ";
                    int res = stoi(inputInfo(info)) - 1;
                    this->vectorAddPerson(workers.at(res).getPerson());
                    auto itr = allWorkers.begin();
                    while(itr != allWorkers.end()){
                        if(itr->getPerson()->getId() == workers.at(res).getPerson()->getId()){
                            break;
                        }
                        itr++;
                    }
                    this->allWorkers.erase(itr);
                    this->allWorkers.insert(PersonRecord("Employed", workers.at(res).getPerson()));
                    cout << "\tThis Person was Employed.";

                }catch(...){
                    cout << "\tAn Error occured. Not a valid index. No one was employed.";
                }
            }
            cout << endl << "\tPress any key to return to the main menu... ";
            clear_Console();
            return 0;
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
