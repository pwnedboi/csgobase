/*      Renderer.cpp
 *
 *
 *
 */
#include "main.h"
#include "renderer.h"

C_Renderer* render = new C_Renderer();

/****************************** Drawings ******************************/

/*
 *  draw_box
 *  Draws a hollow box
 */
void C_Renderer::draw_box(int x, int y, int w, int h, Color color)
{
    pSurface->DrawSetColor(color);
    pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}

/*
 *  draw_box_filled
 *  Draws a filled box
 */
void C_Renderer::draw_box_filled(int x, int y, int w, int h, Color color)
{
    pSurface->DrawSetColor(color);
    pSurface->DrawFilledRect(x, y, x + w, y + h);
}

/*
 *  draw_box_outline
 *  Draws an outline around a box
 */
void C_Renderer::draw_box_outline(int x, int y, int w, int h, Color color)
{
    int aplha = color.a();
    this->draw_box(x, y, w, h, color);   // The fill colour
    this->draw_box(x - 1, y - 1, w + 2, h + 2, Color(0, 0, 0, aplha)); // The border, black
    this->draw_box(x + 1, y + 1, w - 2, h - 2, Color(0, 0, 0, aplha));
}

/*
 *  draw_outlined_box
 *  Draws a box with an outline
 */
void C_Renderer::draw_outlined_box(int x, int y, int w, int h, int thickness, Color color, Color outlined)
{
    this->draw_box_filled(x, y, w, h, color);
    
    x -= thickness;
    y -= thickness;
    w += thickness;
    h += thickness;
    color = outlined;
    
    this->draw_box_filled(x, y, w, thickness, color);
    this->draw_box_filled(x, y, thickness, h, color);
    this->draw_box_filled(x + w, y, thickness, h, color);
    this->draw_box_filled(x, y + h, w + thickness, thickness, color);
}

/*
 *  draw_gradient
 *  Draws a box that gradients from one colour to another
 */
void C_Renderer::draw_gradient(int x, int y, int w, int h, Color col1, Color col2)
{
    this->draw_box_filled(x, y, w, h, col1);
    
    Byte first  = col2.r();
    Byte second = col2.g();
    Byte third  = col2.b();
    
    for (int i = 0; i < h; i++)
    {
        float fi = i, fh = h;
        float a = fi / fh;
        int ia = a * 255;
        
        this->draw_box_filled(x, y + i, w, 1, Color(first, second, third, ia));
    }
}

/*
 *  draw_3d_box
 *  Draws a 3d box around a point
 */
void C_Renderer::draw_3d_box(Vector vecOrigin, Vector min, Vector max, Color color)
{
    min += vecOrigin;
    max += vecOrigin;
    
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
        if (!WorldToScreen(points[it[0]], p1) || !WorldToScreen(points[it[1]], p2))
            return;
        
        this->draw_line(p1.x, p1.y, p2.x, p2.y, color);
    }
}

/*
 *  draw_line
 *  Draws a line from one point to another
 */
void C_Renderer::draw_line(int x, int y, int xx, int yy, Color color)
{
    pSurface->DrawSetColor(color);
    pSurface->DrawLine(x, y, xx, yy);
}

/*
 *  draw_string
 *  Draws a string
 */
void C_Renderer::draw_string(int x, int y, Color color, HFONT font, const char *szString, bool bCenter)
{
    wstring wString = this->string_to_wstring(szString);
    if(bCenter)
    {
        int wide, tall;
        pSurface->GetTextSize(font, wString.c_str(), wide, tall);
        x -= wide / 2;
        y -= tall / 2;
    }
    pSurface->DrawSetTextPos(x, y);
    pSurface->DrawSetTextFont(font);
    pSurface->DrawSetTextColor(color);
    pSurface->DrawPrintText(wString.c_str(), (int)wcslen(wString.c_str()));
}

/*
 *  draw_textured_polygon
 *  Draws a shape with given verticies
 */
void C_Renderer::draw_textured_polygon(int n, Vertex_t* vertice, Color col)
{
    static int texture_id = pSurface->CreateNewTextureID(true);
    static unsigned char buf[4] = { 255, 255, 255, 255 };
    pSurface->DrawSetTextureRGBA(texture_id, buf, 1, 1);
    pSurface->DrawSetColor(col);
    pSurface->DrawSetTexture(texture_id);
    pSurface->DrawTexturedPolygon(n, vertice);
}

/*
 *  draw_circle
 *  Draws a hollow circle
 */
void C_Renderer::draw_circle(Vector2D position, float points, float radius, Color color)
{
    float step = (float)M_PI * 2.0f / points;
    
    for (float a = 0; a < (M_PI * 2.0f); a += step)
    {
        Vector2D start(radius * cosf(a) + position.x, radius * sinf(a) + position.y);
        Vector2D end(radius * cosf(a + step) + position.x, radius * sinf(a + step) + position.y);
        this->draw_line(start.x, start.y, end.x, end.y, color);
    }
}

/*
 *  draw_filled_circle
 *  Draws a filled circle
 */
void C_Renderer::draw_filled_circle(Vector2D center, float points, float radius, Color color)
{
    static bool once = true;
    
    static vector<float> temppointsx;
    static vector<float> temppointsy;
    
    if(once)
    {
        float step = (float) M_PI * 2.0f / points;
        for(float a = 0; a < (M_PI * 2.0f); a += step)
        {
            temppointsx.push_back(cosf(a));
            temppointsy.push_back(sinf(a));
        }
        once = false;
    }
    
    vector<int> pointsx;
    vector<int> pointsy;
    vector<Vertex_t> vertices;
    
    for (int i = 0; i < temppointsx.size(); i++)
    {
        float x = radius * temppointsx[i] + center.x;
        float y = radius * temppointsy[i] + center.y;
        pointsx.push_back(x);
        pointsy.push_back(y);
        
        vertices.push_back(Vertex_t(Vector2D(x, y)));
    }
    
    this->draw_textured_polygon(points, vertices.data(), color);
}


/****************************** Misc / util ******************************/

/*
 *  string_to_wstring
 *  Converts a string to a wide string
 */
wstring C_Renderer::string_to_wstring(string str)
{
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
    try
    {
        return converter.from_bytes(str);
    }
    catch(range_error& e)
    {
        wostringstream s;
        s << str.c_str();
        return s.str();
    }
}

/*
 *  get_text_size
 *  Gets the size of string
 */
Vector2D C_Renderer::get_text_size(const char* text, HFONT font)
{
    wstring wc = string_to_wstring(text);
    int w, h;
    pSurface->GetTextSize(font, wc.c_str(), w, h);
    
    return Vector2D(w, h);
}

/*
 *  draw_watermark
 *  Draws the watermark in the top left corner of the screen
 */
void C_Renderer::draw_watermark()
{
    this->draw_string(10, 20, Color::PastelPink(), espfont, "csgobase");
}

/****************************** Fonts ******************************/

HFONT espfont, menufont;

/*
 *  create_font
 *  Creates a hfont
 */
HFONT C_Renderer::create_font(const char* szFont, int tall, int flags)
{
    HFONT font = pSurface->CreateFont();
    pSurface->SetFontGlyphSet(font, szFont, tall, 150, 0, 0, flags);
    return font;
}

/*
 *  initialise_fonts
 *  Creates all fonts
 */
void C_Renderer::initialise_fonts()
{
    espfont     = this->create_font("Verdana Bold", 13, FONTFLAG_DROPSHADOW);
    menufont    = this->create_font("Tahoma", 11, FONTFLAG_DROPSHADOW);
    
    print("Fonts initlaised", Color::Orange());
}

