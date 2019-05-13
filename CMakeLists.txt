cmake_minimum_required(VERSION 3.14)
project(Chess)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/main.cpp
        src/ChessItems.cpp )

set(HEADER_FILES
        include/ChessItems.h)

set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "C:/SFML-2.5.1/include/")
link_directories("C:/SFML-2.5.1/lib/")


set(YOUR_DIRECTORY "./")
add_executable(Chess ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(Chess PRIVATE ${YOUR_DIRECTORY}/include/)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Chess sfml-graphics-d sfml-window-d sfml-system-d)
endif()