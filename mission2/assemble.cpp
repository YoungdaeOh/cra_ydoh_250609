#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "assemble.hpp"

#ifndef _DEBUG
void CarBuilder::delay(int ms) {
    volatile int sum = 0;
    for (int i = 0; i < 1000; ++i)
        for (int j = 0; j < 1000; ++j)
            for (int t = 0; t < ms; ++t)
                sum++;
}

void CarBuilder::menu_cartype(void)
{
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("� ���� Ÿ���� �����ұ��?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}

void CarBuilder::menu_engine(void)
{
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. ���峭 ����\n");
}

void CarBuilder::menu_brake(void)
{
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void CarBuilder::menu_steering(void)
{
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void CarBuilder::menu_runtest(void)
{
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

void CarBuilder::menu_print(void)
{
    printf(CLEAR_SCREEN);
    printf("===============================\n");
    if (step == CarType_Q)
        menu_cartype();
    else if (step == Engine_Q)
        menu_engine();
    else if (step == brakeSystem_Q)
        menu_brake();
    else if (step == SteeringSystem_Q)
        menu_steering();
    else if (step == Run_Test)
        menu_runtest();
}

bool CarBuilder::is_exit(char* buf)
{
    if (!strcmp(buf, "exit"))
    {
        printf("���̹���\n");
        return true;
    }
    return false;
}

void CarBuilder::get_input(char* buf)
{
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // ���� ���๮�� ����
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}

bool CarBuilder::is_valid_number(char* buf, int* out_answer)
{
    // ���ڷ� �� ������� Ȯ��
    char* checkNumber;
    int answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ
    // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
    if (*checkNumber != '\0')
    {
        printf("ERROR :: ���ڸ� �Է� ����\n");
        delay(DEFAULT_DELAY);
        return false;
    }
    *out_answer = answer;
    return true;
}

void CarBuilder::input_handle_cartype(int answer)
{
    if (!(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
    }
    else {
        select_car_type(answer);
        step = Engine_Q;
    }
    delay(DEFAULT_DELAY);
}

void CarBuilder::input_handle_engine(int answer)
{
    if (!(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
    }
    else {
        select_engine(answer);
        step = brakeSystem_Q;
    }
    delay(DEFAULT_DELAY);
}

void CarBuilder::input_handle_brakesystem(int answer)
{
    if (!(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
    }
    else {
        select_brake_system(answer);
        step = SteeringSystem_Q;
    }
    delay(DEFAULT_DELAY);
}

void CarBuilder::input_handle_steeringsystem(int answer)
{
    if (!(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
    }
    else {
        select_steering_system(answer);
        step = Run_Test;
    }
    delay(DEFAULT_DELAY);
}

void CarBuilder::input_handle_runtest(int answer)
{
    // ó������ ���ư���
    if (answer == 0) {
        step = CarType_Q;
    }
#ifndef _DEBUG
    else if (answer == 1)
    {
        run_produced_car();
        delay(2000);
    }
    else if (answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        test_produced_car();
        delay(2000);
    }
    else {
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        delay(DEFAULT_DELAY);
    }
#endif
}

void CarBuilder::input_handle(int answer)
{
    switch (step) {
    case CarType_Q:
        input_handle_cartype(answer);
        break;
    case Engine_Q:
        input_handle_engine(answer);
        break;
    case brakeSystem_Q:
        input_handle_brakesystem(answer);
        break;
    case SteeringSystem_Q:
        input_handle_steeringsystem(answer);
        break;
    case Run_Test:
        input_handle_runtest(answer);
        break;
    }
}
#endif

CarBuilder& CarBuilder::select_car_type(int answer)
{
    car_type_ = CarType(static_cast<CarType::Type>(answer));
    return *this;
}

CarBuilder& CarBuilder::select_engine(int answer)
{
    engine = Engine(static_cast<Engine::Type>(answer));
    return *this;
}

CarBuilder& CarBuilder::select_brake_system(int answer)
{
    brake_system = BrakeSystem(static_cast<BrakeSystem::Type>(answer));
    return *this;
}

CarBuilder& CarBuilder::select_steering_system(int answer)
{
    steering_system = SteeringSystem(static_cast<SteeringSystem::Type>(answer));
    return *this;
}

int CarBuilder::is_valid_assemble()
{
    if (car_type_.get() == car_type_.SEDAN && brake_system.get() == brake_system.CONTINENTAL)
    {
        return false; }
    else if (car_type_.get() == car_type_.SUV && engine.get() == engine.TOYOTA)
    {
        return false; }
    else if (car_type_.get() == car_type_.TRUCK && engine.get() == engine.WIA)
    {
        return false; }
    else if (car_type_.get() == car_type_.TRUCK && brake_system.get() == brake_system.MANDO)
    {
        return false; }
    else if (brake_system.get() == brake_system.BOSCH && steering_system.get() != steering_system.BOSCH)
    {
        return false; }
    return true;
}

#ifndef _DEBUG
void CarBuilder::print_cartype(void)
{
    printf("Car Type : %s\n", car_type_.get_name());
}

void CarBuilder::print_engine(void)
{
    printf("Engine : %s\n", engine.get_name());
}

void CarBuilder::print_brakesystem(void)
{
    printf("Brake System : %s\n", brake_system.get_name());
}

void CarBuilder::print_steeringsystem(void)
{
    printf("SteeringSystem : %s\n", steering_system.get_name());
}

void CarBuilder::run_produced_car(void)
{
    if (is_valid_assemble() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (engine.get() > engine.COUNT)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        }
        else
        {
            print_cartype();
            print_engine();
            print_brakesystem();
            print_steeringsystem();
            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void CarBuilder::test_produced_car(void)
{
    if (car_type_.get() == car_type_.SEDAN && brake_system.get() == brake_system.CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (car_type_.get() == car_type_.SUV && engine.get() == engine.TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (car_type_.get() == car_type_.TRUCK && engine.get() == engine.WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (car_type_.get() == car_type_.TRUCK && brake_system.get() == brake_system.MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (brake_system.get() == brake_system.BOSCH && steering_system.get() != steering_system.BOSCH)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}

void CarBuilder::run() {
    std::string input;
    while (true) {
        char buf[100];
        int answer;

        menu_print();

        get_input(buf);
        if (is_exit(buf))
            break;

        if (is_valid_number(buf, &answer) == false)
            continue;

        // �������� ���ư���
        if (step > CarType_Q && step < Run_Test && answer == 0)
        {
            step = static_cast<QuestionType>((int)step - 1);
            continue;
        }

        input_handle(answer);
    }
}
#endif


#ifdef _DEBUG
#include "gmock/gmock.h"
int main()
{
    testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else
int main()
{
    CarBuilder app(0);
    app.run();
    return 0;
}
#endif