#ifndef CORE_ROOT_H
#define CORE_ROOT_H

#include <memory>
#include <vector>
#include "core.h"
#include "Singleton.h"

namespace core {


class Root : public Singleton<Root> {

public:
    Root();
    ~Root();

    /// Increments inner counter and returns ID for next object.
    static uint32_t GetNewID();

protected:
    std::vector<std::shared_ptr<Window>> windowsPool;

    std::unique_ptr<LogManager> logManager;
    std::unique_ptr<WindowManager> windowManager;
    std::unique_ptr<RenderManager> renderManager;
    std::unique_ptr<InputManager> inputManager;
    std::unique_ptr<SoundManager> soundManager;
    std::unique_ptr<NetworkManager> networkManager;

private:

    /// Root's ID is always 1
    static uint32_t objectsCounter;
};


}


#endif //CORE_ROOT_H
