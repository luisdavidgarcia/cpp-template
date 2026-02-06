cmake_minimum_required(VERSION 3.28)
project(cpp_template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Optional build type default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# ─── Feature toggles ──────────────────────────────────────
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" OFF)

# ─── Glob source/header files ─────────────────────────────
file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS include/*.hpp)
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

# Filter out main.cpp from ALL_SOURCES for core library
list(FILTER ALL_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

# ─── Output directories ───────────────────────────────────
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# ─── Compiler and linker flags ────────────────────────────
set(COMMON_COMPILE_FLAGS -Wall -Wextra -pedantic -fno-omit-frame-pointer)
set(SANITIZER_FLAGS "")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(ENABLE_ASAN AND ENABLE_TSAN)
        message(FATAL_ERROR "ENABLE_ASAN and ENABLE_TSAN cannot be enabled at the same time.")
    elseif(ENABLE_ASAN)
        list(APPEND SANITIZER_FLAGS "-fsanitize=address")
    elseif(ENABLE_TSAN)
        list(APPEND SANITIZER_FLAGS "-fsanitize=thread")
    endif()

    if(ENABLE_UBSAN)
        list(APPEND SANITIZER_FLAGS "-fsanitize=undefined")
    endif()
endif()

# ─── Targets ───────────────────────────────────────────────
add_library(core ${ALL_SOURCES} ${PROJECT_HEADERS})
target_include_directories(core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_options(core PRIVATE ${COMMON_COMPILE_FLAGS} ${SANITIZER_FLAGS})
target_link_options(core PRIVATE ${SANITIZER_FLAGS})

# Build the application executable from main.cpp
add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE core)
target_compile_options(app PRIVATE ${COMMON_COMPILE_FLAGS} ${SANITIZER_FLAGS})
target_link_options(app PRIVATE ${SANITIZER_FLAGS})

# Test runner
enable_testing()
find_package(Catch2 REQUIRED)

add_executable(run_tests ${TEST_SOURCES})
target_include_directories(run_tests PRIVATE ${CATCH_INCLUDE_DIR})
target_link_libraries(run_tests PRIVATE core Catch2::Catch2WithMain)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_link_libraries(run_tests PRIVATE ${SANITIZER_FLAGS})
endif()

add_test(NAME Catch2Tests COMMAND run_tests)

# ─── clang-format ──────────────────────────────────────────
find_program(CLANG_FORMAT_EXE clang-format)
if(CLANG_FORMAT_EXE)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -style=file -i ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${TEST_SOURCES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running clang-format on project files..."
    )
else()
    message(WARNING "clang-format not found. 'format' target will not be available.")
endif()

# ─── clang-tidy ────────────────────────────────────────────
find_program(CLANG_TIDY_EXE clang-tidy)
if(CLANG_TIDY_EXE)
    add_custom_target(lint
        COMMAND ${CLANG_TIDY_EXE} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${TEST_SOURCES}
                --extra-arg="-std=c++23"
                -p=${CMAKE_BINARY_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running clang-tidy on project files..."
    )
else()
    message(WARNING "clang-tidy not found. 'lint' target will not be available.")
endif()
