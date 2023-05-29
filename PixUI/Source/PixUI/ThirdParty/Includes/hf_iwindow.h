#pragma once

#include "hf_typedef.h"
#ifdef WITH_H5WINDOW_SIGNAL
#include <multicast.hpp>
#endif

namespace script
{
	class ScriptState;
}
namespace pixui
{
	class H5Window;

#ifdef WITH_H5WINDOW_SIGNAL
	struct IWindowSignal {
		util::multifunction<void(H5Window *, script::ScriptState *)> sigOnScriptStateInit;
		util::multifunction<void(H5Window *, script::ScriptState *)> sigOnScriptStateDone;
		util::multifunction<void(pixui::H5Window *)> sigOnWindowLoaded;
		util::multifunction<void(H5Window *, bxstr, bool)> sigOnLoadBegin;
		util::multifunction<void(H5Window *, bxstr, bool)> sigOnLoadComplete;
		util::multifunction<void(const bxstr &)> sigOnTitleChanged;
		util::multifunction<void(const bxstr &)> sigOnStatePopped;
	};
#endif

	typedef void (*PFunWindowOpenCallBack)(void *pContext, int nWndId, int nChildWndId);

	//window interface

	typedef pixui::uint32 PxViewHandle;
	class IHostWindow
	{
	public:
		virtual ~IHostWindow(){};

	public:
		enum InternalErrorCode
		{
			JSBYTECODE_ERROR = 0,
		};
		virtual void onLoadComplete(const char *pszUrl, const int nErrorCode){};
		virtual void onInternalError(int error, const char *msg){};

		virtual uint_ptr onOpen(const char *pszUrl = "", const char *pszName = "", const char *pszFeatures = "", bool bReplace = false, void *pContext = nullptr, PFunWindowOpenCallBack callback = nullptr) { return nullptr; };
		virtual void onClose(){};

		virtual void onAlert(const char *pszText){};
		virtual bool onConfirm(const char *pszMessage) { return false; };
		virtual const char *onPrompt(const char *strText, const char *strDefaultText) { return ""; };

		virtual void onMoveBy(const int nXposMoveBy, const int nYposMoveBy){};
		virtual void onMoveTo(const int nXposMoveTo, const int nYposMoveTo){};
		virtual void onResizeBy(const int nOffsetWidth, const int nOffsetHeight){};
		virtual void onResizeTo(const int nNewWidth, const int nNewHeight){};
		virtual void onScrollBy(const int nOffsetXpos, const int nOffsetYpos){};
		virtual void onScrollTo(const int nNewXpos, const int nNewYpos){};
		virtual int getOpener() { return 0; };
		virtual uint32 getId() { return 0; };
		virtual void setWindowPass(bool value){};
		virtual void setWindowPriority(int value){};

		/*
        for custom event
        */
		virtual void onMessage(const char *pszMessage){};

		/*
        OnActivateInput
        */
		virtual bool onActivateInput(EKeyboardType emKeyboardType, const char *pszDefaultText, const char *pszHintText) { return false; };

		/*
        OnDeativateInput
        */
		virtual bool onDeativateInput() { return false; };

		virtual const char *getClipboardText() { return "noClipboard"; };
		virtual void setClipboardText(const char *text){};

		//virtual ScriptExternal *createExternal() {};
	};

	typedef pixui::IHostWindow *IHostWindowPtr;
}// namespace pixui
