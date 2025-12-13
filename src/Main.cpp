//Esteja na pasta GameEngineTAC
//Comandos: mingw32-make clean
//Compilado para debug: mingw32-make debug
//Compilação normal: mingw32-make all
//Rodar: .\JOGO.exe

#include "Game.h"
#include <stdexcept>
#include <iostream>
#include <cstdio>

int main(int argc, char* argv[]){

    try {
        Game& game = Game::GetInstance();
        game.Run();
    } catch (const std::string& e) {
        fprintf(stderr, "[Main] ERRO FATAL: %s\n", e.c_str()); 
        return 1;
    } catch (const std::exception& e) {
        fprintf(stderr, "[Main] ERRO PADRAO: %s\n", e.what()); 
        return 1;
    }

    return 0;
}
