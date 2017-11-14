include( MunkeiVersionFromGit.cmake )
version_from_git(LOG OFF)
# Get Git tag
execute_process(
        COMMAND           "${GIT_EXECUTABLE}" log --pretty=format:%h -n 1
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        RESULT_VARIABLE   git_result
        OUTPUT_VARIABLE   git_hash
        ERROR_VARIABLE    git_error
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_STRIP_TRAILING_WHITESPACE
)
if( NOT git_result EQUAL 0 )
    message( FATAL_ERROR
            "[MunkeiVersionFromGit] Failed to execute Git: ${git_error}"
            )
endif()

message( STATUS "
Compiling version ${VERSION} hash ${git_hash}
")
set(version "${VERSION}")
set (build "${git_hash}")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in" "${TO}")
