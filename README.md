# CSOPESY OS Emulator Mockup

## How to Build and Run (MinGW / GCC)

```bash
g++ main.cpp UIConfig.cpp imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp imgui_impl_glfw.cpp imgui_impl_opengl3.cpp -I. -L. -lglfw3 -lopengl32 -lgdi32 -o os_mockup.exe
./os_mockup.exe
