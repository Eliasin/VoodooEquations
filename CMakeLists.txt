cmake_minimum_required(VERSION 3.5.1)
project(DT3)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)

	file(GLOB_RECURSE INCLUDE_DEPENDENCIES
		"include/boost/spirit/include/*.hpp"
		"include/boost/fusion/include/*.hpp"
		"include/boost/phoenix/include/*.hpp"
		)

	file(GLOB INCLUDE_DEPENDENCIES
		"include/boost/*.hpp"
		)

elseif(LINUX)

	find_package(Boost)

	if (Boost_FOUND)
		include_directories(${Boost_INCLUDE_DIRS})
		target_link_libraries(DT3 ${Boost_LIBRARIES})
	endif()

endif()

set(SOURCE_FILES main.cpp)

include_directories(include)

add_executable(DT3 ${SOURCE_FILES} ${INCLUDE_DEPENDENCIES})
