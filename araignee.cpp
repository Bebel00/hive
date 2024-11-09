#include "araignee.h"
#include "case.h"
#include "plateau.h"
#include <set>

Araignee::Araignee(Team team) : Insecte(team) { }

void Araignee::get_moves_possibles(std::vector<Case*>& move_possibles) const {
    std::set<Case*> visited;
    std::vector<Case*> path;

    auto dfs = [&](Case* current_case, int depth, auto&& dfs_ref) -> void {
        if (depth == 3) {
            if (Case::is_empty(current_case) && !move_casse_ruche(get_case(), get_case()->get_plateau()->get_cases())) {
                move_possibles.push_back(current_case);
            }
            return;
        }

        visited.insert(current_case);
        for (auto direction : Case::DIRECTIONS_ALL) {
            Case* next_case = current_case->get_case_from_direction(direction);
            if (next_case && visited.find(next_case) == visited.end() && Case::is_empty(next_case)) {
                path.push_back(next_case);
                dfs_ref(next_case, depth + 1, dfs_ref);
                path.pop_back();
            }
        }
        visited.erase(current_case);
    };

    dfs(get_case(), 0, dfs);
}

