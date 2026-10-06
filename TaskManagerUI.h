#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "AWindow.h"
#include "UIConfig.h"

struct ProcessItem {
    int pid;
    std::string name;
    std::string status; // "Running", "Sleeping", "Ready"
    float cpuUsage;    // Percentage [0 - 100]
    float memoryUsage; // MB
};

class TaskManagerUI : public AWindow {
public:
    TaskManagerUI() : AWindow("Task Manager"), historySize(60), updateTimer(0.0f) {
        // Initialize history buffer for performance graphs
        cpuHistory.resize(historySize, 0.0f);
        memoryHistory.resize(historySize, 0.0f);

        // Sample initial process list
        processes = {
            { 1, "System Core / Kernel", "Running",  2.1f, 128.5f },
            { 2, "Window Server",        "Running",  5.4f, 256.0f },
            { 3, "Shell Desktop UI",     "Running",  1.8f,  94.2f },
            { 4, "Background Daemon",    "Sleeping", 0.0f,  32.1f }
        };
    }

    void draw() override {
        if (!isVisible) return;

        ImGui::SetNextWindowSize(UIConfig::scale(ImVec2(600, 420)), ImGuiCond_FirstUseEver);

        if (beginWindow()) {
            updateMetrics();

            if (ImGui::BeginTabBar("TaskManagerTabBar")) {
                
                // -------------------------------------------------------------
                // TAB 1: PROCESS MONITOR TABLE
                // -------------------------------------------------------------
                if (ImGui::BeginTabItem("Processes")) {
                    drawProcessTable();
                    ImGui::EndTabItem();
                }

                // -------------------------------------------------------------
                // TAB 2: SYSTEM PERFORMANCE GRAPHS
                // -------------------------------------------------------------
                if (ImGui::BeginTabItem("Performance")) {
                    drawPerformanceGraph();
                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }
        }
        endWindow();
    }

private:
    std::vector<ProcessItem> processes;
    std::vector<float> cpuHistory;
    std::vector<float> memoryHistory;
    int historySize;
    float updateTimer;

    void updateMetrics() {
        // Simple metric updates for UI demonstration
        updateTimer += ImGui::GetIO().DeltaTime;
        if (updateTimer >= 0.5f) { // Refresh every 500ms
            updateTimer = 0.0f;

            // Compute overall CPU usage from running processes
            float totalCpu = 0.0f;
            float totalMem = 0.0f;
            for (auto& proc : processes) {
                if (proc.status == "Running") {
                    totalCpu += proc.cpuUsage;
                }
                totalMem += proc.memoryUsage;
            }

            // Shift history buffers left
            std::rotate(cpuHistory.begin(), cpuHistory.begin() + 1, cpuHistory.end());
            std::rotate(memoryHistory.begin(), memoryHistory.begin() + 1, memoryHistory.end());

            cpuHistory.back() = std::min(totalCpu, 100.0f);
            memoryHistory.back() = totalMem;
        }
    }

    void drawProcessTable() {
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Borders | 
                                     ImGuiTableFlags_RowBg | 
                                     ImGuiTableFlags_Resizable | 
                                     ImGuiTableFlags_SizingFixedFit;

        if (ImGui::BeginTable("ProcessTable", 5, tableFlags)) {
            ImGui::TableSetupColumn("PID", ImGuiTableColumnFlags_WidthFixed, 40.0f * UIConfig::getScaleFactor());
            ImGui::TableSetupColumn("Process Name", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Status", ImGuiTableColumnFlags_WidthFixed, 90.0f * UIConfig::getScaleFactor());
            ImGui::TableSetupColumn("CPU (%)", ImGuiTableColumnFlags_WidthFixed, 70.0f * UIConfig::getScaleFactor());
            ImGui::TableSetupColumn("Actions", ImGuiTableColumnFlags_WidthFixed, 80.0f * UIConfig::getScaleFactor());
            ImGui::TableHeadersRow();

            for (size_t i = 0; i < processes.size(); ++i) {
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%d", processes[i].pid);

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", processes[i].name.c_str());

                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%s", processes[i].status.c_str());

                ImGui::TableSetColumnIndex(3);
                ImGui::Text("%.1f%%", processes[i].cpuUsage);

                ImGui::TableSetColumnIndex(4);
                ImGui::PushID(static_cast<int>(i));
                if (processes[i].status == "Running") {
                    if (ImGui::SmallButton("Kill")) {
                        processes[i].status = "Terminated";
                        processes[i].cpuUsage = 0.0f;
                    }
                } else {
                    ImGui::TextDisabled("N/A");
                }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
    }

    void drawPerformanceGraph() {
        ImGui::Spacing();
        ImGui::Text("Overall CPU Utilization");
        
        // Display Real-time CPU Usage Line Plot
        char cpuOverlay[32];
        snprintf(cpuOverlay, sizeof(cpuOverlay), "Usage: %.1f%%", cpuHistory.back());
        ImGui::PlotLines("##CPUPlot", 
                         cpuHistory.data(), 
                         static_cast<int>(cpuHistory.size()), 
                         0, 
                         cpuOverlay, 
                         0.0f, 
                         100.0f, 
                         ImVec2(-1.0f, 100.0f * UIConfig::getScaleFactor()));

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Memory Allocation");
        
        // Display Real-time Memory Usage Line Plot
        char memOverlay[32];
        snprintf(memOverlay, sizeof(memOverlay), "Allocated: %.1f MB", memoryHistory.back());
        ImGui::PlotLines("##MemoryPlot", 
                         memoryHistory.data(), 
                         static_cast<int>(memoryHistory.size()), 
                         0, 
                         memOverlay, 
                         0.0f, 
                         1024.0f, 
                         ImVec2(-1.0f, 100.0f * UIConfig::getScaleFactor()));
    }
};