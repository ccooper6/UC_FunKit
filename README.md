# UC Fun Kit Game - Group 306

PONG!

This is a two player interactive game using the ATMega32U2 based on pong, with a few additions of randomness to make the game more fun to play.

### Authors
- Caleb Cooper
- Joshua Ching

### Setup
First, clone this repository to your device by running the command:
```sh
git clone https://eng-git.canterbury.ac.nz/ence260-2020/group306.git
```
Then, move this repository into the `ence260-ucfk4/assignment` directory so that it can properly access the ucfk4 functions properly.

### How to Play
First connect both fun kits to your device and boot them both up by running the command:
```sh
make program
```
Do this twice. This will generate all the necessary .o files and then generate a .hex file that will be flashed onto the fun kits.

After booting, you should see a text screen saying "Choose Player 1" on both screens. Press down on the navswitch on one of the fun kits to start. 
Once the game has started, each player has a slider that they can move side to side using the navswitch.

### Game Rules
- The objective of the game is to defend their goal using the slider
- A player gains a point when the other player fails to defend their goal.
- First player to score 3 points wins
- The ball will spawn at the top of the screen in a random position and move in a random direction
- The ball will bounce off the walls and the sliders
- If the ball hits the slider on the left side, it will bounce to the right and vice versa, a hit to the middle of the slider can 
send the ball left, straight or right with equal chance.

After a player hits 3 points, the game will show text saying whether you won or lost and then return to the main menu with text 
saying "Play Again". Press down on the navswitch to play again.
