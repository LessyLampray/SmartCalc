QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calc_credit.c \
    credit.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    s21_SmartCalc.c

HEADERS += \
    calc_credit.h \
    credit.h \
    mainwindow.h \
    qcustomplot.h \
    s21_SmartCalc.h

FORMS += \
    credit.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
