cmake_minimum_required(VERSION 3.10)

project(MessageHandlerProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(MessageHandlerLib message_handler.cpp)

add_executable(MyExecutable main.cpp)
target_link_libraries(MyExecutable MessageHandlerLib)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(MyTests message_handler_test.cpp)
target_compile_definitions(MyTests PRIVATE UNIT_TEST)
target_link_libraries(MyTests MessageHandlerLib ${GTEST_LIBRARIES} pthread)

include(CPack)

set(CPACK_PACKAGE_NAME "MyProject")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_GENERATOR "ZIP")

install(TARGETS MyExecutable DESTINATION bin)
install(TARGETS MyTests DESTINATION bin)
