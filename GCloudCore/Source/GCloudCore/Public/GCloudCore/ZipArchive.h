#ifndef __ZipArchive__
#define __ZipArchive__
#include "ABasePal.h"

namespace ABase
{
    class EXPORT_CLASS ZipArchive
    {
    private:
        void*		_zipFile;  //zipFile
    public:
        ZipArchive();
        ~ZipArchive();
        bool CreateZipFile(const char* zipFile);
        bool AddFileToZip(const char* file, const char* newName);
        bool CloseZipFile();

    };
}

#endif
