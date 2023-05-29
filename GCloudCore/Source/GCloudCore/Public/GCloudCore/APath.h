
#ifndef __XPATH_H
#define __XPATH_H
#include "ABasePal.h"
#include "AString.h"
#include "AArray.h"

namespace ABase
{
    class EXPORT_CLASS CPath
    {
    public:
#ifdef ANDROID
        static void SetAppPath(const char* path);
        static const char* GetInnerFilePath();
        static const char* GetInnerCachePath();
#endif
        static const char* GetDocPath();
        static const char* GetCachePath();
        static const char* GetDefaultConfigFile();

        static void GetSubPath(AString& dest, const char* pszSrc, const char* pszSubPath);
        static AString& AppendSubPath(AString& strPath, const char* subPath);
        
        static void GetFileName(const char* fullPath, AString& fileShortName);

    public:
        static bool CreatePath(const char* pszPath);
        static bool RemovePath(const char* pszPath);
        static bool GetFiles(const char* pszPath, AArray* files);
        
        
    public:
        static AString NormalizePath(const char* src);

    public:
        static const char* GetAppPath();
    };
}

#endif
