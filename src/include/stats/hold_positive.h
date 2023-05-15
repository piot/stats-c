/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef PIOT_STATS_HOLD_POSITIVE_H
#define PIOT_STATS_HOLD_POSITIVE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct StatsHoldPositive {
    bool isOrWasTrue;
    size_t threshold;
    size_t continousFalseCount;
} StatsHoldPositive;

void statsHoldPositiveInit(StatsHoldPositive* self, size_t threshold);
void statsHoldPositiveAdd(StatsHoldPositive* self, bool on);

#endif
