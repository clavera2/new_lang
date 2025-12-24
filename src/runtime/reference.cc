#include "runtime/reference.h"

Reference::Reference(ReferenceType type) : type(type) {}

OwnedReference::OwnedReference(Object* o) : Reference(ReferenceType::Owned), ptr(o) {}
OwnedReference::OwnedReference(OwnedReference&& o) : Reference(ReferenceType::Owned), ptr(o.ptr) {}
OwnedReference& OwnedReference::operator=(OwnedReference&& o) {
    if (this != &o) {
            delete ptr;
            ptr = o.ptr; o.ptr = nullptr;
        }
    return *this;
}

bool OwnedReference::isOwned() const { return true; }
bool OwnedReference::isBorrowed() const { return false; }

Object *OwnedReference::operator->() {
    return ptr;
}

ReferenceType OwnedReference::getType() const {
    return ReferenceType::Owned;
}

OwnedReference::~OwnedReference() {
    delete ptr;
    ptr = nullptr;
}


BorrowedReference::BorrowedReference(OwnedReference* o) :  Reference(ReferenceType::Borrowed) {
    this->ptr = ptr;
}

BorrowedReference::BorrowedReference(const BorrowedReference& b)  : Reference(ReferenceType::Borrowed) { 
    ptr = b.ptr;
}


BorrowedReference& BorrowedReference::operator=(const BorrowedReference& b) {
    if (this != &b) {
        ptr = b.ptr;
    }
    return *this;
}


BorrowedReference& BorrowedReference::operator=(OwnedReference& owner) {
    ptr = &owner;
    return *this;
} 

Object* BorrowedReference::operator->() {
    if (ptr->ptr == nullptr) {
        throw NullPointerException("owner of object has gone out of scope");
    } else {
        return ptr->ptr;
    }
}

ReferenceType BorrowedReference::getType() const { return ReferenceType::Borrowed; }
bool BorrowedReference::isOwned() const { return false; }
bool BorrowedReference::isBorrowed() const { return true; }