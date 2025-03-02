add_library(animal SHARED
    animal.cpp
)
# Add symbol export definitions
target_compile_definitions(animal PRIVATE BUILDING_ANIMAL)
# Specify include directories
target_include_directories(animal PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Install the shared library to lib directory
install(TARGETS animal
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

add_subdirectory(lion)



add_executable(main_pipeline 
    main_pipeline.cpp
)
target_link_libraries(main_pipeline PRIVATE
    yaml-cpp
    animal
    ${CMAKE_DL_LIBS}  # Add dlopen support
    ${LTDL_LIBRARY}
)