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
        ${SRC_DIR}/ThumbnailView.cpp)

SET (HEADERS
        ${INCLUDE_DIR}/MainWindow.h
        ${INCLUDE_DIR}/ThumbnailView.h)

INCLUDE_DIRECTORIES (${INCLUDE_DIR})

FIND_PACKAGE (Qt5 COMPONENTS Widgets)

ADD_EXECUTABLE (thumbnailviewer ${SOURCES} ${HEADERS})
TARGET_LINK_LIBRARIES (thumbnailviewer Qt5::Widgets)
