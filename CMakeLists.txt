project(harbour-angelfish CXX)
cmake_minimum_required(VERSION 2.8.11)

find_package(Qt5Qml REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Sql REQUIRED)

include(FindPkgConfig)
pkg_search_module(SAILFISH sailfishapp REQUIRED)
pkg_search_module(BLUEZ bluez REQUIRED)

include_directories(${BLUEZ_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(harbour-angelfish src/main.cpp src/angel.cpp src/devicemodel.cpp)

set_property(TARGET harbour-angelfish
  PROPERTY INCLUDE_DIRECTORIES
  INCLUDE_DIRECTORIES "${SAILFISH_INCLUDE_DIRS}")

file( GLOB LIB_SOURCES libgato/*.cpp )
file( GLOB LIB_HEADERS libgato/*.h )
add_library( LIBGATO ${LIB_SOURCES} ${LIB_HEADERS} )

qt5_use_modules(harbour-angelfish Qml Core Quick Sql)
qt5_use_modules(LIBGATO Core)

target_link_libraries(harbour-angelfish ${SAILFISH_LDFLAGS} ${BLUEZ_LDFLAGS} LIBGATO)

install(TARGETS harbour-angelfish
RUNTIME DESTINATION bin)

install(DIRECTORY qml
DESTINATION share/harbour-angelfish)

install(DIRECTORY translations
DESTINATION share/harbour-angelfish
FILES_MATCHING PATTERN "*.qm")

install(FILES harbour-angelfish.desktop
DESTINATION share/applications)

install(FILES harbour-angelfish.png
DESTINATION share/icons/hicolor/86x86/apps)
