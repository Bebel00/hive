#ifndef TEAMS_H
#define TEAMS_H
#include <string>

enum class Team
{
    BLANC,
    NOIR,
    NONE
};

// namespace Team
// {
// inline std::string team_to_str(Team team)
// {
//     switch (team)
//     {
//     case Team::BLANC:
//         return "BLANC";

//     case Team::NOIR:
//         return "NOIR";

//     case Team::NONE:
//         return "NONE";

//     default:
//         return "E";
//     }
// }

// inline Team str_to_team(const std::string& s)
// {
//     std::string str = s;

//     std::transform(str.begin(), str.end(), str.begin(),
//                    [](unsigned char c){ return std::tolower(c); });

//     if (str == "blanc")
//         return Team::BLANC;
//     if (str == "noir")
//         return Team::NOIR;

//     return Team::NONE;
// }
// }
#endif // TEAMS_H
