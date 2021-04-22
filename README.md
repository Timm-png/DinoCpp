## DinoCPP

DinoCPP is not a game, it is a very bad C++ code(

This game write on a C++ with [sfml](https://www.sfml-dev.org/index.php) library.

### Install sfml

Debian/Ubuntu
```sh
apt-get install libsfml-dev
```
Arch Linux
```sh
pacman -S sfml
```
Fedora/RedHat
```sh
If you use Fedora or RedHat, you are not welcome here 
```
### Run
#### Linux:
##### Download releas linux version and run `DinoCPP`

or

##### Compile from source code:
```shell
./Scripts/BuildAndRun.sh

./Scripts/Build.sh

./Scripts/Run.sh
```

#### Windows:

##### Download releas linux version and run `DinoCPP.exe`

or

##### Compile from source code:

Download [DinoWinSourceCode](https://github.com/Timm-png/DinoCPP/releases/download/v0.2beta/DinoWinSourceCode.zip)
```shell
path\to\DinoWinSourceCode>C:\path\to\gcc\g++.exe main.cpp -I "SFML/include" -L "SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system -o DinoCPP.exe
```
##### version: 0.2beta (game in development)

###### And, I don't know why this working.