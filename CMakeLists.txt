cmake_minimum_required(VERSION 3.10)
project(DatabaseManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/database.cpp
    src/table.cpp
    src/index.cpp
    src/query_executor.cpp
    src/transaction_manager.cpp
    src/storage_engine.cpp
)

# Create executable
add_executable(database_manager ${SOURCES})

# Link filesystem library (needed for C++17)
target_link_libraries(database_manager stdc++fs)

# Compiler flags
if(MSVC)
    target_compile_options(database_manager PRIVATE /W4)
else()
    target_compile_options(database_manager PRIVATE -Wall -Wextra -pedantic)
endif()
