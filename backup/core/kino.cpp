//
// Created by luo on 2023/3/5.
//

#include "kino.h"

#include "ui/style/core_fonts.h"

namespace Core {
static KinoState gKinoState;

bool Quitting() {
    return gKinoState != KinoState::Running;
}

Kino::Kino(Launcher *launcher) : _launcher(launcher) {

}

void Kino::Run() {
    Ui::Style::StartFonts();
}
}