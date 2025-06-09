#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

#define CLEAR_SCREEN "\033[H\033[2J"
#define DEFAULT_DELAY 800

int stack[10];

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};


class CarBuilder {
private:
    int stack[10]{};
    QuestionType step = CarType_Q;

public:
    void run();

private:
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
    void select_car_type(int answer);
    void select_engine(int answer);
    void select_brake_system(int answer);
    void select_steering_system(int answer);
    int is_valid_assemble();
    void print_cartype(void);
    void print_engine(void);
    void print_brakesystem(void);
    void print_steeringsystem(void);
    void run_produced_car();
    void test_produced_car();
};

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

void CarBuilder::select_car_type(int answer)
{
    stack[CarType_Q] = answer;
    if (answer == 1)
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void CarBuilder::select_engine(int answer)
{
    stack[Engine_Q] = answer;
    if (answer == 1)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void CarBuilder::select_brake_system(int answer)
{
    stack[brakeSystem_Q] = answer;
    if (answer == 1)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void CarBuilder::select_steering_system(int answer)
{
    stack[SteeringSystem_Q] = answer;
    if (answer == 1)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
}

int CarBuilder::is_valid_assemble()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        return false;
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void CarBuilder::print_cartype(void)
{
    if (stack[CarType_Q] == 1)
        printf("Car Type : Sedan\n");
    if (stack[CarType_Q] == 2)
        printf("Car Type : SUV\n");
    if (stack[CarType_Q] == 3)
        printf("Car Type : Truck\n");
}

void CarBuilder::print_engine(void)
{
    if (stack[Engine_Q] == 1)
        printf("Engine : GM\n");
    if (stack[Engine_Q] == 2)
        printf("Engine : TOYOTA\n");
    if (stack[Engine_Q] == 3)
        printf("Engine : WIA\n");
}

void CarBuilder::print_brakesystem(void)
{
    if (stack[brakeSystem_Q] == 1)
        printf("Brake System : Mando");
    if (stack[brakeSystem_Q] == 2)
        printf("Brake System : Continental\n");
    if (stack[brakeSystem_Q] == 3)
        printf("Brake System : Bosch\n");
}

void CarBuilder::print_steeringsystem(void)
{
    if (stack[SteeringSystem_Q] == 1)
        printf("SteeringSystem : Bosch\n");
    if (stack[SteeringSystem_Q] == 2)
        printf("SteeringSystem : Mobis\n");
}

void CarBuilder::run_produced_car()
{
    if (is_valid_assemble() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (stack[Engine_Q] == 4)
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

void CarBuilder::test_produced_car()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
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
    CarBuilder app;
    app.run();
    return 0;
}
#endif