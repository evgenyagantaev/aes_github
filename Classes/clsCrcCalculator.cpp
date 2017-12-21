// This class provides CRC16 calculation

class clsCrcCalculator
{
//******************************************************************************   
private://                   PRIVATE ZONE
//******************************************************************************   

   //************************* constants ***************************************

   //*********************** end constants *************************************   


   //************************* variables ***************************************


   //*********************** end variables *************************************


   //********************* private functions ***********************************


   //******************** end private functions ********************************
   
      
//******************************************************************************   
public://                    PUBLIC ZONE
//******************************************************************************      

   //---------------------------------------------------------------------------
   // public constructor
   clsCrcCalculator()
   {
      
   }//end clsCrcCalculator
   //--------------------------end----------------------------------------------
   
   
   //************************ properties ***************************************
        
   //********************** end properties *************************************
   
   //********************* public functions ************************************
    uint16_t calcCrc(uint8_t *data, uint16_t size) 
    {
        uint16_t crc = 0;
        while (size--) 
        {
            crc = (crc << 8) ^ crctable[((crc >> 8) ^ *data++)];
        }
        return crc;
    }

   //******************* end public functions **********************************
         
};