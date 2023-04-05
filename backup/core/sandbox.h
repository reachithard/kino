//
// Created by luo on 2023/3/5.
//

#ifndef KINO_SANDBOX_H
#define KINO_SANDBOX_H

#include <memory>

#include "launcher.h"
#include "kino.h"

namespace Wrap {
    class AEL;
}

namespace Core {
class Sandbox {
public:
    Sandbox(Launcher *launcher, int32_t argc, char** argv);

    int32_t Start();

    void LaunchExecuteApp();
private:
    Launcher *_launcher;
    int32_t _argc;
    char **_argv;
    class Wrap::AEL *_ael;
    std::unique_ptr<Kino> _kino;
};
}

#endif //KINO_SANDBOX_H
