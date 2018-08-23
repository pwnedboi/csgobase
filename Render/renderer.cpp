/*      renderer.cpp
 *
 *
 *
 */

#include "main.h"
#include "renderer.h"

C_Renderer* render = new C_Renderer();

/****************************** Window ******************************/

/*
 *  start
 *  Creates the window that everything is rendered to
 */
void C_Renderer::start()
{
    auto& style = ImGui::GetStyle();
    style.WindowBorderSize = 0.f;
    
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({1280, 720});
    ImGui::SetNextWindowBgAlpha(0.f);
    
    bool opened = true;
    int flags = ImGuiWindowFlags_NoTitleBar      | ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoScrollbar     | ImGuiWindowFlags_NoInputs |
    ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
    ImGuiWindowFlags_NoBringToFrontOnFocus;
    
    
    ImGui::Begin("drawings window", &opened, flags);
    
    this->draw = ImGui::GetWindowDrawList();
}

/*
 *  finish
 *
 */
void C_Renderer::finish()
{
    ImGui::End();
}

/****************************** Drawings ******************************/

/*
 *  draw_box
 *  Draws a hollow box
 */
void C_Renderer::draw_box(int x, int y, int w, int h, ImColor col)
{
    draw->AddRect({x, y}, {x + w, y + h}, col);
}

/*
 *  draw_box_filled
 *  Draws a filled box
 */
void C_Renderer::draw_box_filled(int x, int y, int w, int h, ImColor col)
{
    draw->AddRectFilled({x, y}, {x + w, y + h}, col);
}

/*
 *  draw_box_outlined
 *  Draws a box with an outline
 */
void C_Renderer::draw_box_outlined(int x, int y, int w, int h, int thickness, ImColor col, ImColor border)
{
    draw->AddRectFilled({x - thickness, y - thickness}, {x + w + thickness, y + h + thickness}, border);
    draw->AddRectFilled({x, y}, {x + w, y + h}, col);
}

/*
 *  draw_box_gradient
 *  Draws a box that gradients from one coloue to another, top to bottom
 */
void C_Renderer::draw_box_gradient(int x, int y, int w, int h, ImColor col1, ImColor col2)
{
    draw->AddRectFilledMultiColor({x, y}, {x + w, y + h}, col1, col1, col2, col2);
}

/*
 *  draw_box_3d
 *  Draws a 3d box around a point
 */
void C_Renderer::draw_box_3d(Vector origin, Vector min, Vector max, ImColor col)
{
    min += origin;
    max += origin;
    
    Vector points[] =
    {
        Vector(min.x, min.y, min.z),
        Vector(min.x, max.y, min.z),
        Vector(max.x, max.y, min.z),
        Vector(max.x, min.y, min.z),
        Vector(min.x, min.y, max.z),
        Vector(min.x, max.y, max.z),
        Vector(max.x, max.y, max.z),
        Vector(max.x, min.y, max.z)
    };
    
    int edges[12][2] =
    {
        { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
        { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 },
        { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
    };
    
    for (auto it : edges)
    {
        Vector p1, p2;
        if (!world_to_screen(points[it[0]], p1) || !world_to_screen(points[it[1]], p2))
            return;
        
        this->draw_line(p1.x, p1.y, p2.x, p2.y, col);
    }
}

/*
 *  draw_line
 *  Draws a line between 2 points
 */
void C_Renderer::draw_line(int x, int y, int xx, int yy, ImColor col)
{
    draw->AddLine({x, y}, {xx, yy}, col);
}

/*
 *  draw_string
 *  Draws a string
 */
void C_Renderer::draw_string(int x, int y, const char* str, ImFont* font, ImColor col, bool centered)
{
    if(centered)
    {
        auto text_size = get_text_size(str);
        x -= (text_size.x / 2);
        y -= (text_size.y / 2);
    }
    
    draw->AddText(font, font->FontSize, {x, y}, col, str);
}

/*
 *  draw_polygon
 *  Draws a shape with given verticies
 */
void C_Renderer::draw_polygon(ImVec2* verts, ImColor col)
{
    draw->AddConvexPolyFilled(verts, IM_ARRAYSIZE(verts), col);
}

/*
 *  draw_cicle
 *  Draws a hollow circle
 */
void C_Renderer::draw_circle(ImVec2 center, float radius, ImColor col)
{
    draw->AddCircle(center, radius, col);
}

/*
 *  draw_circle_filled
 *  Draws a filled circle
 */
void C_Renderer::draw_circle_filled(ImVec2 center, float radius, ImColor col)
{
    draw->AddCircleFilled(center, radius, col);
}

/****************************** Utils ******************************/

/*
 *  get_text_size
 *  Returns the text width and height
 */
ImVec2 C_Renderer::get_text_size(const char* str)
{
    return ImGui::CalcTextSize(str);
}

/*
 *  in_area
 *  Returns true if the mouse is in the given area
 */
bool C_Renderer::in_area(int x, int y, int w, int h)
{
    auto io = ImGui::GetIO();
    auto mouse = io.MousePos;
    return (mouse.x > x && mouse.y > y) && (mouse.x < x + w && mouse.y < y + h);
}

/****************************** Fonts ******************************/

/*
 *  Fonts namespace
 */
namespace Fonts
{
    ImFont* big;
    ImFont* small;
}

/*
 *  create_font
 *  Loads a font and returns it
 */
ImFont* C_Renderer::create_font(const char* font_path, float font_size)
{
    auto io = ImGui::GetIO();
    ImFontConfig* font_conf = new ImFontConfig;
    font_conf->OversampleH = font_conf->OversampleV = 1;
    font_conf->PixelSnapH = true;
    
    return io.Fonts->AddFontFromFileTTF(font_path, font_size, font_conf);
}

/*
 *  init_fonts
 *  Initialises fonts
 */
void C_Renderer::init_fonts()
{
    Fonts::big  = create_font("/Library/Fonts/ProggyClean.ttf", 13.f);
    Fonts::small= create_font("/Library/Fonts/ProggyTiny.ttf",  10.f);
}
