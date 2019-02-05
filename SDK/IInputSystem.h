class IInputSystem
{
public:
    
    void EnableInput(bool bEnable)
    {
        typedef void (* oEnableInput)(void*, bool);
        return getvfunc<oEnableInput>(this, 11)(this, bEnable);
    }
    
    bool IsButtonDown(ButtonCode_t code)
    {
        typedef bool (* oIsButtonDown)(void*, ButtonCode_t);
        return getvfunc<oIsButtonDown>(this, 15)(this, code);
    }
    
    void ResetInputState()
    {
        typedef void (* oResetInputState)(void*);
        return getvfunc<oResetInputState>(this, 39)(this);
    }
    
    const char* ButtonCodeToString(ButtonCode_t code)
    {
        typedef const char* (* oButtonCodeToString)(void*, ButtonCode_t);
        return getvfunc<oButtonCodeToString>(this, 40)(this, code);
    }
    
    ButtonCode_t VirtualKeyToButtonCode(int nVirtualKey)
    {
        typedef ButtonCode_t (* oVirtualKeyToButtonCode)(void*, int);
        return getvfunc<oVirtualKeyToButtonCode>(this, 44)(this, nVirtualKey);
    }
    
    int ButtonCodeToVirtualKey(ButtonCode_t code)
    {
        typedef int (* oButtonCodeToVirtualKey)(void*, ButtonCode_t);
        return getvfunc<oButtonCodeToVirtualKey>(this, 45)(this, code);
    }
    
    void GetCursorPosition(int* m_pX, int* m_pY)
    {
        typedef void (* oGetCursorPosition)(void*, int*, int*);
        return getvfunc<oGetCursorPosition>(this, 56)(this, m_pX, m_pY);
    }
    
};
