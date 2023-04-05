//
// Created by luo on 2023/3/6.
//

#ifndef KINO_SPECIAL_PLATFORM_H
#define KINO_SPECIAL_PLATFORM_H

namespace Platform {
    void Start();
    void Finish();
}

#if defined(__WIN32__)
#include "platform/win/launcher_win.h"
#elif defined(__APPLE__)

#elif defined(__linux__)

#else
#endif

#endif //KINO_SPECIAL_PLATFORM_H
