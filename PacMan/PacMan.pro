TEMPLATE = app

QT += serialport

SOURCES += \
    main.cpp \
    arduinocontroller.cpp \
    fakecontroller.cpp \
    game.cpp \
    keyboardcontroller.cpp \
    map.cpp \
    pacman.cpp \
    ghost.cpp \
    fakeartificialintelligence.cpp

LIBS += -lglutk32
LIBS += -lopengl32
LIBS += -lglu32

HEADERS += \
    icontroller.h \
    arduinocontroller.h \
    fakecontroller.h \
    iglut.h \
    game.h \
    keyboardcontroller.h \
    map.h \
    imap.h \
    ipacman.h \
    pacman.h \
    ighost.h \
    ghost.h \
    iartificialintelligence.h \
    fakeartificialintelligence.h

DEFINES += NO_USE_QT
