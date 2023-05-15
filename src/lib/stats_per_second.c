/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <limits.h>
#include <stats/stats_per_second.h>

void statsIntPerSecondInit(StatsIntPerSecond* self, MonotonicTimeMs now, MonotonicTimeMs periodMs)
{
    self->lastStatsAt = now;
    self->nextTime = now + periodMs;
    self->sum = 0;
    self->avg = 0;
    self->avgIsSet = false;
    self->periodMs = periodMs;
    self->minAck = INT_MAX;
    self->maxAck = INT_MIN;
    self->min = INT_MAX;
    self->max = INT_MIN;
}

void statsIntPerSecondAdd(StatsIntPerSecond* self, int v)
{
    self->sum += v;
}

int statsIntPerSecondUpdate(StatsIntPerSecond* self, MonotonicTimeMs now)
{
    int didSetStats = 0;

    if (now < self->nextTime) {
        return didSetStats;
    }

    self->nextTime = now + self->periodMs;

    MonotonicTimeMs delta = now - self->lastStatsAt;
    int v = (self->sum * 1000) / delta;

    if (delta > self->periodMs * 3) {
        self->avg = v;
        self->avgIsSet = true;
        self->min = self->minAck;
        self->max = self->maxAck;

        self->sum = 0;
        self->minAck = INT_MAX;
        self->maxAck = INT_MIN;
        self->lastStatsAt = now;
        didSetStats = 1;
    }

    if (v > self->maxAck) {
        self->maxAck = v;
    }

    if (v < self->minAck) {
        self->minAck = v;
    }

    return didSetStats;
}

void statsIntPerSecondDebugOutput(StatsIntPerSecond* self, const char* debug, const char* unit)
{
    CLOG_OUTPUT("stats: %s: %d / %d / %d %s", debug, self->min, self->avg, self->max, unit);
}

void statsIntPerSecondUpdateDebug(StatsIntPerSecond* self, MonotonicTimeMs now, const char* debug, const char* unit)
{
    int didSetStats = statsIntPerSecondUpdate(self, now);
    if (!didSetStats) {
        return;
    }

    statsIntPerSecondDebugOutput(self, debug, unit);
}
