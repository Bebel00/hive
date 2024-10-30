#ifndef TYPES_H
#define TYPES_H

#include <string>

enum class Type
{
    ABEILLE,
    ARAIGNEE,
    COCCINELLE,
    FOURMI,
    MOUSTIQUE,
    SAUTERELLE,
    SCARABE,
    NONE
};

inline std::string type_to_str(Type type)
{
    switch (type)
    {
    case Type::ABEILLE:
        return "Abeille";
    case Type::ARAIGNEE:
        return "Araignee";
    case Type::COCCINELLE:
        return "Coccinelle";
    case Type::FOURMI:
        return "Fourmi";
    case Type::MOUSTIQUE:
        return "Moustique";
    case Type::SAUTERELLE:
        return "Sauterelle";
    case Type::SCARABE:
        return "Scarabe";
    case Type::NONE:
        return "None";
    default:
        return "E";
    }
}

#endif // TYPES_H
