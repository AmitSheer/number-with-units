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
        static std::unordered_map<std::string,std::unordered_map<std::string,int>> types_and_conversions;
        double unit_value;
        std::string unit_type;
        double convert_units(const std::string src_t,const std::string dest_t,const double& src_val);
    public:
        NumberWithUnits(double value,std::string type){};
        double getValue(){
            return unit_value;
        };
        std::string getType(){
            return unit_type;
        };
        static void read_units(std::ifstream& units_file);
        friend std::istream& operator>>(std::istream& is, NumberWithUnits& unit){
            return is;
        };
        friend std::ostream& operator<<(std::ostream& os,const NumberWithUnits& unit){
            os<<unit.unit_value<<"["<<unit.unit_type<<"]";
            return os;
        };
        NumberWithUnits& operator+=(const NumberWithUnits& num){return *this;}
        NumberWithUnits& operator-=(const NumberWithUnits& num){return *this;}
        //----------------------------
        //arithmetic operators that affect the object(this)
        NumberWithUnits& operator--(){
            unit_value--;
            return *this;
        }
        NumberWithUnits operator--(int flag){
            NumberWithUnits copy = *this;
            unit_value--;
            return copy;
        }
        NumberWithUnits& operator++(){
            unit_value++;
            return *this;
        }
        NumberWithUnits operator++(int flag){
            NumberWithUnits copy = *this;
            unit_value++;
            return copy;
        }
        friend NumberWithUnits operator-(const NumberWithUnits& num1,const NumberWithUnits& num2){
            return NumberWithUnits(1,"al");
        };
        friend NumberWithUnits operator+(const NumberWithUnits& num1,const NumberWithUnits& num2){
            return NumberWithUnits(1,"al");
        };
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

        friend bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2){
            return num1.unit_value==num2.unit_value&& num1.unit_type.compare(num2.unit_type);
        };
        friend bool operator<=(NumberWithUnits const& num1, NumberWithUnits const& num2){return false;};
        friend bool operator>=(NumberWithUnits const& num1, NumberWithUnits const& num2){return false;};
        friend bool operator!=(NumberWithUnits const& num1, NumberWithUnits const& num2){return false;};
        friend bool operator<(NumberWithUnits const& num1, NumberWithUnits const& num2){return false;};
        friend bool operator>(NumberWithUnits const& num1, NumberWithUnits const& num2){return false;};
    };
    //----------------------------
    //arithmetic operators that don't affect the object(this)


}

