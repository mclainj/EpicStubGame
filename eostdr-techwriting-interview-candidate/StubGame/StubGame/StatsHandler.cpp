#include "StatsHandler.h"
#include <iostream>

StatsHandler::StatsHandler(EOS_HStats inStatsHandle) : statsHandle(inStatsHandle) {}

void StatsHandler::IngestStat(EOS_ProductUserId userId, const char* statName, int32_t statsCount) 
{
    EOS_Stats_IngestData ingestData = {};
    ingestData.ApiVersion = EOS_STATS_INGESTDATA_API_LATEST;
    ingestData.StatName = statName;
    ingestData.IngestAmount = statsCount;

    EOS_Stats_IngestStatOptions ingestStatOptions = {};
    ingestStatOptions.ApiVersion = EOS_STATS_INGESTSTAT_API_LATEST;
    ingestStatOptions.LocalUserId = userId;
    ingestStatOptions.Stats = &ingestData;
    ingestStatOptions.StatsCount = 1;
    ingestStatOptions.TargetUserId = userId;

    EOS_Stats_IngestStat(statsHandle, &ingestStatOptions, nullptr, OnStatIngestComplete);
    std::cout << "StatsHandler::Called EOS_Stats_IngestStat for " << statName << " with value: " << statsCount << std::endl;
}

void EOS_CALL StatsHandler::OnStatIngestComplete(const EOS_Stats_IngestStatCompleteCallbackInfo* callbackInfo) 
{
    std::cout << "StatsHandler::OnStatIngestComplete callback complete." << std::endl;
    if (callbackInfo)
    {
        std::cout << "ResultCode: " << EOS_EResult_ToString(callbackInfo->ResultCode) << std::endl;
        std::cout << "User: " << callbackInfo->TargetUserId << std::endl;
    }
}