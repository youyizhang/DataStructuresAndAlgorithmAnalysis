cmake_minimum_required(VERSION 3.20)
project(DataStructure_MarkAllenWeiss)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCE_FILE
        include/dsexceptions.h
        include/Vector.hpp
        include/List.hpp
        include/QuadraticProbing.hpp
        )

set(BinarySearchTree include/BinarySearchTree.hpp src/TestBSTree.cpp)
set(AVLTree include/AVLTree.hpp src/TestAVLTree.cpp)
set(SeparateChaining  include/SeparateChaining.hpp src/TestSeparateChaining.cpp)
set(QuadraticProbing include/QuadraticProbing.hpp src/TestQuadraticProbing.cpp)

add_executable(BinarySearchTree ${BinarySearchTree})
add_executable(AVLTree ${AVLTree})
add_executable(SeparateChaining ${SeparateChaining})
add_executable(QuadraticProbing ${QuadraticProbing})
