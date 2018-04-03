// This class provides functionality of timer TIM3

class clsTimer3
{
//******************************************************************************   
private://                   PRIVATE ZONE
//******************************************************************************   

   //************************* constants ***************************************
   //*********************** end constants *************************************   


   //************************* variables ***************************************
   int period;

   //*********************** end variables ************************************


   //********************* private functions **********************************
   void init_timer(void)
   {
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
      TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
      TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
      //60MHz/60 = 1MHz; *1000000=1s=1Hz
      TIM_TimeBaseStructure.TIM_Prescaler = 60;
      TIM_TimeBaseStructure.TIM_Period = period;   // 1000000 -> 1 second
      TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
      TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
      TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

      //TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
      TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

      //TIM_Cmd(TIM3, ENABLE);
      //NVIC_EnableIRQ(TIM3_IRQn);
   }// end init_tim3

   
   //******************** end private functions ********************************
   
      
//******************************************************************************   
public://                    PUBLIC ZONE
//******************************************************************************      

   //---------------------------------------------------------------------------
   // public constructor
   clsTimer3()
   {
      
      // timer initialization:
      setPeriod(1000); // start period -> 1 mSec
      init_timer();
   }//end clsTimer3
   //--------------------------end----------------------------------------------
   
   
   //************************ properties ***************************************
        
   //********************** end properties *************************************
   
   //********************* public functions ************************************
   // function starts timer3 and enables timer 3 IRQs
   void startTimer(void)
   {
      TIM_Cmd(TIM3, ENABLE);
      NVIC_EnableIRQ(TIM3_IRQn);
   }
   
   // function stops timer3 and disables timer 3 IRQs
   void stopTimer(void)
   {
      TIM_Cmd(TIM3, DISABLE);
      NVIC_DisableIRQ(TIM3_IRQn);
   }
   
   void setPeriod(int PERIOD)
   {
      period = PERIOD;
      init_timer();
   }
   //******************* end public functions **********************************
   
   
   //---------------------------------------------------------------------------
   // Method ...
   void someMethod(void)
   {
      
   }//end someMethod
   //--------------------------end----------------------------------------------
   
      
};



// timer 3 interrupt service procedure
extern "C" void TIM3_IRQHandler(void)
{
   timer3_interrupt_service();
   
}
