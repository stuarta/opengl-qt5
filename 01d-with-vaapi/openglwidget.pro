QT += core gui opengl x11extras

INCLUDES += \
    window.h

SOURCES += \
    main.cpp window.cpp

target.path = .
INSTALLS += target

LIBS    += -lva -lva-glx
