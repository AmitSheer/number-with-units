//
// Created by amit on 08/04/2021.
//

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace ariel{
    class NumberWithUnits{
    private:
        static std::unordered_map<std::string,std::unordered_map<std::string,double>> types_and_conversions;
        double unit_value{};
        std::string unit_type;
        static void update_units_map(const double& left_value,const std::string& left_type,const double& right_value,const std::string& right_type);
        static void type_validation(const std::string& src_t,const std::string& dest_t);
        double convert(const NumberWithUnits& num) const;
    public:
        NumberWithUnits(double value,const std::string& type);
        double getValue() const{
            return unit_value;
        };
        std::string getType(){
            return unit_type;
        };
        static void read_units(std::ifstream& units_file);
        friend std::istream& operator>>(std::istream& is, NumberWithUnits& unit);
        friend std::ostream& operator<<(std::ostream& os,const NumberWithUnits& unit);
        NumberWithUnits& operator+=(const NumberWithUnits& num);
        NumberWithUnits& operator-=(const NumberWithUnits& num);
        //----------------------------
        //arithmetic operators that affect the object(this)
        NumberWithUnits& operator--();
        NumberWithUnits operator--(int);
        NumberWithUnits& operator++();
        NumberWithUnits operator++(int);
        NumberWithUnits operator-(const NumberWithUnits& num) const;
        NumberWithUnits operator+(const NumberWithUnits& num) const;
        friend NumberWithUnits operator*(const NumberWithUnits& num1,const double num2){
            return NumberWithUnits(num1.unit_value*num2,num1.unit_type);
        };
        friend NumberWithUnits operator*(const double num2,const NumberWithUnits& num1){
            return NumberWithUnits(num1.unit_value*num2,num1.unit_type);
        };

        NumberWithUnits operator-(){
            return NumberWithUnits(unit_value*-1,unit_type);
        };
        NumberWithUnits operator+(){
            return NumberWithUnits(std::abs(unit_value),unit_type);
        };

        bool operator==(const NumberWithUnits& num) const;
        bool operator<=(const NumberWithUnits& num) const;
        bool operator>=(NumberWithUnits const& num) const;
        bool operator!=(NumberWithUnits const& num) const;
        bool operator<(NumberWithUnits const& num) const;
        bool operator>(NumberWithUnits const& num) const;
    };
}

