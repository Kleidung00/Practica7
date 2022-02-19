/*
* LCDDriver.c
*
*  Created on: 14-Feb-2022
*      Author: Mario Castañeda
*/
/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "LCDDriver.h"
#include "MKL25Z4.h"
/*******************************************************************************
 * Local Variables
 ******************************************************************************/
unsigned char gbLCDWelcomeMSG[2][16];

GPIO_Type *rGpioC = GPIOC;

typedef enum
{
    STATEMSN,
    STATEDOWN,
    STATELSN,
    DELAY_STATE,
    EXECUTION_STATE,
    STATEIDLE  
}InitialStates; 

static unsigned char baLCDConfig[]=
{
    LCD_INIT_CMD0,  //initial 3 steps
    LCD_INIT_CMD1,  //4bits
    LCD_INIT_CMD2,  //specify lines and fonts
    LCD_INIT_CMD3,  //display off
    LCD_INIT_CMD4,  //display clear
    LCD_INIT_CMD5   // mode set
    //LCD_INIT_CMD6
}; 
static unsigned char balJump[]=
{
        0xC0        //Jump
};
static unsigned char bCursor_Home[]=
{
        0x03        //Cursor home
};

unsigned char Data_Out=0x00;
unsigned char bCursor=0x00;
volatile unsigned char bCnt=DELAY;
static unsigned char bDataCnt=0x00;
static unsigned char *bpLCDData=0x00;
static unsigned char xbword=0x00;
static unsigned char brow=0x00;
static unsigned char bRegister_Select=0x00;
static unsigned char bCurrentState=STATEIDLE;    
static unsigned char bNextState = STATEMSN;
static unsigned char bPreviousState;
/*******************************************************************************
* Local Function Prototypes
******************************************************************************/
void vfnLCDDriver();
void vfnDly500nsState();
void vfnState0MSN();
void vfnState1EDown();
void vfnState2LSN();
void vfnStateExecution();
void vfnState_Idle();

void (* vfnDriverLCD[])(void) =
{
    (void (*)(void))vfnState0MSN,
    (void (*)(void))vfnState1EDown,
    (void (*)(void))vfnState2LSN,
    (void (*)(void))vfnDly500nsState,
    (void (*)(void))vfnStateExecution,
    (void (*)(void))vfnState_Idle
};
/*******************************************************************************
* vfnLCDInit
* DESCRIPTION: Set the first config parameters for LCD init 4 bits
*
* RETURNS:
* void
******************************************************************************/
void vfnLCDInit()
{
    if(bCurrentState==STATEIDLE)
    { 
    bDataCnt = sizeof(baLCDConfig);
    bpLCDData = &baLCDConfig[xbword];
    bCurrentState = STATEMSN;
    } 
}
/*******************************************************************************
* vfnLCDDriver
* DESCRIPTION: Array with the funtion pointers
*
* RETURNS:
* void
******************************************************************************/
void vfnLCDDriver()
{
    vfnDriverLCD[bCurrentState]();

}
/*******************************************************************************
* bfnLCDBusy
* DESCRIPTION: Verify if the State machine is busy
*
* RETURNS:
* void
******************************************************************************/
unsigned char bfnLCDBusy()
{
    if (bCurrentState == STATEIDLE)
    {
        return 0;
    }
    else 
    {
        return 1;
    }
}
/*******************************************************************************
* vfn
* DESCRIPTION:
*
* RETURNS:
* void
******************************************************************************/
void vfnLCDUpDate ()
{
    if(bCurrentState==STATEIDLE)
    {

    }
}
/*******************************************************************************
* vfnLCDGotoxy
* DESCRIPTION: Select the Line X or Y
*
* RETURNS:
* void
******************************************************************************/
void vfnLCDGotoxy (void) //0000-0100
{
  
}
/*******************************************************************************
* vfnLCDGotoxy_Home
* DESCRIPTION: Go to the first position
*
* RETURNS:
* void
******************************************************************************/
void vfnLCDGotoxy_Home()
{

}
/*******************************************************************************
* vfn
* DESCRIPTION:
*
* RETURNS:
* void
******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
/***********************STATE Machine******************************************/
////////////////////////////////////////////////////////////////////////////////
void vfnDly500nsState(void) 
{
	if((bCnt--)==0)
	{
		bCnt= DELAY;
		bCurrentState = bNextState;
	}
}
/*******************************************************************************
* vfnState0MSN
* DESCRIPTION:
*
* RETURNS:
* void
******************************************************************************/
void vfnState0MSN()
{         

}
/*******************************************************************************
* vfnState1EDown
* DESCRIPTION: Write 0 to the Enable pin
*
* RETURNS:
* void
******************************************************************************/
void vfnState1EDown(void)
{ 
    rGpioC->PDOR &=  (~ENABLE);
    
    bCurrentState = DELAY_STATE; 
    bNextState = bPreviousState;
}
/*******************************************************************************
* vfnState2LSN Least Significant  
* DESCRIPTION:
*
* RETURNS:
* void
******************************************************************************/
void vfnState2LSN()
{ 
  
}
/*******************************************************************************
* vfnStateExecution
* DESCRIPTION: Routine for the Execution Rouitne RS 
*
* RETURNS:
* void
******************************************************************************/
void vfnStateExecution()
{
    bCurrentState = DELAY_STATE;
    //
    //
       
}
/*******************************************************************************
* vfnState_Idle
* DESCRIPTION: Funtion for IDLE State Machine
*
* RETURNS:
* void
******************************************************************************/
void vfnState_Idle()
{
    //Nothing to do
}
