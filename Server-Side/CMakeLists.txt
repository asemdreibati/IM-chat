project(IMChat LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt6 6.9.2 COMPONENTS Core Gui Widgets Network REQUIRED)
add_executable(SimpleChatServer WIN32
    chatserver.cpp
    servermain.cpp
    serverworker.cpp
    serverwindow.cpp
    chatserver.h
    serverworker.h
    serverwindow.h
    serverwindow.ui
)

target_link_libraries(SimpleChatServer PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)
set_target_properties(SimpleChatServer PROPERTIES
	AUTOMOC ON
	AUTOUIC ON
        CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	VERSION "1.0.0"
)

