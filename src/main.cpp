#include <iostream>
#include "core/engine.hpp"

int main()
{
    Engine game;

    try
    {
        game.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}