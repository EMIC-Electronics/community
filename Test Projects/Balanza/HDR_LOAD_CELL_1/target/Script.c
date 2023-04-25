// Script

const char onReset[] = "#blkLed1(«125»,«250»,«4»)#setCapacity(«10000»)#setmVxV(«1.9992»)#setTime1(«1000»,«T»)";

const char etOut1[] = "#setZero()#setTime2(«15000»,«T»)";

const char etOut2[] = "#blkLed1(«250»,«500»,«2»)#setTime3(«5000»,«T»)";

const char etOut3[] = "#blkLed1(«125»,«250»,«2»)#setReference(«2000»)#setTime4(«1000»,«A»)";

const char etOut4[] = "#pI2C(«Peso»,#Peso;)";

const char eZero[] = "#blkLed1(«250»,«500»,«4»)";

const char eStable[] = "#led1(«1»)";

const char eUnstable[] = "#led1(«0»)";

const char eOverLoad[] = "#blkLed1(«100»,«200»,«40»)";

