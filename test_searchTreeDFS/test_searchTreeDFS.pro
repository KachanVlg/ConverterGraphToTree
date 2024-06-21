QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
           ../mainProject/computingFunctions.cpp \
           ../mainProject/dataStructeres.cpp \
           test_searchTreeDFS.cpp

HEADERS += ../mainProject/computingFuncitons.h
HEADERS += ../mainProject/dataStructeres.h
