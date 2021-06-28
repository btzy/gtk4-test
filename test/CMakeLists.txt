find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

# Define the library
add_executable(test "test.cpp")

target_include_directories(test PRIVATE ${GTK_INCLUDE_DIRS})
target_link_libraries(test PRIVATE ${GTK_LIBRARIES})
