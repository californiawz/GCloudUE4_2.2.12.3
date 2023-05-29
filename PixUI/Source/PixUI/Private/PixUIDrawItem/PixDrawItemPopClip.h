/**************************************************

**** @file:     PixDrawItemPopClip.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/






#pragma once
#include "PixDrawItem.h"


class PixDrawItemPopClip : public PixDrawItem
{
public:
	PixDrawItemPopClip();
	~PixDrawItemPopClip();

public:
	void UpdatePopClipParam(bool b_pop);

public:
	virtual uint32 DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer) override;
	virtual void UpdateParams(const TArray<void*>& aryParams) override;

private:
	bool b_pop_clip_;
};
