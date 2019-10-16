if (POLICY CMP0025)
    # Compiler id for Apple Clang is now AppleClang
    cmake_policy(SET CMP0025 NEW)
endif()

if (POLICY CMP0048)
    # The ``project()`` command manages VERSION variables.
    cmake_policy(SET CMP0048 NEW)
endif()

cmake_minimum_required( VERSION 3.10.2 FATAL_ERROR )
project( DECENT VERSION 1.5.0 LANGUAGES CXX )

if( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
    if( CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.1 )
        message( FATAL_ERROR "GCC version must be at least 5.1" )
    endif()
elseif( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
    if( CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5 )
        message( FATAL_ERROR "Clang version must be at least 3.5" )
    endif()
elseif( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
    if( CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.10 )
        message( FATAL_ERROR "MSVC version must be at least 19.10" )
    endif()
endif()

# Compile in C++14 mode
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )
set( CMAKE_EXPORT_COMPILE_COMMANDS YES )

if( WIN32 )
    add_compile_options( /D_WIN32_WINNT=0x0601 /D_CRT_SECURE_NO_WARNINGS )

    if( "${VCPKG_TARGET_TRIPLET}" MATCHES "windows-static" )
        foreach( flag_var FLAGS FLAGS_DEBUG FLAGS_RELEASE FLAGS_MINSIZEREL FLAGS_RELWITHDEBINFO )
            set( cxx_flag_var "CMAKE_CXX_${flag_var}" )
            if(${cxx_flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${cxx_flag_var} "${${cxx_flag_var}}")
            endif()
        endforeach(flag_var)
    endif()
else() # Apple and Linux
    if( APPLE )
        # Apple Specific Options Here
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -Wall" )
    else()
        # Linux Specific Options Here
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )
    endif()

    if( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-builtin-memcmp" )
        if( NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6 )
            set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive" )
        endif()
    endif()

    if( CMAKE_GENERATOR STREQUAL "Ninja" )
        if( CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" )
            set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics" )
        endif()
    endif()
endif()

if(UNIX)
    set(CMAKE_SKIP_RPATH FALSE CACHE INTERNAL "")
    set(CMAKE_SKIP_BUILD_RPATH FALSE CACHE INTERNAL "")
    set(CMAKE_SKIP_INSTALL_RPATH FALSE CACHE INTERNAL "")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE CACHE INTERNAL "")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE CACHE INTERNAL "")
#   set(CMAKE_NO_BUILTIN_CHRPATH TRUE)
    if(APPLE)
        set(CMAKE_INSTALL_RPATH "@executable_path" CACHE INTERNAL "")
        set(CMAKE_MACOSX_RPATH TRUE CACHE INTERNAL "")
#       set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10 CACHE INTERNAL "")
    else()
        set(CMAKE_INSTALL_RPATH "\$ORIGIN" CACHE INTERNAL "")
    endif()
endif()

add_subdirectory(DCore EXCLUDE_FROM_ALL)
add_subdirectory(src)
