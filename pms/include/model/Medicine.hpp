#ifndef Medicine_hpp
#define Medicine_hpp

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "../helper/Date.hpp"

struct Medicine {
    std::string name, company;
    double price;
    Date expire_at, manufactured_at;
    Medicine(std::string name, std::string company, double price, Date expire_at, Date manufactured_at);
    
    static std::vector<Medicine> medicines;
    static std::vector<int> search(std::string query, bool include_expired);
    static std::string generate_table(std::vector<int> indexes);
    static void load();
    static void save();
};

#endif
