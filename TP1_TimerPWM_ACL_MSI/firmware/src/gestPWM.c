/*--------------------------------------------------------*/
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
#include "Mc32DriverLcd.h"
#include "bsp.h"
#include "app.h"
#include "Mc32DriverAdc.h"
 

 
void GPWM_Initialize(S_pwmSettings *pData)
{
   // Init les data 
    pData->absSpeed=0;   // vitesse 0 à 99
    pData->absAngle=0;    // Angle  0 à 180
    pData->SpeedSetting=0; // consigne vitesse -99 à +99
    pData->AngleSetting=0;
   // Init état du pont en H
   BSP_EnableHbrige();
    // lance les tmers et OC
   DRV_TMR0_Start();  // start du timer 1          

 
}
 
// Obtention vitesse et angle (mise a jour des 4 champs de la structure)
void GPWM_GetSettings(S_pwmSettings *pData)	
{
    S_ADCResults AdcRes;
    // Lecture du convertisseur AD
    AdcRes = BSP_ReadAllADC();
    pData->SpeedSetting = ((abs(((float)Sweepingmoy(&AdcRes,0)/1023)*198))-99);
     // conversion
    //pData->SpeedSetting = ((abs(((float)AdcRes.Chan0/1023)*198))-99);    // vitesse 0 à 99
    pData->absSpeed =abs( pData->SpeedSetting);
   // pData.absAngle;    // Angle  0 à 180
    //pData.SpeedSetting; // consigne vitesse -99 à +99
    //pData.AngleSetting; // consigne angle  -90 à +90
}
int Sweepingmoy(S_ADCResults *AdcRes,char chan)
{
    static int buff[2][11];
    static char iterator=0;
    static char firstTimeSincePowerUp =0;
    int i;
    buff[(int)chan][(int)iterator]=(chan)?AdcRes->Chan0:AdcRes->Chan1;
    iterator++;
    if(iterator == 10)
    {
        iterator=0;
        firstTimeSincePowerUp=1;
    }
    if(firstTimeSincePowerUp)
    {
        for(i=0;i<9;i++)
        {
            buff[(int)chan][10]+=buff[chan][i];
        }
    }
    return (buff[chan][10]/10);
}
 
// Affichage des information en exploitant la structure
void GPWM_DispSettings(S_pwmSettings *pData)
{
    
    lcd_gotoxy(1,2);
    printf_lcd("SpeedSetting: %4d", pData->SpeedSetting);
    lcd_gotoxy(1,3);
    //lcd_ClearLine(3);
    printf_lcd("AbsSpeed: %3d",  pData->absSpeed);
    lcd_gotoxy(1,4);
    //printf_lcd("AbsSpeed: %3d",  pData.absSpeed);
}
 
// Execution PWM et gestion moteur à partir des info dans structure
void GPWM_ExecPWM(S_pwmSettings *pData)
{
    //pdata.SpeedSetting=
}
 
// Execution PWM software
void GPWM_ExecPWMSoft(S_pwmSettings *pData)
{
}
