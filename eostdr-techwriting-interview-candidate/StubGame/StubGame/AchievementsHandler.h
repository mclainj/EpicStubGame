#pragma once
#ifndef ACHIEVEMENTS_HANDLER_H
#define ACHIEVEMENTS_HANDLER_H

#include "eos_achievements.h"
#include <string>

class AchievementsHandler {
public:
    // Constructor: takes a valid EOS achievements handle
    AchievementsHandler(EOS_HAchievements achievementsHandle);

    // Destructor unregisters notifications
    ~AchievementsHandler();

    // Registers for achievement unlock notifications
    void RegisterAchievementNotifications();

    // Unregisters achievement notifications
    void UnregisterAchievementNotifications();

    // Requests to unlock an achievement for the given user
    void UnlockAchievement(EOS_ProductUserId userId, const char* achievementId);

private:
    const EOS_HAchievements achievementsHandle;
    EOS_NotificationId notificationId;

    // Callback when the unlock achievements call completes
    static void EOS_CALL OnUnlockAchievementsComplete(const EOS_Achievements_OnUnlockAchievementsCompleteCallbackInfo* callbackInfo);

    // Callback when an achievement is unlocked
    static void EOS_CALL OnAchievementUnlockedCallback(const EOS_Achievements_OnAchievementsUnlockedCallbackV2Info* callbackInfo);
};

#endif // ACHIEVEMENTS_HANDLER_H