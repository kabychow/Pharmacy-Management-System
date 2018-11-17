#ifndef Order_hpp
#define Order_hpp

#include <sstream>
#include <iomanip>
#include <vector>
#include "../helper/Date.hpp"
#include "OrderItem.hpp"

struct Order {
    int user_index;
    std::vector<OrderItem> items;
    Date date;
    Order(int user_index, Date date);
    double getTotal();
    std::string generate_table();
    
    static std::vector<Order> orders;
    static std::vector<Order> getUserOrders(int user_index);
    static void load();
    static void save();
};

#endif
