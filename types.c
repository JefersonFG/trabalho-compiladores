#include "types.h"

// Checks if the type is arithmetic
int is_type_arithmetic(internal_type type);

int are_types_compatible(internal_type type_a, internal_type type_b)
{
    switch (type_a) {
    case TYPE_BOOL:
        return type_b == TYPE_BOOL;
    case TYPE_CHAR:
    case TYPE_INT:
    case TYPE_POINTER:
        return is_type_arithmetic(type_b);
    }
}

int is_type_arithmetic(internal_type type)
{
    return type == TYPE_CHAR || type == TYPE_INT || type == TYPE_POINTER;
}

char* type_to_string(internal_type type)
{
    switch (type) {
    case TYPE_BOOL:
        return "bool";
    case TYPE_CHAR:
        return "char";
    case TYPE_INT:
        return "int";
    case TYPE_POINTER:
        return "pointer";
    }
}
