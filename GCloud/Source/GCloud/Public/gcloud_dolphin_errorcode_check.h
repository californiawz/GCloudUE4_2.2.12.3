#ifndef _GCLOUD_DOLPHIN_ERROR_CODE_CHECK_H
#define _GCLOUD_DOLPHIN_ERROR_CODE_CHECK_H

namespace gcloud
{
namespace dolphin
{
	enum first_module
	{
		first_module_init = 0,
		first_module_version = 2,		//versionmanager，更新模块
	};

	enum second_module
	{
		second_module_init = 0,
		second_module_versionmanager = 1,       //更新控制
		second_module_version_action = 2,       //连接版本服务器
		second_module_srcupdate_cures_action = 8,       //资源更新阶段
		second_module_appupdate_action = 10,			//程序更新阶段
	};

	//这个用于出现错误，内部与iips项目组确认问题
	enum error_type_inside
	{
		error_type_inside_init = 0,
		error_type_inside_download_error = 1,          //下载错误
		error_type_inside_system_error = 2,            //系统错误
		error_type_inside_module_error = 3,            //模块内部错误
		error_type_inside_ifs_error = 4,               //数据结构错误
		error_type_inside_should_not_happen = 5,       //流程上不能出现的错误
	};

	//这个用于提示用户，出现此类错误如何解决问题。
	enum error_type
	{
		error_type_init = 0,
		error_type_network = 1,                         //网络错误，提示玩家在网络正常状态重启游戏更新
		error_type_net_timeout = 2,                     //网络超时，游戏侧先重试，提示玩家在网络正常状态重启游戏更新
		error_type_device_hasno_space = 3,              //磁盘空间不足，提示玩家提供充足的sd卡空间，然后再启动游戏
		error_type_other_system_error = 4,              //其他系统错误，没权限，或磁盘问题，提示玩家重启手机
		error_type_other_error = 5,                     //模块其他错误，提示玩家重启手机
		error_type_cur_version_not_support_update = 6,  //当前版本不支持更新，提示玩家市场上下载最新版本
		error_type_cur_net_not_support_update = 8,		//当前的环境下载的apk异常（运营商缓存），提示玩家到市场下载最新版本
	};

	struct ErrorCodeInfo
	{
		bool m_bCheckOk;                         //检查是否成功
		error_type m_nErrorType;                        //错误类型，根据此项，提示用户（参见error_type）
		first_module m_nFirstModule;                      //一级模块，不必提示用户，记录日志，以备定位，开发阶段调试定位用
		second_module m_nSecondModule;                     //二级模块，不必提示用户，记录日志，以备定位，开发阶段调试定位用
		error_type_inside m_nInsideErrorType;                  //内部错误类型，不必提示用户，记录日志，以备定位，开发阶段调试定位用
		int m_nErrorCode;                        //具体错误码，不必提示用户，记录日志，以备定位，开发阶段调试定位用
		int m_nLastCheckError;                   //onerror回调的具体错误码，展示到用户提示框以便用户投诉定位，记录日志，以备定位，开发阶段调试定位用
		ErrorCodeInfo(bool bOk)
		{
			m_bCheckOk = bOk;
			m_nFirstModule = first_module::first_module_init;
			m_nSecondModule = second_module::second_module_init;
			m_nErrorType = error_type::error_type_init;
			m_nInsideErrorType = error_type_inside::error_type_inside_init;
			m_nErrorCode = 0;
			m_nLastCheckError = 0;
		}
		ErrorCodeInfo(const ErrorCodeInfo& codeInfo)
		{
			m_bCheckOk = codeInfo.m_bCheckOk;
			m_nFirstModule = codeInfo.m_nFirstModule;
			m_nSecondModule = codeInfo.m_nSecondModule;
			m_nErrorType = codeInfo.m_nErrorType;
			m_nInsideErrorType = codeInfo.m_nInsideErrorType;
			m_nErrorCode = codeInfo.m_nErrorCode;
			m_nLastCheckError = codeInfo.m_nLastCheckError;
		}
	};

	class IIPSMobileErrorCodeCheck
	{
	private:
		int m_nLastCheckErrorCode;
	public:
		IIPSMobileErrorCodeCheck()
		{
			m_nLastCheckErrorCode = 0;
		}

