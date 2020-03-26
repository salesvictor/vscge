include(${PROJECT_SOURCE_DIR}/cmake/GetGoogleTest.cmake)

add_gtest(test_gtest)
add_gtest(test_vector vs::cge)
add_gtest(test_swizzle vs::cge)
