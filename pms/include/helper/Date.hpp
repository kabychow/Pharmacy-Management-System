#ifndef Date_hpp
#define Date_hpp

#include <string>
#include <sstream>
#include <chrono>

class Date {
private:
    static const int MIN_YEAR;
    static const int MAX_YEAR;
    int day, month, year;
    bool isValid();
public:
    Date();
    Date(std::string str);
    static Date now();
    int to_value();
    std::string to_string();
};

#endif
