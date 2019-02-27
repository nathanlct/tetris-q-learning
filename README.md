# Learn to play Tetris using approximate Q-Learning


## Dependencies

* C++17
* SFML

Then compile using `make` or run using `make run`.

## Misc

* Field dimension: 10 cells wide by 20 high
* 7 kind of pieces (tetrominos I, T, O, L, J, Z and S):

    ![Tetrominos](https://i0.wp.com/mindyourdecisions.com/blog/wp-content/uploads/2018/05/tetris-riddle-pieces.png?resize=600%2C165&ssl=1)

----

## Controls

Action | Key
------ | ---
Move Left | Q
Move Right | D
Rotate Left | K
Rotate Right | M
Soft Drop | S
Hard Drop | Z
Hold | Space


---

## Scoring

Action | Reward
------ | ------
Soft Drop | 1 point per cell
Hard Drop | 2 point per cell
Single (1 line) | 100 points
Double (2 lines) | 300 points
Triple (3 lines) | 500 points
Tetris (4 lines) | 800 points
