cmake_minimum_required(VERSION 3.19)
project(browser1)

set(CMAKE_CXX_STANDARD 11)
add_compile_definitions(_UNICODE)

include_directories(D:/lib/wxWidgets-3.0.5/include D:/lib/wxWidgets-3.0.5/include/msvc)
link_directories(D:/lib/wxWidgets-3.0.5/lib/vc_x64_lib)

add_executable(browser1 myapp.cpp mainframe.cpp auth.cpp codesource.cpp fileDownloader.cpp parametres.cpp tab.cpp resources.rc)
set_target_properties(browser1 PROPERTIES WIN32_EXECUTABLE TRUE)
if (CMAKE_BUILD_TYPE MATCHES Debug)
target_link_libraries(browser1 wxmsw30ud_core wxbase30ud wxmsw30ud_aui wxbase30ud_net wxmsw30ud_webview)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
target_link_libraries(browser1 wxmsw30u_core wxbase30u wxmsw30u_aui wxbase30u_net wxmsw30u_webview)
endif()