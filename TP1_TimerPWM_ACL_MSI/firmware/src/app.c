
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
#include "bsp.h"
#include "gestPWM.h"
#include "stdint.h"
<<<<<<< HEAD:TP1_TimerPWM/firmware/src/app.c
=======
#include "gestPWM.h"
>>>>>>> e142cac45b36d9cad9b6feb64956761a2e0f6f79:firmware/src/app.c
#include "Mc32DriverLcd.h"
#include "Mc32DriverAdc.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
S_pwmSettings PWMData;      // pour les settings
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
static S_pwmSettings PWMData;
void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:                //Etat d'initialisation
        {
<<<<<<< HEAD:TP1_TimerPWM/firmware/src/app.c
             
            //start des timers et OC + pont en H 
            GPWM_Initialize(&PWMData);
   
            DRV_TMR0_Start();
                     
=======
            GPWM_Initialize(&PWMData);
            DRV_TMR0_Start();  // start du timer 1
                        
>>>>>>> e142cac45b36d9cad9b6feb64956761a2e0f6f79:firmware/src/app.c
            //init du LCD
            lcd_init();
            lcd_bl_on();
            lcd_gotoxy(1,1);
            printf_lcd("TP1 PWM 2024-25");
            lcd_gotoxy(1,2);
            printf_lcd("Stefanelli Matteo");
            lcd_gotoxy(1,3);
            printf_lcd("Clauzel Aymeric");
            
            //init de l'AD
            BSP_InitADC10();
            
            //Eteindre les leds
            FullLedOff();
            
            //next case 
            appData.state = APP_STATE_WAIT;
            
            break;
        }
        
        case APP_STATE_WAIT:                //Etat d'attente 
        {
            break;
        }
        
        case APP_STATE_SERVICE_TASKS:       //Etat d'execution
        {
            break;
        }        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

void APP_UpdateState(APP_STATES newState)
{
    appData.state = newState;
}




/*****************************************************************************/
//Fonction de callback
/*prototype : void APP_TMR1_CallBack(void); dans app.h*/

void APP_TMR1_CallBack(void)
{
    static uint8_t counter3sec;
 
    if (counter3sec > 150)
    {
        GPWM_GetSettings(&PWMData);
        GPWM_DispSettings(&PWMData);
        counter3sec = 149; 
            //Séquence d'appel de fonctions
        GPWM_GetSettings(&PWMData);     //Obtention vitesse et angle
        GPWM_DispSettings(&PWMData);    //Affichage
        GPWM_ExecPWM(&PWMData);         //Execution PWM et gestion moteur
    }
    else
    {
        counter3sec ++;
    }
    
}


/******************************************************************************/

/*Fonction pour eteindre et allumer les leds (toutes les leds)*/

// Prototypes :
                  /*   void FullLedOn(void);   */
                  /*   void FullLedOff(void);   */  
                   /*voir dans app.h*/

void FullLedOn(void)
{
    BSP_LEDOn(BSP_LED_0);
    BSP_LEDOn(BSP_LED_1);
    BSP_LEDOn(BSP_LED_2);
    BSP_LEDOn(BSP_LED_3);
    BSP_LEDOn(BSP_LED_4);
    BSP_LEDOn(BSP_LED_5);
    BSP_LEDOn(BSP_LED_6);
    BSP_LEDOn(BSP_LED_7);  
}

 void FullLedOff(void)
{
    BSP_LEDOff(BSP_LED_0);
    BSP_LEDOff(BSP_LED_1);
    BSP_LEDOff(BSP_LED_2);
    BSP_LEDOff(BSP_LED_3);
    BSP_LEDOff(BSP_LED_4);
    BSP_LEDOff(BSP_LED_5);
    BSP_LEDOff(BSP_LED_6);
    BSP_LEDOff(BSP_LED_7);  
}
 
 
 /*****************************************************************************/
 /*Fonction pour clear l'ecran en entier*/

// Prototypes :
                  /*   void LCD_CLEARSCREEN (void);   */
                            /*voir dans app.h*/
 
 void LCD_CLEARSCREEN (void)
 {
     lcd_ClearLine(1);
     lcd_ClearLine(2);
     lcd_ClearLine(3);
     lcd_ClearLine(4);     
             
 }