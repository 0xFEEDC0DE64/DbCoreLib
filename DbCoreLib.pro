QT += core
QT -= gui widgets

PROJECT_ROOT = ../..

TARGET = dbcore

DEFINES += DBCORELIB_LIBRARY

SOURCES +=

HEADERS += dbcorelib_global.h \
           fixedsizematrix.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/lib.pri)
