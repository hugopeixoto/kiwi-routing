cmake_minimum_required(VERSION 2.8)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -DGTEST_HAS_TR1_TUPLE=0")
else()
  SET(CMAKE_CXX_FLAGS "-std=c++11 -DGTEST_HAS_TR1_TUPLE=0")
endif()

project(kiwi-routing)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(ext/googletest)

enable_testing()

add_test(NAME test COMMAND $<TARGET_FILE:kiwi-routing-test>)

