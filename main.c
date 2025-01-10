// *********************************************************************
// A6_pwm.c										Version 05.01.2025  hpw
// LED-Dimmer
// Dokumentation bcm2835:
// https://www.airspayce.com/mikem/bcm2835/index.html
// *********************************************************************

#include <stdio.h>					// Header fuer Ein-/Ausgaben
#include "bcm2835.h"					    // Header fuer Broadcom

#define	PIN				RPI_BPLUS_GPIO_J8_12							// PWM-Pin
#define	PWM_CHANNEL		0												// PWM-Channel
#define	PWM_RANGE		1024											// PWM-Range
#define SPEED			1												// Geschwindigkeit

int main(void){
    if(bcm2835_init()==0) return 1;										// Library initalisieren

    // PWM Funktionalität an Pin freischalten
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT5);

    // PWM Frequenz einstellen
    bcm2835_pwm_set_clock(SPEED);

    // PWM Modus einstellen und starten
    bcm2835_pwm_set_mode(PWM_CHANNEL,1,1);

    // PWM Range einstellen
    bcm2835_pwm_set_range(PWM_CHANNEL,PWM_RANGE);

    // In Schleife
    for(int i = 0; i < 10; i++){
        printf("Iteration: %d\n",i);
        // Helligkeit erhöhen (0 bis PWM_RANGE)
        for (int intensity = 0; intensity <= PWM_RANGE; intensity += (PWM_RANGE/500)) {
            bcm2835_pwm_set_data(PWM_CHANNEL, (unsigned int)intensity); // Setze Duty Cycle
            printf("Int: %d\n",intensity);
            bcm2835_delay(1);
        }

        // Helligkeit verringern (PWM_RANGE bis 0)
        for (int intensity = PWM_RANGE; intensity >= 0; intensity -= (PWM_RANGE/500)) {
            bcm2835_pwm_set_data(PWM_CHANNEL, (unsigned int)intensity); // Setze Duty Cycle
            printf("Int: %d\n",intensity);
            bcm2835_delay(1);
        }
    }

    if(bcm2835_close()==0) return 1;									// Library schließen
    return 0;							// Programmende
}

