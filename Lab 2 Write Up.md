#Introduction
In this lab, we created firmware for the controller we designed in lab 2. The requirements were that the left stick controls movement (through standard WASD input) and the right stick controls the mouse.

#Design Methodology
I used the example code for as much of the lab as was fitting. This means that the majority of the face keys the right analog stick were simply slightly modified sample code for writing to keyboard and moving mouse respectively. The left stick simply maps to the WASD keys after the analog stick has passed a certain threshold. This threshold was tuned to what felt natural relative to existing controllers.

The unique additions conist of an enable switch, a mode switch button, and 6 total buttons which were read as a single analog input. The switch was a simple on-off switch that was used as the condition for the rest of the code running. This allows the controller to be silenced when need be. A silence was chosen over a hardware shutoff since it prevents bugs such as improper pull-ups for occuring. Furthermore there is significant startup lag when first plugging in a controller, so a silence allows for the controller to switch between active and inactive states with zero delay.

The mode control button when pressed toggles the d-pad between serving as arrow keys and serving as mouse controls. When in control mode, the up and down buttons increase and decrease sensitivity respectively. Currently they adjust sensitivity linearly, which allows for much more precise sensitivity adjustments at the cost of lots of button presses. the alternative was to have the scale be exponential which would allow rapid sensitivity swings without a lot of user input. 

Ultimately, I will implement the exponential solution; however, since the next lab requires extensive testing of the controller between various people who might enjoy a wide range of sensitivities, I felt it was more important to have a finer resolution for this purpose. Thus, as the firmware works right now, the senstivity buttons are more for initially programming the controller to a single sensitivity and staying with it for a decent length of time rather than rapidly switching sensitivities in action.

The right and left d-pad buttons when in control mode affect the rate of acceleration. Initially, acceleration is 0 but can be increased. The acceleration when non-zero behaves similarly between all values with the only change being that the magnitude of the acceleration and not the duration.

The acceleration works by checking if the user is currently at the maximum position on the analog stick. If they are, the controller assumes the player wants to go faster (otherwise they would pull back a little on the stick). Every poll cycle (around 5ms) if the user is at the max value, the mouse sensitivy increases by 15% time the selected acceleration. For example, if a user is on sensitivity 2 and holds the stick all the way to the right for 15 ms, for the first 5 ms the mouse will move at regular speed, for the next 5 ms the mouse will move 30% faster (15% times 2), and for the last 5 ms the mouse will move 60% faster.

When the user pulls back from the max value, I initially found that the sudden deceleration was jarring for the user, so I chose to dial back the deceleration at a rate of 100% times the acceleration. Thus in our previous example, the mouse would have decelerated instantly, however, if the user had been holding the stick for 7 polling cycles or more, (which corresponds to at least 105% times acceleration max speed), the controller would not automatically snap back to base speed, but will step down by 100% every polling cycle. This feels a lot more natural but has one large downside, it makes the mouse movement less predictible since it is hard to get back to fine control after a long period of acceleration. Ultimately I decided to stick with the slower decelleration since I value usability over precision for a controller input since there exist much more precise control methods already in the way of a keyboard and mouse. 

The final deviation was the map from analog back to digital. This was achieved by simply having a large if-elseif block at the beginning of the code that mapped each range of analog values to a particular set of keys being pressed. This is very inefficient since for some of the latter cases, the code has to go through over 30 if evaluations. Because of  this, I placed the less time sensitive buttons (control button and start button) to correspond to the latter ranges while the more important shoulder and trigger buttons will usually happen in the first 10 to 15 if statements.

The more elegant solution here would be to create a bit association table so that certain bits of the analog input would set certain 'flag' bits within a control signal, then these flags would be used to determine which button had been pressed or not. Since I only, have 6 buttons being evaluated, 2 of them being rarely pressed, I felt that this was unneccessary, but if the cycle time of the loop is found to be too long, this is the first place that can be tremendously optimized.

Finally, I chose arbitrary key assignments for most keys since most modern games allow key rebinding in-game. The keys that I kept to be specific were as follows: the arrow keys were bound to the d-pad, WASD was bound to the left analog stick, enter was bound to start, and escape was bound to back. These are almost universal keys within games, so it was logical to code them as such. Furthermore many games do not allow you to rebind the keys that control the menu, so having the standard arrow keys, enter, and escape is useful for menu navigation.

#Testing Methodology

For testing, I 

#Results and Discussion
Left stick - PWM?

#Conclusions


