# MIT License
# Copyright (c) 2024-2025 Tomáš Mark

# ==============================================================================
# use Static runtime
# ==============================================================================
if(USE_STATIC_RUNTIME)
    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
    endif()
    
    if(UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -pthread")
    endif()
endif()