/**************************************************

**** @file:     IPixInputSystem.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "IPixInputSystem.h"

#include "Framework/Application/SlateApplication.h"
#include "HAL/PlatformApplicationMisc.h"


IInputSystem::IInputSystem()
{
    VirtualKeyboardEntry = FVirtualKeyboardEntry::Create(*this);

    bHasRegisteredTextInputMethodContext = false;
    TextInputMethodContext = FTextInputMethodContext::Create(*this);

    m_textVirtualInputText = FText::FromString("");
    m_bTextChangedByVirtualKeyboard = false;
    m_bTextCommittedByVirtualKeyboard = false;
}

IInputSystem::~IInputSystem()
{
}


void IInputSystem::ActivateInput()
{
    if (FPlatformApplicationMisc::RequiresVirtualKeyboard())
    {
        // @TODO: Create ITextInputMethodSystem derivations for mobile
        FSlateApplication::Get().ShowVirtualKeyboard(true, 0, VirtualKeyboardEntry);
    }
    else
    {
        ITextInputMethodSystem* const TextInputMethodSystem = FSlateApplication::Get().GetTextInputMethodSystem();
        if (TextInputMethodSystem)
        {
            if (!bHasRegisteredTextInputMethodContext)
            {
                bHasRegisteredTextInputMethodContext = true;

                TextInputMethodChangeNotifier = TextInputMethodSystem->RegisterContext(TextInputMethodContext.ToSharedRef());
                if (TextInputMethodChangeNotifier.IsValid())
                {
                    TextInputMethodChangeNotifier->NotifyLayoutChanged(ITextInputMethodChangeNotifier::ELayoutChangeType::Created);
                }
            }

            TextInputMethodContext->CacheWindow();
            TextInputMethodSystem->ActivateContext(TextInputMethodContext.ToSharedRef());
        }
    }
}


void IInputSystem::DeativateInput()
{
    if (FPlatformApplicationMisc::RequiresVirtualKeyboard())
    {
        FSlateApplication::Get().ShowVirtualKeyboard(false, 0);
        OnEndInput(m_textVirtualInputText.ToString());
    }
    else
    {
        ITextInputMethodSystem* const TextInputMethodSystem = FSlateApplication::Get().GetTextInputMethodSystem();
        if (TextInputMethodSystem && bHasRegisteredTextInputMethodContext)
        {
            TextInputMethodSystem->DeactivateContext(TextInputMethodContext.ToSharedRef());
        }
    }
}


void IInputSystem::OnInputTick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
    if (TextInputMethodChangeNotifier.IsValid() && TextInputMethodContext.IsValid() && TextInputMethodContext->UpdateCachedGeometry(AllottedGeometry))
    {
        TextInputMethodChangeNotifier->NotifyLayoutChanged(ITextInputMethodChangeNotifier::ELayoutChangeType::Changed);
    }

    if (m_bTextChangedByVirtualKeyboard)
    {
        OnTextInsert(m_textVirtualInputText.ToString(), true);
        m_textVirtualInputText = FText::FromString("");
        m_bTextChangedByVirtualKeyboard = false;
        m_bTextCommittedByVirtualKeyboard = false;
    }
}

TSharedRef<IInputSystem::FVirtualKeyboardEntry> IInputSystem::FVirtualKeyboardEntry::Create(IInputSystem& InOwnerInput)
{
    return MakeShareable(new FVirtualKeyboardEntry(InOwnerInput));
}

IInputSystem::FVirtualKeyboardEntry::FVirtualKeyboardEntry(IInputSystem& InOwnerInput)
    : m_pInputOwner(&InOwnerInput)
{
}

void IInputSystem::FVirtualKeyboardEntry::SetTextFromVirtualKeyboard(const FText& InNewText, ETextEntryType TextEntryType)
{
    // Update the internal editable text
    // This method is called from the main thread (i.e. not the game thread) of the device with the virtual keyboard
    // This causes the app to crash on those devices, so we're using polling here to ensure delegates are
    // fired on the game thread in Tick.
    m_pInputOwner->m_textVirtualInputText = InNewText;
    m_pInputOwner->m_bTextChangedByVirtualKeyboard = true;
    
    if (TextEntryType == ETextEntryType::TextEntryAccepted)
    {
        m_pInputOwner->m_emVirtualKeyboardTextCommitType = ETextCommit::OnEnter;
        m_pInputOwner->m_bTextCommittedByVirtualKeyboard = true;
    }
    else if (TextEntryType == ETextEntryType::TextEntryCanceled)
    {
        m_pInputOwner->m_emVirtualKeyboardTextCommitType = ETextCommit::Default;
        m_pInputOwner->m_bTextCommittedByVirtualKeyboard = true;
    }
}

#if ENGINE_MAJOR_VERSION < 5

/////////////////////////////////////////////////////////////////////for ue4

#if ENGINE_MINOR_VERSION > 20
void IInputSystem::FVirtualKeyboardEntry::SetSelectionFromVirtualKeyboard(int InSelStart, int InSelEnd)
{
	// Update the text selection and the cursor position
	// This method is called externally (eg. on Android from the native virtual keyboard implementation) 
	// The text may also change on the same frame, so the external selection must happen in Tick after the text update

	//m_pInputOwner->m_bSelectionChangedExternally = true;
	//m_pInputOwner->m_nExternalSelectionStart = InSelStart;
	//m_pInputOwner->m_nExternalSelectionEnd = InSelEnd;
}
#endif //ENGINE_MINOR_VERSION > 20

/////////////////////////////////////////////////////////////////////for ue4

#else

/////////////////////////////////////////////////////////////////////for ue5
void IInputSystem::FVirtualKeyboardEntry::SetSelectionFromVirtualKeyboard(int InSelStart, int InSelEnd)
{
	// Update the text selection and the cursor position
	// This method is called externally (eg. on Android from the native virtual keyboard implementation) 
	// The text may also change on the same frame, so the external selection must happen in Tick after the text update

	//m_pInputOwner->m_bSelectionChangedExternally = true;
	//m_pInputOwner->m_nExternalSelectionStart = InSelStart;
	//m_pInputOwner->m_nExternalSelectionEnd = InSelEnd;
}
/////////////////////////////////////////////////////////////////////for ue5

#endif //ENGINE_MAJOR_VERSION < 5



FText IInputSystem::FVirtualKeyboardEntry::GetText() const
{
    return m_pInputOwner->GetInputText();
}

FText IInputSystem::FVirtualKeyboardEntry::GetHintText() const
{
    return m_pInputOwner->GetInputHintText();
}

EKeyboardType IInputSystem::FVirtualKeyboardEntry::GetVirtualKeyboardType() const
{
    if (m_pInputOwner)
    {
        return m_pInputOwner->GetVirtualKeyboardType();
    }
    return Keyboard_Default;
}

#if ENGINE_MAJOR_VERSION < 5

/////////////////////////////////////////////////////////////////////for ue4

#if ENGINE_MINOR_VERSION > 19
FVirtualKeyboardOptions IInputSystem::FVirtualKeyboardEntry::GetVirtualKeyboardOptions() const
{
	if (m_pInputOwner)
	{
		m_pInputOwner->GetVirtualKeyboardOptions();
	}
	return m_VirtualKeyboardOptions;
}
#endif //ENGINE_MINOR_VERSION > 19

/////////////////////////////////////////////////////////////////////for ue4

#else

/////////////////////////////////////////////////////////////////////for ue5
FVirtualKeyboardOptions IInputSystem::FVirtualKeyboardEntry::GetVirtualKeyboardOptions() const
{
	if (m_pInputOwner)
	{
		m_pInputOwner->GetVirtualKeyboardOptions();
	}
	return m_VirtualKeyboardOptions;
}
/////////////////////////////////////////////////////////////////////for ue5

#endif  //ENGINE_MAJOR_VERSION < 5


bool IInputSystem::FVirtualKeyboardEntry::IsMultilineEntry() const
{
    return false;
}


TSharedRef<IInputSystem::FTextInputMethodContext> IInputSystem::FTextInputMethodContext::Create(IInputSystem& InOwnerLayout)
{
    return MakeShareable(new FTextInputMethodContext(InOwnerLayout));
}

IInputSystem::FTextInputMethodContext::FTextInputMethodContext(IInputSystem& InOwnerInput)
    : m_pInputOwner(&InOwnerInput)
    , bIsComposing(false)
    , CompositionBeginIndex(INDEX_NONE)
    , CompositionLength(0)
{
}

bool IInputSystem::FTextInputMethodContext::IsComposing()
{
    return m_pInputOwner && bIsComposing;
}

bool IInputSystem::FTextInputMethodContext::IsReadOnly()
{
    return false;
}

uint32 IInputSystem::FTextInputMethodContext::GetTextLength()
{
    if (!m_pInputOwner)
    {
        return 0;
    }

    //FTextLayout::FTextOffsetLocations OffsetLocations;
    //m_pInputOwner->TextLayout->GetTextOffsetLocations(OffsetLocations);
    //return OffsetLocations.GetTextLength();

    return 0;
}

void IInputSystem::FTextInputMethodContext::GetSelectionRange(uint32& BeginIndex, uint32& Length, ECaretPosition& OutCaretPosition)
{
    if (!m_pInputOwner)
    {
        BeginIndex = 0;
        Length = 0;
        OutCaretPosition = ITextInputMethodContext::ECaretPosition::Beginning;
        return;
    }

    /*
    const FTextLocation CursorInteractionPosition = m_pInputOwner->CursorInfo.GetCursorInteractionLocation();
    const FTextLocation SelectionLocation = m_pInputOwner->SelectionStart.Get(CursorInteractionPosition);

    FTextLayout::FTextOffsetLocations OffsetLocations;
    m_pInputOwner->TextLayout->GetTextOffsetLocations(OffsetLocations);

    const bool bHasSelection = SelectionLocation != CursorInteractionPosition;
    if (bHasSelection)
    {
    // We need to translate the selection into "editable text" space
    const FTextSelection Selection(SelectionLocation, CursorInteractionPosition);

    const FTextLocation& BeginningOfSelectionInDocumentSpace = Selection.GetBeginning();
    const int32 BeginningOfSelectionInEditableTextSpace = OffsetLocations.TextLocationToOffset(BeginningOfSelectionInDocumentSpace);

    const FTextLocation& EndOfSelectionInDocumentSpace = Selection.GetEnd();
    const int32 EndOfSelectionInEditableTextSpace = OffsetLocations.TextLocationToOffset(EndOfSelectionInDocumentSpace);

    BeginIndex = BeginningOfSelectionInEditableTextSpace;
    Length = EndOfSelectionInEditableTextSpace - BeginningOfSelectionInEditableTextSpace;

    const bool bCursorIsBeforeSelection = CursorInteractionPosition < SelectionLocation;
    OutCaretPosition = (bCursorIsBeforeSelection) ? ITextInputMethodContext::ECaretPosition::Beginning : ITextInputMethodContext::ECaretPosition::Ending;
    }
    else
    {
    // We need to translate the cursor position into "editable text" space
    const int32 CursorInteractionPositionInEditableTextSpace = OffsetLocations.TextLocationToOffset(CursorInteractionPosition);

    BeginIndex = CursorInteractionPositionInEditableTextSpace;
    Length = 0;

    OutCaretPosition = ITextInputMethodContext::ECaretPosition::Beginning;
    }
    */

    BeginIndex = 0;
    Length = 0;
    OutCaretPosition = ITextInputMethodContext::ECaretPosition::Beginning;
}

