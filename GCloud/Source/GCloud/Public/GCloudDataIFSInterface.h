#ifndef GCLOUD_DATAIFS_INTERFACE_H
#define GCLOUD_DATAIFS_INTERFACE_H

#include <string>
#include "GCloudPal.h"

#define DATAIFS_PATHLENGTH 256
#define DATAIFS_PWDLENGTH 64
#define DATAIFS_FILENAMELENGTH 64

#ifdef CU_OS_WIN32
#define DOLPHINEXPORTAPI __declspec(dllexport)
#else
#define DOLPHINEXPORTAPI
#endif

namespace GCloud
{

    typedef struct dataIFSInitInfo
    {
		bool isHasPwd;//Whether need a password, no need by default
		char password[DATAIFS_PWDLENGTH];
		cu_uint64 ifsFileSize;//ifs file size
        char ifspath[DATAIFS_PATHLENGTH];//the path of ifs file
        char ifsname[DATAIFS_FILENAMELENGTH];//the name of ifs file

        dataIFSInitInfo()
        {
			isHasPwd = false;
			ifsFileSize = 0;
            memset(password, 0, DATAIFS_PWDLENGTH);
            memset(ifspath, 0, DATAIFS_PATHLENGTH);
            memset(ifsname, 0, DATAIFS_FILENAMELENGTH);
        }
    }DATAIFSINITINFO;

	class  EXPORT_CLASS IGCloudIFSDataInterface 
	{
	public:
		virtual ~IGCloudIFSDataInterface(){}
		
		//===================Init=======================//		
        /// <summary>
        /// Initially read the handle of ifs.
        /// </summary>
        /// <param name="initinfo">ifs initialization information</param>
        /// <returns>success or failure</returns>
		virtual bool Init(const DATAIFSINITINFO * initinfo) = 0;

        /// <summary>
        /// HelpService
        /// Deinitialize, release resources
        /// </summary>
        /// <returns>success or failure</returns>
		virtual bool Uninit() = 0;

        /// <summary>
        /// The interface is to be implemented, combined with the download update, to determine whether a file is up to date within ifs
        /// </summary>
        /// <param name="fileName">file name</param>
        /// <returns>yes or no</returns>
		virtual bool IsFileNewestInIFS(const char* fileName) = 0;

        /// <summary>
        /// Obtain an error code for a particular phase when all interfaces fail.
        /// </summary>
        /// <returns>error code</returns>
		virtual cu_uint32 GetLastError() = 0;
        
        //virtual char* GetIFSPath(bool bIFSInAPK) = 0; 


        //===================Reader=======================//
        /// <summary>
        /// Read data from the IFS to the buffer.
        /// </summary>
        /// <param name="fileId">file ID</param>
        /// <param name="offset">The offset of the content that needs to be read in the file</param>
        /// <param name="buff">Buffer for receiving data</param>
        /// <param name="readlength">the length of data need to get</param>
        /// <returns>Whether read success</returns>
		virtual bool Read(cu_uint32 fileId, cu_uint64 offset, cu_uint8* buff, cu_uint32& readlength) = 0;

		//===================Query=======================//
        /// <summary>
        /// Get the file name based on the file ID.
        /// </summary>
        /// <param name="fileId">the file ID of the file</param>
        /// <returns>file name</returns>
		virtual  char* GetFileName(cu_uint32 fileId) = 0;
		
		/// <summary>
        /// Get the file ID based on the file name
        /// </summary>
        /// <param name="fileName">the file name of the file</param>
        /// <returns>file ID</returns>
		virtual cu_uint32 GetFileId(const char* fileName) = 0;
		
		/// <summary>
        /// Get the file length based on the file ID.
        /// </summary>
        /// <param name="fileId">the file ID of the file</param>
        /// <returns>the file length</returns>
		virtual cu_uint32 GetFileSize(cu_uint32 fileId) = 0;

		/// <summary>
        /// Determines whether the current file is a directory based on the file ID.
        /// </summary>
        /// <param name="fileId">the file ID of the file</param>
        /// <returns>Whether a directory</returns>
		virtual bool IsDirectory(cu_uint32 fileId) = 0;
		
	};
    EXPORT_API IGCloudIFSDataInterface* CreateDataIFSMgr();
    EXPORT_API void ReleaseDataIFSMgr(IGCloudIFSDataInterface** dataMgr);

}
// for dll
#ifdef CU_OS_WIN32
extern "C" DOLPHINEXPORTAPI GCloud::IGCloudIFSDataInterface* CreateDLLDataIFSMgr();
extern "C" DOLPHINEXPORTAPI void ReleaseDLLDataIFSMgr(GCloud::IGCloudIFSDataInterface** dataMgr);
#endif

#endif

