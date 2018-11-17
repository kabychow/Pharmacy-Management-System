#include "../../include/model/Order.hpp"

std::vector<Order> Order::orders;

std::vector<Order> Order::getUserOrders(int user_index) {
    std::vector<Order> user_orders;
    for (auto order : orders) {
        if (order.user_index == user_index) {
            user_orders.push_back(order);
        }
    }
    return user_orders;
}

Order::Order(int user_index, Date date) : date(date) {
    this->user_index = user_index;
}

double Order::getTotal() {
    double total = 0;
    for (auto item : items) {
        total += item.getSubtotal();
    }
    return total;
}

std::string Order::generate_table() {
    std::stringstream buffer;
    buffer << std::endl << std::endl <<
    " " << date.to_string() << std:: endl <<
    "--------------------------------------------------------------------" << std::endl <<
    std::setw(30) << std::left << "| Medicine Name" <<
    std::setw(15) << std::left << "| Quantity" <<
    std::setw(22) << std::left << "| Subtotal (RM)" << "|" << std::endl <<
    "--------------------------------------------------------------------" << std::endl;
    for (auto item : items) {
        buffer <<
        "| " << std::setw(28) << std::left << item.medicine_name <<
        "| " << std::setw(13) << std::left << item.quantity <<
        "| " << std::setw(20) << std::left << std::fixed << std::setprecision(2) << item.getSubtotal() << "|" << std::endl;
    }
    buffer <<
    "--------------------------------------------------------------------" << std::endl <<
    std::setw(30) << std::left << "" <<
    std::setw(15) << std::left << "" <<
    "| " << std::setw(20) << std::left << std::fixed << std::setprecision(2) << getTotal() << "|" << std::endl;
    
    buffer <<
    "                                             -----------------------" << std::endl;
    return buffer.str();
}


void Order::load() {
    std::string line;
    std::ifstream fin("orders.csv");
    
    getline(fin, line);
    while (getline(fin, line)) {
        std::string split;
        std::stringstream ss(line);
        
        getline(ss, split, ',');
        int user_index = std::stoi(split);
        
        getline(ss, split, ',');
        Date date = Date(split);
        
        orders.push_back(Order(user_index, date));
    }
    
    std::string item_line;
    std::ifstream item_fin("orders_items.csv");
    
    getline(item_fin, item_line);
    while (getline(item_fin, item_line)) {
        std::string split;
        std::stringstream ss(item_line);
        
        getline(ss, split, ',');
        int order_index = std::stoi(split);
        
        getline(ss, split, ',');
        std::string medicine_name = split;
        
        getline(ss, split, ',');
        double medicine_price = std::stod(split);
        
        getline(ss, split, ',');
        int quantity = std::stoi(split);
        
        orders.at(order_index).items.push_back(OrderItem(medicine_name, medicine_price, quantity));
    }
}

void Order::save() {
    std::ofstream fout("orders.csv");
    std::ofstream item_fout("orders_items.csv");
    
    fout << "user_index,date\n";
    item_fout << "order_index,medicine_name,medicine_price,quantity\n";
    
    for (int i = 0; i < orders.size(); i++) {
        fout <<
        orders.at(i).user_index << ',' <<
        orders.at(i).date.to_string() << '\n';
        
        for (auto item : orders.at(i).items) {
            item_fout <<
            i << ',' <<
            item.medicine_name << ',' <<
            item.medicine_price << ',' <<
            item.quantity << '\n';
        }
    }
}
