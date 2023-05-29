/**************************************************

**** @file:     IPixInputSystem.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once
#include "CoreMinimal.h"

#include <string>
#include "Layout/Geometry.h"
#include "Widgets/SWidget.h"

#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION < 5

/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION < 23
//for old version
#include "Framework/Text/TextRange.h"
#else
#include "Core.h"
#endif //ENGINE_MINOR_VERSION < 23
/////////////////////////////////////////////////////////////////////for ue4

#else

/////////////////////////////////////////////////////////////////////for ue5
#include "Containers/UnrealString.h"
/////////////////////////////////////////////////////////////////////for ue5

#endif //ENGINE_MAJOR_VERSION < 5


#include "Widgets/Input/IVirtualKeyboardEntry.h"
#include "GenericPlatform/ITextInputMethodSystem.h"

class IInputSystem
{
public:
    IInputSystem();
    virtual~IInputSystem();

public:
    void ActivateInput();

    void DeativateInput();

    void OnInputTick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

public:
    virtual FText GetInputText() = 0;
    virtual FText GetInputHintText() = 0;
    virtual EKeyboardType GetVirtualKeyboardType() = 0;

#if ENGINE_MAJOR_VERSION < 5

	/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION > 19
	virtual FVirtualKeyboardOptions GetVirtualKeyboardOptions() = 0;
#endif	//ENGINE_MINOR_VERSION > 19
	/////////////////////////////////////////////////////////////////////for ue4

#else

	/////////////////////////////////////////////////////////////////////for ue5
	virtual FVirtualKeyboardOptions GetVirtualKeyboardOptions() = 0;
	/////////////////////////////////////////////////////////////////////for ue5

#endif //ENGINE_MAJOR_VERSION < 5

    virtual bool IsMultilineEntry() = 0;

    virtual TSharedPtr<SWidget> GetWidget() = 0;

protected:
    virtual void OnTextInsert(const FString& strInsert, const bool bReplace) = 0;
    virtual void OnEndInput(const FString& strNewText) = 0;

private:
    /** Virtual keyboard handler for an editable text layout */
    friend class FVirtualKeyboardEntry;
    class FVirtualKeyboardEntry : public IVirtualKeyboardEntry
    {
    public:
        static TSharedRef<FVirtualKeyboardEntry> Create(IInputSystem& InOwner);

        virtual void SetTextFromVirtualKeyboard(const FText& InNewText, ETextEntryType TextEntryType) override;

        virtual FText GetText() const override;
        virtual FText GetHintText() const override;
        virtual EKeyboardType GetVirtualKeyboardType() const override;
        virtual bool IsMultilineEntry() const override;

#if ENGINE_MAJOR_VERSION < 5

		/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION >= 26
		virtual bool GetSelection(int& OutSelStart, int& OutSelEnd) override {
			return true;
		};
#endif //ENGINE_MINOR_VERSION >= 26

#if ENGINE_MINOR_VERSION > 19
		virtual FVirtualKeyboardOptions GetVirtualKeyboardOptions() const override;
#endif //ENGINE_MINOR_VERSION > 19

#if ENGINE_MINOR_VERSION > 20
		virtual void SetSelectionFromVirtualKeyboard(int InSelStart, int InSelEnd) override;
#endif //ENGINE_MINOR_VERSION > 20

	private:
		FVirtualKeyboardEntry(IInputSystem& InputOwner);
		IInputSystem* m_pInputOwner;

#if ENGINE_MINOR_VERSION > 19
		FVirtualKeyboardOptions m_VirtualKeyboardOptions;
#endif	//ENGINE_MINOR_VERSION > 19
		/////////////////////////////////////////////////////////////////////for ue4

#else

		/////////////////////////////////////////////////////////////////////for ue5
		virtual bool GetSelection(int& OutSelStart, int& OutSelEnd) override {
			return true;
		};
		virtual FVirtualKeyboardOptions GetVirtualKeyboardOptions() const override;

		virtual void SetSelectionFromVirtualKeyboard(int InSelStart, int InSelEnd) override;
	private:
		FVirtualKeyboardEntry(IInputSystem& InputOwner);
		IInputSystem* m_pInputOwner;
		FVirtualKeyboardOptions m_VirtualKeyboardOptions;
		/////////////////////////////////////////////////////////////////////for ue5

#endif //ENGINE_MAJOR_VERSION < 5
    };

private:
    /**
    * Note: The IME interface for the multiline editable text uses the pre-flowed version of the string since the IME APIs are designed to work with flat strings
    * This means we have to do a bit of juggling to convert between the two
    */
    friend class FTextInputMethodContext;
    class FTextInputMethodContext : public ITextInputMethodContext
    {
    public:
        static TSharedRef<FTextInputMethodContext> Create(IInputSystem& InputOwne);

        void CacheWindow();

        FORCEINLINE void KillContext()
        {
            m_pInputOwner = nullptr;
            bIsComposing = false;
        }

        FORCEINLINE FTextRange GetCompositionRange() const
        {
            return FTextRange(CompositionBeginIndex, CompositionBeginIndex + CompositionLength);
        }

        bool UpdateCachedGeometry(const FGeometry& InAllottedGeometry)
        {
            if (CachedGeometry != InAllottedGeometry)
            {
                CachedGeometry = InAllottedGeometry;
                return true;
            }
            return false;
        }

        virtual bool IsComposing() override;
        virtual bool IsReadOnly() override;
        virtual uint32 GetTextLength() override;
        virtual void GetSelectionRange(uint32& BeginIndex, uint32& Length, ECaretPosition& CaretPosition) override;
        virtual void SetSelectionRange(const uint32 BeginIndex, const uint32 Length, const ECaretPosition CaretPosition) override;
        virtual void GetTextInRange(const uint32 BeginIndex, const uint32 Length, FString& OutString) override;
        virtual void SetTextInRange(const uint32 BeginIndex, const uint32 Length, const FString& InString) override;
        virtual int32 GetCharacterIndexFromPoint(const FVector2D& Point) override;
        virtual bool GetTextBounds(const uint32 BeginIndex, const uint32 Length, FVector2D& Position, FVector2D& Size) override;
        virtual void GetScreenBounds(FVector2D& Position, FVector2D& Size) override;
        virtual TSharedPtr<FGenericWindow> GetWindow() override;
        virtual void BeginComposition() override;
        virtual void UpdateCompositionRange(const int32 InBeginIndex, const uint32 InLength) override;
        virtual void EndComposition() override;

    private:
        FTextInputMethodContext(IInputSystem& InputOwne);
        IInputSystem* m_pInputOwner;

        TWeakPtr<SWindow> CachedParentWindow;

        FGeometry CachedGeometry;
        bool bIsComposing;
        int32 CompositionBeginIndex;
        uint32 CompositionLength;
    };

private:
    /** Virtual keyboard handler for this text layout */
    TSharedPtr<FVirtualKeyboardEntry> VirtualKeyboardEntry;

    /** True if the IME context for this text layout has been registered with the input method manager */
    bool bHasRegisteredTextInputMethodContext;

    /** IME context for this text layout */
    TSharedPtr<FTextInputMethodContext> TextInputMethodContext;

    /** Notification interface object for IMEs */
    TSharedPtr<ITextInputMethodChangeNotifier> TextInputMethodChangeNotifier;


    FText   m_textVirtualInputText;
    bool    m_bTextChangedByVirtualKeyboard;

    /** How the text was committed by the virtual keyboard */
    ETextCommit::Type m_emVirtualKeyboardTextCommitType;
    
    bool m_bTextCommittedByVirtualKeyboard;
};

