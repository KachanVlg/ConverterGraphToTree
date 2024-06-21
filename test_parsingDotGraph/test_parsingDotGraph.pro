QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
           ../mainProject/parsingCheckDotFunctions.cpp \
           ../mainProject/dataStructeres.cpp \
           test_parsingDotGraph.cpp

HEADERS += ../mainProject/parsingCheckDotFunction.h
HEADERS += ../mainProject/dataStructeres.h
