//
// Created by luo on 2023/3/6.
//

#ifndef KINO_LAUNCHER_PLATFORM_H
#define KINO_LAUNCHER_PLATFORM_H

#if defined(__WIN32__)
#include "platform/win/launcher_win.h"
#elif defined(__APPLE__)

#elif defined(__linux__)

#else
#endif

#endif //KINO_LAUNCHER_PLATFORM_H
