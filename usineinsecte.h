#ifndef USINEINSECTE_H
#define USINEINSECTE_H

#include "insecte.h"
#include "types.h"

#include <unordered_map>
#include <functional>
#include <memory>

/*                                ________
                             _____|      |_____
                            |     |      |     |
                            |     |      |     |
             _______        |     |      |     |         _______
       ______|       |_______|     |      |     |_______|       |______
      |       |       |       |     |      |     |       |       |      |
      |       |       |       |     |      |     |       |       |      |
      |   []  |       |   []  |     |      |     |   []  |       |   []  |
      |_______|_______|_______|_____|______|_____|_______|_______|______|
      |       |       |       |     |      |     |       |       |      |
      |       |       |       |     |      |     |       |       |      |
   ___|   []  |_______|   []  |_____|______|_____|   []  |_______|   []  |___
  |   |_______|       |_______|     |      |     |_______|       |_______|   |
  |   |       |       |       |     |      |     |       |       |       |   |
  |   |   []  |       |   []  |     |      |     |   []  |       |   []  |   |
  |___|_______|_______|_______|_____|______|_____|_______|_______|_______|___|
          |       |       |       |     |      |     |       |       |
          |       |       |       |     |      |     |       |       |
       ___|   []  |_______|   []  |_____|______|_____|   []  |_______|   []  |___
      |   |_______|       |_______|     |      |     |_______|       |_______|   |
      |   |       |       |       |     |      |     |       |       |       |   |
      |   |   []  |       |   []  |     |      |     |   []  |       |   []  |   |
      |___|_______|_______|_______|_____|______|_____|_______|_______|_______|___|
                        /    /    /    /    /    /    /    /    /
              _________/____/____/____/____/____/____/____/____/__________
             |______________________________________________|______________|
             |                     USINE A INSECTE                        |
             |  _______     _______     _______    _______    _______     |
             | |       |   |       |   |       |  |       |  |       |    |
             | |       |   |       |   |       |  |       |  |       |    |
             | |_______|   |_______|   |_______|  |_______|  |_______|    |
             |_______________________________________________|______________|
*/


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

private:
    std::unordered_map<Type::Type, Fabrique> map;

    UsineInsecte() {}

    UsineInsecte(const UsineInsecte&) = delete;
    UsineInsecte operator=(const UsineInsecte&) = delete;
};

#endif // USINEINSECTE_H
