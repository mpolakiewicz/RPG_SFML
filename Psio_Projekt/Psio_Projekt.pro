TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Background.cpp \
        Diamonds.cpp \
        Game.cpp \
        Hero.cpp \
        Skeleton.cpp \
        Totem.cpp \
        main.cpp
INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    AnimatedSprite.h \
    Background.h \
    Diamonds.h \
    Game.h \
    Hero.h \
    Skeleton.h \
    Totem.h \
    classes.h \
