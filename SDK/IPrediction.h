class IPrediction
{
public:
    
    void RunCommand(C_BaseEntity *player, CUserCmd *ucmd, IMoveHelper *moveHelper)
    {
        typedef void (* oRunCommand)(void*, C_BaseEntity*, CUserCmd*, IMoveHelper*);
        return getvfunc< oRunCommand >(this, 20)(this, player, ucmd, moveHelper);
    }
    
    void SetupMove(C_BaseEntity* player, CUserCmd* cmd, IMoveHelper* helper, CMoveData* move)
    {
        typedef void (* oSetupMove)(void*, C_BaseEntity*, CUserCmd*, IMoveHelper*, CMoveData*);
        return getvfunc<oSetupMove>(this, 21)(this, player, cmd, helper, move);
    }
    
    void FinishMove(C_BaseEntity* player, CUserCmd* cmd, CMoveData* move)
    {
        typedef void (* oFinishMove)(void*, C_BaseEntity*, CUserCmd*, CMoveData*);
        return getvfunc<oFinishMove>(this, 22)(this, player, cmd, move);
    }
    
};
