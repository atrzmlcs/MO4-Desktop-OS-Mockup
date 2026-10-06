#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "UIConfig.h"
#include "UIManager.h"
#include "BIOSBootWindow.h"
#include "Desktop.h"
#include "Taskbar.h"
#include "TaskManagerUI.h"
#include "FileExplorer.h"
#include "Settings.h"

int main() {
    // =========================================================================
    // PHASE 1: BOOTSTRAPPING
    // Hardware graphics initialization & ImGui context setup
    // =========================================================================
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "CSOPESY Workstation OS Emulator", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable VSync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // =========================================================================
    // PHASE 2: KERNEL INITIALIZATION
    // Screen resolution polling & DPI scaling factor calculation
    // =========================================================================
    UIConfig::initialize();

    // =========================================================================
    // PHASE 3: START SYSTEM SERVICES
    // Instantiate UI components and register them with UIManager singleton
    // =========================================================================
    auto bootWindow    = std::make_shared<BIOSBootWindow>();
    auto desktopWindow = std::make_shared<Desktop>();
    auto taskbarWindow = std::make_shared<Taskbar>();
    auto taskManager   = std::make_shared<TaskManagerUI>();
    auto fileExplorer  = std::make_shared<FileExplorer>();
    auto settings      = std::make_shared<Settings>();

    // Register all active windows into system registry
    UIManager::getInstance().registerWindow("BIOSBoot", bootWindow.get());
UIManager::getInstance().registerWindow("Desktop", desktopWindow.get());
UIManager::getInstance().registerWindow("Taskbar", taskbarWindow.get());
UIManager::getInstance().registerWindow("TaskManager", taskManager.get());
UIManager::getInstance().registerWindow("FileExplorer", fileExplorer.get());
UIManager::getInstance().registerWindow("Settings", settings.get());

    // Initialize OS lifecycle starting with POST BIOS screen
    UIManager::getInstance().showWindow("BIOSBoot");

    // =========================================================================
    // PHASE 4: MAIN LOOP
    // Event polling, per-frame updates, system rendering, and swap buffers
    // =========================================================================
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start Dear ImGui Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Dispatch rendering calls to all active registered windows
        UIManager::getInstance().renderAllWindows();

        // OpenGL Render Pass
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.10f, 0.12f, 0.15f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // =========================================================================
    // PHASE 5: SHUTDOWN AND CLEANUP
    // Release resources, destroy ImGui context, and close window
    // =========================================================================
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}