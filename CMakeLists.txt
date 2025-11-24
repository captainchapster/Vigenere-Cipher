cmake_minimum_required(VERSION 3.10)
project(cipher C)

set(CMAKE_C_STANDARD 11)

# Find GTK4
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Include GTK4 headers
include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

# Add your source file(s)
add_executable(cipher src/cipher.c)

# Link GTK4
target_link_libraries(cipher ${GTK4_LIBRARIES})

# Ensure correct compiler flags (GTK4 requires them)
target_compile_options(cipher PRIVATE ${GTK4_CFLAGS_OTHER})
