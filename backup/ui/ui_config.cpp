//
// Created by luo on 2023/3/6.
//

#include "ui_config.h"

namespace Ui {
void UiConfig::SetAppAttr() {
    QApplication::setApplicationName(QString("Kino"));
    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling, true);
    QApplication::setHighDpiScaleFactorRoundingPolicy(
            Qt::HighDpiScaleFactorRoundingPolicy::Floor);
}
}

