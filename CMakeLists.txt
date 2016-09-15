# cmake_minimum_required(VERSION 2.8.11)
# 2.8.11 required for Qt5 build but travis uses 2.8.7 on osx
cmake_minimum_required(VERSION 2.8)
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    # WARNING
else()
    cmake_policy(SET CMP0020 NEW)
endif (CMAKE_VERSION VERSION_LESS 2.8.11)


project(QtSupercast)
set (SUPERCAST_VERSION_MAJOR "1")
set (SUPERCAST_VERSION_MINOR "1")
set (SUPERCAST_VERSION_PATCH "0")


add_subdirectory (deps/qjson)

set (SUPERCAST_SRC
    code/supercast.cpp
    code/supercast.h
    code/supercasthttp.cpp
    code/supercasthttp.h
    code/supercasthttpreply.cpp
    code/supercasthttpreply.h
    code/supercasthttprequest.cpp
    code/supercasthttprequest.h
    code/supercastsignal.cpp
    code/supercastsignal.h
    code/supercast_consts.h)

# dependencies
set (SUPERCAST_DEPS_INCLUDES  "")
set (SUPERCAST_DEPS_LIBRARIES "")

# qt
set (SUPERCAST_QT_LIBRARIES "")
set (SUPERCAST_QT_INCLUDES "")

find_package(Qt4 QUIET)

if (QT4_FOUND)

    message(STATUS "QtWebsockets not supported. Fallback to TCP.")
    find_package (Qt4 REQUIRED QtCore QtNetwork)
    include (${QT_USE_FILE})
    set (SUPERCAST_QT_INCLUDES
        ${Qt4Core_INCLUDE_DIRS}
        ${Qt4Network_INCLUDE_DIRS})

    set (SUPERCAST_SRC ${SUPERCAST_SRC}
        code/supercastsocket.cpp
        code/supercastsocket.h)

    set (SUPERCAST_QT_LIBRARIES ${QT_LIBRARIES})

else()

    find_package(Qt5Core REQUIRED)
    find_package(Qt5Network REQUIRED)
    set (SUPERCAST_QT_INCLUDES
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Network_INCLUDE_DIRS})
    set (SUPERCAST_QT_LIBRARIES
        Qt5::Core
        Qt5::Network)

    # Use websocket if available
    find_package(Qt5WebSockets QUIET)

    if (Qt5WebSockets_FOUND)

        message(STATUS "QtWebsockets found.")
        add_definitions(-DUSE_WEBSOCKET)
        find_package(Qt5Websockets REQUIRED)
        set (SUPERCAST_QT_INCLUDES
            ${SUPERCAST_QT_INCLUDES}
            ${Qt5WebSockets_INCLUDE_DIRS})
        set(SUPERCAST_QT_LIBRARIES
            ${SUPERCAST_QT_LIBRARIES}
            Qt5::WebSockets)
        set (SUPERCAST_SRC
            ${SUPERCAST_SRC}
            code/supercastwebsocket.cpp
            code/supercastwebsocket.h)

    else()

        message(STATUS "QtWebsockets not supported. Fallback to TCP.")
        set (SUPERCAST_SRC
            ${SUPERCAST_SRC}
            code/supercastsocket.cpp
            code/supercastsocket.h)

    endif (Qt5WebSockets_FOUND)

endif(QT4_FOUND)

include_directories (
    code/
    deps/qjson/
    ${SUPERCAST_QT_INCLUDES})
add_library(supercast ${SUPERCAST_SRC})
target_link_libraries(supercast ${SUPERCAST_QT_LIBRARIES} qjson)
