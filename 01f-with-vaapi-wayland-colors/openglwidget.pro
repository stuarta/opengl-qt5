QT += core gui opengl x11extras
CONFIG += debug

INCLUDES += \
    window.h

SOURCES += \
    main.cpp window.cpp

target.path = .
INSTALLS += target

LIBS    += -lva -lva-glx -lva-wayland -lwayland-client
