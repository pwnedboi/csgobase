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
 *  add_checkbox
 *  Draws checkbox
 *  Just an example
 */
void C_Menu::add_checkbox(int x, int y, const char* label, bool* value)
{
    const int w = 10, h = 10;
    bool clicked = io.MouseClicked[0];
    
    if(draw->in_area(x, y, w, h) && clicked)
        *value = !*value;
    
    /*
     *  -1 and +2 are to make the border larger than the fill
     */
    draw->draw_box(x - 1, y - 1, w + 2, h + 2, ImColor(60, 60, 60));
    
    if(*value)
        draw->draw_box_filled(x, y, w, h, ImColor(255, 0, 0));
}

/*
 *  display
 *  Draws the menu
 */
void C_Menu::display()
{
    // Below is ImGUI::Begin();
    draw->start();
    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Checkbox("Enabled", &set.visuals.enabled);
    
    
    // Below is ImGui::End()
    draw->finish();
}


