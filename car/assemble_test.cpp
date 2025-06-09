#include "gmock/gmock.h"
#include "assemble.hpp"
#include "component.hpp"

using namespace testing;

TEST(CarBuilderTest, ValidConfiguration_Passes) {
    CarBuilder builder;
    builder.select_car_type(CarType::Type::SEDAN);
    builder.select_engine(Engine::Type::GM);
    builder.select_brake_system(BrakeSystem::Type::MANDO);
    builder.select_steering_system(SteeringSystem::Type::BOSCH);

    EXPECT_TRUE(builder.is_valid_assemble());
}

TEST(CarBuilderTest, Invalid_SedanWithContinentalBrake_Fails) {
    CarBuilder builder;
    builder.select_car_type(CarType::Type::SEDAN);
    builder.select_engine(Engine::Type::GM);
    builder.select_brake_system(BrakeSystem::Type::CONTINENTAL);
    builder.select_steering_system(SteeringSystem::Type::BOSCH);

    EXPECT_FALSE(builder.is_valid_assemble());
}

TEST(CarBuilderTest, Invalid_SUVWithToyotaEngine_Fails) {
    CarBuilder builder;
    builder.select_car_type(CarType::Type::SUV);
    builder.select_engine(Engine::Type::TOYOTA);
    builder.select_brake_system(BrakeSystem::Type::MANDO);
    builder.select_steering_system(SteeringSystem::Type::MOBIS);

    EXPECT_FALSE(builder.is_valid_assemble());
}

TEST(CarBuilderTest, Invalid_TruckWithWIAEngine_Fails) {
    CarBuilder builder;
    builder.select_car_type(CarType::Type::TRUCK);
    builder.select_engine(Engine::Type::WIA);
    builder.select_brake_system(BrakeSystem::Type::CONTINENTAL);
    builder.select_steering_system(SteeringSystem::Type::BOSCH);

    EXPECT_FALSE(builder.is_valid_assemble());
}

TEST(CarBuilderTest, Invalid_BoschBrakeWithNonBoschSteering_Fails) {
    CarBuilder builder;
    builder.select_car_type(CarType::Type::SUV);
    builder.select_engine(Engine::Type::GM);
    builder.select_brake_system(BrakeSystem::Type::BOSCH);
    builder.select_steering_system(SteeringSystem::Type::MOBIS);

    EXPECT_FALSE(builder.is_valid_assemble());
}

TEST(CarBuilderTest, BoschBrakeWithBoschSteering_Passes) {
    CarBuilder builder;
    builder.select_car_type(CarType::Type::SUV);
    builder.select_engine(Engine::Type::GM);
    builder.select_brake_system(BrakeSystem::Type::BOSCH);
    builder.select_steering_system(SteeringSystem::Type::BOSCH);

    EXPECT_TRUE(builder.is_valid_assemble());
}

TEST(CarBuilderTest, TruckWithMandoBrake_Passes) {
    CarBuilder builder;
    builder.select_car_type(CarType::Type::TRUCK).select_engine(Engine::Type::GM).select_brake_system(BrakeSystem::Type::MANDO).select_steering_system(SteeringSystem::Type::BOSCH);

    EXPECT_FALSE(builder.is_valid_assemble());
}