QT += quick
CONFIG += c++11

SOURCES += \
    main.cpp \
    speedcontroller.cpp

HEADERS += \
    speedcontroller.h

# CAN 통신을 위한 socketcan 라이브러리 추가
LIBS += -lsocketcan
