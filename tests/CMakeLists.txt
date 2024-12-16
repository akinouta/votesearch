
project(HCNNG_TEST CXX)

file(GLOB TEST_SOURCES "*.cpp")
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    
    target_link_libraries(${TEST_NAME} HCNNG_LIB)
    
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${TEST_NAME} ${OpenMP_CXX_FLAGS})
    endif()
endforeach()