//
// Created by luo on 2023/3/6.
//

#include "ael.h"

#include "core/kino.h"
#include "core/sandbox.h"

namespace Wrap {
AEL::AEL(Core::Sandbox *box, int32_t argc, char **argv) : _box(box), QApplication(argc, _argv){
    setQuitOnLastWindowClosed(false);
}

int32_t AEL::Start() {
    LaunchExecuteApp();

    _started = true;
    return exec();
}

void AEL::LaunchExecuteApp() {
    if (Core::Quitting()) {
        return;
    }

    // 检测是否单实例启动

    // TODO 进行屏幕分辩率设置

    installNativeEventFilter(this);

    // 进行回调
    _box->LaunchExecuteApp();
}

bool AEL::nativeEventFilter(const QByteArray &eventType, void *message, long *result) {
    return false;
}
}

