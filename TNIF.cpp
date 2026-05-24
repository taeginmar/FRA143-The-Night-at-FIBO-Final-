#include "Game.cpp"
#include "Title.cpp"
#include <SFML/Audio.hpp>



int main() {
    int state = 0;
    while( state != 4 || state != 3 ) {
        state = Title(); 
        if(state == 1){
            Play();
        }
        if(state == 3){
            return 0;
        }

    }

}