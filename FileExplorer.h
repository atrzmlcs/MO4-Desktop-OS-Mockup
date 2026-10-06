#pragma once
#include "AWindow.h"
#include "imgui.h"

class FileExplorer : public AWindow {
public:
    FileExplorer() : AWindow("FileExplorer") {}

    void draw() override {
        if (!isVisible) return;

        // Set default size, but allow user to resize
        ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
        
        if (ImGui::Begin("File Explorer", &isVisible)) {
            ImGui::Text("Local Disk (C:)");
            ImGui::Separator();
            
            if (ImGui::TreeNode("Documents")) {
                ImGui::BulletText("CSOPESY_Report.docx");
                ImGui::BulletText("Architecture_Diagram.png");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Downloads")) {
                ImGui::BulletText("glfw-3.5.1.zip");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Pictures")) {
                ImGui::BulletText("OS_Wallpaper.jpg");
                ImGui::TreePop();
            }
        }
        endWindow(); // Maps to ImGui::End() from your AWindow parent
    }
};