cmake_minimum_required(VERSION 3.0)

project(Custom_Modules)

#Setup libraries
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
                        #project_dir/include
                        #"         "/lib
add_library(FSystem OBJECT
  "${CMAKE_CURRENT_SOURCE_DIR}/File_System_Tools/include/FSystem_Tools.cpp")
add_library(Logging OBJECT
  "${CMAKE_CURRENT_SOURCE_DIR}/Log_Tools/include/Logger.cpp")
add_library(Time OBJECT
  "${CMAKE_CURRENT_SOURCE_DIR}/Misc_Tools/Time_Tools/include/Time_Tools.cpp")
add_library(Thermal OBJECT
  "${CMAKE_CURRENT_SOURCE_DIR}/Misc_Tools/Thermal_Tools/include/Thermal.cpp")

    #Boost uses shared libraries by default
    #Boost_REALPATH is needed to use libs supplied
set(Boost_REALPATH ON)
find_package(Boost COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
    message("Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}\n")
    target_include_directories(FSystem PRIVATE ${Boost_INCLUDE_DIRS})
    set(FSystem_Libs ${Boost_LIBRARIES} PARENT_SCOPE)
endif()

find_package(Boost COMPONENTS system REQUIRED)
if(Boost_FOUND)
    target_include_directories(Logging PRIVATE ${Boost_INCLUDE_DIRS})
    set(Logging_Libs ${Boost_LIBRARIES} PARENT_SCOPE)
endif()