void IInputSystem::FTextInputMethodContext::SetSelectionRange(const uint32 BeginIndex, const uint32 Length, const ECaretPosition InCaretPosition)
{
    if (!m_pInputOwner)
    {
        return;
    }

    /*
    const uint32 TextLength = GetTextLength();

    const uint32 MinIndex = FMath::Min(BeginIndex, TextLength);
    const uint32 MaxIndex = FMath::Min(MinIndex + Length, TextLength);

    FTextLayout::FTextOffsetLocations OffsetLocations;
    m_pInputOwner->TextLayout->GetTextOffsetLocations(OffsetLocations);

    // We need to translate the indices into document space
    const FTextLocation MinTextLocation = OffsetLocations.OffsetToTextLocation(MinIndex);
    const FTextLocation MaxTextLocation = OffsetLocations.OffsetToTextLocation(MaxIndex);

    m_pInputOwner->ClearSelection();

    switch (InCaretPosition)
    {
    case ITextInputMethodContext::ECaretPosition::Beginning:
    {
    m_pInputOwner->CursorInfo.SetCursorLocationAndCalculateAlignment(*m_pInputOwner->TextLayout, MinTextLocation);
    m_pInputOwner->SelectionStart = MaxTextLocation;
    }
    break;

    case ITextInputMethodContext::ECaretPosition::Ending:
    {
    m_pInputOwner->SelectionStart = MinTextLocation;
    m_pInputOwner->CursorInfo.SetCursorLocationAndCalculateAlignment(*m_pInputOwner->TextLayout, MaxTextLocation);
    }
    break;
    }

    m_pInputOwner->OwnerWidget->OnCursorMoved(OwnerLayout->CursorInfo.GetCursorInteractionLocation());
    m_pInputOwner->UpdateCursorHighlight();
    */
}

