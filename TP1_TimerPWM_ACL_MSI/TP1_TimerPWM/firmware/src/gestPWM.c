// GestPWM.c
/*--------------------------------------------------------*/
//	Description :	Gestion des PWM 
//			        pour TP1 2016-2017
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.1
//	Compilateur	:	XC32 V1.42 + Harmony 1.08
//
/*--------------------------------------------------------*/

#include "GestPWM.h"
#include "app.h"
#include "stdint.h"
#include "Mc32DriverLcd.h"


//S_pwmSettings PWMData;      // pour les settings

void GPWM_Initialize(S_pwmSettings *pData)
{
   // Init les data 
 
    
     // Init état du pont en H
    BSP_EnableHbrige(); 
    
    /*Initialize TMR0 */
    DRV_TMR0_Initialize();
     /*Initialize TMR1 */
    DRV_TMR1_Initialize();
     /*Initialize TMR2 */
    DRV_TMR2_Initialize();
     /*Initialize TMR3 */
    DRV_TMR3_Initialize();
    
    /* Initialize the OC Driver */
    DRV_OC0_Initialize();
    DRV_OC1_Initialize();
}

// Obtention vitesse et angle (mise a jour des 4 champs de la structure)
void GPWM_GetSettings(S_pwmSettings *pData)	
{
    S_ADCResults AdcRes;
    
    //déclaration variables
    uint16_t recupValBruteADC0;
//    uint16_t recupValBruteADC1;
    uint8_t valNormaliseeADC0;
   // uint8_t valNetADC1;
    int8_t speedADC0;
    uint8_t absSpeed;
    
//    uint8_t angleADC1;
   // int8_t angleSignee;
    
    
   

    // Lecture du convertisseur AD  
    AdcRes = BSP_ReadAllADC();
    recupValBruteADC0 = AdcRes.Chan0;       //lecture ADC0
    //recupValBruteADC1 = AdcRes.Chan1;       //lecture ADC1
    
    // conversion   
    //-------------traitement ADC0-----------------------//
    
    valNormaliseeADC0 = (recupValBruteADC0*198) / VAL_BRUTE_MAX_ADC; //transformation de la valeur brute
    speedADC0 = (valNormaliseeADC0 - 99);               //vitesse signée
    absSpeed = abs(speedADC0);                          //vitesse absolue
    
    
    //------------traitement ADC1------------------------//
    
  //  angleADC1 = (recupValBruteADC1*180) / VAL_BRUTE_MAX_ADC;     //transformation de la valeur brute
    //angleSignee = (int8_t)angleADC1 - 99;                       //angle signé

    
    
    //---------- mise à jour des champs dans la structure----------//
    pData->SpeedSetting = speedADC0;
    pData->absSpeed = absSpeed;
   // pData->AngleSetting = 
   // pData->absAngle = 
            
}


// Affichage des information en exploitant la structure
void GPWM_DispSettings(S_pwmSettings *pData)
{
    LCD_CLEARSCREEN();
    lcd_gotoxy(1,1);
    printf_lcd("TP1 PWM 2024-25");
    
    lcd_gotoxy(1,2);
    printf_lcd("speedSetting", pData->SpeedSetting);
    
    lcd_gotoxy(1,3);
    printf_lcd("absSpeed", pData->absSpeed);
    
    lcd_gotoxy(1,4);
    printf_lcd("Angle", pData->absAngle);
        
}

// Execution PWM et gestion moteur à partir des info dans structure
void GPWM_ExecPWM(S_pwmSettings *pData)
{
    //test -> si la valeur de la vitesse est positive
    //si oui, tourner dans un sens
    //si non, tourner dans un autre sens 
    if (pData->SpeedSetting >= 0)
     {
         
     }
     else
     {
         
     }
}

// Execution PWM software
void GPWM_ExecPWMSoft(S_pwmSettings *pData)
{
    
}


