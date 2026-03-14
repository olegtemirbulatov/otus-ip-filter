cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

# option(WITH_GOOGLE_TEST "Whether to build Google test" ON)

# configure_file(ip_filter.h)

add_executable(ipfilter ip_filter.cpp)

set_target_properties(ipfilter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# target_include_directories(ip_filter
#     PRIVATE "${CMAKE_BINARY_DIR}"
# )

# target_link_libraries(helloworld_cli PRIVATE
#     helloworld
# )

# if (WITH_GOOGLE_TEST)
#     add_subdirectory(googletest)
#     add_executable(test_ip_filter test_ip_filter.cpp)

#     set_target_properties(test_ip_filter PROPERTIES
#         CXX_STANDARD 14
#         CXX_STANDARD_REQUIRED ON
#     )
    
#     target_include_directories(ipfilter
#         PRIVATE "${CMAKE_BINARY_DIR}"
#     )

#     # target_link_libraries(test_ip_filter
#     #     gtest_main
#     #     helloworld
#     # )
# endif()

if (MSVC)
    target_compile_options(ipfilter PRIVATE
        /W4
    )
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    # if(WITH_GOOGLE_TEST)
    #     target_compile_options(test_ip_filter PRIVATE
    #         /W4
    #     )
    # endif()
else ()
    target_compile_options(ipfilter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    # target_compile_options(ip_filter PRIVATE
    #     -Wall -Wextra -pedantic -Werror
    # )
    # if(WITH_GOOGLE_TEST)
    #     target_compile_options(test_ip_filter PRIVATE
    #         -Wall -Wextra -pedantic -Werror
    #     )
    # endif()
endif()

install(TARGETS ipfilter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

# if(WITH_GOOGLE_TEST)
#     enable_testing()
#     add_test(test_ip_filter test_ip_filter)
# endif()