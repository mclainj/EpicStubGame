#pragma once
#ifndef STATS_HANDLER_H
#define STATS_HANDLER_H

#include "eos_stats.h"
#include <string>
#include <cstdint>

class StatsHandler {
public:
    // Constructor: takes a valid EOS stats handle
    StatsHandler(EOS_HStats statsHandle);

    // Ingests a stat value for the given user
    void IngestStat(EOS_ProductUserId userId, const char* statName, int32_t amount);

private:
    const EOS_HStats statsHandle;

    // Callback when the stat ingestion completes
    static void EOS_CALL OnStatIngestComplete(const EOS_Stats_IngestStatCompleteCallbackInfo* callbackInfo);
};

#endif // STATS_HANDLER_H