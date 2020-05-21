cmake_minimum_required(VERSION 3.14)

project(libidevices-support C)
find_package(PkgConfig REQUIRED)

include_directories(include)

option(enable_debug "Enable debug code" false)

pkg_check_modules(PLIST REQUIRED IMPORTED_TARGET libplist)

# These are the potential TLS backends - check which are available
pkg_check_modules(GNUTLS REQUIRED IMPORTED_TARGET gnutls)
pkg_check_modules(LIBGCRYPT REQUIRED IMPORTED_TARGET libgcrypt)
pkg_check_modules(LIBUSBMUXD REQUIRED IMPORTED_TARGET libusbmuxd)

# This is the test framework and is not a required module
pkg_check_modules(CRITERION IMPORTED_TARGET criterion)

if(enable_debug)
    add_compile_definitions(DEBUG)
endif()

add_library(libidevices-support src/array src/debug src/socket src/thread src/userpref src/utils)
message("GCrypt ${GCRYPT_INCLUDE_DIRS}")
target_include_directories(libidevices-support PUBLIC ${GNUTLS_INCLUDE_DIRS} ${GCRYPT_INCLUDEDIR} ${LIBUSBMUXD_INCLUDE_DIRS} ${LIBGCRYPT_INCLUDE_DIRS})
target_link_libraries(libidevices-support PUBLIC PkgConfig::PLIST PkgConfig::GNUTLS PkgConfig::LIBGCRYPT)

enable_testing()

add_executable(test_libidevices_support test/array_test)
target_link_libraries(test_libidevices_support PUBLIC libidevices-support PkgConfig::PLIST PkgConfig::CRITERION)
add_test(NAME lib_idevices_tests COMMAND test_libidevices_support)