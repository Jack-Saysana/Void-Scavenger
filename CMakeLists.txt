cmake_minimum_required(VERSION 3.5)
project(VS)

# Set source and include directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)

# Set output directory for executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Add all .c files in the src directory
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.c)
file(GLOB_RECURSE DLL_FILES ${LIB_DIR}/*.dll)

# Include directories
include_directories(${INCLUDE_DIR})

# Create executable target and add source files
add_executable(VS ${SRC_FILES})

# Check operating system
if(WIN32)
    # Link libraries for Windows
    target_link_libraries(VS
        ${LIB_DIR}/libcglm.a
        ${LIB_DIR}/libengine_win.a
        opengl32
    )


    # Additional libraries for Windows
    find_file(ALUT_DLL_FOUND libalut-0.dll PATHS ${LIB_DIR})
    find_file(GCC_SEH_DLL_FOUND libgcc_s_seh-1.dll PATHS ${LIB_DIR})
    find_file(OPENAL_DLL_FOUND libopenal-1.dll PATHS ${LIB_DIR})
    find_file(STD_CPP_DLL_FOUND libstdc++-6.dll PATHS ${LIB_DIR})
    find_file(WINPTHREAD_DLL_FOUND libwinpthread-1.dll PATHS ${LIB_DIR})
    find_file(VCRUNTIME_DLL_FOUND vcruntime140.dll PATHS ${LIB_DIR})
    find_file(GLFW_DLL_FOUND glfw3.dll PATHS ${LIB_DIR})

    if(NOT VCRUNTIME_DLL_FOUND)
        message(FATAL_ERROR "DLL file vcruntime140.dll not found. Check that the Microsoft Visual Studio C++ Redistributables are installed.")
    endif()

    if(NOT ALUT_DLL_FOUND)
        message(FATAL_ERROR "DLL file libalut-0.dll not found. Check that freealut mingw64 package is installed.")
    endif()

    if(NOT GCC_SEH_DLL_FOUND)
        message(FATAL_ERROR "DLL file libgcc_s_seh-1.dll not found. Check that x86_64 toolchain mingw64 package is installed.")
    endif()

    if(NOT OPENAL_DLL_FOUND)
        message(FATAL_ERROR "DLL file libopenal-1.dll not found. Check that openal mingw64 package is installed.")
    endif()

    if(NOT STD_CPP_DLL_FOUND)
        message(FATAL_ERROR "DLL file libstdc++-6.dll not found. Check that x86_64 toolchain mingw64 package is installed.")
    endif()

    if(NOT WINPTHREAD_DLL_FOUND)
        message(FATAL_ERROR "DLL file libwinpthread-1.dll not found. Check that x86_64 toolchain mingw64 package is installed.")
    endif()

    if (NOT GLFW_DLL_FOUND)
	message(FATAL_ERROR "DLL file glfw3.dll not found. Check that glfw mingw64 package is installed.")
    endif()

# Link found DLL files
target_link_libraries(VS
    ${ALUT_DLL_FOUND}
    ${GCC_SEH_DLL_FOUND}
    ${OPENAL_DLL_FOUND}
    ${STD_CPP_DLL_FOUND}
    ${WINPTHREAD_DLL_FOUND}
    ${VCRUNTIME_DLL_FOUND}
    ${GLFW_DLL_FOUND}
)

else()
    # Link libcglm.a if on Linux (assuming non-Windows is Linux)
    target_link_libraries(VS ${LIB_DIR}/libengine_lin.a)

    # Find and link libglfw.so.3 dynamically
    find_library(GLFW_LIBRARY glfw)
    if(GLFW_LIBRARY)
        target_link_libraries(VS ${GLFW_LIBRARY})
        message(STATUS "Found libglfw.so: ${GLFW_LIBRARY}")
    else()
        message(FATAL_ERROR "libglfw.so not found.")
    endif()

    # Find and link libXrandr.so.2 dynamically
    find_library(XRANDR_LIBRARY Xrandr)
    if(XRANDR_LIBRARY)
        target_link_libraries(VS ${XRANDR_LIBRARY})
        message(STATUS "Found libXrandr.so: ${XRANDR_LIBRARY}")
    else()
        message(FATAL_ERROR "libXrandr.so not found.")
    endif()

    # Find and link libXi.so.6 dynamically
    find_library(XI_LIBRARY Xi)
    if(XI_LIBRARY)
        target_link_libraries(VS ${XI_LIBRARY})
        message(STATUS "Found libXi.so: ${XI_LIBRARY}")
    else()
        message(FATAL_ERROR "libXi.so not found.")
    endif()

    # Find and link libcglm.so dynamically
    find_library(CGLM_LIBRARY cglm)
    if(CGLM_LIBRARY)
        target_link_libraries(VS ${CGLM_LIBRARY})
        message(STATUS "Found libcglm.so: ${CGLM_LIBRARY}")
    else()
        message(FATAL_ERROR "libcglm.so not found.")
    endif()

    # Link libraries for Linux
    target_link_libraries(VS
        GL
        X11
        dl
        m
        pthread
        alut
        openal
    )

endif()

# Copy all the .dll files from the ./lib directory to the ./bin directory after compilation
file(COPY ${DLL_FILES} DESTINATION ${BIN_DIR})

# Set the cmake build to be multi-threaded
if(UNIX)
    # Use multiple threads for GNU Make
    set(CMAKE_MAKE_PROGRAM "$(MAKE)" "-j${nproc}")
elseif(MSVC)
    # Enable parallel builds for Visual Studio
    target_compile_options(VS PRIVATE /MP)
endif()

# Add a custom target to build with parallelism
if (UNIX)
  add_custom_target(full
      COMMAND ${CMAKE_MAKE_PROGRAM} -j VS
  )
endif()

# Add a custom target to run the binary
add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VS
    DEPENDS VS
)
