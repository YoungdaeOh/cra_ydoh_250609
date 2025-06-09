#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <string>
#include <gtest/gtest.h>

class CarType {
public:
    CarType() {}
    enum Type { SEDAN = 1, SUV, TRUCK, COUNT = TRUCK };
    explicit CarType(Type type);
    Type get() const;
#ifndef _DEBUG
    const char* get_name();
#endif
private:
    Type type_;
    static const std::string names[COUNT];
};

class Engine {
public:
    Engine() {}
    enum Type { GM = 1, TOYOTA, WIA, COUNT = WIA };
    explicit Engine(Type type);
    Type get() const;
#ifndef _DEBUG
    const char* get_name();
#endif

private:
    Type type_;
    static const std::string names[COUNT];
};

class BrakeSystem {
public:
    BrakeSystem() {}
    enum Type { MANDO = 1, CONTINENTAL, BOSCH, COUNT = BOSCH };
    explicit BrakeSystem(Type type);
    Type get() const;
#ifndef _DEBUG
    const char* get_name();
#endif

private:
    Type type_;
    static const std::string names[COUNT];
};

class SteeringSystem {
public:
    SteeringSystem() {}
    enum Type { BOSCH = 1, MOBIS, COUNT = MOBIS };
    explicit SteeringSystem(Type type);
    Type get() const;
#ifndef _DEBUG
    const char* get_name();
#endif

private:
    Type type_;
    static const std::string names[COUNT];
};

#endif
