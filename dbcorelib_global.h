#pragma once

#include <QtGlobal>

#if defined(DBCORELIB_LIBRARY)
#  define DBCORELIB_EXPORT Q_DECL_EXPORT
#else
#  define DBCORELIB_EXPORT Q_DECL_IMPORT
#endif
