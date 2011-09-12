cmake_minimum_required(VERSION 2.6)
set(PROJECT_TITLE untitled)

project(${PROJECT_TITLE})

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-2.4)

add_subdirectory(src)

