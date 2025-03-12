project(HCNNG_LIB CXX)

file(GLOB SOURCES "*.cpp")
add_library(HCNNG_LIB STATIC ${SOURCES})

if(OpenMP_CXX_FOUND)
    target_link_libraries(HCNNG_LIB PRIVATE ${OpenMP_CXX_FLAGS})
endif()

target_link_libraries(HCNNG_LIB
    PRIVATE
    Boost::serialization  # 序列化核心库
    Boost::system         # 序列化依赖的系统库
)