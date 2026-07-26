There is a N player tournament. Players have rank 1 to N and each player has a unique rank. Assume that the best player always wins, where the best player is the player with rank 1.

The tournament is a knockout tournament. This means if we have 8 players with their ranks [1 2 3 4 5 6 7 8], the tournament will look like this:
1st round: [1 2] [3 4] [5 6] [7 8]
2nd round: [1 3] [5 7]
3rd round: [1 5]
champion : [1]

We are calling [1 2 3 4 5 6 7 8] a "draw" where in the 1st round: the first two players meet in the first match, the next two players meet in the second match, and so on.
In the 2nd round: in the first match, the winner of the first match of the 1st round and the winner of the second match of the 1st round will play together. And similarly, in the second match, the winner of the third match of the 1st round and the winner of the fourth match of the 1st round will play together.

In short: given a draw, if we don't change the order of the players, players will meet in their order on the draw, and of course the winner moves to the next round. The tournament ends when there is only a single player remaining.

A draw is a valid draw when in each round, the best (based on rank) player plays with the worst player available, the second best player plays with the second worst player available, and so on.

Given a draw, find out whether it is a valid draw.
