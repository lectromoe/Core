/**
 * This header contains forward-declarations for core and bgfx classes
 */
#ifndef CORE_ESSENTIALS_H
#define CORE_ESSENTIALS_H

// ### Core defines ###
#ifndef SDL_MAIN_HANDLED
#   define SDL_MAIN_HANDLED
#endif

#ifndef NULL
#   define NULL 0
#endif

#ifndef __FILENAME__
#   ifdef _WIN32
#       define __FILENAME__ (strrchr("\\" __FILE__, '\\') + 1)
#   endif
#   ifdef __unix__
#       define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)
#   endif
#endif

#ifndef CORE_MAJOR_VERSION
#   define CORE_MAJOR_VERSION 0
#endif

#ifndef CORE_MINOR_VERSION
#   define CORE_MINOR_VERSION 2
#endif

#ifndef CORE_PATCH_VERSION
#   define CORE_PATCH_VERSION 0
#endif
// Core defines

// ### Core includes ###
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include <utility>
#include <cstdint>
#include <cassert>
// Core includes

namespace core {

class Core;
class CoreConfig;
class EngineLoop;
class Entity;
class FileSystem;
class Layer;
class Light;
class Logger;
class LogEntry;
class Mesh;
class Model;
class Object;
class Scene;
class ScriptedBehaviour;
class Shader;
class GUIBehaviour;
class GUIContext;

// Core Module classes
class GUIModule;
class EditorModule;
class ApplicationModule;
class EngineModule;
class SceneModule;
class InputModule;

// Core Components classes
class Camera;
class Renderer;
class Transform;
class Light;
template<typename T> class Script;

// Core interface classes
class IDrawable;
class IComponent;
class IModule;
class ITicker;
class IModuleContainer;

// Core template classes
template<typename T> class Pool;
template<typename T> class Singleton;
template<typename T> class Instantiable;
template<typename T> class TypeMap;
template <class T, class D> class ModuleContainer;
template <typename T> class LayerLinked;

// Core structs
typedef struct Rect Rect;
struct Cube;
struct Sphere;
struct Cone;
struct Cylinder;
struct WireCube;
struct WireSphere;
struct WireCone;
struct WireCylinder;


//      std
template <typename T>
using shared = std::shared_ptr<T>;
template <typename T>
using unique = std::unique_ptr<T>;
using std::make_shared;
using std::vector;
using std::string;

} // namespace core

#endif //CORE_ESSENTIALS_H
