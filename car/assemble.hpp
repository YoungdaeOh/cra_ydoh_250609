#ifndef ASSEMBLE_HPP
#define ASSEMBLE_HPP

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "component.hpp"

#define CLEAR_SCREEN "\033[H\033[2J"
#define DEFAULT_DELAY 800

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

class CarBuilder {
private:
    int value_;
    CarType car_type_;
    Engine engine;
    BrakeSystem brake_system;
    SteeringSystem steering_system;
    int stack[10]{};
    QuestionType step = CarType_Q;

public:
    CarBuilder() {} // »ý¼ºÀÚ
#ifndef _DEBUG
    void run();
#endif
    CarBuilder& select_car_type(int answer);
    CarBuilder& select_engine(int answer);
    CarBuilder& select_brake_system(int answer);
    CarBuilder& select_steering_system(int answer);
    int is_valid_assemble();

private:
#ifndef _DEBUG
    void menu_cartype(void);
    void menu_engine(void);
    void menu_brake(void);
    void menu_steering(void);
    void menu_runtest(void);
    void menu_print(void);
    bool is_exit(char* buf);
    void get_input(char* buf);
    bool is_valid_number(char* buf, int* out_answer);
    void delay(int ms);
    void input_handle_cartype(int answer);
    void input_handle_engine(int answer);
    void input_handle_brakesystem(int answer);
    void input_handle_steeringsystem(int answer);
    void input_handle_runtest(int answer);
    void input_handle(int answer);

    void print_cartype(void);
    void print_engine(void);
    void print_brakesystem(void);
    void print_steeringsystem(void);
    void run_produced_car(void);
    void test_produced_car(void);
#endif
};

#endif