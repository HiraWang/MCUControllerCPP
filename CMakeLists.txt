cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project("MCUControllerCPP")

set(CMAKE_PREFIX_PATH $ENV{QTDIR})
# set(QT6_DIR C:/Qt/6.5.3/msvc2019_64/lib/cmake/Qt6)

FIND_PACKAGE(OpenGL REQUIRED)
find_package(Qt6 COMPONENTS Widgets Core Gui OpenGL OpenGLWidgets REQUIRED)

add_executable(MCUControllerCPP)

target_sources(MCUControllerCPP PRIVATE
			   main.cpp
			   MET.rc
			   "main_window.h" 
			   "main_window.cpp"
			   "main_window_ui.h"
			   "utility.h"
			   "utility.cpp" 
			   "devices/device.h"
			   "devices/device.cpp"
			   "devices/g1b.cpp"
			   "devices/reglo_icc.cpp"
			   "views/automation_view.h"
			   "views/automation_view.cpp"
			   "views/bottom_view.h"
			   "views/bottom_view.cpp"
			   "views/g1b_view.h"
			   "views/g1b_view.cpp"
			   "views/pump_channel_view.h"
			   "views/pump_channel_view.cpp"
			   "views/reglo_icc_view.h"
			   "views/reglo_icc_view.cpp"
			   "views/upper_view.h"
			   "views/upper_view.cpp"
			   "widgets/button.h" 
			   "widgets/button.cpp"
			   "widgets/canvas.h"
			   "widgets/canvas.cpp"
			   "widgets/color.h"
			   "widgets/combo_box.h" 
			   "widgets/combo_box.cpp"
			   "widgets/font.h" 
			   "widgets/helper.h"
			   "widgets/helper.cpp"
			   "widgets/label.h"
			   "widgets/label.cpp"
			   "widgets/line_edit.h"
			   "widgets/line_edit.cpp"
			   "widgets/loading.h"
			   "widgets/loading.cpp"
			   "widgets/login_subwindow.h"
			   "widgets/login_subwindow.cpp"
			   "widgets/menu.h"
			   "widgets/menu.cpp"
			   "widgets/msg_subwindow.h"
			   "widgets/msg_subwindow.cpp"
			   "widgets/process_unit.h"
			   "widgets/process_unit.cpp"
			   "widgets/tab.h"
			   "widgets/tab.cpp")

set(MET_IMAGES ${./images/})

target_include_directories(MCUControllerCPP PRIVATE MET_IMAGES)

target_link_libraries(MCUControllerCPP PRIVATE
					  Qt6::Widgets
					  Qt6::Core
					  Qt6::Gui
					  Qt6::OpenGL
					  Qt6::OpenGLWidgets
					  ${OPENGL_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MCUControllerCPP PROPERTY CXX_STANDARD 20)
endif()
