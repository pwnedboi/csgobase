/*
 *  renderer.h
 */
#pragma once

extern HFONT espfont, menufont;

class RenderManager
{
public:
    
    wstring  string_to_wstring(string str);
    HFONT    create_font(const char* szFont, int tall, int flags);
    Vector2D get_text_size(const char* text, HFONT font);
    
    void drawBox(int x, int y, int w, int h, Color color);
    void drawBoxFilled(int x, int y, int w, int h, Color color);
    void drawBoxOutline(int x, int y, int w, int h, Color color);
    void drawBox3D(Vector vecOrigin, Vector min, Vector max, Color color);
    void drawOutlinedBox(int x, int y, int w, int h, int thickness, Color color, Color outlined);
    void drawLine(int x, int y, int xx, int yy, Color color);
    void drawString(int x, int y, Color color, HFONT font, const char* szString, bool bCenter = false);
    void drawGradient(int x, int y, int w, int h, Color col1, Color col2);
    void drawTexturedPolygon(int n, Vertex_t* vertice, Color col);
    void drawCircle(Vector2D position, float points, float radius, Color color);
    void drawFilledCircle(Vector2D center, float points, float radius, Color color);
    
    void initialise_fonts();
    
    void draw_watermark();
};

extern RenderManager* render;
