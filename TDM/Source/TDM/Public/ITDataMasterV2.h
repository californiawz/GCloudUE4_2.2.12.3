
#ifndef ITDataMasterV2_hpp
#define ITDataMasterV2_hpp

#include "ITDataMaster.h"
_TDM_Name_Space
{
    #define TDM_JINGFEN_GAMEID     "tdm_jf_game_id"          //经分ID
    #define TDM_PLATFORM_GAMEID    "tdm_platform_id"         //登录第三方账号平台分配的ID
    #define TDM_ACCOUNT_TYPE       "tdm_account_type"       //账号类型，openid为1，gopenid为2
    #define TDM_ZONE_ID            "tdm_zone_id"            //用户登录的游戏小区ID
    
    class ITDataMasterV2 : public ITDataMaster
    {
    protected:
        ITDataMasterV2(){}
        virtual ~ITDataMasterV2(){}

    public:
        static PUBLIC_API ITDataMasterV2* GetInstance();

    public:
        virtual int GetVersion() { return 2; }
        virtual PUBLIC_API void ReportLoginV2(int platform, const char* openid, const IEventData *eventData) = 0;
    };
}

#endif /* ITDataMasterV2_h */
