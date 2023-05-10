// Script

const char onReset[] = "#blkLed1(«125»,«250»,«4»)#load()«#setTime3(«1000»,«A»)»«#mVxV_cal=«1.9992»;#setCapacity(«10000»)#setTime1(«5000»,«T»)»";

const char etOut1[] = "#blkLed1(«500»,«1000»,«1»)#setZero()#setTime2(«15000»,«T»)";

const char etOut2[] = "#blkLed1(«500»,«1000»,«2»)#setReference(«2000»)#save()#setTime3(«1000»,«A»)";

const char etOut3[] = "#pI2C(«MED»,#Peso;)";

const char eError[] = "#blkLed1(«125»,«250»,«8»)#pI2C(«Code»,«Error»)";

