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

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

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
			   "views/bottom_view.h"
			   "views/bottom_view.cpp"
			   "views/g1b_view.h"
			   "views/g1b_view.cpp"
			   "views/reglo_icc_view.h"
			   "views/reglo_icc_view.cpp"
			   "views/upper_view.h"
			   "views/upper_view.cpp"
			   "widgets/buttons.h" 
			   "widgets/buttons.cpp"
			   "widgets/color.h"
			   "widgets/combo_box.h" 
			   "widgets/combo_box.cpp"
			   "widgets/font.h" 
			   "widgets/label.h"
			   "widgets/label.cpp"
			   "widgets/line_edit.h"
			   "widgets/line_edit.cpp"
			   "widgets/menu.h"
			   "widgets/menu.cpp"
			   "widgets/msg_subwindow.h"
			   "widgets/msg_subwindow.cpp"
			   "widgets/pump_channel.h"
			   "widgets/pump_channel.cpp"
			   "widgets/tab.h"
			   "widgets/tab.cpp")

set(MET_IMAGES ${./images/})
target_include_directories(MCUControllerCPP PRIVATE MET_IMAGES)

target_link_libraries(MCUControllerCPP
					  Qt6::Widgets
					  Qt6::Core
					  Qt6::Gui)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MCUControllerCPP PROPERTY CXX_STANDARD 20)
endif()
