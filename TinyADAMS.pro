QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    circle.cpp \
    constraint.cpp \
    line.cpp \
    main.cpp \
    mainwindow.cpp \
    matrix.cpp \
    rectangle.cpp \
    revolute_pair.cpp \
    shape_base.cpp \
    solid.cpp \
    vector.cpp

HEADERS += \
    circle.h \
    constraint.h \
    identity_matrix.h \
    line.h \
    mainwindow.h \
    matrix.h \
    rectangle.h \
    revolute_pair.h \
    shape.h \
    shape_base.h \
    solid.h \
    vector.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
