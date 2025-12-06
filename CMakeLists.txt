cmake_minimum_required(VERSION 3.0)
# Set up the project
project(sv205_project)
# INDI and OpenCV flags
# Find pkg-config system tool
# We need this tooling
find_package(PkgConfig REQUIRED)
#Now using PkgConfig find libindi
pkg_check_modules(INDI REQUIRED libindi)

# INDI_CFLAGS is now available as INDI_CFLAGS or INDI_CFLAGS_OTHER
message(STATUS "INDI CFLAGS: ${INDI_CFLAGS}")
# And link libindi itself
message(STATUS "INDI LFLAGS: ${INDI_LIBRARIES}")

########### Tutorial one ##############
# --- Split source and header files ---
set(SRC
    indi_sv205.cpp 
)

set(HDR
    indi_sv205.h
)


add_executable(sv205_exe ${SRC})
#add_library(sv205_exe  SHARED ${SRC})
# Add include directories to your target
target_include_directories(sv205_exe PRIVATE ${INDI_INCLUDE_DIRS})
target_link_libraries(sv205_exe PRIVATE ${INDI_LIBRARIES})

# --- Include directories ---
target_include_directories(sv205_exe PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}  # your headers live here
    ${INDI_INCLUDE_DIRS}         # INDI includes
)

# --- Optional: add compile flags from INDI pkg-config ---
target_compile_options(sv205_exe PRIVATE ${INDI_CFLAGS_OTHER})
