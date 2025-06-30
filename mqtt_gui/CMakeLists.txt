cmake_minimum_required(VERSION 3.16)
project(mqtt_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 찾기
find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

# Qt6 버전 체크 무시
set(QT_NO_PACKAGE_VERSION_CHECK TRUE)

# 로컬 Qt6 MQTT 모듈 경로 설정
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};../qt6_local/usr/lib/x86_64-linux-gnu/cmake")
find_package(Qt6Mqtt REQUIRED)

# Publisher GUI 실행파일
add_executable(mqtt_pub_gui
    main_pub_gui.cpp
    publisher_gui.cpp
    publisher_gui.h
    common_widget.cpp
    common_widget.h
)

# Subscriber GUI 실행파일
add_executable(mqtt_sub_gui
    main_sub_gui.cpp
    subscriber_gui.cpp
    subscriber_gui.h
    common_widget.cpp
    common_widget.h
)

# Qt6 MOC 자동 처리
set_target_properties(mqtt_pub_gui PROPERTIES AUTOMOC ON)
set_target_properties(mqtt_sub_gui PROPERTIES AUTOMOC ON)

# 라이브러리 링크
target_link_libraries(mqtt_pub_gui Qt6::Core Qt6::Network Qt6::Widgets Qt6::Mqtt)
target_link_libraries(mqtt_sub_gui Qt6::Core Qt6::Network Qt6::Widgets Qt6::Mqtt)

# 헤더 경로 추가
target_include_directories(mqtt_pub_gui PRIVATE ../qt6_local/usr/include/x86_64-linux-gnu/qt6)
target_include_directories(mqtt_sub_gui PRIVATE ../qt6_local/usr/include/x86_64-linux-gnu/qt6)