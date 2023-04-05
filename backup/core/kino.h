//
// Created by luo on 2023/3/5.
//

#ifndef KINO_KINO_H
#define KINO_KINO_H

namespace Core {
enum class KinoState {
    Running,
    QuitRequested,
    QuitProcessed,
};

class Kino {
public:
    explicit Kino(class Launcher *launcher);

    void Run();

private:
    class Launcher *_launcher;
};

bool Quitting();
}

#endif //KINO_KINO_H
