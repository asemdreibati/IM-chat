project(IMChat LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt6 6.9.2 COMPONENTS Core Gui Widgets Network REQUIRED)
add_executable(SimpleChatClient WIN32
    clientmain.cpp
    chatwindow.cpp
    chatclient.cpp
    chatwindow.ui
    chatwindow.h
    chatclient.h
	chatwithone.h
	chatwithone.cpp
	chatwithone.ui
	chatwithgroup.h
	chatwithgroup.cpp
	chatwithgroup.ui
	chat.h
)

target_link_libraries(SimpleChatClient PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)
set_target_properties(SimpleChatClient PROPERTIES
	AUTOMOC ON
	AUTOUIC ON
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	VERSION "1.0.0"
)

