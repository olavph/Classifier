#-------------------------------------------------
#
# Project created by QtCreator 2011-03-25T13:24:04
#
#-------------------------------------------------

QT       += core gui

TARGET = Classifier
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    circle.cpp \
    classifier.cpp \
    class.cpp \
    generator.cpp \
    line.cpp \
    datum.cpp \
    triple.cpp \
    datacontainer.cpp \
    ibl/ibl2.cpp \
    ibl/ibl1.cpp \
    ibl/ibl3.cpp \
    ibl/ibl.cpp \
    ibl/classificationrecord.cpp \
    ibl/ibl4.cpp

HEADERS  += mainwindow.h \
    circle.h \
    classifier.h \
    class.h \
    generator.h \
    datum.h \
    distancecalculation.h \
    euclidiandistance.h \
    line.h \
    manhattandistance.h \
    triple.h \
    datacontainer.h \
    singleton.h \
    ibl/ibl2.h \
    ibl/ibl1.h \
    ibl/ibl.h \
    ibl/ibl3.h \
    ibl/classificationrecord.h \
    ibl/ibl4.h

FORMS    += mainwindow.ui
