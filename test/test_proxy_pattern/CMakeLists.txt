file(GLOB test_proxy_pattern_SRCS *.cc
							 ${PROJECT_SOURCE_DIR}/3rdparty/gtest/src/gtest-all.cc
							 ${PROJECT_SOURCE_DIR}/3rdparty/gtest/src/gtest_main.cc)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty ${PROJECT_SOURCE_DIR}/3rdparty/gtest, ../)

if (MSVC)
link_directories(${LIBRARY_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/)
endif (MSVC)

add_executable(proxy_pattern_unittest ${test_proxy_pattern_SRCS})
target_link_libraries(proxy_pattern_unittest simcc_static ${DEPENDENT_LIBRARIES})

include (CTest)
add_test(NAME proxy_pattern_unittest COMMAND proxy_pattern_unittest)
