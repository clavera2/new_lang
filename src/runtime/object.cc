#include "runtime/object.h"

Object::Object(RTTI* rtti) : rtti(rtti) {}

Object::~Object() {
    for (const auto& p : fields) {
        if (p.second->isOwned()) delete p.second;
    }
}

bool Object::containsField(const std::string& name) {
    return fields.find(name) != fields.end();
}

Reference* Object::getField(const std::string& name) {
    if (! containsField(name)) throw AttributeException("no such field");
    return fields[name];
}

void Object::setField(const std::string& name, Reference* r) {
    fields[name] = r;
}

