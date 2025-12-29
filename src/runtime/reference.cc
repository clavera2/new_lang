#include "runtime/reference.h"

Reference::Reference(ReferenceType type) : type(type) {}

OwnedReference::OwnedReference(Object* o) : Reference(ReferenceType::Owned), block(new cBlock(o)) {}

OwnedReference::OwnedReference(OwnedReference&& o) : Reference(ReferenceType::Owned), block(o.block) {
    o.type = ReferenceType::None;
    o.block = nullptr;
}

OwnedReference& OwnedReference::operator=(OwnedReference&& o) {
    if (this != &o) {
            drop(*this);
            this->block = o.block; o.block = nullptr;
            o.type = ReferenceType::None;
        }
    return *this;
}

bool OwnedReference::isOwned() const { return true; }
bool OwnedReference::isBorrowed() const { return false; }
bool OwnedReference::isNone() const { return false; }
bool OwnedReference::isDangling() const { return block == nullptr; } // used by syntactive sugar: given reference x (&x), x?. Can only be dangling after a move

Object *OwnedReference::operator->() {
    return block->obj;
}

ReferenceType OwnedReference::getType() const {
    return ReferenceType::Owned;
}

OwnedReference::~OwnedReference() {
    drop(*this);
}


BorrowedReference::BorrowedReference(OwnedReference* o) :  Reference(ReferenceType::Borrowed) {
    this->block = o->block; // they both point to the same cblock
    block->refCount++;
}

BorrowedReference::BorrowedReference(const BorrowedReference& b)  : Reference(ReferenceType::Borrowed) { 
    block = b.block;
    block->refCount++;
}


BorrowedReference& BorrowedReference::operator=(const BorrowedReference& b) {
    if (this != &b) {
        drop(*this);
        block = b.block;
        block->refCount++;
    }
    return *this;
}


BorrowedReference& BorrowedReference::operator=(OwnedReference& owner) {
    drop(*this);
    block = owner.block;
    block->refCount++;
    return *this;
} 

Object* BorrowedReference::operator->() {
    if (! block || ! block->isAlive) throw NullPointerException("owner of object has gone out of scope");
    return block->obj;
}

ReferenceType BorrowedReference::getType() const { return ReferenceType::Borrowed; }
bool BorrowedReference::isOwned() const { return false; }
bool BorrowedReference::isBorrowed() const { return true; }
bool BorrowedReference::isNone() const { return false; }
bool BorrowedReference::isDangling() const { return ! block || ! block->isAlive; }

ReferenceType NoneReference::getType() const { return ReferenceType::None; }
bool NoneReference::isBorrowed() const { return false; }
bool NoneReference::isNone() const { return true; }
bool NoneReference::isOwned() const { return false; }
bool NoneReference::isDangling() const { return true; }

void drop(OwnedReference& ref) {
    ref.block->refCount--;
    if (ref.block->refCount != 0) {
        delete ref.block->obj;
        ref.block->isAlive = false;
        ref.block->obj = nullptr;
    } else { // this means no other reference to the object, safe to delete cblock;
        delete ref.block;
    }
}

void drop(BorrowedReference& ref) {
    ref.block->refCount--;
    if (ref.block->refCount == 0) {
        delete ref.block;
    } // else do nothing
}
