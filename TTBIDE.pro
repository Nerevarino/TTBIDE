TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    application.cpp

unix:!macx: LIBS += -lwayland-egl

unix:!macx: LIBS += -lwayland-client

HEADERS += \
    application.h
