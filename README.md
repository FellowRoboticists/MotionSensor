MotionSensor
============

This is an Arduino sketch to leverage a DIY motion sensor.

The motion sensor can easily be constructed as follows:

  * Get a clean sheet of paper
  * Strip a solid-core wire completely and use electrical tape
    to attach the copper wire to the sheet of paper. Leave 
    bare copper exposed intermittently across the paper.
  * Connect one end of the copper wire to ground.
  * Attach a spring contact (or any piece of conductive material)
    to a wooden dowel.
  * Connect the spring contact to 5V through a 10Kohm resistor.
  * Connect the node between the spring contact and the resistor to
    digital pin 7

Compile and upload the sketch to your Arduino, then turn on your serial
monitor.

Slowly move the spring contact over the taped copper wire on the piece
of paper. Notice that as long as your moving, the LED at pin 13 (built in)
will be on. When you stop moving, the LED will be off. The serial monitor
will also inform you of the state of motion.

That's it.
