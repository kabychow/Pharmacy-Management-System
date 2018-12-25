#include <iostream>

#include "include/model/User.hpp"
#include "include/model/Medicine.hpp"
#include "include/model/Order.hpp"
#include "include/model/OrderItem.hpp"

std::string get_input(bool is_empty);

void login();
void register_customer();

void edit_profile();
void change_password();

void customer_menu();
void customer_shop_medicines();
void customer_view_orders();

void admin_menu();
void admin_manage_medicines();

int user_index;

int main(int argc, const char * argv[]) {
    User::load();
    Medicine::load();
    Order::load();
    
    while (true) {
        std::cout << std::endl << std::endl <<
        "PHARMACY MANAGEMENT SYSTEM (PMS)" << std::endl <<
        "1. Login" << std::endl <<
        "2. Register" << std::endl <<
        "00. Exit" << std::endl << std::endl <<
        "Choose your option: ";
        
        std::string choice = get_input(false);
        
        if (choice == "1") login();
        else if (choice == "2") register_customer();
        else if (choice == "00") break;
    }
    
    User::save();
    Medicine::save();
    Order::save();
    
    return 0;
}



void login() {
    std::string username, password;
    
    for (int i = 0; i < 3; i++) {
        std::cout << std::endl;
        
        std::cout << "Username: ";
        username = get_input(true);
        
        std::cout << "Password: ";
        password = get_input(true);
        
        user_index = User::login(username, password);
        
        if (user_index >= 0) {
            auto user = User::users.at(user_index);
            std::cout << std::endl << "Logged in with as " << user.name << " [" << user.role << "]" << std::endl;
            if (user.role == User::ROLE_ADMIN) admin_menu();
            else if (user.role == User::ROLE_CUSTOMER) customer_menu();
            return;
        }
        
        std::cout << "Incorrect credentials." << std::endl;
    }
    
    std::cout << std::endl << "Max fail attempts exceeded. Redirecting to main menu..." << std::endl;
}



void register_customer() {
    std::cout << std::endl;
    
    std::cout << "Enter your name: ";
    std::string name = get_input(false);
    
    std::string username;
    while (true) {
        std::cout << "Pick a username: ";
        username = get_input(false);
        if (!User::is_username_exist(username)) break;
        std::cout << "Username already taken." << std::endl;
    }
    
    std::string password;
    while (true) {
        std::cout << "Enter new password: ";
        password = get_input(false);
        std::cout << "Confirm new password: ";
        std::string c_password = get_input(false);
        if (password == c_password) break;
        std::cout << "Passwords does not match." << std::endl;
    }
    
    User::users.push_back(User(User::ROLE_CUSTOMER, name, username, password));
    std::cout << std::endl << "Registered successfully." << std::endl;
}



void edit_profile() {
    std::cout << std::endl;
    
    auto &user = User::users.at(user_index);
    
    std::cout << "Enter your name [" << user.name << "]: ";
    std::string name = get_input(true);
    if (name != "") user.name = name;
    
    std::string username;
    while (true) {
        std::cout << "Pick a username [" << user.username << "]: ";
        username = get_input(true);
        if (username == "" || username == user.username) {
            break;
        } else if (!User::is_username_exist(username)) {
            user.username = username;
            break;
        }
        std::cout << "Username already taken." << std::endl;
    }
    
    std::cout << std::endl << "Profile updated successfully." << std::endl;
}



void change_password() {
    auto &user = User::users.at(user_index);
    
    std::string password;
    while (true) {
        std::cout << std::endl;
        
        std::cout << "Enter new password: ";
        password = get_input(false);
        
        std::cout << "Confirm new password: ";
        std::string c_password = get_input(false);
        if (password == c_password) break;
        std::cout << "Passwords does not match." << std::endl;
    }
    
    user.password = password;
    std::cout << std::endl << "Password changed successfully." << std::endl;
}



