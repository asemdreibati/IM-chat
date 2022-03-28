project(IMChat LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 5.7 COMPONENTS Core Gui Widgets Network REQUIRED)
add_executable(SimpleChatClient WIN32
    clientmain.cpp
    chatwindow.cpp
    chatclient.cpp
    chatwindow.ui
    chatwindow.h
    chatclient.h
)
target_link_libraries(SimpleChatClient PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)
#target_compile_definitions(SimpleChatClient PRIVATE QT_NO_CAST_FROM_ASCII)
set_target_properties(SimpleChatClient PROPERTIES
	AUTOMOC ON
	AUTOUIC ON
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED ON
	VERSION "1.0.0"
)

