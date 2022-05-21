#include "game_rules.hpp"

bool infected_adjacency(GameRules game, int y, int x)
{
    int count = 0;

    for (int i : {-1, 0, 1})
         for (int j : {-1, 0, 1}) 
            if (i != 0 || j != 0)
            {
                if (y + i >= 0 && y + i < game.grid_size && \
                    x + j >= 0 && x + j < game.grid_size)
                    if (game.map[y + i][x + j] == INFECTED)
                        count++;

            }
    if (game.map[y][x] == HEALTHY)
    {
        if (count > game.infection_threshold)
            return (true);
        return (false);
    }
    if (8 - count > game.recovery_threshold)
        return (false);
    return (true);
}

void populate_next(GameRules &game)
{
    for (int i = 0; i < game.grid_size; i++)
    {
        for (int j = 0; j < game.grid_size; j++)
        {
            if (infected_adjacency(game, i, j))
                game.next_round_map[i][j] = INFECTED;
            else
                game.next_round_map[i][j] = HEALTHY;
        }
    }
    for (int i = 0; i < game.grid_size; i++)
        for (int j = 0; j < game.grid_size; j++)
            game.map[i][j] = game.next_round_map[i][j];
}

void simulate(GameRules game)
{
    for (int i = 0; i < game.rounds; i++)
    {
        populate_next(game);
        // std::cout << "//-------round " << i + 1 << "-------//" << std::endl;
        // std::cout << game;
    }
    std::cout << "//-------end-------//" << std::endl;

    std::cout << game;
}


int main(int ac, char **av)
{
    if (ac != 6)
    {
        std::cout << "Wrong format, example: ./pandemic grid_size rounds infection_threshold recovery_threshold {<y,x>,<y,x>}" << std::endl;
        return (1);
    }

    try 
    {
        GameRules game(ac, av);
        std::cout << "//-------start-------//" << std::endl;
        std::cout << game;
        simulate(game);
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
        return (1);
    }
    return (0);

}