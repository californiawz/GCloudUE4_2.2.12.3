#pragma once

#include "hf_typedef.h"

namespace px_plugin
{
	struct IPluginImp {
		IPluginImp()
		{
			StartLoaderFile = nullptr;
			StopLoaderFile = nullptr;
			OnPixPluginLog = nullptr;
		}

		bool (*StartLoaderFile)(int windowID, const char *pszUrl,
								void (*funOnLoadedCall)(int windowId, const char *pszUrl,
														const unsigned char *pData,
														unsigned int unSize));

		bool (*StopLoaderFile)(const char *pszUrl);
		void (*OnPixPluginLog)(pixui::ELogGroup emLogGroup, pixui::ELogLevel emLogLevel, const char *pszLog);
	};

}// namespace px_plugin