/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef STATS_PER_SECOND_H
#define STATS_PER_SECOND_H

#include <monotonic-time/monotonic_time.h>
#include <stddef.h>

typedef struct StatsIntPerSecond {
    int sum;

    int minAck;
    int maxAck;

    int min;
    int max;

    int avg;

    size_t debugCount;
    MonotonicTimeMs lastStatsAt;
    MonotonicTimeMs nextTime;
    MonotonicTimeMs periodMs;
} StatsIntPerSecond;

void statsIntPerSecondInit(StatsIntPerSecond* self, MonotonicTimeMs now, MonotonicTimeMs periodMs);
void statsIntPerSecondAdd(StatsIntPerSecond* self, int v);
int statsIntPerSecondUpdate(StatsIntPerSecond* self, MonotonicTimeMs now);
void statsIntPerSecondUpdateDebug(StatsIntPerSecond* self, MonotonicTimeMs now, const char* debug, const char* unit);
void statsIntPerSecondDebugOutput(StatsIntPerSecond* self, const char* debug, const char* unit);

#endif // TURMOIL_DEPS_STATS_C_SRC_INCLUDE_STATS_STATS_PER_SECOND_H