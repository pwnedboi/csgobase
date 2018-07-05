/*
 *  renderer.h
 */
#pragma once

extern HFONT espfont, menufont;

class C_Renderer
{
private:
    
    wstring  string_to_wstring(string str);
    HFONT    create_font(const char* szFont, int tall, int flags);
    
public:
    
    Vector2D get_text_size(const char* text, HFONT font);
    
    void draw_box(int x, int y, int w, int h, Color color);
    void draw_box_filled(int x, int y, int w, int h, Color color);
    void draw_box_outline(int x, int y, int w, int h, Color color);
    void draw_outlined_box(int x, int y, int w, int h, int thickness, Color color, Color outlined);
    void draw_gradient(int x, int y, int w, int h, Color col1, Color col2);
    void draw_3d_box(Vector vecOrigin, Vector min, Vector max, Color color);
    void draw_line(int x, int y, int xx, int yy, Color color);
    void draw_string(int x, int y, Color color, HFONT font, const char* szString, bool bCenter = false);
    void draw_textured_polygon(int n, Vertex_t* vertice, Color col);
    void draw_circle(Vector2D position, float points, float radius, Color color);
    void draw_filled_circle(Vector2D center, float points, float radius, Color color);
    
    void initialise_fonts();
    
    void draw_watermark();
};

extern C_Renderer* render;
