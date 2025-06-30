cmake_minimum_required(VERSION 3.16)
project(mqtt_tls_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 찾기
find_package(Qt6 REQUIRED COMPONENTS Core Network)

# Qt6 버전 체크 무시
set(QT_NO_PACKAGE_VERSION_CHECK TRUE)

# 로컬 Qt6 MQTT 모듈 경로 설정
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/home/kwon/Documents/QT_mqtt/tls/qt6_local/usr/lib/x86_64-linux-gnu/cmake")
find_package(Qt6Mqtt REQUIRED)

# Publisher 실행파일
add_executable(mqtt_pub
    main_pub.cpp
    publisher.cpp
    publisher.h
)

# Subscriber 실행파일
add_executable(mqtt_sub
    main_sub.cpp
    subscriber.cpp
    subscriber.h
)

# Qt6 MOC 자동 처리
set_target_properties(mqtt_pub PROPERTIES AUTOMOC ON)
set_target_properties(mqtt_sub PROPERTIES AUTOMOC ON)

# 라이브러리 링크
target_link_libraries(mqtt_pub Qt6::Core Qt6::Network Qt6::Mqtt)
target_link_libraries(mqtt_sub Qt6::Core Qt6::Network Qt6::Mqtt)

# 헤더 경로 추가
target_include_directories(mqtt_pub PRIVATE /home/kwon/Documents/QT_mqtt/tls/qt6_local/usr/include/x86_64-linux-gnu/qt6)
target_include_directories(mqtt_sub PRIVATE /home/kwon/Documents/QT_mqtt/tls/qt6_local/usr/include/x86_64-linux-gnu/qt6)