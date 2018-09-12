
INCLUDE_DIRECTORIES(
    ${MDUILIB_HOME_DIR}
    ${MDUILIB_HOME_DIR}/WindowXX
)

#	Windows
set(	WINDOWS_HEADERS
	Windows/WinXXWindow.hpp
)
set(	WINDOWS_SOURCES
	Windows/WinXXWindow.cpp
)

SOURCE_GROUP("Windows" FILES
	${WINDOWS_HEADERS}
	${WINDOWS_SOURCES}
)


add_executable(WindowXX
    ${WINDOWS_HEADERS}
	${WINDOWS_SOURCES}
	WindowXXApplication.hpp
    WindowXXApplication.cpp
)
target_link_libraries(WindowXX Framework)