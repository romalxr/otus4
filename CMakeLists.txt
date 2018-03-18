cmake_minimum_required(VERSION 3.2.2)

if (NOT "$ENV{TRAVIS_BUILD_NUMBER}" STREQUAL "")
    project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(print_ip VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 14)

configure_file(version.h.in version.h)

add_executable(print_ip print_ip.cpp)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT cowwwboy@ya.ru)
include(CPack)