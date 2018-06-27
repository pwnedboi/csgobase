#pragma once

enum TraceType_t /* Taken from GamerFood's TraceEngine. Credits to him! */
{
    TRACE_EVERYTHING = 0,
    TRACE_WORLD_ONLY,                // NOTE: This does *not* test static props!!!
    TRACE_ENTITIES_ONLY,            // NOTE: This version will *not* test static props
    TRACE_EVERYTHING_FILTER_PROPS,    // NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

struct Ray_t
{
    Ray_t( ) { }
    
    VectorAligned        m_Start;
    VectorAligned        m_Delta;
    VectorAligned        m_StartOffset;
    VectorAligned        m_Extents;
    const matrix3x4_t    *m_pWorldAxisTransform;
    bool                m_IsRay;
    bool                m_IsSwept;
    
    void Init( Vector vecStart, Vector vecEnd )
    {
        m_Delta = VectorAligned( vecEnd - vecStart );
        m_IsSwept = ( m_Delta.LengthSqr( ) != 0 );
        m_Extents.Zero( );
        m_pWorldAxisTransform = NULL;
        m_IsRay = true;
        m_StartOffset.Zero( );
        m_Start = vecStart;
    }
};

struct cplane_t
{
    Vector normal;
    float dist;
    unsigned char type;
    unsigned char signbits;
    unsigned char pad[2];
};

class ITraceFilter
{
public:
    virtual bool ShouldHitEntity( C_BaseEntity* pEntityHandle, int contentsMask )
    {
        return !( pEntityHandle == pSkip );
    }
    virtual TraceType_t    GetTraceType( )
    {
        return TRACE_EVERYTHING;
    }
    void* pSkip; // Entity
    int   m_icollisionGroup;
};

class CTraceFilter : public ITraceFilter
{
public:
    
    CTraceFilter(C_BaseEntity* pEntToSkip = NULL)
    {
        pSkip = pEntToSkip;
    }
    
    virtual bool ShouldHitEntity( C_BaseEntity* pEntityHandle, int contentsMask )
    {
        return !( pEntityHandle == pSkip );
    }
    
    virtual TraceType_t    GetTraceType( ) const
    {
        return TRACE_EVERYTHING;
    }
    void* pSkip;
};

class CTraceFilterSkipTwoEntities : public ITraceFilter
{
public:
    CTraceFilterSkipTwoEntities( void *pPassEnt1, void *pPassEnt2 )
    {
        pPassEntity1 = pPassEnt1;
        pPassEntity2 = pPassEnt2;
    }
    
    virtual bool ShouldHitEntity( C_BaseEntity *pEntityHandle, int contentsMask )
    {
        return !( pEntityHandle == pPassEntity1 || pEntityHandle == pPassEntity2 );
    }
    
    virtual TraceType_t GetTraceType( ) const
    {
        return TRACE_EVERYTHING;
    }
    
    void *pPassEntity1;
    void *pPassEntity2;
};

class CTraceFilterWorldOnly : public CTraceFilter
{
public:
    bool ShouldHitEntity(C_BaseEntity* pServerEntity, int contentsMask)
    {
        return false;
    }
    virtual TraceType_t    GetTraceType() const
    {
        return TRACE_WORLD_ONLY;
    }
};

typedef bool( *ShouldHitFunc_t )( IHandleEntity *pHandleEntity, int contentsMask );

class CTraceFilterSimple : public CTraceFilter
{
public:
    // It does have a base, but we'll never network anything below here..
    CTraceFilterSimple( const IHandleEntity *passentity, int collisionGroup, ShouldHitFunc_t pExtraShouldHitCheckFn = NULL );
    
    virtual bool ShouldHitEntity( IHandleEntity *pHandleEntity, int contentsMask );
    
    virtual void SetPassEntity( const IHandleEntity *pPassEntity )
    {
        m_pPassEnt = pPassEntity;
    }
    
    virtual void SetCollisionGroup( int iCollisionGroup )
    {
        m_collisionGroup = iCollisionGroup;
    }
    
    const IHandleEntity *GetPassEntity( void )
    {
        return m_pPassEnt;
    }
    
private:
    
    const IHandleEntity *m_pPassEnt;
    int m_collisionGroup;
    ShouldHitFunc_t m_pExtraShouldHitCheckFunction;
    
};

struct csurface_t
{
    const char*        name;
    short            surfaceProps;
    unsigned short    flags;
};

struct trace_t
{
    Vector startpos;
    Vector endpos;
    cplane_t plane;
    
    float fraction;
    
    int contents;
    unsigned int dispFlags;
    
    bool allsolid;
    bool startsolid;
    
    float fractionleftsolid;
    
    csurface_t surface;
    
    HitGroups hitgroup;
    short physicsbone;
    
    unsigned short worldSurfaceIndex;
    C_BaseEntity* m_pEnt;
    int hitbox;
    
    bool DidHit() const;
    bool DidHitWorld() const;
    bool DidHitNonWorldEntity() const;
    
};

inline bool trace_t::DidHit() const
{
    return fraction < 1.0f || allsolid || startsolid;
}

inline bool trace_t::DidHitWorld() const
{
    return m_pEnt->GetIndex() == 0;
}

inline bool trace_t::DidHitNonWorldEntity() const
{
    return m_pEnt != NULL && !DidHitWorld();
}

class IEngineTrace
{
public:
    // Returns the contents mask + entity at a particular world-space position
    virtual int GetPointContents(const Vector &vecAbsPosition, int contentsMask = MASK_ALL, IHandleEntity** ppEntity = NULL) = 0;
    
    // Returns the contents mask of the world only @ the world-space position (static props are ignored)
    virtual int GetPointContents_WorldOnly(const Vector &vecAbsPosition, int contentsMask = MASK_ALL) = 0;
    
    // Get the point contents, but only test the specific entity. This works
    // on static props and brush models.
    //
    // If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
    // bFailed to true if bFailed is non-null.
    virtual int GetPointContents_Collideable(ICollideable *pCollide, const Vector &vecAbsPosition) = 0;
    
    // Traces a ray against a particular entity
    virtual void ClipRayToEntity(const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace) = 0;
    
    // Traces a ray against a particular entity
    virtual void ClipRayToCollideable(const Ray_t &ray, unsigned int fMask, ICollideable *pCollide, trace_t *pTrace) = 0;
    
    // A version that simply accepts a ray (can work as a traceline or tracehull)
    virtual void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace) = 0;
};

