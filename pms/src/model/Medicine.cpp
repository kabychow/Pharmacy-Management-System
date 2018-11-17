#include "../../include/model/Medicine.hpp"

Medicine::Medicine(std::string name, std::string company, double price, Date expire_at, Date manufactured_at) {
    this->name = name;
    this->company = company;
    this->price = price;
    this->expire_at = expire_at;
    this->manufactured_at = manufactured_at;
}


std::vector<Medicine> Medicine::medicines;

std::vector<int> Medicine::search(std::string query, bool include_expired) {
    std::vector<int> result;
    
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);
    
    for (int i = 0; i < medicines.size(); i++) {
        Medicine medicine = medicines.at(i);
        
        if (include_expired || (!include_expired && Date().to_value() < medicine.expire_at.to_value())) {
            std::string name = medicine.name;
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            std::string company = medicine.company;
            std::transform(company.begin(), company.end(), company.begin(), ::tolower);
            
            if ((name.find(query) != std::string::npos) || (company.find(query) != std::string::npos)) {
                result.push_back(i);
            }
        }
    }
    
    return result;
}

std::string Medicine::generate_table(std::vector<int> indexes) {
    std::stringstream buffer;
    buffer << std::endl <<
    "------------------------------------------------------------------------------------------------------------------------------" << std::endl <<
    std::setw(10) << std::left << "| Index" <<
    std::setw(30) << std::left << "| Name" <<
    std::setw(30) << std::left << "| Company" <<
    std::setw(17) << std::left << "| Price (RM)" <<
    std::setw(19) << std::left << "| Expiry Date" <<
    std::setw(19) << std::left << "| Manufacture Date" << "|" << std::endl <<
    "------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    for (int i = 0; i < indexes.size(); i++) {
        buffer <<
        "| " << std::setw(8) << std::left << i + 1 <<
        "| " << std::setw(28) << std::left << medicines.at(indexes.at(i)).name <<
        "| " << std::setw(28) << std::left << medicines.at(indexes.at(i)).company <<
        "| " << std::setw(15) << std::left << std::fixed << std::setprecision(2) << medicines.at(indexes.at(i)).price <<
        "| " << std::setw(17) << std::left << medicines.at(indexes.at(i)).expire_at.to_string() <<
        "| " << std::setw(17) << std::left << medicines.at(indexes.at(i)).manufactured_at.to_string() << "|" << std::endl;
    }
    buffer <<
    "------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    return buffer.str();
}

void Medicine::load() {
    std::string line;
    std::ifstream fin("medicines.csv");
    
    getline(fin, line);
    while (getline(fin, line)) {
        std::string split;
        std::stringstream ss(line);
        
        getline(ss, split, ',');
        std::string name = split;
        
        getline(ss, split, ',');
        std::string company = split;
        
        getline(ss, split, ',');
        double price = std::stod(split);
        
        getline(ss, split, ',');
        Date expire_at = Date(split);
        
        getline(ss, split, ',');
        Date manufactured_at = Date(split);
        
        medicines.push_back(Medicine(name, company, price, expire_at, manufactured_at));
    }
}

void Medicine::save()
{
    std::ofstream fout("medicines.csv");
    
    fout << "name,company,price,expire_at,manufactured_at\n";
    
    for (auto medicine : medicines) {
        fout <<
        medicine.name << ',' <<
        medicine.company << ',' <<
        medicine.price << ',' <<
        medicine.expire_at.to_string() << ',' <<
        medicine.manufactured_at.to_string() << '\n';
    }
}
