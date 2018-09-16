
INCLUDE_DIRECTORIES(
    ${MDUILIB_HOME_DIR}
    ${MDUILIB_HOME_DIR}/WindowXX
)

#	Windows
set(	WINDOWS_HEADERS
	Windows/WinXXWindow.hpp
	Windows/Win7OrPlusWindow.hpp
)
set(	WINDOWS_SOURCES
	Windows/WinXXWindow.cpp
	Windows/Win7OrPlusWindow.cpp
)

SOURCE_GROUP("Windows" FILES
	${WINDOWS_HEADERS}
	${WINDOWS_SOURCES}
)

#	Graphics
set(	GRAPHICS_HEADERS
	Graphics/Win7OrPlusRenderSystem.hpp
)
set(	GRAPHICS_SOURCES
	Graphics/Win7OrPlusRenderSystem.cpp
)

SOURCE_GROUP("Graphics" FILES
	${GRAPHICS_HEADERS}
	${GRAPHICS_SOURCES}
)

#	Runtime
set(	RUNTIME_HEADERS
	Runtime/WindowXXApplication.hpp
)
set(	RUNTIME_SOURCES
	Runtime/WindowXXApplication.cpp
)

SOURCE_GROUP("Runtime" FILES
	${RUNTIME_HEADERS}
	${RUNTIME_SOURCES}
)

set(	WINDOWXX_HEADERS
	${WINDOWS_HEADERS}
	${GRAPHICS_HEADERS}
	${RUNTIME_HEADERS}
)
set(	WINDOWXX_SOURCES
	${WINDOWS_SOURCES}
	${GRAPHICS_SOURCES}
	${RUNTIME_SOURCES}
)

add_executable(WindowXX
	${WINDOWXX_HEADERS}
	${WINDOWXX_SOURCES}
)
target_link_libraries(WindowXX Framework)