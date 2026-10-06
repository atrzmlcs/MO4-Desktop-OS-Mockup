#pragma once
#include <string>
#include "imgui.h"

class AWindow {
public:
    AWindow(const std::string& name) : windowName(name), isVisible(false) {}
    virtual ~AWindow() = default;

    // Pure virtual method for window-specific Dear ImGui rendering
    virtual void draw() = 0;

    void show() { isVisible = true; }
    void hide() { isVisible = false; }
    bool isShown() const { return isVisible; }

protected:
    // Helper to streamline ImGui::Begin / ImGui::End calls
    bool beginWindow() {
        if (!isVisible) return false;
        return ImGui::Begin(windowName.c_str(), &isVisible);
    }

    void endWindow() {
        ImGui::End();
    }

    std::string windowName;
    bool isVisible;
};