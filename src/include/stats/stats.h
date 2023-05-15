/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef PIOT_STATS_H
#define PIOT_STATS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct StatsInt {
    int sum;
    size_t count;
    int min;
    int max;

    int avg;
    int maxAck;
    int minAck;
    bool avgIsSet;

    size_t threshold;
} StatsInt;

void statsIntInit(StatsInt* self, size_t threshold);
void statsIntAdd(StatsInt* self, int v);
int statsIntMean(const StatsInt* self);
void statsIntDebug(const StatsInt* self, const char* debug, const char* unit);

#endif
