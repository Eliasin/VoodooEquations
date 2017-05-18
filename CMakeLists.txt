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

set(SOURCE_FILES src/main.cpp src/linsys/systemparts.h src/linsys/systemparts.cpp src/linsys/linearsystem.h src/linsys/session.h src/linsys/parser.h src/linsys/linearsystem.cpp src/linsys/session.cpp src/menu/menu.cpp src/menu/menu.h src/menu/displayMenuOption.cpp src/menu/displayMenuOption.hpp src/menu/createRandomSystemsMenuOption.hpp src/menu/createRandomSystemsMenuOption.cpp src/menu/quitMenuOption.hpp src/menu/quitMenuOption.cpp src/menu/deferringmenuoption.cpp src/menu/deferringmenuoption.h)

if(CYGWIN)

	include_directories(include src)

else()

	include_directories(src)

endif()


add_executable(DT3 ${SOURCE_FILES} ${INCLUDE_DEPENDENCIES})
