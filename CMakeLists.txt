CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (thumbnailviewer)

SET (CMAKE_AUTOMOC ON)
SET (CMAKE_AUTOUIC ON)
SET (CMAKE_CXX_STANDARD 11)

SET (SRC_DIR src)
SET (INCLUDE_DIR include)

SET (SOURCES
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/MainWindow.cpp
        ${SRC_DIR}/ThumbnailView.cpp
        ${SRC_DIR}/ThumbnailModel.cpp)

SET (HEADERS
        ${INCLUDE_DIR}/MainWindow.h
        ${INCLUDE_DIR}/ThumbnailView.h
        ${INCLUDE_DIR}/ThumbnailModel.h)

INCLUDE_DIRECTORIES (${INCLUDE_DIR})

FIND_PACKAGE (Qt5 COMPONENTS Widgets Concurrent)

IF (Apple)
    SET (CMAKE_OSX_ARCHITECTURES "x86_64;i386")
ENDIF (Apple)

ADD_EXECUTABLE (thumbnailviewer WIN32 ${SOURCES} ${HEADERS})
TARGET_LINK_LIBRARIES (thumbnailviewer Qt5::Widgets Qt5::Concurrent)
