#Introduction
In this lab, we created firmware for the controller we designed in lab 2. The requirements were that the left stick controls movement (through standard WASD input) and the right stick controls the mouse.

#Design Methodology
I used the example code for as much of the lab as was fitting. This means that the majority of the face keys the right analog stick were simply slightly modified sample code for writing to keyboard and moving mouse respectively. The left stick simply maps to the WASD keys after the analog stick has passed a certain threshold. This threshold was tuned to what felt natural relative to existing controllers.

The unique additions conist of an enable switch, a mode switch button, and 6 total buttons which were read as a single analog input. The switch was a simple on-off switch that was used as the condition for the rest of the code running. This allows the controller to be silenced when need be. A silence was chosen over a hardware shutoff since it prevents bugs such as improper pull-ups for occuring. Furthermore there is significant startup lag when first plugging in a controller, so a silence allows for the controller to switch between active and inactive states with zero delay.

The mode control button when pressed toggles the d-pad between serving as arrow keys and serving as mouse controls. When in control mode, the up and down buttons increase and decrease sensitivity respectively. Currently they adjust sensitivity linearly, which allows for much more precise sensitivity adjustments at the cost of lots of button presses. the alternative was to have the scale be exponential which would allow rapid sensitivity swings without a lot of user input. 

Ultimately, I will implement the exponential solution; however, since the next lab requires extensive testing of the controller between various people who might enjoy a wide range of sensitivities, I felt it was more important to have a finer resolution for this purpose. Thus, as the firmware works right now, the senstivity buttons are more for initially programming the controller to a single sensitivity and staying with it for a decent length of time rather than rapidly switching sensitivities in action.

The right and left d-pad buttons when in control mode affect the rate of acceleration. Initially, acceleration is 0 but can be increased. The acceleration when non-zero behaves similarly between all values with the only change being that the magnitude of the acceleration and not the duration. 



#Testing Methodology


#Results and Discussion
Left stick - PWM?

#Conclusions


