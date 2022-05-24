#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <initializer_list>

typedef struct coord_pair
{
    int y;
    int x;

    bool operator==(const coord_pair &c) const 
    {
        return (c.x == x && c.y == y);
    }
} coords;

enum health
{
    INFECTED,
    HEALTHY
};

class GameRules
{
public:

    GameRules(int ac, char **av);
    ~GameRules(void);

    void simulate(void);

    int grid_size;
    int rounds;
    int infection_threshold;
    int recovery_threshold;
    int **map;
    int **next_round_map;
    std::vector<coord_pair> starting_coords;



};

std::ostream& operator<<(std::ostream &os, const GameRules &rules);