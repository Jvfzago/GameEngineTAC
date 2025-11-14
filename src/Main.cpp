#include "Game.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char* argv[]){
    try {
        Game& game = Game::GetInstance();
        game.Run();

    } catch (const std::string& e) {
        std::cerr << "ERRO FATAL: " << e << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "ERRO PADRAO: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}