INCLUDE_DIRECTORIES(
	${MDUILIB_HOME_DIR}
	${MDUILIB_HOME_DIR}/Framework
)

#	Common
set(	COMMON_HEADERS
	Common/MDUILibAfx.hpp
)
set(	COMMON_SOURCES
	Common/main.cpp
)

#	Common/Core
set(	COMMON_CORE_HEADERS
	Common/Core/Events.hpp
	Common/Core/Object.hpp
	Common/Core/Object.cpp
	Common/Core/IUnknown.hpp
)
set(	COMMON_CORE_SOURCES
)

#	Common/Runtime
set(	COMMON_RUNTIME_HEADERS
	Common/Runtime/BaseApplication.hpp
)
set(	COMMON_RUNTIME_SOURCES
	Common/Runtime/BaseApplication.cpp
)

#	Common/Utils
set(	COMMON_UTILS_HEADERS
	Common/Utils/Any.hpp
	Common/Utils/MDelegate.hpp
	Common/Utils/MString.hpp
	Common/Utils/Utils.hpp
)
set(	COMMON_UTILS_SOURCES
)

#	Common/Core/Controls
set(	COMMON_CORE_CONTROLS_HEADERS
	Common/Core/Controls/IControl.hpp
	Common/Core/Controls/BaseControl.hpp
	Common/Core/Controls/ControlManager.hpp
	Common/Core/Controls/WindowCanvas.hpp
	Common/Core/Controls/Label.hpp
)
set(	COMMON_CORE_CONTROLS_SOURCES
	Common/Core/Controls/BaseControl.cpp
	Common/Core/Controls/ControlManager.cpp
	Common/Core/Controls/WindowCanvas.cpp
	Common/Core/Controls/Label.cpp
)

#	Common/Core/Geometries
set(	COMMON_CORE_GEOMETRIES_HEADERS
	Common/Core/Geometries/MRect.hpp
)
set(	COMMON_CORE_GEOMETRIES_SOURCES
		Common/Core/Geometries/MRect.cpp
)

#	Common/Core/Graphics
set(	COMMON_CORE_GRAPHICS_HEADERS
		Common/Core/Graphics/MColor.hpp
		Common/Core/Graphics/IRenderSystem.hpp
)
set(	COMMON_CORE_GRAPHICS_SOURCES
		Common/Core/Graphics/MColor.cpp
)

#	Common/Core/Windows
set(	COMMON_CORE_WINDOWS_HEADERS
	Common/Core/Windows/IWindow.hpp
	Common/Core/Windows/BaseWindow.hpp
	Common/Core/Windows/IWindowFactory.hpp
)
set(	COMMON_CORE_WINDOWS_SOURCES
	Common/Core/Windows/BaseWindow.cpp
)

#	Interface
set(	INTERFACE_HEADERS
	Interface/IApplication.hpp
	Interface/Interface.hpp
	Interface/IRuntime.hpp
)

SOURCE_GROUP("Common" FILES
	${COMMON_HEADERS}
	${COMMON_SOURCES}
)

SOURCE_GROUP("Interface" FILES
	${INTERFACE_HEADERS}
)

SOURCE_GROUP("Common\\Core" FILES
	${COMMON_CORE_HEADERS}
	${COMMON_CORE_SOURCES}
)

SOURCE_GROUP("Common\\Core\\Controls" FILES
	${COMMON_CORE_CONTROLS_HEADERS}
	${COMMON_CORE_CONTROLS_SOURCES}
)

SOURCE_GROUP("Common\\Core\\Geometries" FILES
	${COMMON_CORE_GEOMETRIES_HEADERS}
	${COMMON_CORE_GEOMETRIES_SOURCES}
)

SOURCE_GROUP("Common\\Core\\Graphics" FILES
	${COMMON_CORE_GRAPHICS_HEADERS}
	${COMMON_CORE_GRAPHICS_SOURCES}
)

SOURCE_GROUP("Common\\Core\\Windows" FILES
	${COMMON_CORE_WINDOWS_HEADERS}
	${COMMON_CORE_WINDOWS_SOURCES}
)

SOURCE_GROUP("Common\\Runtime" FILES
	${COMMON_RUNTIME_HEADERS}
	${COMMON_RUNTIME_SOURCES}
)

SOURCE_GROUP("Common\\Utils" FILES
	${COMMON_UTILS_HEADERS}
	${COMMON_UTILS_SOURCES}
)

set(HEADERS_FILES
	${COMMON_HEADERS}
	${INTERFACE_HEADERS}
	${COMMON_CORE_HEADERS}
	${COMMON_RUNTIME_HEADERS}
	${COMMON_UTILS_HEADERS}
	${COMMON_CORE_CONTROLS_HEADERS}
	${COMMON_CORE_GEOMETRIES_HEADERS}
	${COMMON_CORE_GRAPHICS_HEADERS}
	${COMMON_CORE_WINDOWS_HEADERS}
)

set(SOURCES_FILES
	${COMMON_SOURCES}
	${INTERFACE_SOURCES}
	${COMMON_CORE_SOURCES}
	${COMMON_RUNTIME_SOURCES}
	${COMMON_UTILS_SOURCES}
	${COMMON_CORE_CONTROLS_SOURCES}
	${COMMON_CORE_GEOMETRIES_SOURCES}
	${COMMON_CORE_GRAPHICS_SOURCES}
	${COMMON_CORE_WINDOWS_SOURCES}
)

set(LIBRARY_OUTPUT_PATH ${MDUILIB_LIB_DIR})

ADD_LIBRARY( Framework STATIC
	${HEADERS_FILES}
	${SOURCES_FILES}
)

SET_TARGET_PROPERTIES( Framework PROPERTIES FOLDER "Framework")




