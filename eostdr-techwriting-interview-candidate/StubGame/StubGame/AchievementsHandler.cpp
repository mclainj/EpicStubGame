#include "AchievementsHandler.h"
#include <iostream>

AchievementsHandler::AchievementsHandler(EOS_HAchievements achievementsHandle)
    : achievementsHandle(achievementsHandle), notificationId(EOS_INVALID_NOTIFICATIONID) {}

AchievementsHandler::~AchievementsHandler() 
{
    UnregisterAchievementNotifications();
}

void AchievementsHandler::RegisterAchievementNotifications() 
{
    EOS_Achievements_AddNotifyAchievementsUnlockedV2Options options = {};
    options.ApiVersion = EOS_ACHIEVEMENTS_ADDNOTIFYACHIEVEMENTSUNLOCKEDV2_API_LATEST;

    notificationId = EOS_Achievements_AddNotifyAchievementsUnlockedV2(
        achievementsHandle,
        &options,
        nullptr,
        OnAchievementUnlockedCallback
    );

    if (notificationId == EOS_INVALID_NOTIFICATIONID) {
        std::cerr << "AchievementsHandler::Failed to register achievement notifications." << std::endl;
    }
    else {
        std::cout << "AchievementsHandler::Successfully registered for achievement notifications." << std::endl;
    }
}

void AchievementsHandler::UnregisterAchievementNotifications() 
{
    if (notificationId != EOS_INVALID_NOTIFICATIONID) {
        EOS_Achievements_RemoveNotifyAchievementsUnlocked(achievementsHandle, notificationId);
        std::cout << "AchievementsHandler::Unregistered achievement notifications." << std::endl;
    }
}

void AchievementsHandler::UnlockAchievement(EOS_ProductUserId userId, const char* achievementId)
{
    EOS_Achievements_UnlockAchievementsOptions unlockOptions = {};
    unlockOptions.ApiVersion = EOS_ACHIEVEMENTS_UNLOCKACHIEVEMENTS_API_LATEST;
    unlockOptions.UserId = userId;

    const char* achievementIds[] = { achievementId };
    unlockOptions.AchievementIds = achievementIds;
    unlockOptions.AchievementsCount = 1;

    EOS_Achievements_UnlockAchievements(achievementsHandle, &unlockOptions, nullptr, OnUnlockAchievementsComplete);
    std::cout << "AchievementsHandler::Called EOS_Achievements_UnlockAchievements for " << achievementId << std::endl;
}

void EOS_CALL AchievementsHandler::OnUnlockAchievementsComplete(const EOS_Achievements_OnUnlockAchievementsCompleteCallbackInfo* callbackInfo) 
{
    std::cout << "AchievementsHandler::OnUnlockAchievementsComplete callback complete." << std::endl;
    if (callbackInfo)
    {
        std::cout << "ResultCode: " << EOS_EResult_ToString(callbackInfo->ResultCode) << std::endl;
        std::cout << "Achievements unlocked: " << callbackInfo->AchievementsCount << std::endl;
    }
}

void EOS_CALL AchievementsHandler::OnAchievementUnlockedCallback(const EOS_Achievements_OnAchievementsUnlockedCallbackV2Info* callbackInfo) 
{
    std::cout << "AchievementsHandler::OnAchievementUnlockedCallback complete." << std::endl;
    if (callbackInfo)
    {
        std::cout << "Achievement Unlocked: " << callbackInfo->AchievementId << std::endl;
        std::cout << "Unlocked At: " << callbackInfo->UnlockTime << std::endl;
    }
}