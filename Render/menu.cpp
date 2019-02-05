/*      menu.cpp
 *
 *
 *
 */
#include "menu.h"
#include "imgui.h"

// Tabs
enum {
    AIMBOT,
    VISUALS,
    MISC,
    COLOUR,
};

void Menu::drawMenu() {
    //int flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
 
    static int tab = AIMBOT;
    
    /* ***** Start ***** */
    if(ImGui::Begin("csgobase", &set.menu, {300, 200}, ImGuiWindowFlags_NoResize)) {
    /* ***** Start ***** */
        
        
        ImGui::Columns(2, NULL, true); { // First Column [Stacked]
            ImGui::Text(("Visuals"));
            ImGui::Checkbox(("Enabled"), &set.vis.enabled);
        }
        /* ***** Separator ***** */
        ImGui::Separator();
        /* ***** Separator ***** */
        ImGui::BeginChild(("COL1"), ImVec2(0, 0), true);
        {
        }
        ImGui::NextColumn();
        {
            ImGui::Columns(1, NULL, true); { // First Column [Stacked]
                ImGui::Checkbox(("Box"), &set.vis.box);
                if(set.vis.box) {
                    ImGui::Text("Vis Color");
                    ImGui::ColorEdit4("Vis", (float*)&set.colors.box, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel); // Vis Box Colour
                    ImGui::Text("NonVis Color");
                    ImGui::ColorEdit4("NonVis", (float*)&set.colors.box_ign, ImGuiColorEditFlags_NoInputs| ImGuiColorEditFlags_NoLabel); // NonVis Box Colour
                }
                ImGui::Checkbox(("Name/Health"), &set.vis.name);
                ImGui::Checkbox(("Crosshair"), &set.vis.crosshair);
                if(set.vis.crosshair) {
                    ImGui::Text("Crosshair Color");
                    ImGui::ColorEdit4("cColor", (float*)&set.colors.crosshair, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel); // Crosshair Color
                    ImGui::Text("Crosshair Length");
                    ImGui::SliderInt("Length", &set.vis.crosshairlength, 1, 50);
                }
                ImGui::Checkbox(("NoScope"), &set.vis.noscope);
            }
        }
        /* ***** End Begin Child ***** */
        ImGui::EndChild();
        /* ***** End Begin Child ***** */
    }
    
    
    /* ***** End ***** */
    ImGui::End();
    /* ***** End ***** */
}

void Menu::setupStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({400, 400});
    ImGui::SetNextWindowBgAlpha(1.f);
    ImGui::StyleColorsDark();

    style.WindowBorderSize = 0.f;
}

