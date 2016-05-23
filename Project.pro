QT       += core gui
LIBS     += -lsfml-graphics -lsfml-window -lsfml-system -lQSFML
QMAKE_CXXFLAGS += -std=c++11 -Wno-sign-compare

INCLUDEPATH += /usr/include

DESTDIR=build
OBJECTS_DIR=build/obj

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Retro-Breaker
TEMPLATE = app

HEADERS += \
    Ball.hpp \
    Brick.hpp \
    Game.hpp \
    Leaderboards.hpp \
    Player.hpp \
    toString.hpp \
    MainMenu.hpp \
    Records.hpp

SOURCES += \
    main.cpp \
    Ball.cpp \
    Game.cpp \
    Brick.cpp \
    Leaderboards.cpp \
    MainMenu.cpp \
    Records.cpp

DISTFILES += \
    assets/default/brick.png \
    assets/default/ball.png \
    assets/default/bitfont.ttf

RESOURCES += \
    assets/default/default.qrc