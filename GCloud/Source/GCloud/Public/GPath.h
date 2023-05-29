
#ifndef __GPATH_H
#define __GPATH_H
#include "GCloudPal.h"
#include "AString.h"
#include "AArray.h"
#include <string>
#include <map>

namespace GCloud
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

        static void GetSubPath(GCloud::AString& dest, const char* pszSrc, const char* pszSubPath);
        static GCloud::AString& AppendSubPath(GCloud::AString& strPath, const char* subPath);
        
        static void GetFileName(const char* fullPath, GCloud::AString& fileShortName);

    public:
        static bool CreatePath(const char* pszPath);
        static bool CreatePathRecursive(const char* pszPath);
        static bool RemovePath(const char* pszPath);
        static bool GetFiles(const char* pszPath, AArray* files);
        static bool Exist(const char* pszPath);
        static std::string JoinPath(const std::string& path1, const std::string& path2);
        static bool NormalizePath(char* lpszDest, int nCount, const char* lpszSrc);
        static bool NormalizeIFSPath(char* lpszDest, int nCount, const char* lpszSrc);
        static bool NormalizeLinuxPath(char* lpszDest, int nCount, const char* lpszSrc);
        static bool GetParentPath(const std::string& path, std::string& parentPath);
        static bool isFilepathInDirectoryPath(const std::string& filepath, const std::string& directPath);
        static bool MakeSureDirUseFull(const std::string& strDir);
        static bool RemoveFilesInDir(const std::string& dirPath);
        static bool GetAllFilesInDir(const std::string dirPath, std::map<std::string, std::string>& mpFiles);
        
    //public:
    //    static GCloud::AString NormalizePath(const char* src);

    public:
        static const char* GetAppPath();
    };
}

#endif
