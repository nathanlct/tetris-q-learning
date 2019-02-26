# Learn to play Tetris using approximate Q-Learning

## Todo

- [x] Controls
- [ ] Scoring system
- [ ] UI
- [ ] \(Optional) More complex wall kicks when rotating (could be exploited by agent)
- [ ] Q-Learning

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
Left | Q
Right | D
Rotate Left | A
Rotate Right | E
Soft Drop | S
Hard Drop | Z
Hold | Space


---

## Scoring

Action | Points
------ | ------
Single | 100 × level
Double | 300 × level
Triple | 500 × level
Tetris | 800 × level; difficult
T-Spin Mini no lines | 100 × level
T-Spin no lines | 400 × level
T-Spin Mini Single | 200 × level; difficult
T-Spin  |  	800 × level; difficult
T-Spin Mini Double (if present) | 400 × level; difficult
T-Spin Double | 1200 × level; difficult
T-Spin Triple | 1600 × level; difficult
Back-to-Back difficult line clears | points x 1.5
Combo | 50 × combo count × level
