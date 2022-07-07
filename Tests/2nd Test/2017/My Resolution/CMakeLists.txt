cmake_minimum_required(VERSION 3.20)
project(My_Resolution)

set(CMAKE_CXX_STANDARD 14)

add_executable(My_Resolution main.cpp Patient.cpp Patient.h Doctor.cpp Doctor.h Hospital.cpp Hospital.h Test.cpp)
