//
//  ITDataMaster_GCloud.h
//  TDM
//
//  Created by lucasfan on 18/12/10.
//  Copyright © 2018年 TDataMaster. All rights reserved.
//


#include <stdint.h>
#include "TDataMasterDefines.h"

#define GCLOUD_API TDM_EXPORT

_TDM_Name_Space
{

#ifdef  __cplusplus
extern "C"
{
#endif
	class IEvent
	{
	public:
		virtual ~IEvent() {}

	public:
		virtual void Add(const char* key, const char* value, const int valueLen) = 0;
		virtual void Add(int key, const char* value, const int valueLen) = 0;
		virtual void Add(int key, int64_t value) = 0;

	public:
		virtual void Report() = 0;
	};

	GCLOUD_API void TDM_Initialize(const char* appId, const char* appChannel, bool isTest);
	GCLOUD_API void TDM_Release_Instance();
	GCLOUD_API void TDM_Set_Log_Level(int level);
	GCLOUD_API void TDM_Enable_Report(bool enable);
    GCLOUD_API void TDM_Enable_Device_Info(bool enable);

	GCLOUD_API IEvent* TDM_Create_Event(int srcId, const char* eventName);
	GCLOUD_API void TDM_Destroy_Event(IEvent** ppEvent);
	GCLOUD_API void TDM_Report_Binary(int srcID, const char* eventName, const char* data, int len);

	#ifdef  __cplusplus
	}
	#endif

}
