#ifndef RUNTIME_REFERENCE_H
#define RUNTIME_REFERENCE_H

#include <cstddef>
#include "exceptions.h"

struct Object;

enum class ReferenceType {
    Owned, Borrowed
};

class Reference {
public:
    Reference(ReferenceType type);
    virtual ~Reference() = default;
    virtual ReferenceType getType() const = 0;
    virtual bool isOwned() const = 0;
    virtual bool isBorrowed() const = 0;
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
private:
    OwnedReference* ptr;
};

#endif // RUNTIME_REFERENCE_H