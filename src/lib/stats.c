/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <limits.h>
#include <stats/stats.h>
#include <stats/stats_per_second.h>

void statsIntInit(StatsInt* self, size_t threshold)
{
    self->sum = 0;
    self->count = 0;
    self->max = INT_MIN;
    self->min = INT_MAX;
    self->threshold = threshold;
    self->maxAck = INT_MIN;
    self->minAck = INT_MAX;
    self->avg = 0;
}

int statsIntMean(const StatsInt* self)
{
    if (self->count < 10) {
        return 0;
    }

    return self->sum / (int)self->count;
}

void statsIntAdd(StatsInt* self, int v)
{
    self->sum += v;
    self->count++;
    if (v > self->maxAck) {
        self->maxAck = v;
    }

    if (v < self->minAck) {
        self->minAck = v;
    }

    if (self->count >= self->threshold) {
        self->avg = statsIntMean(self);
        self->min = self->minAck;
        self->max = self->maxAck;
        self->maxAck = INT_MIN;
        self->minAck = INT_MAX;
        self->count = 0;
        self->sum = 0;
    }
}

void statsIntDebug(const StatsInt* self, const char* debug, const char* unit)
{
    CLOG_OUTPUT_STDERR("%s: %d %s (min:%d, max:%d, count:%zu)", debug, self->avg, unit, self->min, self->max,
                 self->count);
}

void statsIntPerSecondInit(StatsIntPerSecond* self, MonotonicTimeMs now, MonotonicTimeMs periodMs)
{
    self->lastStatsAt = now;
    self->nextTime = now + periodMs;
    self->sum = 0;
    self->avg = 0;
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
    CLOG_VERBOSE("stats: %s: %d / %d / %d %s", debug, self->min, self->avg, self->max, unit);
}

void statsIntPerSecondUpdateDebug(StatsIntPerSecond* self, MonotonicTimeMs now, const char* debug, const char* unit)
{
    int didSetStats = statsIntPerSecondUpdate(self, now);
    if (!didSetStats) {
        return;
    }

    statsIntPerSecondDebugOutput(self, debug, unit);
}
