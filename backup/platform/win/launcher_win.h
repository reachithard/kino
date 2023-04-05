//
// Created by luo on 2023/3/6.
//

#ifndef KINO_LAUNCHER_WIN_H
#define KINO_LAUNCHER_WIN_H

#include "core/launcher.h"

#if defined(__WIN32__)
namespace Platform{
class Launcher : public Core::Launcher {
public:
    Launcher(int argc, char*argv[]);
};
}
#endif

#endif //KINO_LAUNCHER_WIN_H
