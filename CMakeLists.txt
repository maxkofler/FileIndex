cmake_minimum_required(VERSION 3.5)

project(FileIndex VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_subdirectory(Indexer)
add_subdirectory(Log)

include_directories(include)
include_directories(Log/include)

include_directories(Indexer/include)

file (GLOB_RECURSE CXX_SOURCES "src/**.cpp")
file (GLOB_RECURSE HEADERS "include/**.h")
file (GLOB_RECURSE UI_FILES "ui/**.ui")

set(PROJECT_SOURCES
		${HEADERS}
		${CXX_SOURCES}
		${UI_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(FileIndex
		MANUAL_FINALIZATION
		${PROJECT_SOURCES}
	)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FileIndex APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
	if(ANDROID)
		add_library(FileIndex SHARED
			${PROJECT_SOURCES}
		)
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
	else()
		add_executable(FileIndex
			${PROJECT_SOURCES}
		)
	endif()
endif()

target_link_libraries(FileIndex PRIVATE Qt${QT_VERSION_MAJOR}::Widgets log indexer)

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(FileIndex)
endif()
