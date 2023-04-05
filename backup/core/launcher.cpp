//
// Created by luo on 2023/3/5.
//

#include "launcher.h"

#include "platform/launcher_platform.h"
#include "ui/ui_config.h"
#include "platform/special_platform.h"

#include "sandbox.h"

namespace Core {
Launcher::Launcher(int argc, char **argv) : _argc(argc), _argv(argv) {

}

std::unique_ptr<Launcher> Launcher::Create(int argc, char **argv) {
    return std::make_unique<Platform::Launcher>(argc, argv);
}

int32_t Launcher::Exec() {
    Init();

    // TODO 日志等初始化

    Platform::Start();

    int32_t ret = ExecuteApplication();

    // TODO 对于更新以及重启操作

    // TODO 日志结束 crash结束
    Platform::Finish();

    return ret;
}

void Launcher::Init() {
    // TODO 对于参数以及message 日志进行设置
    Ui::UiConfig::SetAppAttr();
    InitCallback();
}

int32_t Launcher::ExecuteApplication() {
    // TODO 对于输入参数解析

    Sandbox sandbox(this, _argc, _argv);
    // TODO 任务队列开启
    // TODO timer
    return sandbox.Start();
}
}

