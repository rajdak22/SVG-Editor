cmake_minimum_required(VERSION 3.16)

project(cop290_raj VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp

        model/graphics_object.h
        model/graphics_object.cpp

        model/line.h
        model/line.cpp

        model/circle.h
        model/circle.cpp

        model/rectangle.h
        model/rectangle.cpp

        model/rounded_rectangle.h
        model/rounded_rectangle.cpp

        model/hexagon.h
        model/hexagon.cpp

        model/text.h
        model/text.cpp

        model/polyline.h
        model/polyline.cpp

        model/diagram.h
        model/diagram.cpp

        parser/svg_parser.h
        parser/svg_parser.cpp

        gui/mainwindow.h
        gui/mainwindow.cpp

        gui/canvas.h
        gui/canvas.cpp

        gui/tools/tool.h

        gui/tools/select_tool.h
        gui/tools/select_tool.cpp

        gui/tools/rectangle_tool.h
        gui/tools/rectangle_tool.cpp

        gui/tools/circle_tool.h
        gui/tools/circle_tool.cpp

        gui/tools/line_tool.h
        gui/tools/line_tool.cpp

        gui/tools/rounded_rectangle_tool.h
        gui/tools/rounded_rectangle_tool.cpp

        gui/tools/hexagon_tool.h
        gui/tools/hexagon_tool.cpp

        gui/tools/polyline_tool.h
        gui/tools/polyline_tool.cpp

        gui/tools/text_tool.h
        gui/tools/text_tool.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(cop290_raj
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET cop290_raj APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(cop290_raj SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(cop290_raj
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(cop290_raj PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.cop290_raj)
endif()
# set_target_properties(cop290_raj PROPERTIES
#     ${BUNDLE_ID_OPTION}
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

include(GNUInstallDirs)
install(TARGETS cop290_raj
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(cop290_raj)
endif()
