cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(MCUControllerCPP)

set(CMAKE_PREFIX_PATH $ENV{QTDIR})

FIND_PACKAGE(OpenGL REQUIRED)
find_package(Qt6 COMPONENTS Widgets Core Gui Quick OpenGL OpenGLWidgets REQUIRED)

qt_standard_project_setup()

qt_add_executable(MCUControllerCPP
	main.cpp
	MET.rc
	images.qrc
	main_window.h
	main_window.cpp
	main_window_ui.h
	utility.h
	utility.cpp
	devices/device.h
	devices/device.cpp
	devices/due.cpp
	devices/g1b.cpp
	devices/reglo_icc.cpp
	views/automation_view.h
	views/automation_view.cpp
	views/bottom_view.h
	views/bottom_view.cpp
	views/pulse_generator_view.h
	views/pulse_generator_view.cpp
	views/monitor_view.h
	views/monitor_view.cpp
	views/pump_channel_view.h
	views/pump_channel_view.cpp
	views/pump_view.h
	views/pump_view.cpp
	views/upper_view.h
	views/upper_view.cpp
	widgets/button.h
	widgets/button.cpp
	widgets/canvas.h
	widgets/canvas.cpp
	widgets/color.h
	widgets/combo_box.h
	widgets/combo_box.cpp
	widgets/dialog.h
	widgets/dialog.cpp
	widgets/font.h
	widgets/helper.h
	widgets/helper.cpp
	widgets/label.h
	widgets/label.cpp
	widgets/lcd.h
	widgets/lcd.cpp
	widgets/line_edit.h
	widgets/line_edit.cpp
	widgets/loading.h
	widgets/loading.cpp
	widgets/login_subwindow.h
	widgets/login_subwindow.cpp
	widgets/menu.h
	widgets/menu.cpp
	widgets/msg_subwindow.h
	widgets/msg_subwindow.cpp
	widgets/process_unit.h
	widgets/process_unit.cpp
	widgets/slider.h
	widgets/slider.cpp
	widgets/tab.h
	widgets/tab.cpp
	widgets/text_edit.h
	widgets/text_edit.cpp
	widgets/tree.h
	widgets/tree.cpp)

qt_add_qml_module(MCUControllerCPP
    URI QmlSource
    VERSION 1.0
    QML_FILES splash_screen.qml
	RESOURCES images.qrc
)

set(MET_IMAGES ${./images/})

target_include_directories(MCUControllerCPP PRIVATE MET_IMAGES)

target_link_libraries(MCUControllerCPP PRIVATE
					  Qt6::Widgets
					  Qt6::Core
					  Qt6::Gui
					  Qt6::Quick
					  Qt6::OpenGL
					  Qt6::OpenGLWidgets
					  ${OPENGL_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MCUControllerCPP PROPERTY CXX_STANDARD 20)
endif()
