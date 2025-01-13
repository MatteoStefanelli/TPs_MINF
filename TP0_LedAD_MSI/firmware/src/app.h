/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "Mc32DriverAdc.h"
#include "system_definitions.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

#define TIMER1_MAX_COUNT      29   // Nombre de cycles pour 3 secondes
#define TIMER1_RESET_COUNT    28   // Valeur de réinitialisation après déclenchement
    
    
    
// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
	/* Application's state machine's initial state. */
	APP_STATE_INIT=0,
    APP_STATE_WAIT,        
	APP_STATE_SERVICE_TASKS,

	/* TODO: Define states used by the application state machine. */

} APP_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_STATES state;
    S_ADCResults AdcRes;
    /* TODO: Define any additional data used by the application. */

} APP_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/
	
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/***************************************************************
 * Nom de la fonction : void APP_Initialize ( void )
 * Description         : Initialise l'application MPLAB Harmony.
 *                       Met l'application dans son état initial 
 *                       et la prépare à exécuter la fonction APP_Tasks.
 * Paramètres          : Aucun.
 * Retour              : void.
 * Préconditions       : Toutes les routines d'initialisation système 
 *                       doivent être appelées avant d'invoquer cette fonction.
 * Remarques           : Doit être appelée depuis la fonction SYS_Initialize.
 ***************************************************************/
void APP_Initialize ( void );



/***************************************************************
 * Nom de la fonction : void APP_UpdateState ( APP_STATES NewState )
 * Description         : Met à jour l'état actuel de la machine d'état 
 *                       avec un nouvel état spécifié.
 * Paramètres          : 
 *   - NewState : type APP_STATES            
 * Retour              : void.
 * Remarques           : 
 *   - Cette fonction est utilisée pour contrôler la logique de la machine 
 *     d'état en définissant son nouvel état.
 *   - Les états possibles sont définis dans l'énum `APP_STATES`.
 ***************************************************************/
void APP_UpdateState ( APP_STATES NewState );



/***************************************************************
 * Nom de la fonction : void APP_Timer1CallBack ( void )
 * Description         : Fonction de rappel (callback) associée au Timer 1. 
 *                       Cette fonction est appelée périodiquement, elle 
 *                       attend 3 secondes avant de maintenir un cycle 
 *                       de 100 ms et met à jour l'état d'exécution.
 * Paramètres          : Aucun.
 * Retour              : void.
 
 ***************************************************************/
void APP_Timer1CallBack(void);



/***************************************************************
 * Function Name : void chenillard ( void )
 * Description   : Effectue un chenillard sur les LEDs, où chaque LED
 *                 s'allume et s'éteint successivement en boucle.
 * Parameters    : None
 * Return        : void
 ***************************************************************/
void chenillard(void);



/***************************************************************
 * Function Name : void FullLedOn ( void )
 * Description   : Allume toutes les LEDs simultanément.
 * Parameters    : None
 * Return        : void
 ***************************************************************/
void FullLedOn(void);



/***************************************************************
 * Function Name : void FullLedOff ( void )
 * Description   : Éteint toutes les LEDs simultanément.
 * Parameters    : None
 * Return        : void
 ***************************************************************/
void FullLedOff(void);



/***************************************************************
 * Function Name : void APP_Tasks ( void )
 * Description   :     This routine is the Harmony Demo application's tasks function.
 *                     It defines the application's state machine and core logic.
 * Parameters    :
 *   - <param1> : None
 *   - <param2> : None
 *   - ...      : ...
 * Return        : void
 ***************************************************************/
void APP_Tasks( void );


#endif /* _APP_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

