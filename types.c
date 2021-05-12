#include "types.h"

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

int are_types_compatible(internal_type type_a, internal_type type_b)
{
    if (type_a == type_b)
        return 1;
    else
        return 0;
}