void admin_menu() {
    while (true) {
        std::cout << std::endl << std::endl <<
        "1. Manage medicines" << std::endl <<
        "e. Edit profile" << std::endl <<
        "p. Change password" << std::endl <<
        "0. Logout" << std::endl << std::endl <<
        "Choose your option: ";
        
        std::string choice = get_input(false);
        
        if (choice == "1") admin_manage_medicines();
        else if (choice == "e") edit_profile();
        else if (choice == "p") change_password();
        else if (choice == "0") break;
    }
}



void admin_manage_medicines() {
    std::string query = "";
    
    while (true) {
        auto indexes = Medicine::search(query, true);
        
        std::cout << std::endl << std::endl <<
        "Search query: '" << query << "' returned with total of " << indexes.size() << " result(s)" << std::endl <<
        Medicine::generate_table(indexes) << std::endl <<
        "1. Add medicine" << std::endl <<
        "2. Edit medicine" << std::endl <<
        "3. Delete medicine" << std::endl <<
        "s. Edit search query" << std::endl <<
        "0. Back" << std::endl << std::endl <<
        "Choose your option: ";
        
        std::string choice = get_input(false);
        
        if (choice == "1") {
            std::cout << std::endl;
            
            std::cout << "Enter medicine name: ";
            std::string name = get_input(false);
            
            std::cout << "Enter medicine company: ";
            std::string company = get_input(false);
            
            double price;
            while (true) {
                try {
                    std::cout << "Enter medicine price (RM): ";
                    price = std::stod(get_input(false));
                    break;
                } catch (std::exception &e) {
                    std::cout << "Please input a valid price." << std::endl;
                }
            }
            
            Date expire_at;
            while (true) {
                try {
                    std::cout << "Enter medicine expiry date (dd/mm/yyyy): ";
                    expire_at = Date(get_input(false));
                    break;
                } catch (std::exception &e) {
                    std::cout << "Please input a valid date." << std::endl;
                }
            }
            
            Date manufactured_at;
            while (true) {
                try {
                    std::cout << "Enter medicine manufactured date (dd/mm/yyyy): ";
                    manufactured_at = Date(get_input(false));
                    break;
                } catch (std::exception &e) {
                    std::cout << "Please input a valid date." << std::endl;
                }
            }
            
            Medicine::medicines.push_back(Medicine(name, company, price, expire_at, manufactured_at));
            std::cout << std::endl << "Medicine added successfully." << std::endl;
        }
        
        else if (choice == "2") {
            while (true) {
                int index;
                
                try {
                    std::cout << "Enter index to edit: ";
                    index = std::stoi(get_input(false));
                    if (index > indexes.size() || index <= 0) throw std::exception();
                } catch (std::exception &e) {
                    std::cout << "Please input a valid index." << std::endl;
                    continue;
                }
                
                Medicine &medicine = Medicine::medicines.at(indexes.at(index - 1));
                
                std::cout << "Enter medicine name [" << medicine.name << "]: ";
                std::string name = get_input(true);
                if (name != "") medicine.name = name;
                
                std::cout << "Enter medicine company [" << medicine.company << "]: ";
                std::string company = get_input(true);
                if (company != "") medicine.company = company;
                
                while (true)
                {
                    std::cout << "Enter medicine price [" << std::fixed << std::setprecision(2) << medicine.price << "]:";
                    std::string s_price = get_input(true);
                    if (s_price == "") break;
                    try {
                        double price = std::stod(s_price);
                        medicine.price = price;
                        break;
                    } catch (std::exception &e) {
                        std::cout << "Please input a valid price." << std::endl;
                    }
                }
                
                while (true)
                {
                    std::cout << "Enter medicine expiry date [" << medicine.expire_at.to_string() << "]: ";
                    std::string s_expire_at = get_input(true);
                    if (s_expire_at == "") break;
                    try {
                        Date expire_at(s_expire_at);
                        medicine.expire_at = expire_at;
                        break;
                    } catch (std::exception &e){
                        std::cout << "Please input a valid date." << std::endl;
                    }
                }
                
                while (true)
                {
                    std::cout << "Enter medicine manufactured date [" << medicine.manufactured_at.to_string() << "]: ";
                    std::string s_manufactured_at = get_input(true);
                    if (s_manufactured_at == "") break;
                    try {
                        Date manufactured_at(s_manufactured_at);
                        medicine.manufactured_at = manufactured_at;
                        break;
                    } catch (std::exception &e){
                        std::cout << "Please input a valid date." << std::endl;
                    }
                }
                
                std::cout << std::endl << "Medicine updated successfully." << std::endl;
                break;
            }
        }
        
        else if (choice == "3") {
            while (true) {
                int index;
                
                try {
                    std::cout << "Enter index to delete: ";
                    index = std::stoi(get_input(false));
                    if (index > indexes.size() || index <= 0) throw std::exception();
                } catch (std::exception &e) {
                    std::cout << "Please input a valid index." << std::endl;
                    continue;
                }
                
                Medicine::medicines.erase(Medicine::medicines.begin() + indexes.at(index - 1));
                std::cout << std::endl << "Medicine deleted successfully." << std::endl;
                break;
            }
        }
        
        else if (choice == "s") {
            std::cout << "Search query: ";
            query = get_input(true);
        }
        
        else if (choice == "0") break;
    }
}


