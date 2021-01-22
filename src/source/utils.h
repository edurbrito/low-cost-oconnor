#ifndef AEDA_PROJECT_UTILS_H
#define AEDA_PROJECT_UTILS_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Date {

    int year, month, day;

public:
    Date(int year=1, int month=1, int day=1) : year(year), month(month), day(day) {
        if(!this->validDate()) throw string("Invalid Date");
    };

    int getYear() const {
        return year;
    }

    void setYear(int year) {
        Date::year = year;
    }

    int getMonth() const {
        return month;
    }

    void setMonth(int month) {
        Date::month = month;
    }

    int getDay() const {
        return day;
    }

    void setDay(int day) {
        Date::day = day;
    }

    bool validDate(){
        if( day < 1 || day > 31) return 0;
        if( month < 1 || month > 12) return 0;
        if( year < 0) return 0;

        if(month < 1 || month > 12) return 0;

        else if(month == 1 || month == 3 || month == 5 || month == 7 || month ==8 || month == 10 || month == 12){
            if(day < 1 || day > 31)
                return 0;}
        else if (month == 2) {
            if(day < 1 || day > 27)
                return 0;}
        else {
            if(day < 1 || day > 30)
                return 0;}
        if(year < 0) return 0;

        return 1;
    }

    bool operator==(const Date &rhs) const {
        if (this->day==rhs.day)
        {
            if(this->month==rhs.month)
            {
                if(this->year==rhs.year)
                    return true;
            }
        }
        return false;
    }

    bool operator<(const Date &rhs) const {
        if (year < rhs.year)
            return true;
        if (rhs.year < year)
            return false;
        if (month < rhs.month)
            return true;
        if (rhs.month < month)
            return false;
        return day < rhs.day;
    }

    friend ostream &operator<<(ostream &os, const Date &date) {
        os << date.year << " - " << date.month << " - " << date.day;
        return os;
    }

    friend ostream &operator<<(ostream &os, const Date *date) {
        os << date->year << " - " << date->month << " - " << date->day;
        return os;
    }

};

class Hour{

    int hour;
    int minute;

public:

    Hour(int hour=1, int minute=1) : hour(hour), minute(minute) {
        if(!validHour()) throw string("Invalid Hour");
    };

    int getHour() const {
        return hour;
    }

    void setHour(int hour) {
        Hour::hour = hour;
    }

    int getMinute() const {
        return minute;
    }

    void setMinute(int minute) {
        Hour::minute = minute;
    }

    bool validHour(){
        if(hour < 0 || hour >= 24) return 0;
        if(minute < 0 || minute >= 60) return 0;

        return 1;
    }

    friend ostream &operator<<(ostream &os, const Hour &hour) {
        os << hour.hour << ":" <<hour.minute;
        return os;
    }

    friend ostream &operator<<(ostream &os, const Hour *hour) {
        os << hour->hour << ":" <<hour->minute;
        return os;
    }

    bool operator==(const Hour &rhs) const
    {
        if (this->hour==rhs.hour){
            if (this->minute==rhs.minute)
                return true;
            }
        return false;
    }

    bool operator<(const Hour &rhs) const {
        if (hour < rhs.hour)
            return true;
        if (rhs.hour < hour)
            return false;
        return minute < rhs.minute;
    }

    float operator-(const Hour &rhs) const
    {
        int hourDiff = hour - rhs.hour - 1;

        // difference between minutes
        int minDiff = minute + (60 - rhs.minute);

        if (minDiff >= 60) {
            hourDiff++;
            minDiff = minDiff - 60;
        }
        return abs(float(hourDiff + minDiff/60.0));
    }

};

class Location{

    string country, city, GPS;

public:
    Location() = default;
    Location(string co, string ci, string g) : country(co) , city(ci) , GPS(g) {};

    const string &getCountry() const {
        return country;
    }

    void setCountry(const string &country) {
        Location::country = country;
    }

    const string &getCity() const {
        return city;
    }

    void setCity(const string &city) {
        Location::city = city;
    }

    const string &getGps() const {
        return GPS;
    }

    void setGps(const string &gps) {
        GPS = gps;
    }

    bool operator<(const Location &rhs) const {
        if (country < rhs.country)
            return true;
        else if (rhs.country < country)
            return false;
        return city < rhs.city;
    }

    friend ostream &operator<<(ostream &os, const Location &location) {
        os << "\tCountry  : " << location.country << endl
           << "\tCity     : " << location.city << endl
           << "\tGPS      : " << location.GPS;
        return os;
    }

    friend ostream &operator<<(ostream &os, const Location *location) {
        os << "\tCountry  : " << location->country << endl
           << "\tCity     : " << location->city << endl
           << "\tGPS      : " << location->GPS;
        return os;
    }

    bool operator!=(const Location &rhs) const {
        if (this->city==rhs.city)
        {
            if (this->country==rhs.country)
            {
                if (this->GPS==rhs.GPS)
                    return false;
            }
        }
        return  true;
    }

    bool operator==(const Location &rhs) const {
        return country == rhs.country &&
               city == rhs.city &&
               GPS == rhs.GPS;
    }

};

class InvalidRemoval{
    string message;
public:
    InvalidRemoval(string message) : message(message){};
    string getMessage(){
        return message;
    }
};

#endif //AEDA_PROJECT_UTILS_H
