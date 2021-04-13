//
// Created by amit on 08/04/2021.
//
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
namespace ariel {
    std::unordered_map<std::string, std::unordered_map<std::string, double>> NumberWithUnits::types_and_conversions = std::unordered_map<std::string, std::unordered_map<std::string, double>>();


    void NumberWithUnits::read_units(ifstream &units_file) {
        string str;
        if (units_file.is_open()) {
            while (getline(units_file, str)) {
                str.erase(str.begin() + (long)str.find_first_of('='));
                double left_value = 0;
                double right_value = 0;
                string left_type;
                string right_type;
                istringstream stream(str);
                stream >> left_value >> left_type >> right_value >> right_type;
                for (int i = 0; i < left_type.length(); i++) {
                    left_type.at((unsigned long)i) = std::tolower(left_type.at((unsigned long)i));
                }
                for (int i = 0; i < right_type.length(); i++) {
                    right_type.at((unsigned long)i) = std::tolower(right_type.at((unsigned long)i));
                }
                update_units_map(left_value, left_type, right_value, right_type);
            }
        }
        for (const auto &item : types_and_conversions) {
            cout<< item.first<<'[';
            for (const auto &kv : item.second) {
                cout << '('<<kv.first<<','<<kv.second << ')';
            }
            cout<<']'<<endl;
        }
        units_file.close();
    }

    void NumberWithUnits::update_units_map(const double &left_value, const string &left_type, const double &right_value,
                                           const string &right_type) {
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
    }
};