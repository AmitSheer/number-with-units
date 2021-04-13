//
// Created by amit on 08/04/2021.
//

#include "doctest.h"
#include <string>
#include <experimental/random>
#include <unistd.h>
#include <algorithm>
using namespace std;
using namespace doctest;

#include "NumberWithUnits.hpp"
using namespace ariel;

const std::string test_file = "./units.txt";



TEST_CASE("operator +") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK((NumberWithUnits(1,"kg")+NumberWithUnits(1,"kg"))==NumberWithUnits(2,"kg"));
    CHECK((NumberWithUnits(1,"kg")+NumberWithUnits(1,"g"))==NumberWithUnits(1.001,"kg"));
    CHECK((NumberWithUnits(1,"g")+NumberWithUnits(1,"kg"))==NumberWithUnits(1001,"g"));
    CHECK((NumberWithUnits(1,"g")+NumberWithUnits(1,"ton"))==NumberWithUnits(1000001,"g"));
    CHECK((NumberWithUnits(1,"ton")+NumberWithUnits(1,"g"))==NumberWithUnits(1.000001,"ton"));
    CHECK_THROWS_MESSAGE(NumberWithUnits(1,"kg")+NumberWithUnits(1,"sec"),"Types not from the same system");
    CHECK_THROWS_MESSAGE(NumberWithUnits(1,"sec")+NumberWithUnits(1,"kg"),"Types not from the same system");
}
TEST_CASE("operator +=") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK((NumberWithUnits(1,"kg")+=NumberWithUnits(1,"kg"))==NumberWithUnits(2,"kg"));
    CHECK((NumberWithUnits(1,"kg")+=NumberWithUnits(1,"g"))==NumberWithUnits(1.001,"kg"));
    CHECK((NumberWithUnits(1,"g")+=NumberWithUnits(1,"kg"))==NumberWithUnits(1001,"g"));
    CHECK((NumberWithUnits(1,"g")+=NumberWithUnits(1,"ton"))==NumberWithUnits(1000001,"g"));
    CHECK((NumberWithUnits(1,"ton")+=NumberWithUnits(1,"g"))==NumberWithUnits(1.000001,"ton"));
    CHECK_THROWS_MESSAGE(NumberWithUnits(1,"kg")+=NumberWithUnits(1,"sec"),"Types not from the same system");
    CHECK_THROWS_MESSAGE(NumberWithUnits(1,"sec")+=NumberWithUnits(1,"kg"),"Types not from the same system");

}

TEST_CASE("operator + unary") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(1,"kg");
            CHECK((+a).getValue()==1);
            CHECK((+a).getType()=="kg");
    NumberWithUnits b(-1,"kg");
            CHECK((+b).getValue()==1);
            CHECK((+b).getType()=="kg");
}
TEST_CASE("operator -") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK((NumberWithUnits(1,"kg")-NumberWithUnits(1,"kg"))==NumberWithUnits(0,"kg"));
    CHECK((NumberWithUnits(1,"kg")-NumberWithUnits(1,"g"))==NumberWithUnits(0.999,"kg"));
    CHECK((NumberWithUnits(1,"g")-NumberWithUnits(1,"kg"))==NumberWithUnits(-999,"g"));
    CHECK((NumberWithUnits(1,"g")-NumberWithUnits(1,"ton"))==NumberWithUnits(999999,"g"));
    CHECK((NumberWithUnits(1,"ton")-NumberWithUnits(1,"g"))==NumberWithUnits(1.000001,"ton"));
    CHECK_THROWS_MESSAGE(NumberWithUnits(1,"kg")-NumberWithUnits(1,"sec"),"Types not from the same system");
    CHECK_THROWS_MESSAGE(NumberWithUnits(1,"sec")-NumberWithUnits(1,"kg"),"Types not from the same system");
}
TEST_CASE("operator -=") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK((NumberWithUnits(1,"kg")-=NumberWithUnits(1,"kg"))==NumberWithUnits(0,"kg"));
    CHECK((NumberWithUnits(1,"kg")-=NumberWithUnits(1,"g"))==NumberWithUnits(0.999,"kg"));
    CHECK((NumberWithUnits(1,"g")-=NumberWithUnits(1,"kg"))==NumberWithUnits(-999,"g"));
    CHECK((NumberWithUnits(1,"g")-=NumberWithUnits(1,"ton"))==NumberWithUnits(999999,"g"));
    CHECK((NumberWithUnits(1,"ton")-=NumberWithUnits(1,"g"))==NumberWithUnits(1.000001,"ton"));
    CHECK_THROWS_MESSAGE(NumberWithUnits(1,"kg")-=NumberWithUnits(1,"sec"),"Types not from the same system");
    CHECK_THROWS_MESSAGE(NumberWithUnits(1,"sec")-=NumberWithUnits(1,"kg"),"Types not from the same system");
}
TEST_CASE("operator - unary") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(1,"kg");
            CHECK((-a).getValue()==-1);
            CHECK((-a).getType()=="kg");
    NumberWithUnits b(-1,"kg");
            CHECK((-b).getValue()==1);
            CHECK((-b).getType()=="kg");
}

