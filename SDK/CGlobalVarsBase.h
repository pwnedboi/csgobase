#pragma once

class CGlobalVarsBase
{
public:
    
    CGlobalVarsBase(bool bIsClient);
    bool IsClient() const;
    int  GetNetworkBase(int nTick, int nEntity);
    
public:
    
    float       realtime;                       // 0x00
    int         framecount;                     // 0x4
    float       absoluteframetime;              // 0x8
    float       absoluteframestarttimestddev;   // 0xC
    float       curtime;                        // 0x10
    float       frametime;
    int         maxClients;
    int         tickcount;
    float       interval_per_tick;
    float       interpolation_amount;
    int         simTicksThisFrame;
    int         network_protocol;
    void*       pSaveData;
    
private:
    
    bool        m_bClient;
    
public:
    
    bool        m_bRemoteClient;
    
private:
    
    int         nTimestampNetworkingBase;
    int         nTimestampRandomizeWindow;
    
};