		ErrorCodeInfo CheckIIPSErrorCode(int nErrorCode)
		{
			m_nLastCheckErrorCode = nErrorCode;
			int nFirstModule = GetFirstModuleType();
			int nSecondModule = GetSecondModuleType();
			int nErrorInsideType = GetErrorCodeType();
			int nRealErrorCode = GetRealErrorCode();
			int nErrorType = error_type::error_type_init;

			if (nErrorInsideType == error_type_inside::error_type_inside_download_error)
			{
				//下载错误
				int nDownloadErrorType = GetDownloadErrorType(nRealErrorCode);
				int realdownerror = GetReadDownloadErrorCode(nRealErrorCode);
				if (nDownloadErrorType == 5)
				{
					//磁盘满错误码
					if (realdownerror == 112 || realdownerror == 39 || realdownerror == 28)
					{
						nErrorType = error_type::error_type_device_hasno_space;
					}
					else
					{
						nErrorType = error_type::error_type_other_system_error;
					}
				}
				else if (nDownloadErrorType == 1)
				{
					nErrorType = error_type::error_type_net_timeout;
					realdownerror = nRealErrorCode;
				}
				else if (nDownloadErrorType == 2)
				{
					nErrorType = error_type::error_type_network;
				}
				else
				{
					nErrorType = error_type::error_type_other_error;
				}
				nRealErrorCode = realdownerror;
			}
			else if (nErrorInsideType == error_type_inside::error_type_inside_system_error)
			{
				//系统错误
				//磁盘满错误码
				if (nRealErrorCode == 112 || nRealErrorCode == 39 || nRealErrorCode == 28)
				{
					nErrorType = error_type::error_type_device_hasno_space;
				}
				else
				{
					nErrorType = error_type::error_type_other_system_error;
				}
			}
			else if (nErrorInsideType == error_type_inside::error_type_inside_module_error)
			{
				//各模块错误
				if (nFirstModule == first_module::first_module_version)
				{
					nErrorType = GetSecondModuleNoticeErrorType(nSecondModule, nRealErrorCode);
				}
				else
				{
					nErrorType = error_type::error_type_other_error;
				}
			}
			else if (nErrorInsideType == error_type_inside::error_type_inside_ifs_error)
			{
				//系统错误
				//磁盘满错误码
				if (nRealErrorCode == 112 || nRealErrorCode == 39 || nRealErrorCode == 28)
				{
					nErrorType = error_type::error_type_device_hasno_space;
				}
				else
				{
					nErrorType = error_type::error_type_other_system_error;
				}
			}
			else if (nErrorInsideType == error_type_inside::error_type_inside_should_not_happen)
			{
				nErrorType = error_type::error_type_other_error;
			}
			else
			{
				nErrorType = error_type::error_type_other_error;
			}

			ErrorCodeInfo stInfo(false);
			stInfo.m_bCheckOk = true;
			stInfo.m_nErrorType = (error_type)nErrorType;
			stInfo.m_nFirstModule = (first_module)nFirstModule;
			stInfo.m_nSecondModule = (second_module)nSecondModule;
			stInfo.m_nInsideErrorType = (error_type_inside)nErrorInsideType;
			stInfo.m_nErrorCode = nRealErrorCode;
			stInfo.m_nLastCheckError = m_nLastCheckErrorCode;
			return stInfo;
		}

	private:
		//获取错误码对应一级模块
		int GetFirstModuleType()
		{
			int nTemp = m_nLastCheckErrorCode >> 23;
			nTemp = nTemp & 0x07;
			return nTemp;
		}
		//获取错误码对应二级模块
		int GetSecondModuleType()
		{
			int nTemp = m_nLastCheckErrorCode >> 26;
			nTemp = nTemp & 0x0f;
			return nTemp;
		}
		//获取错误码类型
		int GetErrorCodeType()
		{
			int nTemp = m_nLastCheckErrorCode >> 20;
			nTemp = nTemp & 0x07;
			return nTemp;
		}
		//获取具体错误码
		int GetRealErrorCode()
		{
			int nTemp = m_nLastCheckErrorCode & 0xfffff;
			return nTemp;
		}
		int GetDownloadErrorType(int downloaderror)
		{
			int nTemp = downloaderror >> 16;
			nTemp = nTemp & 0x0f;
			return nTemp;
		}

		int GetReadDownloadErrorCode(int downloaderror)
		{
			int nTemp = downloaderror & 0xffff;
			return nTemp;
		}

		int GetSecondModuleNoticeErrorType(int secondModule, int errorcode)
		{
			int nTemp = 0;
			if (secondModule == second_module::second_module_versionmanager)
			{
				nTemp = error_type::error_type_other_error;
			}
			else if (secondModule == second_module::second_module_version_action)
			{
				if (errorcode == 15 || errorcode == 16 || errorcode == 17 || errorcode == 22)
				{
					nTemp = error_type::error_type_cur_version_not_support_update;
				}
				else
				{
					nTemp = error_type::error_type_network;
				}
			}
			else
			{
				nTemp = error_type::error_type_other_error;
			}
			return nTemp;
		}
	};
}
}

#endif//_GCLOUD_DOLPHIN_ERROR_CODE_CHECK_H