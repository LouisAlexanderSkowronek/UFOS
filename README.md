# Spaceships
A simple 2D space-shooter written in C++ using [SFML](https://www.sfml-dev.org/).

## How to try it out (Linux)

- clone the repo: Run `git clone https://github.com/LouisAlexanderSkowronek/UFOS.git` or download as zip and then extract it.
- create and change into build directory: run `cd UFOS/ && mkdir build && cd build/`
- Build the game: Make sure that you have GNU C++ compiler, cmake, and SFML libraries installed within your system, then run `cmake .. && make`
- Run the game using `./UFOS`


## Copyright limitations

Due to copyright reasons, the public version of the game has currently no music. Instead, there is a placeholder file, kleiner-satellit.ogg, in the assets directory and the header file include/Spaceships/copyright_limitations.hpp. To play the full version of the game, place two slashes (//) right before the `#define COPYRIGHT_LIMITED` statement in the file after replacing the placeholder file with actual music (I recommend the song "Kleiner Satellit" by Jasmin Wagner but I don't have permission to upload it yet), and after rebuilding the game (see above in "How to try it out" under "Build the game") you can enjoy the full game.

## Contact

You can email me if you have any questions, bugs or improvement ideas.
Email: louis.alexander.skowronek@gmail.com