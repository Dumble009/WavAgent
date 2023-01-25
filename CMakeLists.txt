cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(ProjectName WavAgent)
set(LibraryName WavAgent)
set(ExecutableName WavAgentTest)

project(${ProjectName} VERSION 0.1.0)

enable_testing()
add_subdirectory(tests)

file(GLOB_RECURSE LIB_SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS "libsources/*.cpp")

add_library(${LibraryName} ${LIB_SOURCES})

target_include_directories(${LibraryName} PUBLIC "libsources")


if(NOT DEFINED ENV{CIRCLECI})
file(GLOB_RECURSE EXE_SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS "sources/*.cpp")
add_executable(${ExecutableName} ${EXE_SOURCES})

target_include_directories(${ExecutableName} PUBLIC "libsources")
target_link_directories(${ExecutableName} PUBLIC "build")
target_link_libraries(${ExecutableName} WavAgent)

include("C:/MyLib/CMakeModules/deploy.cmake")
deploy_lib("WavAgent" ${ProjectName} ${ProjectName})
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)