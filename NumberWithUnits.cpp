//
// Created by amit on 08/04/2021.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <list>
#include <vector>

using namespace std;

#include "NumberWithUnits.hpp"
std::unordered_map<std::string, std::unordered_map<std::string, double>> ariel::NumberWithUnits::types_and_conversions = std::unordered_map<std::string, std::unordered_map<std::string, double>>();
void ariel::NumberWithUnits::read_units(ifstream &units_file) {
    types_and_conversions = std::unordered_map<std::string, std::unordered_map<std::string, double>>();
    string str;
    if (units_file.is_open()) {
        while (std::getline(units_file, str)) {
            str.erase(str.begin() + (long)str.find_first_of('='));
            double left_value = 0;
            double right_value = 0;
            string left_type;
            string right_type;
            istringstream stream(str);
            stream >> left_value >> left_type >> right_value >> right_type;
//            cout<< left_type<<"->"<<right_type<<endl;
//            for (int i = 0; i < left_type.length(); i++) {
//                left_type.at((unsigned long)i) = std::tolower(left_type.at((unsigned long)i));
//            }
//            for (int i = 0; i < right_type.length(); i++) {
//                right_type.at((unsigned long)i) = std::tolower(right_type.at((unsigned long)i));
//            }
            update_units_map(left_value, left_type, right_value, right_type);

        }
    }

    units_file.close();
}
void ariel::NumberWithUnits::update_units_map(const double &left_value, const string &left_type, const double &right_value,const string &right_type) {
    double into_left = right_value / left_value;
    double into_right = left_value / right_value;
    ariel::NumberWithUnits::types_and_conversions[left_type][right_type] = into_left;
    ariel::NumberWithUnits::types_and_conversions[right_type][left_type] = into_right;
    for (const auto &item : types_and_conversions[left_type]) {
        if (item.first != right_type&&item.first != left_type) {
            ariel::NumberWithUnits::types_and_conversions[item.first][right_type] = into_left / item.second;
            ariel::NumberWithUnits::types_and_conversions[right_type][item.first] = item.second / into_left;
        }
    }
    for (const auto &item : types_and_conversions[right_type]) {
        if (item.first != right_type&&item.first != left_type) {
            ariel::NumberWithUnits::types_and_conversions[item.first][left_type] = into_right/item.second;
            ariel::NumberWithUnits::types_and_conversions[left_type][item.first] =  item.second/into_right;
        }
    }
//    cout<< left_type<<"->"<<right_type<<types_and_conversions[left_type][right_type]<<endl;
//    cout<< right_type<<"->"<<left_type<<types_and_conversions[right_type][left_type]<<endl;
}

ariel::NumberWithUnits::NumberWithUnits(double value, const std::string& type) {
    type_validation(type,type);
    this->unit_value= value;
    this->unit_type=type;
}

std::istream &ariel::operator>>(istream &is, ariel::NumberWithUnits &unit) {
    is >> unit.unit_value;
    is >> unit.unit_type;
    while(isalpha(unit.unit_type.at(0))==0){is >> unit.unit_type;}
    ariel::NumberWithUnits::type_validation(unit.unit_type,unit.unit_type);
    return is;
}

std::ostream &ariel::operator<<(ostream &os, const ariel::NumberWithUnits &unit) {
    os<<unit.unit_value<<"["<<unit.unit_type<<"]";
    return os;
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator+=(const ariel::NumberWithUnits &num) {
    type_validation(this->unit_type,num.unit_type);
    this->unit_value += convert(num);
    return *this;
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator-=(const ariel::NumberWithUnits &num) {
    type_validation(this->unit_type,num.unit_type);
    this->unit_value -= convert(num);
    return *this;
}

ariel::NumberWithUnits ariel::NumberWithUnits::operator-(const ariel::NumberWithUnits &num) const {
    type_validation(num.unit_type,this->unit_type);
    return NumberWithUnits(
            this->unit_value - convert(num), this->unit_type);
}

ariel::NumberWithUnits ariel::NumberWithUnits::operator+(const ariel::NumberWithUnits &num) const {
    type_validation(num.unit_type,this->unit_type);
        return NumberWithUnits(
                this->unit_value + convert(num), this->unit_type);
}

void ariel::NumberWithUnits::type_validation(const string &src_t, const string &dest_t) {
    string a = "Data types don't match "+dest_t+" != "+src_t;
    if(types_and_conversions.empty()){
        throw std::invalid_argument(a);
    }
    types_and_conversions.at(src_t);
    types_and_conversions.at(dest_t);
    if(types_and_conversions[src_t][dest_t]==0&&dest_t!=src_t) {
        throw std::invalid_argument(a);
    }
}

bool ariel::NumberWithUnits::operator==(const ariel::NumberWithUnits &num) const {
    type_validation(this->unit_type,num.unit_type);
    return this->unit_value== convert(num);
}

bool ariel::NumberWithUnits::operator<=(const ariel::NumberWithUnits &num) const {
    type_validation(this->unit_type,num.unit_type);
    return this->unit_value<=convert(num);
}

bool ariel::NumberWithUnits::operator>=(const ariel::NumberWithUnits &num) const {
    type_validation(this->unit_type,num.unit_type);
    return this->unit_value>=convert(num);
}

double ariel::NumberWithUnits::convert(const ariel::NumberWithUnits &num) const {
    if (num.unit_type!=this->unit_type) {
        return num.unit_value*types_and_conversions[num.unit_type][this->unit_type];
    }
    return num.unit_value;
}

bool ariel::NumberWithUnits::operator!=(const ariel::NumberWithUnits &num) const {
    type_validation(this->unit_type,num.unit_type);
    return this->unit_value!=convert(num);
}

bool ariel::NumberWithUnits::operator<(const ariel::NumberWithUnits &num) const {
    type_validation(this->unit_type,num.unit_type);
    return this->unit_value<convert(num);
}

bool ariel::NumberWithUnits::operator>(const ariel::NumberWithUnits &num) const {
    type_validation(this->unit_type,num.unit_type);
    return this->unit_value>convert(num);
}


ariel::NumberWithUnits & ariel::NumberWithUnits::operator--(){
    this->unit_value--;
    return *this;
}
ariel::NumberWithUnits ariel::NumberWithUnits::operator--(int){
    NumberWithUnits copy {this->unit_value,this->unit_type};
    --this->unit_value;
    return copy;
}
ariel::NumberWithUnits & ariel::NumberWithUnits::operator++(){
    this->unit_value++;
    return *this;
}
ariel::NumberWithUnits ariel::NumberWithUnits::operator++(int){
    NumberWithUnits copy {this->unit_value,this->unit_type};
    ++this->unit_value;
    return copy;
}