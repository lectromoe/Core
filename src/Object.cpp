#include <core/Object.h>
#include <core/Logger.h>


namespace core {

std::atomic<uint32_t> Object::objectCounter { 0 };

Object::Object(string name) noexcept
: name(std::move(name)), id(++objectCounter)
{
    Logger::Log(OBJECT, INFO) << "Created object " << GetInfo();
}
Object::Object(Object &&other) noexcept
: name(std::move(other.name)), id(other.id)
{
    other.id = 0;
}
Object::~Object() {
    // id == 0 means that object was moved, no need to log destruction
    if (id != 0) {
        Logger::Log(OBJECT, INFO) << "Destroyed object " << GetInfo();
    }
}
uint32_t Object::GetId() const {
    return id;
}
string Object::GetInfo() const {
    return "\"" + name + "\""  + " ID(" + std::to_string(GetId()) + ")";
}
bool Object::operator==(const Object &rhs) const {
    return id == rhs.id;
}
bool Object::operator!=(const Object &rhs) const {
    return !(id == rhs.id);
}
Object& Object::operator=(Object &&other) noexcept {
    if (this != &other) {
        Logger::Log(OBJECT, INFO) << "Object " << other.GetInfo() << " was moved into " << this->GetInfo();
        id = other.id;
        other.id = 0;
        name = std::move(other.name);
    }
    return *this;
}
const string& Object::GetName() {
    return name;
}

}