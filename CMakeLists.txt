project(DbCoreLib)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Test CONFIG REQUIRED)
find_package(Qt5LinguistTools CONFIG REQUIRED)

enable_testing()

set(HEADERS
    cpp14polyfills.h
    dbcorelib_global.h
    fifostream.h
    fixedsizematrix.h
    randomdevice.h
    waverecorder.h
    utils/datastreamutils.h
    utils/fileutils.h
    utils/jsonutils.h
    utils/timeutils.h
)

set(SOURCES
    fifostream.cpp
    randomdevice.cpp
    waverecorder.cpp
    utils/fileutils.cpp
    utils/jsonutils.cpp
    utils/timeutils.cpp
)

set(TRANSLATIONS
    translations/dbcorelib_en.ts
    translations/dbcorelib_de.ts
)

set_source_files_properties(${TRANSLATIONS} PROPERTIES OUTPUT_LOCATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/translations)
QT5_CREATE_TRANSLATION(TRANSLATIONS_C ${TRANSLATIONS} ${HEADERS} ${SOURCES} OPTIONS -no-obsolete)
#QT5_ADD_TRANSLATION(TRANSLATIONS_C ${TRANSLATIONS})

add_library(dbcorelib SHARED ${HEADERS} ${SOURCES} ${TRANSLATIONS_C})

target_compile_definitions(dbcorelib PRIVATE DBCORELIB_LIBRARY)

target_link_libraries(dbcorelib Qt5::Core)

target_include_directories(dbcorelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_dependencies(libs dbcorelib)


add_executable(tst_fixedsizematrix tst_fixedsizematrix.cpp)
add_test(tst_fixedsizematrix tst_fixedsizematrix)
target_link_libraries(tst_fixedsizematrix Qt5::Core Qt5::Test dbcorelib)
