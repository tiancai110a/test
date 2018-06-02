CONFIG += c++11 console
CONFIG -= app_bundle
#CONFIG += -fno-elide-constructors
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -fno-elide-constructors

DEFINES +=BOOST_USE_LIB
INCLUDEPATH+= /home/tiancai/boost/include/
DEFINES +=BOOST_USE_LIB
LIBS+=  -L/home/tiancai/boost/lib/

LIBS+=  -L/home/tiancai/boost/lib/
LIBS+=  -L/home/tiancai/boost/lib/ -lboost_program_options
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT-= core gui
SOURCES += \
    getlocalip.cpp