void customer_menu()
{
    while (true)
    {
        std::cout << std::endl << std::endl <<
        "1. Shop medicines" << std::endl <<
        "2. View orders" << std::endl <<
        "e. Edit profile" << std::endl <<
        "p. Change password" << std::endl <<
        "0. Logout" << std::endl << std::endl <<
        "Choose your option: ";
        
        std::string choice = get_input(false);
        
        if (choice == "1") customer_shop_medicines();
        else if (choice == "2") customer_view_orders();
        else if (choice == "e") edit_profile();
        else if (choice == "p") change_password();
        else if (choice == "0") break;
    }
}



void customer_shop_medicines()
{
    Order order(user_index, Date::now());
    std::string query = "";
    
    while (true) {
        auto indexes = Medicine::search(query, true);
        
        std::cout << std::endl << std::endl <<
        "Search query: '" << query << "' returned with total of " << indexes.size() << " result(s)" << std::endl <<
        Medicine::generate_table(indexes) << std::endl <<
        order.generate_table() << std::endl <<
        "1. Add medicine to cart" << std::endl <<
        "2. Checkout" << std::endl <<
        "c. Clear cart" << std::endl <<
        "s. Edit search query" << std::endl <<
        "0. Back" << std::endl << std::endl <<
        "Choose your option: ";
        
        std::string choice = get_input(false);
        
        if (choice == "1") {
            while (true) {
                int index;
                
                try {
                    std::cout << "Enter index to add: ";
                    index = std::stoi(get_input(false));
                    if (index > indexes.size() || index <= 0) throw std::exception();
                } catch (std::exception &e) {
                    std::cout << "Please input a valid index." << std::endl;
                    continue;
                }
                
                int quantity;
                try {
                    std::cout << "Enter quantity: ";
                    quantity = std::stoi(get_input(false));
                } catch (std::exception &e) {
                    std::cout << "Please input a valid number." << std::endl;
                    continue;
                }
                
                auto medicine = Medicine::medicines.at(indexes.at(index - 1));
                order.items.push_back(OrderItem(medicine.name, medicine.price, quantity));
                std::cout << std::endl << "Medicine added to cart." << std::endl;
                break;
            }
        }
        
        else if (choice == "2") {
            if (order.items.size() > 0) {
                Order::orders.push_back(order);
                std::cout << std::endl << "Order placed successfully." << std::endl;
                break;
            }
        }
        
        else if (choice == "c") order.items.clear();
        
        else if (choice == "s") {
            std::cout << "Search query: ";
            query = get_input(true);
        }
        
        else if (choice == "0") break;
    }
}


void customer_view_orders() {
    for (auto order : Order::getUserOrders(user_index)) {
        std::cout << order.generate_table();
    }
}


std::string get_input(bool allow_empty)
{
    std::string input;
    
    do
    {
        getline(std::cin, input);
    }
    while ((!allow_empty && input == "") || (input.find(",") != std::string::npos));
    
    return input;
}
