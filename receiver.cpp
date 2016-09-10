#include "switch.h"
#include <stdlib.h>
#include <stdio.h>


RCSwitch mySwitch;



int main(int argc, char *argv[]) {

     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     int PIN = 2;

     if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }

     int pulseLength = 0;
     if (argv[1] != NULL) pulseLength = atoi(argv[1]);

     mySwitch = RCSwitch();
     printf("Ready to listen on pin %i with pulsenlength %i\n", PIN, pulseLength);
     if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
     mySwitch.enableReceive(PIN);  // Receiver on interrupt 0 => that is pin #2
     printf("Listengin...\n");

     while(1) {

      if (mySwitch.available()) {

        int value = mySwitch.getReceivedValue();

        if (value == 0) {
          printf("Unknown encoding\n");
        } else {

          printf("Received %i\n", mySwitch.getReceivedValue() );
        }

        mySwitch.resetAvailable();

      }


  }

  exit(0);


}
