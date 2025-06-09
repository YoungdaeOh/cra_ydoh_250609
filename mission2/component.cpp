#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "component.hpp"


const std::string CarType::names[CarType::COUNT] = {
    "SEDAN", "SUV", "TRUCK"
};
CarType::CarType(CarType::Type type) : type_(type) {
    printf("���� Ÿ������ %s�� �����ϼ̽��ϴ�.\n", names[type_ - 1].c_str());
}
CarType::Type CarType::get() const {
    return type_;
}
#ifndef _DEBUG
const char* CarType::get_name() {
    return names[type_ - 1].c_str();
}
#endif


const std::string Engine::names[Engine::COUNT] = {
    "GM", "TOYOTA", "WIA"
};
Engine::Engine(Type type) : type_(type) {
    printf("%s ������ �����ϼ̽��ϴ�.\n", names[type_ - 1].c_str());
}
Engine::Type Engine::get() const {
    return type_;
}
#ifndef _DEBUG
const char* Engine::get_name() {
    return names[type_ - 1].c_str();
}
#endif


const std::string BrakeSystem::names[BrakeSystem::COUNT] = {
    "MANDO", "CONTINENTAL", "BOSCH"
};
BrakeSystem::BrakeSystem(Type type) : type_(type) {
    printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", names[type_ - 1].c_str());
}
BrakeSystem::Type BrakeSystem::get() const {
    return type_;
}
#ifndef _DEBUG
const char* BrakeSystem::get_name() {
    return names[type_ - 1].c_str();
}
#endif


const std::string SteeringSystem::names[SteeringSystem::COUNT] = {
    "BOSCH", "MOBIS"
};
SteeringSystem::SteeringSystem(Type type) : type_(type) {
    printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", names[type_ - 1].c_str());
}
SteeringSystem::Type SteeringSystem::get() const {
    return type_;
}
#ifndef _DEBUG
const char* SteeringSystem::get_name() {
    return names[type_ - 1].c_str();
}
#endif
