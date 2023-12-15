TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        board.cpp \
        is_input_clear.cpp \
        main.cpp

HEADERS += \
    board.hh \
    is_input_clear.hh