void IInputSystem::FTextInputMethodContext::GetTextInRange(const uint32 BeginIndex, const uint32 Length, FString& OutString)
{
    if (!m_pInputOwner)
    {
        OutString.Reset();
        return;
    }

    //const FText EditedText = m_pInputOwner->GetText();
    //OutString = EditedText.ToString().Mid(BeginIndex, Length);

    OutString = "";
}

void IInputSystem::FTextInputMethodContext::SetTextInRange(const uint32 BeginIndex, const uint32 Length, const FString& InString)
{
    if (!m_pInputOwner)
    {
        return;
    }

    // We don't use Start/FinishEditing text here because the whole IME operation handles that.
    // Also, we don't want to support undo for individual characters added during an IME context
    //const FText OldEditedText = m_pInputOwner->GetText();

    // We do this as a select, delete, and insert as it's the simplest way to keep the text layout correct
    //SetSelectionRange(BeginIndex, Length, ITextInputMethodContext::ECaretPosition::Beginning);
    //m_pInputOwner->DeleteSelectedText();
    m_pInputOwner->OnTextInsert(InString, false);

    // Has the text changed?
    /*
    const FText EditedText = m_pInputOwner->GetText();
    const bool HasTextChanged = !EditedText.ToString().Equals(OldEditedText.ToString(), ESearchCase::CaseSensitive);
    if (HasTextChanged)
    {
        m_pInputOwner->OnTextInsert(InString);
    }
    */
}

