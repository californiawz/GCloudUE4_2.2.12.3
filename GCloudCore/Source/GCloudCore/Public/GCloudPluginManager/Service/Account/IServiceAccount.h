///*
/*!
 * @Header IServiceAccount.h
 * @Author Hillson Song
 * @Version 1.0.0
 * @Date 2018/9/3
 * @Abstract 文件功能的声明
 *
 * @Module MSDK
 *
 * Copyright © 2018 GCloud. All rights reserved.
 */

#ifndef IServiceAccount_H
#define IServiceAccount_H

#include "GCloudPluginManager/IPluginService.h"

namespace GCloud { namespace Plugin { namespace MSDK {
    
    class MSDKAccount
    {
    public:
        char * openID;
        char * token;
        char * userName;
        char * channel;
        int channelID;
        int64_t tokenExpire;
        
    public:
        MSDKAccount()
        {
            openID = (char *) calloc(128 , sizeof(char));
            token = (char *) calloc(1024 , sizeof(char)); // 后台对第三方 token 进行非对称加密，预留较大的空间
            userName = (char *) calloc(64 , sizeof(char));
            channel = (char *) calloc(16 , sizeof(char));
            channelID = 0;
            tokenExpire = 0;
        };
        ~MSDKAccount()
        {
            if (openID != NULL)
            {
                free(openID);
                openID = NULL;
            }
            
            if (token != NULL)
            {
                free(token);
                token = NULL;
            }
            
            if (userName != NULL)
            {
                free(userName);
                userName = NULL;
            }
            
            if (channel != NULL)
            {
                free(channel);
                channel = NULL;
            }
        };
    };
    
    class IServiceAccount : public GCloud::Plugin::IPluginService
    {
        
    public:
        virtual bool getLoginRet(MSDKAccount &account) = 0;
    };
    
} } }

#endif /* IServiceAccount_H */
