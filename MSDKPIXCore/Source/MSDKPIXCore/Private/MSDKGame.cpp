//
// Created by mikefu on 2021/8/11.
// Copyright (c) 2021 Epic Games, Inc. All rights reserved.
//


#include "MSDKGame.h"

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

void MSDKGame::SetGameObserver(MSDKGameObserver *gameObserver) {}

void MSDKGame::Setup(const String &channel, const String &extraJson) {}

void MSDKGame::ShowAchievement(const String &channel, const String &extraJson) {}

void MSDKGame::ShowLeaderBoard(const String &board, const String &channel, const String &extraJson) {}

void MSDKGame::SetScore(const String &board, int score, const String &channel, const String &extraJson) {}

void MSDKGame::UnlockAchievement(const String &achieve, double count, const String &channel, const String &extraJson) {}

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

void MSDKGame::SetGameObserver(MSDKGameObserver *gameObserver) {}

void MSDKGame::Setup(const String &channel, const String &extraJson) {}

void MSDKGame::ShowAchievement(const String &channel, const String &extraJson) {}

void MSDKGame::ShowLeaderBoard(const String &board, const String &channel, const String &extraJson) {}

void MSDKGame::SetScore(const String &board, int score, const String &channel, const String &extraJson) {}

void MSDKGame::UnlockAchievement(const String &achieve, double count, const String &channel, const String &extraJson) {}

NS_MSDK_SPACE_NO_STL_END

#endif




