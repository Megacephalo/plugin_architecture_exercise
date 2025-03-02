add_library(lion SHARED
    lion.cpp
)

target_include_directories(lion
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(lion
    PUBLIC animal
)
