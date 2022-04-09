cmake_minimum_required(VERSION 3.22)

project(cmake-template)

add_executable(${PROJECT_NAME})

add_subdirectory(lib)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(resources)

if( WIN32 ) 
    # dosnt work on linux from package manager (need to manualy compile dynamic lib)...
    set (SFML_STATIC_LIBRARIES TRUE)
    set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")
endif()

find_package (SFML 2.5 COMPONENTS graphics REQUIRED)

if( WIN32 ) 
    # sfml-main - is windows only 
    set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
    target_link_libraries (${PROJECT_NAME}sfml-graphics sfml-main)
else()
    set_target_properties (sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
    target_link_libraries (${PROJECT_NAME} sfml-graphics)
endif()

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++20")