int32 IInputSystem::FTextInputMethodContext::GetCharacterIndexFromPoint(const FVector2D& Point)
{
    if (!m_pInputOwner)
    {
        return INDEX_NONE;
    }

    /*
    const FTextLocation CharacterPosition = OwnerLayout->TextLayout->GetTextLocationAt(Point * OwnerLayout->TextLayout->GetScale());

    FTextLayout::FTextOffsetLocations OffsetLocations;
    m_pInputOwner->TextLayout->GetTextOffsetLocations(OffsetLocations);
    */

    return 0;
    //return OffsetLocations.TextLocationToOffset(CharacterPosition);
}

bool IInputSystem::FTextInputMethodContext::GetTextBounds(const uint32 BeginIndex, const uint32 Length, FVector2D& Position, FVector2D& Size)
{
    if (!m_pInputOwner)
    {
        Position = FVector2D::ZeroVector;
        Size = FVector2D::ZeroVector;
        return false;
    }

    /*
    FTextLayout::FTextOffsetLocations OffsetLocations;
    m_pInputOwner->TextLayout->GetTextOffsetLocations(OffsetLocations);

    const FTextLocation BeginLocation = OffsetLocations.OffsetToTextLocation(BeginIndex);
    const FTextLocation EndLocation = OffsetLocations.OffsetToTextLocation(BeginIndex + Length);

    const FVector2D BeginPosition = m_pInputOwner->TextLayout->GetLocationAt(BeginLocation, false);
    const FVector2D EndPosition = m_pInputOwner->TextLayout->GetLocationAt(EndLocation, false);

    if (BeginPosition.Y == EndPosition.Y)
    {
    // The text range is contained within a single line
    Position = BeginPosition;
    Size = EndPosition - BeginPosition;
    }
    else
    {
    // If the two positions aren't on the same line, then we assume the worst case scenario, and make the size as wide as the text area itself
    Position = FVector2D(0.0f, BeginPosition.Y);
    Size = FVector2D(m_pInputOwner->TextLayout->GetDrawSize().X, EndPosition.Y - BeginPosition.Y);
    }

    // Translate the position (which is in local space) into screen (absolute) space
    // Note: The local positions are pre-scaled, so we don't scale them again here
    Position += CachedGeometry.AbsolutePosition;
    */

    return false; // false means "not clipped"
}

