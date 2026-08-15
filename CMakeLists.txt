# This CMake file derives from the one provided by wxWidgets
# in the minimal sample directory.

# Declare the minimum required CMake version
cmake_minimum_required(VERSION 3.10.0)

# Name the project
project(HexRay VERSION 0.1.0)

# Define wxWidgets environment variables.
# WXWIN: the wxWidgets sources root directory
# WXCFG: the build sub-directory of $WXWIN\lib
#        specifying the compiler and library type (static or dynamic)
#
# in VS Code the better way is to define them in cmake.environment settings
# as Workspace Environment variables.
# In this way, you can specify a wxWidgets release at Workspace basis.
#
# It is possible to override Workspace settings uncommenting the 2 lines below:
#set(ENV{WXWIN} /path/tp/wxWidgets/sources/root/directory)
#set(ENV{WXCFG} gcc_lib/mswu)

# Request the required wxWidgets libs
find_package(wxWidgets COMPONENTS core base)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

# Define the list of source files for the project
set(SRC_FILES
    main.cpp
    gui.cpp
    )
if(WIN32)
    # Include a RC file for windows
    list(APPEND SRC_FILES resources/sample.rc)
endif()

# Define the build target for the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
