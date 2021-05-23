/**
 *  core::Entity template function implementations file
 */

#include "Logger.h"
#include "Component.h"

namespace core {

template<template<typename> typename T, typename S, typename ...Args>
Entity& Entity::AddComponent(Args... args) {
    static_assert(std::is_base_of<core::Component, T<S>>::value, "Component S must inherit from core::Component");

    // Create a copy of provided component, to ensure heap allocation of all children
    std::shared_ptr<T<S>> component = std::make_shared<T<S>>(*this, args...);

    components.push_back(std::move(component));
    return *this;

};
template<typename T, typename... Args>
Entity& Entity::AddComponent(Args... args) {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");

    // Create a copy of provided component, to ensure heap allocation of all children
    auto component = std::make_shared<T>(*this, args...);

    components.push_back(std::move(component));
    return *this;
}
template<typename T, typename C>
bool Entity::assertRequiredComponent(C* caller) {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");
    static_assert(std::is_base_of<core::Component, C>::value, "Component C must inherit from core::Component");

    if ( !this->HasComponent<T>() ) {
        Logger::Log(OBJECT, ERR_HERE) << "Entity " << this->GetInfo() << " does not have component "
                                          << typeid(T).name() << ", required by " << caller->GetInfo();
        return false;
    } else {
        return true;
    }
}
template<typename T>
bool Entity::assertExistingComponent() {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");

    if ( this->HasComponent<T>() ) {
        Logger::Log(OBJECT, ERR_HERE) << "Entity " << this->GetInfo() << " already has component "
                                          << typeid(T).name();
        return true;
    } else {
        return false;
    }
}

template<typename T>
Component* Entity::GetComponent() {
    auto it = std::find_if(components.begin(),
                           components.end(),
                           [&](std::shared_ptr<Component> const& p) {
                               return typeid(*p).hash_code() == typeid(T).hash_code();
                           });

    if ( it != components.end() ) {
        return it->get();
    } else {
        return nullptr;
    }
}
template<typename T>
bool Entity::HasComponent() {
    return std::any_of(components.begin(),
                       components.end(),
                       [&](std::shared_ptr<Component> &c) { return typeid(*c).hash_code() == typeid(T).hash_code(); }
                       );
}

} // namespace core