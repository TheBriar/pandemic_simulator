#include "game_rules.hpp"

void parse_infected_coords(std::vector<coord_pair> &start_coords, char *coords)
{
    struct coord_pair temp;

    while (*coords++)
    {
        if (*coords == '<')
        {
            coords++;
            temp.y = atoi(coords);
            while (*coords && *(coords - 1) != ',')
                coords++;
            temp.x = atoi(coords);
            start_coords.push_back(temp);
        }
    }
}

void verify_values(const GameRules &rules)
{
    if (rules.grid_size < 0 || rules.rounds < 0 || rules.infection_threshold < 0 || rules.recovery_threshold < 0)
        throw std::invalid_argument("wrong value in arguments");
    for (int i = 0; i < rules.starting_coords.size(); i++)
    {
        if (rules.starting_coords[i].x < 0 || rules.starting_coords[i].x >= rules.grid_size || \
        rules.starting_coords[i].y < 0 || rules.starting_coords[i].y >= rules.grid_size)
            throw std::invalid_argument("wrong value in arguments");
    }
}

GameRules::GameRules(int ac, char **av)
{
    this->grid_size = atoi(av[1]);
    this->rounds = atoi(av[2]);
    this->infection_threshold = atoi(av[3]);
    this->recovery_threshold = atoi(av[4]);
    this->map = new int*[grid_size];
    this->next_round_map = new int*[grid_size];
    parse_infected_coords(this->starting_coords, av[5]);
    verify_values(*this);
    for (int i = 0; i < grid_size; i++)
    {
        this->map[i] = new int[grid_size];
        this->next_round_map[i] = new int[grid_size];
    }

    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            struct coord_pair temp = {.y = i, .x = j};
            if (std::find(this->starting_coords.begin(), this->starting_coords.end(), temp) != std::end(this->starting_coords))
                 this->map[i][j] = INFECTED;
            else
                this->map[i][j] = HEALTHY;
        }
    }
}

GameRules::~GameRules(void)
{
 
}

std::ostream& operator<<(std::ostream &os, const GameRules &rules)
{
    for (int i = 0; i < rules.grid_size; i++)
    {
        for (int j = 0; j < rules.grid_size; j++)
        {
            if (rules.map[i][j] == INFECTED)
                os << "🤢";
            else
                os << "😀";
        }
        os << '\n';
    }
    return os;
}