//
//  ABaseCommon.h
//  ABase
//
//  Created by vforkk on 16/10/11.
//  Copyright © 2016年 vforkk. All rights reserved.
//

#ifndef ABaseCommon_h
#define ABaseCommon_h
#include "AString.h"

namespace ABase
{

    class EXPORT_CLASS ABaseCommon
    {
    private:
        AString m_projectname;
        AString _channelid;
        AString _openid;
        AString _transceiver_url;
        AString _comParams;
        AString _gameid;

        ABaseCommon()
        {
            m_projectname = "GCloud";
        }

    public:
        static ABaseCommon& GetInstance();
        static void ReleaseInstance();

    public:
        void SetProjectName(const char* projectname)
        {
            m_projectname = projectname;
        }

        const char* GetProjectName()
        {
            return m_projectname.c_str();
        }

    public:
        void SetUserInfo(const char* channelid, const char* openid);

        const char* GetChannelID();

        const char* GetOpenID();
        
        const char* GetTransceiverUrl();

        const char* GetComParams();

        const char* GetGameID();



    };
}

#endif /* ABaseCommon_h */
