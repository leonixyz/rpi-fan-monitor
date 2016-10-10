#fand - Raspberry Pi Temperature Daemon

Super simple fan daemon. Used on my Raspberry Pi model B where some GPIO pins have been wired to
a micro fan and a transistor controlling its motion.

Ships together with a systemd unit file.

##dependencies

 * GNU make
 * git (to clone other deps)
 * [Wiring Pi](http://wiringpi.com) (pulled in by make)
 * gcc

##config

Edit `fand.c` sources. The following values can be customized:

 * the GPIO pin that activates the fan (using Wiring Pi's numeration)
 * blow duration: how many seconds the fan will activate each time the temperature is measured as too high
 * sleep duration: how many seconds the program will wait before reading the temperature again
 * max temperature (°Celsius)

##building + installation

Clone this repo and run `make`. If don't want systemd unit file, then copy the executable `fand` were appropriate.

If you want systemd unit file then run `make install` and `systemctl enable fand.service`.
