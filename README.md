# MeArm
This repository contains a library to control the MeArm v1.02 with an Arduino. 

To include the library in your Arduino program, add `include "mearm.h"` to the top of your Arduino code. This will allow you to access the `MeArm` and the `SerialMeArm` classes.

## Setting up the MeArm
To set up the MeArm you'll need to figure out which pins will be used for each of the servos. Once you've got pins chosen, create a MeArm instance and pass it the pins for each corresponding servo:

`MeArm * meArm = new MeArm(basePin, radialPin, zPin, gripPin)`

Normally you won't have to use `MeArm::setOffsets(base, radial, z, grip)`. If you initially set up your MeArm incorrectly (not set the initial positions correctly), you can use the setOffsets to set the correct angles. To use this, use the `MeArm::setAngles(base, radial, z, grip)` to replicate the position in image: 

![MeArm Setup](/img/setup.png)

Example: `meArm->setAngles(0, 145, 90, 0);`

Once you've got that set up, replace `setAngles` with `setOffsets` like below:

Example: `meArm->setOffsets(0, 145-90, 90, 0);`
## Controlling the MeArm
Once you have the MeArm set up you can choose which method of control you would like. You can control the MeArm's servos directly by calling `setAngles(..)` or you can control the desired arm position by using `goTo(...)`.

# Serial MeArm
To use the SerialMeArm interface, feel free to reference the `SerialMeArm` example.

The serial interface example uses the default serial connection for Arduino and allows you to control your MeArm over serial by sending a command in the following format:

`MAAABB.BCC.CD`
- `M`: The character 'M'
- `AAA`: The angle that the base should rotate as
- `BB.B`: The radial position of the end effector
- `CC.C`: The z position of the end effector
- `D`: Control for whether the grip should be open (`0`) or closed (`1`)
