# CS50 Final Project
## Asher Vogel, Rory Doyle, Eli Rosnberg, Nate Roe

The assignment is in a [public repo](https://github.com/cs50-2022-fall/project).
Do not clone that repo; view it on GitHub.  One person from your team should accept the assignment from GitHub classroom.
Watch if there for any commits that may represent updates to the assignment or specs.

See the course web site for [detailed description of the project](https://www.cs.dartmouth.edu/~tjp/cs50/project/index.html)

Add here any assumptions you made while writing the solution, or any ways in which you know your implementation fails to work.

## Usage

Run `make` from the home directory.
In one terminal window, navigate to the dealer directory `./dealer-given 1 *num_games* 8094`.
In another terminal window, navigate to the player directory and run `./player Asher 129.170.64.104 8094 ../data/training`.

## Known Problems

We chose to implement a different training algorithm that keeps track of which cards the player has, not just the number of points. Because storing this information requires the use of more memory, valgrind runs so slowly that we cannot run valgrind at the server's speed. This is not a problem for tournament play because our program is fast enough to run at the server's speed without valgrind on.

Because of this, we instead testing our player with valgrind using our own server running with longer delays. We found no memory leaks, but received a few errors that don't seem to impact the program's functionality. The output of this valgrind testing can be found in a file called `testing.out` within the `player` directory.