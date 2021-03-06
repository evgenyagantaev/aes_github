void bayevskyTask(void *parameters)
{
   
   char debugString1[133];
   char debugString2[133];
   
   int binLength;
   int binMin;
   int binMax;
   double binAver;
   
   void *binPointer;
   
   while(1)
   {
      
      rrHistogramm.min_max_finding(bayevsky.getRRvectorPointer(), 
                                   bayevsky.getRRVECTORLENGTH(), 
                                   rrHistogramm.getSAMPLELENGTH());
      
      if(rrHistogramm.getMin() != 0)
      {
         rrHistogramm.calculateNumberOfhistogrammBins();
      
         //rrHistogramm.freeExistingBins();
         
         rrHistogramm.fillBins(bayevsky.getRRvectorPointer(), 
                               bayevsky.getRRVECTORLENGTH(), 
                               rrHistogramm.getSAMPLELENGTH());
         
         // form string with histogramm information
         strcpy(debugString1, "hist");
         for(int i=0; i<rrHistogramm.getNumberOfhistogrammBins(); i++)
         {
            binPointer = rrHistogramm.getBinPointerByIndex(i);
            int binLength = rrHistogramm.getBinLength(binPointer);
            sprintf(debugString2, " %d", binLength);
            strcat(debugString1, debugString2);
         }
         strcat(debugString1, "\r\n");
         
         xSemaphoreTake(uartMutex, portMAX_DELAY);
         uart.sendMessage(debugString1);
         xSemaphoreGive(uartMutex);
      
         /*
         void *binPointer;
         
         for(int i=0; i<rrHistogramm.getNumberOfhistogrammBins(); i++)
         {
            //sprintf(debugString1, "bin %d -> lower = %d; upper = %d; -----------%d\r\n", i+1, rrHistogramm.getBinLowerBound(binPointer),
            //        rrHistogramm.getBinUpperBound(binPointer), rrHistogramm.getBinLength(binPointer));
            
            
            //binPointer = rrHistogramm.getBinPointerByIndex(i);
            //int binLength = rrHistogramm.getBinLength(binPointer);
            
            //for(int j=0; j<binLength; j++)
               //debugString1[j] = '*';
            
            //debugString1[binLength] = '\r';
            //debugString1[binLength+1] = '\n';
            //debugString1[binLength+2] = 0;
            //xSemaphoreTake(uartMutex, portMAX_DELAY);
            //uart.sendMessage(debugString1);
            //xSemaphoreGive(uartMutex);
            
            //debug print bin charachteristics
            binPointer = rrHistogramm.getBinPointerByIndex(i);
            binLength = rrHistogramm.getBinLength(binPointer);
            binMin = rrHistogramm.getBinMin(binPointer);
            binMax = rrHistogramm.getBinMax(binPointer);
            binAver = rrHistogramm.getBinAver(binPointer);
            sprintf(debugString1, "%d---%f---%d---%d\r\n", binMin,
                    binAver, binMax, binLength);
            xSemaphoreTake(uartMutex, portMAX_DELAY);
            uart.sendMessage(debugString1);
            xSemaphoreGive(uartMutex);
            
            vTaskDelay(delay30);
         }
         //*/
         
         /*/
         sprintf(debugString1, "I = %f\r\n\r\n", rrHistogramm.getTensionIndex());
         xSemaphoreTake(uartMutex, portMAX_DELAY);
         uart.sendMessage(debugString1);
         xSemaphoreGive(uartMutex);
         vTaskDelay(delay30);
         //*/
         
         /*/
         sprintf(debugString1, "min = %d; max = %d.\r\n", rrHistogramm.getMin(), rrHistogramm.getMax());
         sprintf(debugString2, "lower = %d; upper = %d; bins = %d\r\n", rrHistogramm.getLowerBound(), 
                 rrHistogramm.getUpperBound(), rrHistogramm.getNumberOfhistogrammBins());
         xSemaphoreTake(uartMutex, portMAX_DELAY);
         uart.sendMessage(debugString1);
         uart.sendMessage(debugString2);
         xSemaphoreGive(uartMutex);
         //*/
      
      }
      // yield control to scheduler
      //taskYIELD();
      vTaskDelay(delay3000);
   }
}