#ifndef RUNTIME_REFERENCE_H
#define RUNTIME_REFERENCE_H

#include <cstddef>
#include "exceptions.h"

// represents an object allocated on the heap
struct Object;

/*
Every name within a namespace is mapped to a reference to an object on the heap. There are 3 types of references:
1) owned referece: the name "owns" the object. Once the name is deleted from the namespace implicitly or explicitly,
the object is automatically deallocated.

2) borrowed reference: the name borrows the object on the heap without gaining ownership of it. Once the name is deleted
implicitly or explicitly, the object still resides in the heap until its owning name is deleted.

3) none reference: the name refers to no object, this is automatically set when a move occurs or an  object is deleted from memory

*/
enum class ReferenceType {
    Owned, Borrowed, None
};

class Reference {
public:
    Reference(ReferenceType type);
    virtual ~Reference() = default;
    virtual ReferenceType getType() const = 0;
    virtual bool isOwned() const = 0;
    virtual bool isBorrowed() const = 0;
    virtual bool isNone() const = 0;
protected:
    ReferenceType type;
};

class OwnedReference : public Reference {
public:
    OwnedReference(Object* o);
    OwnedReference(const OwnedReference&) = delete;
    OwnedReference(OwnedReference&& o);

    OwnedReference& operator=(const OwnedReference&) = delete;
    // used for assignment and returns
    OwnedReference& operator=(OwnedReference&& o);

    bool isOwned() const override;
    bool isBorrowed() const override;
    bool isNone() const override;

    Object* operator->();

    ReferenceType getType() const override;


    void* operator new(size_t) = delete; 

    ~OwnedReference();
private:
    friend class BorrowedReference;
    Object* ptr;
};

// a borrowed reference is created from an Owned reference (via. &owner)
// borrowed references can also be copied
class BorrowedReference : public Reference {
public:
    BorrowedReference(OwnedReference* ptr);
    
    BorrowedReference(const BorrowedReference& b);

    BorrowedReference& operator=(const BorrowedReference& b);

    BorrowedReference& operator=(OwnedReference& owner);

    // accesses the borrowed object
    Object* operator->();

    ~BorrowedReference() = default;

    ReferenceType getType() const override;
    bool isOwned() const override;
    bool isBorrowed() const override;
    bool isNone() const override;
private:
    OwnedReference* ptr;
};

class NoneReference : public Reference {
public:
    NoneReference() : Reference(ReferenceType::None) {}

    ReferenceType getType() const override;
    bool isNone() const override;
    bool isOwned() const override;
    bool isBorrowed() const override;
    
    ~NoneReference() = default;
};

#endif // RUNTIME_REFERENCE_H