#ifndef OrderItem_hpp
#define OrderItem_hpp

#include "Medicine.hpp"

struct OrderItem {
    std::string medicine_name;
    double medicine_price;
    int quantity;
    OrderItem(std::string medicine_name, double medicine_price, int quantity);
    double getSubtotal();
};

#endif
