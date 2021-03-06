QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animation.cpp \
    circle.cpp \
    constraint.cpp \
    controller.cpp \
    dynamics.cpp \
    dynamics_method.cpp \
    euler_method.cpp \
    force.cpp \
    inertial_matrix.cpp \
    line.cpp \
    link.cpp \
    main.cpp \
    mainwindow.cpp \
    matrix.cpp \
    pid.cpp \
    point.cpp \
    rectangle.cpp \
    revolute_pair.cpp \
    runge_kutta.cpp \
    sensor.cpp \
    shape.cpp \
    solid.cpp

HEADERS += \
    animation.h \
    circle.h \
    constraint.h \
    controller.h \
    dynamics.h \
    dynamics_method.h \
    euler_method.h \
    force.h \
    identity_matrix.h \
    inertial_matrix.h \
    line.h \
    link.h \
    mainwindow.h \
    matrix.h \
    object.h \
    pid.h \
    point.h \
    pub_include.h \
    rectangle.h \
    revolute_pair.h \
    runge_kutta.h \
    sensor.h \
    shape.h \
    solid.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
