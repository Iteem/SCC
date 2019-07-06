cmake_minimum_required( VERSION 2.8 )

project( LexThree )

# extlibs
set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH} )
find_package( SFML 2 REQUIRED system window graphics network audio )
find_package( Thor REQUIRED )
find_package( Boost REQUIRED )
find_package( ZLIB REQUIRED )
include_directories( ${SFML_INCLUDE} ${THOR_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS} )

# Source files
set( SRC_DIR "${PROJECT_SOURCE_DIR}/src/" )
set( INC_DIR "${PROJECT_SOURCE_DIR}/include/" )
include_directories( ${INC_DIR} )

set( SOURCES
	${SRC_DIR}/button.cpp
	${SRC_DIR}/enemy.cpp
	${SRC_DIR}/game.cpp
	${SRC_DIR}/gamestate.cpp
	${SRC_DIR}/main.cpp
	${SRC_DIR}/map.cpp
	${SRC_DIR}/menustate.cpp
	${SRC_DIR}/shared.cpp
	${INC_DIR}/button.hpp
	${INC_DIR}/enemy.hpp
	${INC_DIR}/game.hpp
	${INC_DIR}/gamestate.hpp
	${INC_DIR}/menustate.hpp
	${INC_DIR}/map.hpp
	${INC_DIR}/shared.hpp
	${INC_DIR}/state.hpp
)

# GCC
if( CMAKE_COMPILER_IS_GNUCXX )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wno-unused-local-typedefs" )
endif()

add_executable( ${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries( ${CMAKE_PROJECT_NAME} ${SFML_LIBRARIES} ${THOR_LIBRARY} ${Boost_LIBRARIES} ${ZLIB_LIBRARIES} )

# Copy data directory to build cache directory to be able to run examples from
# there. Useful for testing stuff.
add_custom_target(
	export_files
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/data" "${PROJECT_BINARY_DIR}/data"
)
