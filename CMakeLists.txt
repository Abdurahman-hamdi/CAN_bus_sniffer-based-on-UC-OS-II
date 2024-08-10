

cmake_minimum_required(VERSION 3.22) ## set the required cmake version
set(CMAKE_SYSTEM_NAME Generic) ##cross compilaion process
set(CMAKE_C_COMPILER arm-none-eabi-gcc CACHE STRING "C compiler" FORCE) #define C compiler
set(CMAKE_OBJCOPY arm-none-eabi-objcopy CACHE STRING "arm-none-eabi-objcopy" FORCE)# define objcpy tool
project( CAN_BUS_SNIFFER)