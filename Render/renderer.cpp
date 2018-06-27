/*      Renderer.cpp
 *
 *
 *
 */
#include "main.h"
#include "renderer.h"

RenderManager* render = new RenderManager();

//============================================ Drawings =============================================\\

void RenderManager::drawBox(int x, int y, int w, int h, Color color)
{
    pSurface->DrawSetColor(color);
    pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}

void RenderManager::drawBoxFilled(int x, int y, int w, int h, Color color)
{
    pSurface->DrawSetColor(color);
    pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void RenderManager::drawBoxOutline(int x, int y, int w, int h, Color color)
{
    int aplha = color.a();
    this->drawBox(x, y, w, h, color);   // The fill colour
    this->drawBox(x - 1, y - 1, w + 2, h + 2, Color(0, 0, 0, aplha)); // The border, black
    this->drawBox(x + 1, y + 1, w - 2, h - 2, Color(0, 0, 0, aplha));
}

void RenderManager::drawLine(int x, int y, int xx, int yy, Color color)
{
    pSurface->DrawSetColor(color);
    pSurface->DrawLine(x, y, xx, yy);
}

void RenderManager::drawString(int x, int y, Color color, HFONT font, const char *szString, bool bCenter)
{
    wstring wString = this->stringToWstring(szString);
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

void RenderManager::drawTexturedPolygon(int n, Vertex_t* vertice, Color col)
{
    static int texture_id = pSurface->CreateNewTextureID(true);
    static unsigned char buf[4] = { 255, 255, 255, 255 };
    pSurface->DrawSetTextureRGBA(texture_id, buf, 1, 1);
    pSurface->DrawSetColor(col);
    pSurface->DrawSetTexture(texture_id);
    pSurface->DrawTexturedPolygon(n, vertice);
}

void RenderManager::drawOutlinedBox(int x, int y, int w, int h, int thickness, Color color, Color outlined)
{
    this->drawBoxFilled(x, y, w, h, color);
    
    x -= thickness;
    y -= thickness;
    w += thickness;
    h += thickness;
    color = outlined;
    
    this->drawBoxFilled(x, y, w, thickness, color);
    this->drawBoxFilled(x, y, thickness, h, color);
    this->drawBoxFilled(x + w, y, thickness, h, color);
    this->drawBoxFilled(x, y + h, w + thickness, thickness, color);
}

void RenderManager::drawBox3D(Vector vecOrigin, Vector min, Vector max, Color color)
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
        
        this->drawLine(p1.x, p1.y, p2.x, p2.y, color);
    }
}

void RenderManager::drawGradient(int x, int y, int w, int h, Color col1, Color col2)
{
    this->drawBoxFilled(x, y, w, h, col1);
    
    Byte first  = col2.r();
    Byte second = col2.g();
    Byte third  = col2.b();
    
    for (int i = 0; i < h; i++)
    {
        float fi = i, fh = h;
        float a = fi / fh;
        int ia = a * 255;
        
        this->drawBoxFilled(x, y + i, w, 1, Color(first, second, third, ia));
    }
    
}

void RenderManager::drawCircle(Vector2D position, float points, float radius, Color color)
{
    float step = (float)M_PI * 2.0f / points;
    
    for (float a = 0; a < (M_PI * 2.0f); a += step)
    {
        Vector2D start(radius * cosf(a) + position.x, radius * sinf(a) + position.y);
        Vector2D end(radius * cosf(a + step) + position.x, radius * sinf(a + step) + position.y);
        this->drawLine(start.x, start.y, end.x, end.y, color);
    }
}

void RenderManager::drawFilledCircle(Vector2D center, float points, float radius, Color color)
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
    
    this->drawTexturedPolygon(points, vertices.data(), color);
}


//============================================ Misc =============================================\\

wstring RenderManager::stringToWstring(string str)
{
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
    try
    {
        return converter.from_bytes(str);
    }
    catch(range_error)
    {
        wostringstream s;
        s << str.c_str();
        return s.str();
    }
}

Vector2D RenderManager::getTextSize(const char* text, HFONT font)
{
    wstring wc = stringToWstring(text);
    int w, h;
    pSurface->GetTextSize(font, wc.c_str(), w, h);
    
    return Vector2D(w, h);
}

//============================================ Fonts =============================================\\

HFONT espfont, menufont;

HFONT RenderManager::createFont(const char *szFont, int tall, int flags)
{
    HFONT font = pSurface->CreateFont();
    pSurface->SetFontGlyphSet(font, szFont, tall, 150, 0, 0, flags);
    return font;
}

void RenderManager::InitialiseFonts()
{
    espfont     = this->createFont("Tahoma", 11, FONTFLAG_OUTLINE);
    menufont    = this->createFont("Tahoma", 11, FONTFLAG_DROPSHADOW);
    
    print("Fonts initlaised", Color::Orange());
}

