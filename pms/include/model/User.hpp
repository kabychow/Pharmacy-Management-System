#ifndef User_hpp
#define User_hpp

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

struct User {
    static const std::string ROLE_ADMIN, ROLE_CUSTOMER;
    std::string role, name, username, password;
    User(std::string role, std::string name, std::string username, std::string password);
    
    static std::vector<User> users;
    static int login(std::string username, std::string password);
    static bool is_username_exist(std::string username);
    static void load();
    static void save();
};

#endif
