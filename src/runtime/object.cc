#include "runtime/object.h"


Object::~Object() {
    for (const auto& p : fields) {
        drop(p.second);
    }
}

// if the field isnt in the object's namespace, check the type
bool Object::containsField(const std::string& name) {
    if (fields.count(name) == 0) {
        auto type = fields["__type__"];
        if (type->getType() == ReferenceType::None) {
            return false;
        }
        return (*type)->containsField(name);
    } else {
        return fields[name];
    }
}

Reference* Object::getField(const std::string& name) {
    if (! containsField(name)) throw AttributeException("no such field");
    if (fields.count(name) != 0) {
        return fields[name];
    } else {
        auto type = fields["__type__"];
        return (*type)->getField(name);
    }
}

void Object::setField(const std::string& name, Reference* r) {
    fields[name] = r;
}

