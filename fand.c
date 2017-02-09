/*
 *
 * Name:	fand
 * 
 * Date:	16 october 2014
 * Author:	leonixyz@gmail.com
 * 
 * Desc:	Constantly checks file /sys/class/thermal/thermal_zone0/temp
 * 		that contains the temperature of the cpu; in case temperature 
 * 		is too high it activates for a given timeout a gpio pin to 
 * 		start the fan.
 */

/* Configure here */
#define GPIO_SWITCH 	15	// GPIO pin activating the fan (using wiringPi's numeration)
#define BLOW_DURATION 	33	// duration of the fan blow (seconds)
#define SLEEP_DURATION 	66	// duration of the iteration (seconds)
#define MAX_TEMPERATURE 55	// max temperature allowed (° Celsius)


/* Dont't touch below here */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>



int main(int argc, char* argv[])
{
  int temperature,
      gpio_switch = GPIO_SWITCH, 
      blow = BLOW_DURATION * 1000 * 1000, 
      sleep = SLEEP_DURATION * 1000 * 1000,
      maxTemp = MAX_TEMPERATURE;

  FILE* file; // to read temperature from /sys/class/thermal/thermal_zone0/temp
 
  // set up wiringPi
  if (wiringPiSetup() == -1)
    exit(1);

  // check parameter passed
  switch(argc)
  {
    case 1:
      break;
    case 2:
      blow = atoi(argv[1]) * 1000 * 1000;
      sleep = blow * 2;
      break;
    case 3:
      blow = atoi(argv[1]) * 1000 * 1000;
      sleep = atoi(argv[2]) * 1000 * 1000;
      break;
    case 4:
      blow = atoi(argv[1]) * 1000 * 1000;
      sleep = atoi(argv[2]) * 1000 * 1000;
      maxTemp = atoi(argv[3]);
      break;
    case 5:
      blow = atoi(argv[1]) * 1000 * 1000;
      sleep = atoi(argv[2]) * 1000 * 1000;
      maxTemp = atoi(argv[3]);
      gpio_switch = atoi(argv[4]);
      break;
    default:
      exit(3);
      break;
  }

  // reset default values in case of error
  if(blow == 0 || sleep == 0 || maxTemp == 0)
  {
    blow = BLOW_DURATION * 1000 * 1000;
    sleep = SLEEP_DURATION * 1000 * 1000;
    maxTemp = MAX_TEMPERATURE;
  }

  // set the gpio pin to no-signal
  pinMode(gpio_switch, OUTPUT);
  digitalWrite(gpio_switch, 0);

  // iterate...
  for(;;)
  {
    file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    
    // read the temperature
    if(fscanf(file, "%d", &temperature ) != 1)
      exit(2); 
    
    fclose(file);

    if(temperature > 50000)
    {
      // activate the fan in case of high temperature
      digitalWrite(gpio_switch, 1);
      usleep(blow);
      digitalWrite(gpio_switch, 0);
    }
  
  // sleep a while
  usleep(sleep);

  }
}
