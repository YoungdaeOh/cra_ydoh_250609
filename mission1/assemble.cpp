#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"
#define DEFAULT_DELAY 800

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

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

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

void menu_cartype(void)
{
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}

void menu_engine(void)
{
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
}

void menu_brake(void)
{
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void menu_steering(void)
{
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void menu_run(void)
{
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

void menu_print(int step)
{
    printf(CLEAR_SCREEN);
    printf("===============================\n");
    if (step == CarType_Q)
    {
        menu_cartype();
    }
    else if (step == Engine_Q)
    {
        menu_engine();
    }
    else if (step == brakeSystem_Q)
    {
        menu_brake();
    }
    else if (step == SteeringSystem_Q)
    {
        menu_steering();
    }
    else if (step == Run_Test)
    {
        menu_run();
    }
}

int input_handle_cartype(int step, int answer)
{
    if (!(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
    }
    else {
        selectCarType(answer);
        step = Engine_Q;
    }
    delay(DEFAULT_DELAY);
    return step;
}

int input_handle_engine(int step, int answer)
{
    if (!(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
    }
    else {
        selectEngine(answer);
        step = brakeSystem_Q;
    }
    delay(DEFAULT_DELAY);
    return step;
}

int input_handle_brakesystem(int step, int answer)
{
    if (!(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
    }
    else {
        selectbrakeSystem(answer);
        step = SteeringSystem_Q;
    }
    delay(DEFAULT_DELAY);
    return step;
}

int input_handle_steeringsystem(int step, int answer)
{
    if (!(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
    }
    else {
        selectSteeringSystem(answer);
        step = Run_Test;
    }
    delay(DEFAULT_DELAY);
    return step;
}

int input_handle_runtest(int step, int answer)
{
    // 처음으로 돌아가기
    if (answer == 0) {
        step = CarType_Q;
    }
    else if (answer == 1)
    {
        runProducedCar();
        delay(2000);
    }
    else if (answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
        delay(2000);
    }
    else {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        delay(DEFAULT_DELAY);
    }
    return step;
}

int input_handle(int step, int answer)
{
    switch (step) {
    case CarType_Q:
        return input_handle_cartype(step, answer);
    case Engine_Q:
        return input_handle_engine(step, answer);
    case brakeSystem_Q:
        return input_handle_brakesystem(step, answer);
    case SteeringSystem_Q:
        return input_handle_steeringsystem(step, answer);
    case Run_Test:
        return input_handle_runtest(step, answer);
    default:
        return step;
    }
}

bool isValidNumber(char* buf, int* out_answer)
{
    // 숫자로 된 대답인지 확인
    char* checkNumber;
    int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환
    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(DEFAULT_DELAY);
        return false;
    }
    *out_answer = answer;
    return true;
}

bool is_exit(char* buf)
{
    if (!strcmp(buf, "exit"))
    {
        printf("바이바이\n");
        return true;
    }
    return false;
}

void getInput(char* buf)
{
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}

int main()
{
    int step = CarType_Q;

    while (1)
    {
        char buf[100];
        int answer;
        menu_print(step);
        getInput(buf);
        if (is_exit(buf))
            break;

        if (isValidNumber(buf, &answer) == false)
            continue;

        // 이전으로 돌아가기
        if (step > CarType_Q && step < Run_Test && answer == 0)
        {
            step -= 1;
            continue;
        }

        step = input_handle(step, answer);
    }
}

void selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    if (answer == 1)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (answer == 2)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (answer == 3)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    if (answer == 1)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (answer == 2)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (answer == 3)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    if (answer == 1)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (answer == 3)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    if (answer == 1)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

int isValidCheck()
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

void print_cartype(void)
{
    if (stack[CarType_Q] == 1)
        printf("Car Type : Sedan\n");
    if (stack[CarType_Q] == 2)
        printf("Car Type : SUV\n");
    if (stack[CarType_Q] == 3)
        printf("Car Type : Truck\n");
}

void print_engine(void)
{
    if (stack[Engine_Q] == 1)
        printf("Engine : GM\n");
    if (stack[Engine_Q] == 2)
        printf("Engine : TOYOTA\n");
    if (stack[Engine_Q] == 3)
        printf("Engine : WIA\n");
}

void print_brakesystem(void)
{
    if (stack[brakeSystem_Q] == 1)
        printf("Brake System : Mando");
    if (stack[brakeSystem_Q] == 2)
        printf("Brake System : Continental\n");
    if (stack[brakeSystem_Q] == 3)
        printf("Brake System : Bosch\n");
}

void print_steeringsystem(void)
{
    if (stack[SteeringSystem_Q] == 1)
        printf("SteeringSystem : Bosch\n");
    if (stack[SteeringSystem_Q] == 2)
        printf("SteeringSystem : Mobis\n");
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (stack[Engine_Q] == 4)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            print_cartype();
            print_engine();
            print_brakesystem();
            print_steeringsystem();
            printf("자동차가 동작됩니다.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}