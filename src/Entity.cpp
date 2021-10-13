#include <core/Components/Camera.h>
#include <core/Scene/SceneImporter.h>
#include <core/Model.h>
#include <core/Entity.h>
#include <core/Logger.h>

namespace core {

Entity::Entity(const string& name, GraphObject* parent, ComponentsContainer c, Layer* layer)
: core::Object(name), GraphObject(parent), components(std::move(c)), layer(layer)
{
    layer->AddEntity(*this);
}
Entity::~Entity() {
    layer->RemoveEntity(*this);
}
bool Entity::operator!=(const Entity &rhs) const {
    return !(rhs == *this);
}
void Entity::FixedTick() {
    std::for_each(components.begin(), components.end(), [&](std::shared_ptr<IComponent> &c) { c->FixedTick(); });
}
void Entity::EarlyTick() {
    std::for_each(components.begin(), components.end(), [&](std::shared_ptr<IComponent> &c) { c->EarlyTick(); });
}
void Entity::Tick() {
    std::for_each(components.begin(), components.end(), [&](std::shared_ptr<IComponent> &c) { c->Tick(); });
}
void Entity::LateTick() {
    std::for_each(components.begin(), components.end(), [&](std::shared_ptr<IComponent> &c) { c->LateTick(); });
}
bool Entity::operator==(const Entity &rhs) const {
    return this->GetId() == rhs.GetId();
}
vector<shared<Entity>> Entity::Load(const string& filepath) {
    SceneImporter sceneImporter;
    SceneData* sceneData = sceneImporter.ImportScene(filepath);
    return sceneImporter.ImportEntities(*sceneData);
}
void Entity::SetLayer(const string& name) {
    layer->RemoveEntity(*this);
    Layer* newLayer = Layer::Get(name);
    newLayer->AddEntity(*this);
    layer = newLayer;
}
void Entity::SetLayer(Layer* newLayer) {
    layer->RemoveEntity(*this);
    newLayer->AddEntity(*this);
    layer = newLayer;
}

} // namespace core