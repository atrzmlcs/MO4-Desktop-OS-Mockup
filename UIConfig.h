#pragma once
#include <GLFW/glfw3.h>
#include "imgui.h"

class UIConfig {
public:
    // Calculates scaling factor based on monitor resolution (Phase 2: Kernel Init)
    static void initialize() {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        if (!monitor) return;

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if (!mode) return;

        float baseWidth = 1920.0f;
        float currentWidth = static_cast<float>(mode->width);
        scaleFactor = currentWidth / baseWidth;

        // Clamp to a safe scaling range [1.0, 2.0]
        if (scaleFactor < 1.0f) scaleFactor = 1.0f;
        if (scaleFactor > 2.0f) scaleFactor = 2.0f;
    }

    static float getScaleFactor() {
        return scaleFactor;
    }

    // Utility helper to scale ImVec2 dimensions (windows, buttons, icons)
    static ImVec2 scale(const ImVec2& size) {
        return ImVec2(size.x * scaleFactor, size.y * scaleFactor);
    }

private:
    static float scaleFactor;
};