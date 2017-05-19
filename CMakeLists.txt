cmake_minimum_required(VERSION 3.5.1)
project(DT3)

set(CMAKE_CXX_STANDARD 14)

if (CYGWIN)

	file(GLOB_RECURSE INCLUDE_DEPENDENCIES
		"include/boost/spirit/include/*.hpp"
		"include/boost/fusion/include/*.hpp"
		"include/boost/phoenix/include/*.hpp"
		)

	file(GLOB INCLUDE_DEPENDENCIES
		"include/boost/*.hpp"
		)

endif()

file(GLOB_RECURSE SOURCE_FILES
	"src/*"
	)

if(CYGWIN)

	include_directories(include src)

else()

	include_directories(src)

endif()


add_executable(DT3 ${SOURCE_FILES} ${INCLUDE_DEPENDENCIES})
