#ifndef GCLOUD_DOLPHINE_UTILITY_H
#define GCLOUD_DOLPHINE_UTILITY_H
#include "GCloudPal.h"

#ifdef CU_OS_WIN32
#define DOLPHINEIMPXPORTAPI __declspec(dllexport)
#else
#define DOLPHINEIMPXPORTAPI
#endif

namespace GCloud
{
	#define GR_MAX_PATH 256

	typedef struct _GRFileInfo
	{
		char			name[GR_MAX_PATH];
	} GRFileInfo;

	typedef struct _GRFileList
	{
		cu_uint32		size;
		GRFileInfo *	list;
	} GRFileList;

	// same with dolphinPathInfo.updatePath, it is just a path, we will find the res under the floder
	// end with \0
	typedef struct _DolphinUtilInitInfo
	{
		char			resOrifsPath[GR_MAX_PATH];  
	} DolphinUtilInitInfo;

    class EXPORT_CLASS GCloudDolphinUtility
    {
    public:
        virtual ~GCloudDolphinUtility() {}
		
		// if fail, just extract *.ifs.res and filelist.json to _DolphinUtilInitInfo.resOrifsPath
		virtual bool		Init(DolphinUtilInitInfo * info) = 0;
		virtual bool		Uninit() = 0;

		// do not release grfile, or any GRFileInfo in the list
		// you must copy the data from it to anywhere
		// we will delete it, when Uninit or Call the interface again
		virtual GRFileList* GetFileList() = 0;
    };
    
    EXPORT_API GCloudDolphinUtility * CreateDolphinUtility();
    EXPORT_API void ReleaseDolphinUtility(GCloudDolphinUtility ** dolphinUtility);
}

#ifdef CU_OS_WIN32
extern "C" DOLPHINEIMPXPORTAPI GCloud::GCloudDolphinUtility * CreateDllDolphinUtility();
extern "C" DOLPHINEIMPXPORTAPI void ReleaseDllDolphinUtility(GCloud::GCloudDolphinUtility ** dolphinUtility);
#endif

#endif
