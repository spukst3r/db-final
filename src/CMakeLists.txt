cmake_minimum_required(VERSION 2.6)

include_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

configure_file (
	"${PROJECT_SOURCE_DIR}/src/lab.h.in"
	"${PROJECT_BINARY_DIR}/src/lab.h"
	)

set(SOURCES main.cpp connectdialog.cpp)
set(HEADERS connectdialog.h)
add_executable(${PROJECT_TITLE} ${SOURCES})
target_link_libraries(${PROJECT_TITLE} ${GTKMM_LIBRARIES})

