# CSOPESY OS Emulator Mockup

An Operating System UI simulation built using C++, GLFW, OpenGL 3, and Dear ImGui.

---

## How to Build and Run (MinGW / GCC)

Run the following command in your terminal from the project root folder:

```bash
g++ main.cpp UIConfig.cpp imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp imgui_impl_glfw.cpp imgui_impl_opengl3.cpp -I. -L. -lglfw3 -lopengl32 -lgdi32 -o os_mockup.exe
./os_mockup.exe



G:\CSOPESY\MO4\
├── 📄 main.cpp                     # Application Entry Point & Main Loop
├── 📄 UIConfig.h / UIConfig.cpp    # Global UI Configurations, Styling, & Fonts
├── 📄 AWindow.h                    # Abstract Base Class for UI Windows
├── 📄 UIManager.h                  # Singleton UI Window Manager
│
├── 📂 Subsystems & Windows (Header-Only)
│   ├── 📄 BIOSBootWindow.h         # BIOS / POST Boot Sequence Window
│   ├── 📄 Desktop.h                # Desktop Environment & Icons
│   ├── 📄 Taskbar.h                # Start Menu, Taskbar, & System Clock
│   ├── 📄 TaskManagerUI.h          # Process & Resource Monitor UI
│   ├── 📄 FileExplorer.h           # Virtual File System Navigation UI
│   └── 📄 Settings.h               # System Configuration & Options UI
│
└── 📂 Third-Party Dependencies (Dear ImGui & GLFW) (DO NOT EDIT)
    ├── 📄 imgui.h / imgui.cpp
    ├── 📄 imgui_internal.h
    ├── 📄 imgui_widgets.cpp
    ├── 📄 imgui_draw.cpp
    ├── 📄 imgui_tables.cpp
    ├── 📄 imgui_demo.cpp
    ├── 📄 imconfig.h
    ├── 📄 imstb_textedit.h
    ├── 📄 imstb_rectpack.h
    ├── 📄 imstb_truetype.h
    ├── 📄 imgui_impl_glfw.h / .cpp
    ├── 📄 imgui_impl_opengl3.h / .cpp
    ├── 📄 imgui_impl_opengl3_loader.h
    └── 📄 libglfw3.a
