file(GLOB FILES {FILES} "*.hpp")
set(SUBPATH ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
set(SUBDIRECTORIES "")
#Add all subdirectories 
foreach(VAR ${SUBDIRECTORIES})
	add_subdirectory(${VAR})
endforeach()

if(FILES)
	#Add source files to target
	target_sources("${PROJECT_NAME}" PUBLIC ${FILES})
	
	#Install our source files
	install(FILES ${FILES} DESTINATION ${SUBPATH})
endif()