void IInputSystem::FTextInputMethodContext::GetScreenBounds(FVector2D& Position, FVector2D& Size)
{
    if (!m_pInputOwner)
    {
        Position = FVector2D::ZeroVector;
        Size = FVector2D::ZeroVector;
        return;
    }

    Position = FVector2D(CachedGeometry.AbsolutePosition.X, CachedGeometry.AbsolutePosition.Y);
    Size = CachedGeometry.GetDrawSize();
}

void IInputSystem::FTextInputMethodContext::CacheWindow()
{
    if (!m_pInputOwner)
    {
        return;
    }

    const TSharedRef<const SWidget> OwningSlateWidgetPtr = m_pInputOwner->GetWidget()->AsShared();

    CachedParentWindow = FSlateApplication::Get().FindWidgetWindow(OwningSlateWidgetPtr);
}

TSharedPtr<FGenericWindow> IInputSystem::FTextInputMethodContext::GetWindow()
{
    if (!m_pInputOwner)
    {
        return nullptr;
    }

    const TSharedPtr<SWindow> SlateWindow = CachedParentWindow.Pin();
    return SlateWindow.IsValid() ? SlateWindow->GetNativeWindow() : nullptr;
}

void IInputSystem::FTextInputMethodContext::BeginComposition()
{
    if (!m_pInputOwner)
    {
        return;
    }

    if (!bIsComposing)
    {
        bIsComposing = true;

        //m_pInputOwner->BeginEditTransation();
        //m_pInputOwner->UpdateCursorHighlight();
    }
}

void IInputSystem::FTextInputMethodContext::UpdateCompositionRange(const int32 InBeginIndex, const uint32 InLength)
{
    if (!m_pInputOwner)
    {
        return;
    }

    if (bIsComposing)
    {
        CompositionBeginIndex = InBeginIndex;
        CompositionLength = InLength;

        //m_pInputOwner->UpdateCursorHighlight();
    }
}

void IInputSystem::FTextInputMethodContext::EndComposition()
{
    if (!m_pInputOwner)
    {
        return;
    }

    if (bIsComposing)
    {
        //m_pInputOwner->EndEditTransaction();
        //m_pInputOwner->UpdateCursorHighlight();

        bIsComposing = false;
    }
}
