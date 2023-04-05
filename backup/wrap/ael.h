//
// Created by luo on 2023/3/6.
//

#ifndef KINO_AEL_H
#define KINO_AEL_H

#include "core/sandbox.h"

#include <QApplication>
#include <QAbstractNativeEventFilter>

namespace Wrap {
class AEL final : public QApplication
        , private QAbstractNativeEventFilter {
public:
    AEL(class Core::Sandbox *box, int32_t argc, char** argv);

    int32_t Start();

protected:
    void LaunchExecuteApp();

    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;
private:
    Core::Sandbox *_box;
    int32_t _argc;
    char** _argv;
    bool _started = false;
};
}

#endif //KINO_AEL_H
