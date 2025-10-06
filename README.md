# Tamagotchi for LandTiger LPC1768

A Tamagotchi-inspired virtual pet game for the **LandTiger LPC1768 ARM Cortex-M3** development board.  
The project was developed using **Keil µVision**, implementing features such as interactive animations and audio feedback.

---
## Features

- **Pet Lifecycle**: The pet’s age, happiness, and satiety are shown in real time. Values gradually decrease if the pet is neglected.  
- **Feeding Interaction**: A food selection menu is displayed at the bottom of the LCD, offering meals and snacks. Navigation and selection are handled with the joystick. Feeding triggers an animation where the pet moves toward the food.  
- **Death Condition**: When either happiness or satiety reaches zero, the pet dies. The game ends with a death animation and a "reset?" message. Pressing the reset button spawns a new pet.  
- **Touch Input**: Touching the pet on the screen starts a cuddling sequence, boosting its happiness level.  
- **Audio System**: Distinct sound effects accompany actions such as menu navigation, eating, cuddling, and the death event. Output volume is adjustable through the onboard potentiometer.  


---

## Technical Implementation

- **Hardware timers** are used for primary functions:  
  - Timers **1** and **3** → manage sound reproduction  
  - Timer **2** → handles animation frames
- **Touch detection** is implemented in [`board/project/timer/IRQ_RIT.c`](IRQ_RIT.c):  
  - Confirms the touch is within the pet’s area  
  - Ensures no other animations are currently running
- **Animation sequence** is managed in [`board/project/timer/IRQ_timer.c`](IRQ_timer.c):  
  - Updates the display  
  - Increases the `hap` (happiness) variable  
  - Runs over a two-second duration

---

## Hardware & Tools

- **Board:** LandTiger with NXP LPC1768  
- **Display:** Touchscreen LCD  
- **Audio:** On-board speaker  
- **Input:** Touchscreen & Potentiometer  
- **IDE/Compiler:** Keil µVision  

---
