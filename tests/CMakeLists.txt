
include_directories(../src ../ext/googletest/include)
add_executable(kiwi-routing-test kiwi/routing/base.cc kiwi/routing/rule.cc)
target_link_libraries(kiwi-routing-test kiwi-routing gtest gtest_main boost_regex-mt)

add_test(kiwi-routing-test kiwi-routing-test)
