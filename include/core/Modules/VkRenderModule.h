#ifndef CORE_VKRENDERMODULE_H
#define CORE_VKRENDERMODULE_H

#include <core/Essential.h>
#include <core/Modules/IRenderModule.h>

#include <vulkan/vulkan.h>

namespace core {

typedef VkRenderModule RenderModule;

class VkRenderModule : public IRenderModule {
    friend class VkWindowRenderer;
public:
    VkRenderModule();
    ~VkRenderModule();

    void Frame() override;

    bool isReady();

private:
    void Init(Window& window);
    void Cleanup();
    void CreateInstance(Window& window);

    VkInstance instance;

    bool initialized             { false };
    bool validationLayersEnabled { false };

    std::vector<const char*> requiredExtensions;
    std::vector<const char*> requiredLayers;

    void CheckValidationLayerSupport();
};

}

#endif //CORE_VKRENDERMODULE_H
