# Introduction

This project implements a simple text-based version of the gambling game [Keno](https://en.wikipedia.org/wiki/Keno). The player interacts with the game by providing a file with the starting credit, the number of rounds, and a maximum of 15 numbers between 1 and 80 representing the bets,  called spots.

To calculate how much a player wins in a round it's used the number of hits associated with how many numbers were bet. To win this game the player must finish with a credit greater than the initial one.

# Author(s)

Fernanda Lustosa (fernandals)

Paulo Andrade (PauloFAndrade)

# Problems found or limitations

During development, there was a slight difficulty in creating Cmake and testing extreme cases.

# Grading

Preencha os itens que você implementou.

- [X] Receives input data via command line (5 credits);
- [X] Correctly handles the input bet file, treating both regular and problematic cases accordingly (20 credits);
- [X] Codes correctly the KenoBet class, according to the description provided in Code 1 (25 credits);
- [X] Executes correctly the amount of rounds defined in the input bet file (15 credits);
- [X] Identifies correctly the hits and the player’s payoff for every round (20 credits);
- [X] Displays correctly the information requested in Section 2.2 (15 credits).


# Compiling and Runnig

There are two possibilities to compile this project: using CMake or g++. Instructions for doing this are listed below.

##### Using cmake
Inside the project folder run the code below:
```
	cd source
	cmake -S . -B build
	cmake --build build
	cd build
```
Compilation generates an executable file named `keno` inside the `build` folder. 

##### Using g++
Again, inside the project folder, run the code below:
```
	cd source/core
	g++ -Wall -std=c++11 main.cpp keno_bet.cpp -o keno
```
This will generate an executable file named `keno` inside the `core` folder.

##### Running
To run this project, you will need to provide a bet file as stated before.
The file must be written in a specific way for the program to work correctly, follow the template below in your bet file.
```
wage_amount
number_of_rounds
the_numbers_you_bet
```
P.S.: Do not put empty lines between data.
P.P.S.: The numbers you bet must be separated by a space.

Now to execute the project, run the following command (inside `build` if you used Cmake or inside `core` if you choose g++) making the necessary adaptations:
```
	./keno file_path/bet_file.dat
```
