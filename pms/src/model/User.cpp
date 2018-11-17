#include "../../include/model/User.hpp"

const std::string User::ROLE_ADMIN = "admin";
const std::string User::ROLE_CUSTOMER = "customer";

User::User(std::string role, std::string name, std::string username, std::string password) {
    this->role = role;
    this->name = name;
    this->username = username;
    this->password = password;
}


std::vector<User> User::users;

int User::login(std::string username, std::string password) {
    for (int i = 0; i < users.size(); i++)
        if (users.at(i).username == username && users.at(i).password == password) return i;
    return -1;
}

bool User::is_username_exist(std::string username) {
    for (auto user : users)
        if (user.username == username) return true;
    return false;
}

void User::load() {
    std::string line;
    std::ifstream fin("users.csv");
    
    getline(fin, line);
    while (getline(fin, line)) {
        std::string split;
        std::stringstream ss(line);
        
        getline(ss, split, ',');
        std::string role = split;
        
        getline(ss, split, ',');
        std::string name = split;
        
        getline(ss, split, ',');
        std::string username = split;
        
        getline(ss, split, ',');
        std::string password = split;
        
        users.push_back(User(role, name, username, password));
    }
}

void User::save() {
    std::ofstream fout("users.csv");
    
    fout << "role,name,username,password\n";
    
    for (auto user : users) {
        fout <<
        user.role << ',' <<
        user.name << ',' <<
        user.username << ',' <<
        user.password << '\n';
    }
}
