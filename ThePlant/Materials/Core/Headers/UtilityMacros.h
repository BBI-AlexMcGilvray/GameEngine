#pragma once

#include "Core/Headers/Macros.h"

#define UNUSED_1(_1) (void)_1
#define UNUSED_2(_1, _2) (void)_1, (void)_2
#define UNUSED_3(_1, _2, _3) (void)_1, (void)_2, (void)_3
#define UNUSED_4(_1, _2, _3, _4) (void)_1, (void)_2, (void)_3, (void)_4
#define UNUSED_5(_1, _2, _3, _4, _5) (void)_1, (void)_2, (void)_3, (void)_4, (void)_5
#define UNUSED_6(_1, _2, _3, _4, _5, _6) (void)_1, (void)_2, (void)_3, (void)_4, (void)_5, (void)_6
#define UNUSED_7(_1, _2, _3, _4, _5, _6, _7) (void)_1, (void)_2, (void)_3, (void)_4, (void)_5, (void)_6, (void)_7
#define UNUSED_8(_1, _2, _3, _4, _5, _6, _7, _8) (void)_1, (void)_2, (void)_3, (void)_4, (void)_5, (void)_6, (void)_7, (void)_8
#define UNUSED_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) (void)_1, (void)_2, (void)_3, (void)_4, (void)_5, (void)_6, (void)_7, (void)_8, (void)_9
#define UNUSED(...) CAT(UNUSED_, VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)