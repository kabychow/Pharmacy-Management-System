#include "../../include/helper/Date.hpp"

const int Date::MIN_YEAR = 1800;
const int Date::MAX_YEAR = 4000;

Date::Date() {
    day = 1;
    month = 1;
    year = MIN_YEAR;
}

Date::Date(std::string str)
{
    std::stringstream ss(str);
    std::string tmp;
    
    getline(ss, tmp, '/');
    day = std::stoi(tmp);
    getline(ss, tmp, '/');
    month = std::stoi(tmp);
    getline(ss, tmp, '/');
    year = std::stoi(tmp);
    
    if (!isValid()) throw std::exception();
}

Date Date::now()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);
    
    Date date;
    date.day = local_tm.tm_mday;
    date.month = local_tm.tm_mon + 1;
    date.year = local_tm.tm_year + 1900;
    
    return date;
}

int Date::to_value()
{
    return year * 10000 + month * 100 + day;
}

bool Date::isValid()
{
    if ((year >= MIN_YEAR && year <= MAX_YEAR) && (month >= 1 && month <= 12)) {
        if (month == 2) {
            if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
                return (day <= 29);
            return (day <= 28);
        }
        if (month == 4 || month == 6 || month == 9 || month == 11)
            return (day <= 30);
        return day <= 31;
    }
    return false;
}

std::string Date::to_string()
{
    std::string s_day = std::string(2 - std::to_string(day).length(), '0') + std::to_string(day);
    std::string s_month = std::string(2 - std::to_string(month).length(), '0') + std::to_string(month);
    std::string s_year = std::string(4 - std::to_string(year).length(), '0') + std::to_string(year);
    return s_day + "/" + s_month + "/" + s_year;
}
