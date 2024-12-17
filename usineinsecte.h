#ifndef USINEINSECTE_H
#define USINEINSECTE_H

#include "insecte.h"
#include "types.h"

#include <unordered_map>
#include <functional>
#include <memory>

class UsineInsecte
{
    using Fabrique = std::function<std::unique_ptr<Insecte>(Team)>;

public:
    static UsineInsecte& get_usine() { static UsineInsecte usine; return usine; }

    bool enregistrer_type(Type::Type t, Fabrique f) { map[t] = f; return true; }

    std::unique_ptr<Insecte> fabriquer(Type::Type type, Team team) const
    {
        auto i = map.find(type);

        if (i != map.end())
            return (i->second)(team);

        return nullptr;
    }

     int get_jetons_max(Type::Type type) const {
        auto insecte_temp = fabriquer(type, Team::BLANC);
        if (insecte_temp) {
            return insecte_temp->get_jetons_max();
        }
        return 0;
    }
private:
    std::unordered_map<Type::Type, Fabrique> map;

    UsineInsecte() {}

    UsineInsecte(const UsineInsecte&) = delete;
    UsineInsecte operator=(const UsineInsecte&) = delete;
};

#endif // USINEINSECTE_H
