/*      menu.cpp
 *
 *
 *
 */
#include "menu.h"
#include "imgui.h"

C_Menu* menu;

/*
 *  render
 *  Renders the menu
 */
void C_Menu::render()
{
    const int flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
 
    static int tab = AIMBOT;
    
    if(ImGui::Begin("csgobase", &set.menu, {300, 200}, flags))
    {
        ImGui::Checkbox("Visuals", &set.visuals.enabled);
        ImGui::ColorEdit4("Box colour", (float*)&set.colors.box, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
    }
    ImGui::End();
}

/*
 *  setup_style
 *  Setups the ImGui style
 */
void C_Menu::setup_style()
{
    ImGuiStyle& style = ImGui::GetStyle();
    
    style.WindowPadding     = ImVec2(8, 8);
    style.WindowRounding    = 4.0f;
    style.WindowBorderSize  = 0.0f;
    style.WindowMinSize     = ImVec2(32, 32);
    style.WindowTitleAlign  = ImVec2(0.5f, 0.5f);
    style.ChildRounding     = 1.f;
    style.ChildBorderSize   = 1.1f;
    style.PopupRounding     = 0.f;
    style.PopupBorderSize   = 0.f;
    style.FramePadding      = ImVec2(4, 3);
    style.FrameRounding     = 1.0f;
    style.FrameBorderSize   = 0.f;
    style.ItemSpacing       = ImVec2(8, 4);
    style.ItemInnerSpacing  = ImVec2(4, 4);
    style.TouchExtraPadding = ImVec2(0, 0);
    style.IndentSpacing     = 21.0f;
    style.ColumnsMinSpacing = 3.0f;
    style.ScrollbarSize     = 14.0f;
    style.ScrollbarRounding = 5.0f;
    style.GrabMinSize       = 5.0f;
    style.GrabRounding      = 1.0f;
    style.ButtonTextAlign   = ImVec2(0.5f, 0.5f);
    style.DisplayWindowPadding  = ImVec2(22, 22);
    style.DisplaySafeAreaPadding= ImVec2(4, 4);
    style.CurveTessellationTol  = 1.25f;
    style.MouseCursorScale      = style.MouseCursorScale;
    style.AntiAliasedLines      = true;
    style.AntiAliasedFill       = true;
    style.CurveTessellationTol  = style.CurveTessellationTol;
    
    ImColor orange      = ImColor(255, 71, 43, 255);
    ImColor titleBarCol = ImColor(15, 15, 15, 255);
    ImColor backgroundCol = ImColor(28, 28, 28, 210);
    
    
    style.Colors[ImGuiCol_Text]                 = ImColor(255, 255, 255, 255);
    style.Colors[ImGuiCol_TextDisabled]         = ImColor(255, 255, 255, 255);;
    style.Colors[ImGuiCol_WindowBg]             = backgroundCol;
    style.Colors[ImGuiCol_ChildBg]              = ImColor(0 ,0, 0, 0);
    style.Colors[ImGuiCol_ChildWindowBg]        = ImColor(0, 0, 0, 0);
    style.Colors[ImGuiCol_PopupBg]              = backgroundCol;
    style.Colors[ImGuiCol_Border]               = ImColor(15, 15, 15, 255);
    style.Colors[ImGuiCol_BorderShadow]         = ImColor(255, 255, 255, 255);
    style.Colors[ImGuiCol_FrameBg]              = backgroundCol;
    style.Colors[ImGuiCol_FrameBgHovered]       = backgroundCol;
    style.Colors[ImGuiCol_FrameBgActive]        = backgroundCol;
    style.Colors[ImGuiCol_TitleBg]              = titleBarCol;
    style.Colors[ImGuiCol_TitleBgActive]        = titleBarCol;
    style.Colors[ImGuiCol_TitleBgCollapsed]     = titleBarCol;
    style.Colors[ImGuiCol_MenuBarBg]            = titleBarCol;
    style.Colors[ImGuiCol_ScrollbarBg]          = backgroundCol;
    style.Colors[ImGuiCol_ScrollbarGrab]        = ImColor(150, 150, 150, 255);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(150, 150, 150, 255);
    style.Colors[ImGuiCol_ScrollbarGrabActive]  = ImColor(150, 150, 150, 255);
    style.Colors[ImGuiCol_CheckMark]            = orange;
    style.Colors[ImGuiCol_SliderGrab];
    style.Colors[ImGuiCol_SliderGrabActive];
    style.Colors[ImGuiCol_Button]               = titleBarCol;
    style.Colors[ImGuiCol_ButtonHovered]        = ImColor(255, 71, 43, 200);
    style.Colors[ImGuiCol_ButtonActive]         = orange;
    style.Colors[ImGuiCol_Header];
    style.Colors[ImGuiCol_HeaderHovered];
    style.Colors[ImGuiCol_HeaderActive];
    style.Colors[ImGuiCol_Separator];
    style.Colors[ImGuiCol_SeparatorHovered];
    style.Colors[ImGuiCol_SeparatorActive];
    style.Colors[ImGuiCol_ResizeGrip];
    style.Colors[ImGuiCol_ResizeGripHovered];
    style.Colors[ImGuiCol_ResizeGripActive];
    style.Colors[ImGuiCol_CloseButton]          = ImColor(162, 69, 69, 255);
    style.Colors[ImGuiCol_CloseButtonHovered]   = ImColor(162, 69, 69, 255);;
    style.Colors[ImGuiCol_CloseButtonActive]    = ImColor(162, 69, 69, 255);;
    style.Colors[ImGuiCol_PlotLines];
    style.Colors[ImGuiCol_PlotLinesHovered];
    style.Colors[ImGuiCol_PlotHistogram];
    style.Colors[ImGuiCol_PlotHistogramHovered];
    style.Colors[ImGuiCol_TextSelectedBg]       = ImColor(15, 15, 15, 255);
    style.Colors[ImGuiCol_ModalWindowDarkening];
    style.Colors[ImGuiCol_DragDropTarget];
    style.Colors[ImGuiCol_NavHighlight];
    style.Colors[ImGuiCol_NavWindowingHighlight];
}

