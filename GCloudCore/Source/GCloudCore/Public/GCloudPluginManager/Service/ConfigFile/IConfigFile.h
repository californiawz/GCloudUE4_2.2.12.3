//
// Created by aaronyan on 2019/8/23.
//

#ifndef ICONFIGFILE_H
#define ICONFIGFILE_H
namespace GCloud {
    class IConfigFile
    {
    public:
        IConfigFile(){};
        virtual ~IConfigFile(){};
        
    public:
        virtual bool SetCache(const char* section, const char* key, int value) = 0;
        virtual bool SetCache(const char* section, const char* key, long long value) = 0;
        virtual bool SetCache(const char* section, const char* key, const char* value) = 0;
        virtual bool SetCache(const char* section, const char* key, bool value) = 0;
        virtual bool RemoveValueForKey(const char*  section, const char*  key) = 0;
        virtual bool RemoveSection(const char* section) = 0;
        virtual bool RemoveAll() = 0;
        virtual bool SaveCacheToFile() = 0;
        
        virtual bool SetAndSave(const char* section, const char* key, int value) = 0;
        virtual bool SetAndSave(const char* section, const char* key, long long value) = 0;
        virtual bool SetAndSave(const char* section, const char* key, const char* value) = 0;
        virtual bool SetAndSave(const char* section, const char* key, bool value) = 0;
        virtual bool RemoveValueForKeyAndSave(const char*  section, const char*  key) = 0;
        virtual bool RemoveSectionAndSave(const char* section) = 0;
        virtual bool RemoveAllAndSave() = 0;
        
        virtual long long GetFromCache(const char* section, const char* key, long long defaultvalue) = 0;
        virtual int GetFromCache(const char* section, const char* key, int defaultvalue) = 0;
        virtual bool GetFromCache(const char* section, const char* key, char* value, int& len, const char* defaultvalue) = 0;
        virtual bool GetFromCache(const char* section, const char* key, bool defaultvalue) = 0;
        virtual bool IsContainKey(const char* section, const char* key) = 0;
    };
    // for Games
    IConfigFile* NewGCloudConfigFile(const char* name);
    void DeleteGCloudConfigFile(IConfigFile** configFile);
}
#endif //ILOCALCONFIG_H
