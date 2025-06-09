# cra_ydoh_250609


< mission1 >

완료.
main 함수 내에 while loop 코드가 과하게 길어 가독성이 떨어지는 문제가 있었습니다.
이를 모듈별로 쪼개어 외부 함수로 추출하였습니다.

runProducedCar 함수 내부에 있는 조건문도 부품별로 함수로 추출하였습니다.


< mission2 >

D1 - 완료

D2 - 완료. Unit Test 완료

D3 - 완료. 부품 추가되더라도 client code 변경 없더록 구현 완료.

D4 - 완료. Builder pattern 적용하여 "builder.select_car_type(CarType::Type::TRUCK).select_engine(Engine::Type::GM).select_brake_system(BrakeSystem::Type::MANDO).select_steering_system(SteeringSystem::Type::BOSCH);" 와 같이 연달아서 호출 가능.

D5 - 완료. coverage_file.jpg 에 100% 완료 하여 제출. printf 구문들은 _DEBUG define으로 gtest 시에 제거하였습니다.