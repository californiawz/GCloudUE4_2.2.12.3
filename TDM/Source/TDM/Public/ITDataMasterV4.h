
#ifndef ITDataMasterV4_h
#define ITDataMasterV4_h

#include "ITDataMasterV3.h"
_TDM_Name_Space
{
    class ITDataMasterV4 : public ITDataMasterV3
    {
    protected:
        ITDataMasterV4(){}
        virtual ~ITDataMasterV4(){}

    public:
        static PUBLIC_API ITDataMasterV4* GetInstance();
        virtual int GetVersion() { return 4; }
        
        /**
        * 设置WebView UserAgent信息。
        * @param value      浏览器UserAgent信息
        * @return int       返回值：-1失败, 0成功
        */
        virtual PUBLIC_API int SetUserAgent(const char *value) = 0;
    };
}

#endif /* ITDataMasterV4_h */
