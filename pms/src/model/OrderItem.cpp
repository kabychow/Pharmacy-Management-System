#include "../../include/model/OrderItem.hpp"

OrderItem::OrderItem(std::string medicine_name, double medicine_price, int quantity) {
    this->medicine_name = medicine_name;
    this->medicine_price = medicine_price;
    this->quantity = quantity;
}

double OrderItem::getSubtotal() {
    return medicine_price * quantity;
}