TEST_CASE("operator ==") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK(NumberWithUnits(5,"kg")==NumberWithUnits(5,"kg"));
    CHECK(NumberWithUnits(5,"kg")==NumberWithUnits(5000,"g"));
            CHECK_THROWS(NumberWithUnits(5,"km")==NumberWithUnits(5,"kg"));

}
TEST_CASE("operator <=") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK(NumberWithUnits(5,"kg")<=NumberWithUnits(5,"kg"));
    CHECK(NumberWithUnits(5,"kg")<=NumberWithUnits(6,"kg"));
    CHECK_FALSE(NumberWithUnits(6,"kg")<=NumberWithUnits(5,"kg"));
    CHECK(NumberWithUnits(5,"kg")<=NumberWithUnits(5000,"g"));
    CHECK(NumberWithUnits(5,"kg")<=NumberWithUnits(6000,"g"));
            CHECK_THROWS(NumberWithUnits(5,"km")<=NumberWithUnits(5,"kg"));
}
TEST_CASE("operator >=") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
            CHECK(NumberWithUnits(5,"kg")>=NumberWithUnits(5,"kg"));
            CHECK_FALSE(NumberWithUnits(5,"kg")>=NumberWithUnits(6,"kg"));
            CHECK(NumberWithUnits(6,"kg")>=NumberWithUnits(5,"kg"));
            CHECK(NumberWithUnits(5,"kg")>=NumberWithUnits(5000,"g"));
            CHECK_FALSE(NumberWithUnits(5,"kg")>=NumberWithUnits(6000,"g"));
            CHECK(NumberWithUnits(6000,"g")>=NumberWithUnits(5,"kg"));
            CHECK_THROWS(NumberWithUnits(5,"km")>=NumberWithUnits(5,"kg"));
}
TEST_CASE("operator <") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
            CHECK_FALSE(NumberWithUnits(5,"kg")<NumberWithUnits(5,"kg"));
            CHECK(NumberWithUnits(5,"kg")<NumberWithUnits(6,"kg"));
            CHECK_FALSE(NumberWithUnits(6,"kg")<NumberWithUnits(5,"kg"));
            CHECK_FALSE(NumberWithUnits(5,"kg")<NumberWithUnits(5000,"g"));
            CHECK(NumberWithUnits(5,"kg")<NumberWithUnits(6000,"g"));
            CHECK_THROWS(NumberWithUnits(5,"km")<NumberWithUnits(5,"kg"));
}
TEST_CASE("operator >") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
            CHECK_FALSE(NumberWithUnits(5,"kg")>NumberWithUnits(5,"kg"));
            CHECK_FALSE(NumberWithUnits(5,"kg")>NumberWithUnits(6,"kg"));
            CHECK(NumberWithUnits(6,"kg")>NumberWithUnits(5,"kg"));
            CHECK_FALSE(NumberWithUnits(5,"kg")>NumberWithUnits(5000,"g"));
            CHECK_FALSE(NumberWithUnits(5,"kg")>NumberWithUnits(6000,"g"));
            CHECK(NumberWithUnits(6000,"g")>NumberWithUnits(5,"kg"));
    CHECK_THROWS(NumberWithUnits(5,"km")>NumberWithUnits(5,"kg"));
}
TEST_CASE("operator --num") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(5,"kg");
    NumberWithUnits b = --a;
    CHECK(a.getValue()==4);
            CHECK(a.getType()=="kg");
            CHECK(b.getValue()==5);
            CHECK(b.getType()=="kg");
}
TEST_CASE("operator num--") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(5,"kg");
    NumberWithUnits b = a--;
    CHECK(a.getValue()==4);
    CHECK(a.getType()=="kg");
    CHECK(b.getValue()==4);
    CHECK(b.getType()=="kg");
}
TEST_CASE("operator ++num") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(5,"kg");
    NumberWithUnits b = ++a;
            CHECK(a.getValue()==6);
            CHECK(a.getType()=="kg");
            CHECK(b.getValue()==5);
            CHECK(b.getType()=="kg");
}
TEST_CASE("operator num++") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(5,"kg");
    NumberWithUnits b = a++;
            CHECK(a.getValue()==6);
            CHECK(a.getType()=="kg");
            CHECK(b.getValue()==6);
            CHECK(b.getType()=="kg");
}
TEST_CASE("operator *") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    double num =1.5;
    NumberWithUnits a(5,"kg");
    NumberWithUnits b = a*num;
            CHECK(a.getValue()==5);
            CHECK(a.getType()=="kg");
            CHECK(b.getValue()==7.5);
            CHECK(b.getType()=="kg");
    NumberWithUnits c = num*a;
            CHECK(a.getValue()==5);
            CHECK(a.getType()=="kg");
            CHECK(b.getValue()==7.5);
            CHECK(b.getType()=="kg");
}

TEST_CASE("operator <<") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(5,"kg");
    stringstream str;
    str << a<< endl;
    CHECK(str.str()=="4[kg]");
}
TEST_CASE("operator >>") {
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(5,"kg");
    istringstream str{"700 [ ton ]"};
    str >> a;
    CHECK(str.str()=="700[kg]");
    istringstream str2("700 [ blalalal ]");
    CHECK_THROWS(str2 >> a);
    CHECK(str.str()=="700[kg]");
}

