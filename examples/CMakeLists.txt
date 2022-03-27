include_directories(${CMAKE_SOURCE_DIR}/include)
set ( PROJECT_LINK_LIBS libProperty.a )
link_directories(${CMAKE_INSTALL_LIBDIR})


add_executable("Example" "Main.cpp")
target_link_libraries("Example" LINK_PUBLIC  ${PROJECT_NAME} ${PROJECT_LINK_LIBS})
