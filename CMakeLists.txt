cmake_minimum_required(VERSION 3.20)
project(lofmi)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCE
    main.cpp
    ${SOURCE_DIR}/truth_table.cpp
    ${SOURCE_DIR}/elem_oper.cpp
    ${SOURCE_DIR}/normal_form.cpp
    ${SOURCE_DIR}/gray_code.cpp
    ${SOURCE_DIR}/karnaugh_map.cpp
    ${SOURCE_DIR}/karnaugh_minimization.cpp
    ${SOURCE_DIR}/karnaugh_area.cpp
)

add_executable(main ${SOURCE})

find_package(Boost REQUIRED)

if(${Boost_FOUND})
    target_include_directories(main PUBLIC ${Boost_INCLUDE_DIRS})
endif()

target_include_directories(
    main PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
