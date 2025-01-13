/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "Mc32DriverLcd.h"
#include "Mc32DriverAdc.h"
#include "bsp.h"

#include <stdint.h>

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}



/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Tasks ( void )
{
    
    uint8_t firstTimeIn = 0;
    
    /* Check the application's current state. */
    switch (appData.state)
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            //lancement du timer
            DRV_TMR0_Start();
            
            //init du LCD
            lcd_init();
            lcd_bl_on();
            lcd_gotoxy(1,1);
            printf_lcd("TP0 LED+AD 2024-25");
            lcd_gotoxy(1,2);
            printf_lcd("Stefanelli");

            //init de l'AD
            BSP_InitADC10();
            
            //allumage des leds
            FullLedOn();

            //next case 
            appData.state = APP_STATE_WAIT;
                
            break;
        }
        
        case APP_STATE_WAIT : 
        {
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {                     
            if (firstTimeIn == 0)
            {
                FullLedOff();
                firstTimeIn = 1;
            }
            
            //Lecture des potentiomètres et affichage sur LCD de la 3ème ligne
            appData.AdcRes = BSP_ReadAllADC();
            lcd_gotoxy(1,3);
            printf_lcd("CH0 %4d CH1 %4d",appData.AdcRes.Chan0,appData.AdcRes.Chan1);
                        
            //chenillard
            chenillard();
            
            //Retour dans l'état d'attente
            APP_UpdateState ( APP_STATE_WAIT );
            
            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


 //****************************************************************************/
//Fonction pour l'activation apreès 3 secondes, puis toutes les 100ms
// Prototypes :
                  /*   void APP_Timer1CallBack(void);   */
                            /*voir dans app.h*/
void APP_Timer1CallBack(void)
{
   static uint16_t count = 0;
   // Attente 3 secondes, puis cycle de 100 ms
   count++;
   if (count >= TIMER1_MAX_COUNT ) 
    {
        // Etablit etat d'execution
        APP_UpdateState ( APP_STATE_SERVICE_TASKS );
        count = TIMER1_RESET_COUNT;
    }    
}


//*****************************************************************************/
//Fonction pour charger le nouvelle de la machine d'etat
// Prototypes :
                  /*   void APP_UpdateState(APP_STATES newState);   */
                            /*voir dans app.h*/
void APP_UpdateState(APP_STATES newState)
{
    appData.state = newState;
}


/*****************************************************************************/
//Fonction pour eteindre et allumer les leds (toutes les leds)
// Prototypes :
                  /*   void FullLedOn(void);   */
                  /*   void FullLedOff(void);   */  
                   /*voir dans app.h*/
void FullLedOn(void)
{
    // Allumer les LEDs dans la plage séquentielle
    uint8_t i;
    for (i = BSP_LED_0; i <= BSP_LED_7; i++) 
    {
        BSP_LEDOn(i); // Allumer LEDs 0 à 6
    }
    // gestion de la led 7 hors de la boucle parce que selon l'enum dans bsp.c
    // la led 7 se trouve sur un autre port 
    BSP_LEDOn(BSP_LED_7); // Gérer LED7
}

void FullLedOff(void)
{
    uint8_t i;
    for (i = BSP_LED_0; i <= BSP_LED_6; i++) 
    {
        BSP_LEDOff(i); // Éteindre LEDs 0 à 6
    }
    // gestion de la led 7 hors de la boucle parce que selon l'enum dans bsp.c
    // la led 7 se trouve sur un autre port 
    BSP_LEDOff(BSP_LED_7); // Gérer les LEDs hors de la plage séquentielle
}


//****************************************************************************/
//Fonction de chenillard sur les leds de la carte PIC32
// Prototypes :
                  /*   void chenillard(void);   */
                            /*voir dans app.h*/
void chenillard(void)
{
    static uint8_t i = 0; 

    FullLedOff(); // Éteindre toutes les LEDs

    // Allumer uniquement la LED correspondant à i
    switch (i)
    {
        case 0: BSP_LEDOn(BSP_LED_0); 
            break;
        case 1: BSP_LEDOn(BSP_LED_1); 
            break;
        case 2: BSP_LEDOn(BSP_LED_2); 
            break;
        case 3: BSP_LEDOn(BSP_LED_3); 
            break;
        case 4: BSP_LEDOn(BSP_LED_4); 
            break;
        case 5: BSP_LEDOn(BSP_LED_5); 
            break;
        case 6: BSP_LEDOn(BSP_LED_6); 
            break;
        case 7: BSP_LEDOn(BSP_LED_7); 
            break;
        default: break;
    }

    // Passer à la LED suivante en rebouclant après LED7
    i = (i + 1) % 8;
}


/*******************************************************************************
 End of File
 */
