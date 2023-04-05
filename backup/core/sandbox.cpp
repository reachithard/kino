//
// Created by luo on 2023/3/5.
//

#include "sandbox.h"

#include "wrap/ael.h"

namespace Core {
Sandbox::Sandbox(Core::Launcher *launcher, int32_t argc, char **argv) : _launcher(launcher), _argc(argc), _argv(argv), _ael(
        nullptr) {

}

int32_t Sandbox::Start() {
    _ael = new Wrap::AEL(this, _argc, _argv);
    return 0;
}

void Sandbox::LaunchExecuteApp() {
    _kino = std::make_unique<Kino>(_launcher);

}
}

