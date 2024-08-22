cmake_minimum_required (VERSION 2.8.12)

# set the build type
if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug build.")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  message("Release build.")
endif()

# set search path for CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)


# include OpenOCD module, but make it not required
find_package(Openocd)

# Project specific settings
set(application_name "CAN_bus_sniffer")

project (${application_name} C CXX ASM)

# Speed of external resonator
set(HSE_VALUE 8000000)

# Used linker file (just for testing)
get_filename_component(LINKER_SCRIPT stm32f4_flash.ld ABSOLUTE)

# Use LTO? WARNING: This might break the code
#set(ADDITIONAL_CORE_FLAGS -flto)

# OpenOCD config file
get_filename_component(OPENOCD_CONFIG tools/stm32f4discovery.cfg ABSOLUTE)

# add libraries
add_subdirectory(LIB/STM32F4xx_StdPeriph_Driver)

# add main project
add_subdirectory(SRS)