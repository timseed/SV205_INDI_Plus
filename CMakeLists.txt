cmake_minimum_required(VERSION 3.0)
# Set up the project
project(sv205_project)
# INDI and OpenCV flags
# Find pkg-config system tool
# We need this tooling
find_package(PkgConfig REQUIRED)
#Now using PkgConfig find libindi
pkg_check_modules(INDI REQUIRED libindi)

if(INDI_FOUND)
    # INDI_CFLAGS is now available as INDI_CFLAGS or INDI_CFLAGS_OTHER
    message(STATUS "INDI CFLAGS: ${INDI_CFLAGS}")
    message(STATUS "INDI CFLAGS_OTHER: ${INDI_CFLAGS_OTHER}")
    # And link libindi itself
    message(STATUS "Lib flags are:" ${INDI_LIBS_OTHER})
    message(STATUS "INDI LFLAGS: ${INDI_LIBRARIES}")
    # Assuming 'PackageName::LibraryName' is the imported target for your library
    # The actual target name may vary, consult the package's documentation or find module
  
endif()

########### Tutorial one ##############
# --- Split source and header files ---
set(SRC
    sv205_main.cpp 
    indi_sv205.cpp 
)

set(HDR
    indi_sv205.h
)


add_executable(sv205 ${SRC} ${HDR})
#add_library(sv205 SHARED ${SRC})
# Add include directories to your target
target_include_directories(sv205 PRIVATE ${INDI_INCLUDE_DIRS})
target_link_libraries(sv205 ${INDI_LIBRARIES}  indidriver)
message(STATUS "Lib set to ${INDI_LIBRARIES}")

# --- Include directories ---
target_include_directories(sv205 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}  # your headers live here
    ${INDI_INCLUDE_DIRS}         # INDI includes
)

# --- Optional: add compile flags from INDI pkg-config ---
target_compile_options(sv205 PRIVATE ${INDI_CFLAGS_OTHER})

# Ensure output is predictable
#set_target_properties(sv205 PROPERTIES
#    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
#    PREFIX "libindi_" 
#    OUTPUT_NAME "sv205"
#)
