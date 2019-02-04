/*      menu.cpp
 *
 *
 *
 */

#include "menu.h"
#include "imgui.h"

C_Menu* menu = new C_Menu();

/*
 *  Constructor
 */
C_Menu::C_Menu()
{
    
}

/*
 *  Deconstructor
 */
C_Menu::~C_Menu()
{
    delete draw;
}

/*
 *  init
 *  Initialises the menu
 */
void C_Menu::init()
{
    draw = new C_Renderer();
    draw->init_fonts();
    
    this->io = ImGui::GetIO();
}

/*
 *  display
 *  Draws the menu
 */
void C_Menu::display()
{
    // Below is ImGUI::Begin();
    draw->start();
    
    ImGui::Checkbox("Enabled", &set.visuals.enabled);
    ImGui::SliderInt("IntTest", &set.test.islider, 0, 180);
    ImGui::SliderFloat("FloatTest", &set.test.fslider, 0, 180, "%.0f");
    ImGui::ColorEdit4("Box colour", (float*)&set.colors.box, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

    // Below is ImGui::End()
    draw->finish();
}


