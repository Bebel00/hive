#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <algorithm>

namespace Type
{
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

    inline Type str_to_type(const std::string& s)
    {
        std::string str = s;

        std::transform(str.begin(), str.end(), str.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        if (str == "abeille")
            return Type::ABEILLE;
        if (str == "araignee")
            return Type::ARAIGNEE;
        if (str == "coccinelle")
            return Type::COCCINELLE;
        if (str == "fourmi")
            return Type::FOURMI;
        if (str == "moustique")
            return Type::MOUSTIQUE;
        if (str == "sauterelle")
            return Type::SAUTERELLE;
        if (str == "scarabe")
            return Type::SCARABE;

        return Type::NONE;
    }
}

#endif // TYPES_H
