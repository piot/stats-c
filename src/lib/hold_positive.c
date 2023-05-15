/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <stats/hold_positive.h>

void statsHoldPositiveInit(StatsHoldPositive* self, size_t threshold)
{
    self->isOrWasTrue = false;
    self->threshold = threshold;
    self->continousFalseCount = 0;
}

void statsHoldPositiveAdd(StatsHoldPositive* self, bool on)
{
    if (on) {
        self->isOrWasTrue = true;
    } else {
        if (!self->isOrWasTrue) {
            return;
        }
        self->continousFalseCount++;
        if (self->continousFalseCount > self->threshold) {
            self->isOrWasTrue = false;
            self->continousFalseCount = 0;
        }
    }
}
