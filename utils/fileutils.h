#pragma once

#include "dbcorelib_global.h"

class QString;

bool DBCORELIB_EXPORT emptyDirectory(const QString &path);

const DBCORELIB_EXPORT QString &translationsDir();
