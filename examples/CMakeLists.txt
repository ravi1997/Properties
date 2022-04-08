include_directories(${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/${PROJECT_NAME}/include)
set ( PROJECT_SUB_LINK_LIBS libProperty.a )
link_directories(${CMAKE_INSTALL_LIBDIR})

add_executable("Example" "Main.cpp")
target_link_libraries("Example" LINK_PUBLIC  ${PROJECT_SUB_LINK_LIBS})
