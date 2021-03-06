cmake_minimum_required(VERSION 2.8.2)

project(GEN_labo_5)

include(CTest)

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# When using CMake 2.8.11 or later, header path dependencies
# are automatically added to the gtest and gmock targets.
# For earlier CMake versions, we have to explicitly add the
# required directories to the header search path ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()
#
## Trivial example using gtest and gmock
add_executable(CustomerTest CustomerTest.cpp PriceCode.h)
target_link_libraries(CustomerTest gtest gmock_main)
add_test(NAME Customer_test_mock COMMAND CustomerTestMock)
add_test(NAME Customer_test_empty COMMAND CustomerTestEmpty)
#
## Trivial example using gtest and gmock
add_executable(PriceCodeTest PriceCodeTest.cpp)
target_link_libraries(PriceCodeTest gtest gmock_main)
add_test(NAME Regular_test_getAmount COMMAND RegularTestAmount)
add_test(NAME Childrens_test_getAmount COMMAND ChildrensTestAmount)
add_test(NAME NewRelease_test_getAmount COMMAND NewReleaseTestAmount)
add_test(NAME Regular_test_bonus COMMAND RegularTestBonus)
add_test(NAME Childrens_test_bonus COMMAND ChildrensTestBonus)
add_test(NAME NewRelease_test_bonus COMMAND NewReleaseTestBonus)

add_executable(main main.cpp)
target_link_libraries(main gtest gmock_main)
