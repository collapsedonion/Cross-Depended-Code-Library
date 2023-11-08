cmake_minimum_required(VERSION 3.25)
project(CDC)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)


if(APPLE)
	add_definitions(-Dunix=true)
	if ((${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm64"))
		enable_language(C ASM)
		add_library(CDC STATIC ${PROJECT_SOURCE_DIR}/cdc.h ${PROJECT_SOURCE_DIR}/cdc.c ${PROJECT_SOURCE_DIR}/cdc_asm_arm64.S)
	elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
		enable_language(C ASM)
		add_library(CDC STATIC ${PROJECT_SOURCE_DIR}/cdc.h ${PROJECT_SOURCE_DIR}/cdc.c ${PROJECT_SOURCE_DIR}/cdc_asm_gnu.S)
	endif()


endif()

if(WIN32)
	add_definitions(-DWIN32=true)
	enable_language(C ASM)
	add_library(CDC STATIC ${PROJECT_SOURCE_DIR}/cdc.h ${PROJECT_SOURCE_DIR}/cdc.c ${PROJECT_SOURCE_DIR}/cdc_asm_gnu.S)
endif()

if(LINUX)
	add_definitions(-Dunix)
	enable_language(C ASM)
	add_definitions(-Dlinux)
	add_library(CDC STATIC ${PROJECT_SOURCE_DIR}/cdc.h ${PROJECT_SOURCE_DIR}/cdc.c ${PROJECT_SOURCE_DIR}/cdc_asm_gnu.S)
endif()