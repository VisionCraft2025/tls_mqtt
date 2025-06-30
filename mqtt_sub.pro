QT += core network mqtt
QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# Qt6 MQTT 로컬 설치 경로
INCLUDEPATH += /home/kwon/Documents/QT_mqtt/tls/qt6_local/usr/include/x86_64-linux-gnu/qt6
LIBS += -L/home/kwon/Documents/QT_mqtt/tls/qt6_local/usr/lib/x86_64-linux-gnu -lQt6Mqtt

TARGET = mqtt_sub

SOURCES += \
    main_sub.cpp \
    subscriber.cpp

HEADERS += \
    subscriber.h