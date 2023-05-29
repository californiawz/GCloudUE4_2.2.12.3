//#if defined(_WIN32) || defined(_WIN64)
#ifndef _FISH_INI_FILE_
#define _FISH_INI_FILE_

#include "AString.h"
#include "AArray.h"

namespace ABase
{
    class IniFile
    {
    public:
        //
        static IniFile* CreateIniFile(const char*fileName);
        static IniFile* CreateEncrptedFile(const char* fileName);
        virtual ~IniFile();
    
    public:
        virtual bool Load(void) = 0;
        virtual bool Save(void) = 0;
        
    public:
        virtual AString ReadString( const char*section, const char*key, const char*value) = 0;
        virtual int ReadInt( const char*section, const char*key, int value) = 0;
        virtual long long ReadLongLong( const char*section, const char*key, long long value) = 0;
        virtual AString ReadString( const char*section, const char*key, const char*value, bool& hasValue) = 0;
        virtual int ReadInt( const char*section, const char*key, int value , bool& hasValue) = 0;
        virtual long long ReadLongLong( const char*section, const char*key, long long value , bool& hasValue) = 0;
        virtual bool WriteString( const char*section, const char*key, const char*value ) = 0;
        virtual bool WriteInt( const char*section, const char*key, int value ) = 0;
        virtual bool WriteLongLong( const char*section, const char*key, long long value ) = 0;
        //virtual void GetAllSections(AArray* sections) = 0;
        virtual void GetAllKeys( const char* section ,AArray* keys) = 0;
        virtual bool IsContainKey(const char* section, const char*key) = 0;
        
    public:
        virtual bool RemoveSection( const char*section ) = 0;
        virtual bool RemoveKey( const char*section, const char*key ) = 0;
        virtual bool RemoveAll() = 0;
        
    };
    
    int getline(FILE *fp, AString& line);
}


#endif

//#endif
