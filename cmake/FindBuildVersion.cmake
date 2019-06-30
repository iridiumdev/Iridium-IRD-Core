if("${PROJECT_VERSION_TWEAK}" STREQUAL "")
    find_package(Git QUIET)
    if(COMMIT_ID_IN_VERSION AND Git_FOUND)
      execute_process(
        COMMAND git log -1 --format=%h # Get latest git commit short hash
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE COMMIT_ID
        OUTPUT_STRIP_TRAILING_WHITESPACE)
        set(PROJECT_VERSION_TWEAK ${COMMIT_ID})
    else()
      set(PROJECT_VERSION_TWEAK "unknown")
    endif()
endif()

set(VERSION "${PROJECT_VERSION} (${PROJECT_VERSION_TWEAK}) ${CMAKE_BUILD_TYPE}")
set(COMMIT_ID ${PROJECT_VERSION_TWEAK})
set(VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(GIT_REVISION ${PROJECT_VERSION_TWEAK})

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/version/version.h")

add_custom_target(version ALL)
