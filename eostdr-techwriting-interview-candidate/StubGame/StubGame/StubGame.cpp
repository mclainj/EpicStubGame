// Copyright Epic Games, Inc. All Rights Reserved.

#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <Windows/eos_Windows.h>
#include <eos_init.h>
#include <eos_logging.h>
#include <eos_common.h>
#include <eos_auth.h>
#include <eos_connect.h>
#include <eos_sdk.h>
#include <cassert>
#include <string.h>
#include "SDKConfig.h"
#include "PlatformHandler.h"
#include "AuthHandler.h"
#include "AchievementsHandler.h"
#include "StatsHandler.h"

// Starts thread to tick EOS Platform
std::thread StartTickThread(EOS_HPlatform platformHandle)
{
	return std::thread([platformHandle]()
		{
			while (true)
			{
				EOS_Platform_Tick(platformHandle);
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		});
}

int main()
{
	// Initialize config and platform
	SDKConfig* config = new SDKConfig;
	PlatformHandler* platformInitializer = new PlatformHandler();
	EOS_HPlatform platformHandle = nullptr;
	platformHandle = platformInitializer->InitializePlatform(config);
	assert(platformHandle != nullptr);

	// Login and retrieve a PUID
	AuthHandler* auth = new AuthHandler();
	EOS_ProductUserId puid = nullptr;
	puid = auth->Login(config, platformHandle);
	assert(puid != nullptr);

	std::cout << "Logged in and PUID is: " << puid << std::endl;

	// Tick EOS Platform
	std::thread tickThread = StartTickThread(platformHandle);

	// Get Achievements interface from EOS Platform and register for notifications
	EOS_HAchievements achievementsHandle = nullptr;
	achievementsHandle = EOS_Platform_GetAchievementsInterface(platformHandle);
	assert(achievementsHandle != nullptr);
	AchievementsHandler* achievementsHandler = new AchievementsHandler(achievementsHandle);
	achievementsHandler->RegisterAchievementNotifications();

	// Get Stats interface from EOS Platform to ingest stats
	EOS_HStats statsHandle = nullptr;
	statsHandle = EOS_Platform_GetStatsInterface(platformHandle);
	assert(statsHandle != nullptr);
	StatsHandler* statsHandler = new StatsHandler(statsHandle);

	// Unlock an achievement manually
	achievementsHandler->UnlockAchievement(puid, "achievement-1");

	// Ingest a stat, potentially triggering an achievement unlock
	statsHandler->IngestStat(puid, "stat1", 1);

	// Join the thread to block until the loop in StartTickThread finishes (Note: currently runs indefinitely)
	tickThread.join();

	// Shut down EOS SDK:
	EOS_Platform_Release(platformHandle);
	EOS_Shutdown();

	// Clean up new objects
	delete config;
	delete platformInitializer;
	delete auth;
	delete achievementsHandler;
	delete statsHandler;
}