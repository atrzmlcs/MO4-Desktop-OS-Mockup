#pragma once
#include "AWindow.h"
#include "imgui.h"

class Settings : public AWindow {
public:
    Settings() : AWindow("Settings") {}

    void draw() override {
        if (!isVisible) return;

        ImGui::SetNextWindowSize(ImVec2(300, 350), ImGuiCond_FirstUseEver);
        
        if (ImGui::Begin("System Settings", &isVisible)) {
            ImGui::Text("Appearance");
            ImGui::Separator();
            static int displayMode = 1;
            ImGui::RadioButton("Light Mode", &displayMode, 0);
            ImGui::RadioButton("Dark Mode", &displayMode, 1);
            
            ImGui::Spacing();
            ImGui::Text("Network Configuration");
            ImGui::Separator();
            ImGui::TextDisabled("Status: Connected");
            ImGui::TextDisabled("IPv4: 192.168.1.100");

            ImGui::Spacing();
            ImGui::Text("System Information");
            ImGui::Separator();
            ImGui::Text("OS: CSOPESY OS v1.0");
            ImGui::Text("CPU: Pentium III (Emulated)");
            ImGui::Text("RAM: 64000K OK");
        }
        endWindow();
    }
};