SRC
│  CMakeLists.txt
│  
├─Framework
│  │  CMakeLists.txt
│  │  
│  ├─Common
│  │  │  main.cpp
│  │  │  MDUILibAfx.hpp
│  │  │  
│  │  ├─Core
│  │  │  │  Events.hpp
│  │  │  │  IUnknown.hpp
│  │  │  │  Object.cpp
│  │  │  │  Object.hpp
│  │  │  │  
│  │  │  ├─Controls
│  │  │  │      IControl.hpp
│  │  │  │      
│  │  │  ├─Geometries
│  │  │  │      MRect.cpp
│  │  │  │      MRect.hpp
│  │  │  │      
│  │  │  ├─Graphics
│  │  │  └─Windows
│  │  │          BaseWindow.cpp
│  │  │          BaseWindow.hpp
│  │  │          IWindow.hpp
│  │  │          IWindowFactory.hpp
│  │  │          
│  │  ├─Runtime
│  │  │      BaseApplication.cpp
│  │  │      BaseApplication.hpp
│  │  │      
│  │  └─Utils
│  │          Any.hpp
│  │          MDelegate.hpp
│  │          MString.hpp
│  │          Utils.hpp
│  │          
│  └─Interface
│          IApplication.hpp
│          Interface.hpp
│          IRuntime.hpp
│          
├─lib
│  └─Debug
│          Framework.lib
│          Framework.pdb
│          
└─WindowXX
    │  CMakeLists.txt
    │  WindowXXApplication.cpp
    │  WindowXXApplication.hpp
    │  
    └─Windows
            WinXXWindow.cpp
            WinXXWindow.hpp
            
