#include <stdio.h>
#include <malloc.h>
#include <memory.h>

// This file is a demo of how reference counted objects / structs
// could be implemented in the C backend of FTL.


/**
 * Creates a new object, zeros its memory and sets its refcount to 1.
 * @param type_size The size of the object to be created.
 * @return A Pointer to the newly creates object.
 */
void* internal_new_object(size_t type_size) {
    void* obj = calloc(1, type_size);

    // First attribute in struct is always the internal_refcount. Set it to 1
    size_t* refcount = (size_t*) obj;
    *refcount = 1;

    return obj;
}

// CAT -----------------------------------------

typedef struct {
    // Reference count
    size_t internal_refcount;
    int color;
    int mau;
} Cat;

/**
 * Creates a new cat. Nothing special here.
 */
Cat* internal_Cat_new() {
    Cat* cat = internal_new_object(sizeof(Cat));
    printf("Allocate cat %p\n", cat);
    return cat;
}

/**
 * Decrements the reference count of cat at the end of a scope. If refcount is 0 after decrementing, frees cat. If
 * cat is NULL, nothing happens.
 */
void internal_Cat_out_of_scope(Cat* const cat) {
    if (cat == NULL) {
        // Not yet initialized (maybe because it is a maybe null attribute of another struct) or already deallocated.
        return;
    }
    cat->internal_refcount--;
    if (cat->internal_refcount == 0) {
        printf("Deallocate cat %p\n", cat);
        free(cat);
    }
}

// PERSON -------------------------------------

typedef struct {
    size_t internal_refcount;
    char name[50];
    int age;
    // NotNull, therefore this is initialized in constructor
    Cat* cat;
} Person;

/**
 * Creates a new Person. Every NotNull member attribute (e.g. cat here) is initialized.
 */
Person * internal_Person_new() {
    Person* person = internal_new_object(sizeof(Person));
    printf("Allocate person %p\n", person);
    person->cat = internal_Cat_new();
    return person;
}

/**
 * Decrements the reference count of person at the end of a scope. If refcount is 0 after decrementing, frees person.
 * If person is NULL, nothing happens.
 */
void internal_Person_out_of_scope(Person* const person) {
    if (person == NULL) {
        // Not yet initialized (maybe because it is a maybe null attribute of another struct) or already deallocated.
        return;
    }
    person->internal_refcount--;
    internal_Cat_out_of_scope(person->cat);
    if (person->internal_refcount == 0) {
        printf("Deallocate person %p\n", person);
        free(person);
    }
}

// FAMILY --------------------------------------

typedef struct {
    size_t internal_refcount;
    char name[50];
    // Maybe null, therefore not in initialized in constructor
    Cat* cat;
} Family;

/**
 * Creates a new Family. Because cat may be null, it is not initialized.
 */
Family* internal_Family_new() {
    Family* family = internal_new_object(sizeof(Family));
    printf("Allocate family %p\n", family);
    return family;
}

/**
 * Creates a new alias (i.e. a copy of the reference) to family and increments its reference count. If family is
 * NULL, returns NULL.
 */
Family* internal_Family_alias(Family* const family) {
    if (family == NULL) {
        return NULL;
    }
    family->internal_refcount++;
    return family;
}

/**
 * Decrements the reference count of family at the end of a scope. If refcount is 0 after decrementing, frees family.
 * If family is NULL, nothing happens.
 */
void internal_Family_out_of_scope(Family* const family) {
    if (family == NULL) {
        // Not yet initialized (maybe because it is a maybe null attribute of another struct) or already deallocated.
        return;
    }
    family->internal_refcount--;
    internal_Cat_out_of_scope(family->cat);
    if (family->internal_refcount == 0) {
        printf("Deallocate family %p\n", family);
        free(family);
    }
}


int main() {
    Person* person = internal_Person_new();
    printf("person cat color %d\n", person->cat->color);

    Family* family = internal_Family_new();
    printf("family cat %p\n", family->cat);
    {
        // Local copy/alias of family
        Family* familyAlias = internal_Family_alias(family);
        printf("family refcount after alias %lu\n", familyAlias->internal_refcount);

        // RAII scope end. Decrement reference count
        internal_Family_out_of_scope(familyAlias);
    }
    printf("family refcount after alias out of scope %lu\n", family->internal_refcount);


    // RAII scope end. Decrement reference count
    internal_Person_out_of_scope(person);
    internal_Family_out_of_scope(family);
}
