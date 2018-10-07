project(DbCoreLib)

enable_testing()

set(HEADERS
    cpp14polyfills.h
    dbcorelib_global.h
    fixedsizematrix.h
    randomdevice.h
    utils/jsonutils.h
    utils/timeutils.h
)

set(SOURCES
    randomdevice.cpp
    utils/jsonutils.cpp
    utils/timeutils.cpp
)

add_library(dbcorelib ${HEADERS} ${SOURCES})

target_compile_definitions(dbcorelib PRIVATE DBCORELIB_LIBRARY)

target_link_libraries(dbcorelib Qt5::Core)

target_include_directories(dbcorelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(tst_fixedsizematrix tst_fixedsizematrix.cpp)
add_test(tst_fixedsizematrix tst_fixedsizematrix)
target_link_libraries(tst_fixedsizematrix Qt5::Core Qt5::Test dbcorelib)
