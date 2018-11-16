#pragma once

#include <QTime>

#include "dbcorelib_global.h"

int DBCORELIB_EXPORT timeToSeconds(const QTime &time);
QTime DBCORELIB_EXPORT timeBetween(const QTime &l, const QTime &r);
QTime DBCORELIB_EXPORT timeAdd(const QTime &l, const QTime &r);
QTime DBCORELIB_EXPORT timeNormalise(const QTime &time);

QDate DBCORELIB_EXPORT beginOfMonth(QDate date);
QDate DBCORELIB_EXPORT endOfMonth(const QDate &date);
