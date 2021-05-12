#pragma once

typedef enum {
    TYPE_NONE = 0,
    TYPE_BOOL,
    TYPE_CHAR,
    TYPE_INT,
    TYPE_POINTER
} internal_type;

// Returns a string representation of the type
char* type_to_string(internal_type type);

// Returns true (1) if types are compatible, false otherwise
// Types are compatible for operations is both are booleans, arithmetic or pointer types
int are_types_compatible(internal_type type_a, internal_type type_b);
