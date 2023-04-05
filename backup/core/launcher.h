//
// Created by luo on 2023/3/5.
//

#ifndef KINO_LAUNCHER_H
#define KINO_LAUNCHER_H

#include <memory>

namespace Core {
class Launcher {
public:
    Launcher(int argc, char *argv[]);

    static std::unique_ptr<Launcher> Create(int argc, char *argv[]);

    virtual int32_t Exec();

protected:
    void Init();
    virtual void InitCallback(){}

    int32_t ExecuteApplication();

private:
    int32_t _argc;
    char** _argv;
};
}

#endif //KINO_LAUNCHER_H
