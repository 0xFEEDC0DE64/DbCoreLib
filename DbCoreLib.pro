QT += core
QT -= gui widgets

PROJECT_ROOT = ../..

TARGET = dbcore

DEFINES += DBCORELIB_LIBRARY

SOURCES += \
    randomdevice.cpp \
    utils/timeutils.cpp \
    utils/jsonutils.cpp

HEADERS += dbcorelib_global.h \
           fixedsizematrix.h \
    randomdevice.h \
    utils/timeutils.h \
    utils/jsonutils.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/lib.pri)
