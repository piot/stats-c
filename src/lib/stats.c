/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <limits.h>
#include <stats/stats.h>

void statsIntInit(StatsInt* self, size_t threshold)
{
    self->sum = 0;
    self->count = 0U;
    self->max = INT_MIN;
    self->min = INT_MAX;
    self->threshold = threshold;
    self->maxAck = INT_MIN;
    self->minAck = INT_MAX;
    self->avg = 0;
    self->avgIsSet = false;
}

int statsIntMean(const StatsInt* self)
{
    if (self->count < 10) {
        return 0;
    }

    return self->sum / (int) self->count;
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
        self->count = 0U;
        self->avgIsSet = true;
        self->sum = 0;
    }
}

void statsIntDebug(const StatsInt* self, const Clog* log, const char* debug, const char* unit)
{
    CLOG_C_DEBUG(log, "%s: %d %s (min:%d, max:%d, count:%zu)", debug, self->avg, unit, self->min, self->max,
                 self->count);
}
