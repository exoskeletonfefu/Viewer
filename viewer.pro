QT += core network widgets gui
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = viewer

QMAKE_CXXFLAGS += -g

TEMPLATE = app
INCLUDEPATH += $$PWD/include /usr/local/include/
#INCLUDEPATH += ../../messages/messages/include

#LIBS += -L../../messages/build-messages-Desktop_Qt_5_9_1_clang_64bit-Debug
#LIBS += -lmessages
#/Users/ilyazuev/CommonUbuntuVB/exoskeleton/Qt/messages/build-messages-Desktop_Qt_5_9_1_clang_64bit-Debug/libmessages.dylib

SOURCES += main.cpp $$PWD/src/*.cpp
HEADERS += $$PWD/include/*.h
FORMS   += $$PWD/forms/mainwindow.ui
