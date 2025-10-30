Simple C and javascript minimax programs for playing/solving NIM.

This code is for the variant with
* 2 players.
* 4 rows of 1, 3, 5, 7 items.
* A turn can remove 1, 2, or 3 items from one row.
* misere play (player who takes last item loses.)

There are many sources that say NIM can be solved by suitably calculating 
the "nim-weight", typicaly the xor of the number in each row in binary,
possibly mod 4. None of these methods seem to work with this variation of NIM.

The recursive minimax approach is simple and works perfectly.
As expected, the player who goes first will always lose.

For the human player, the nim_list program calculates all possible 
"winning" boards, and these are listed in the nim_list.txt file.
The human player can win if they go second, and if on every turn they
make a move that results in one of the listed "winning" boards.
