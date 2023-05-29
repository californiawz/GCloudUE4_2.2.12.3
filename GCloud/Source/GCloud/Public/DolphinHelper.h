
#include "AString.h"

namespace GCloud
{    
class EXPORT_CLASS DolphinHelper   
	 {    public:
#ifdef ANDROID       
		       static const char* GetCurApkPath();
               static bool InstallAPK(const char* path);
			   static const char* GetSDCardPath();
#endif   
	 static bool CopyResFileFromApp(const char* srcPath, const char* dstPath);
     };
}
