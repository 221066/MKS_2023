# MKS_2023


**NUCLEOF030R8**\
cv01 - Základné funkcie (noHAL, priradenie pinov etc.); \
cv02 - SysTick, GPIO manuálne, manualný interrupt; \
cv03 - manualný výpis na 7-seg cez sct knihovnu;\
cv03B - 7-seg s HAL, sct primitivné, NEPOUZIVAŤ;\
cv04 - ADC a bargraf - rotačny enkoder, prepinanie displeja na teplotu a napetie pomocou tlačítok, FSM s TIMEOUT, NEBLOKOVACI;\
cv05 - UART s DMA, EEPROM cez I2C - UART buffer + zpracovanie zprávy, strcasecmp a printf strom, HAL zapis pinov, SPRAVNE NAMAPOVANIE PINOV A NASTAVENIE: EEPROM UART;\
cv06 - Teplotné čidla digital/analog - knihovna 1WIRE a SCT, výčet z digitalu cez 1wire, analog NTC z lookup tabulky, FSM SPATNEJ s flagama (static sa predsa neprepíše);\
cv07 - FreeRTOS - LIS2DW12 knihovna pre akcelerometer, upraveny UART kompatibilny s RTOS, kod sa píše dole do Tasku hlavný while je prázdny;\
**NUCLEOF429ZI**\
cv10 - Maticová klávesnica, kódový zámok - čítanie klavesnice cez SWV, v navode je ako naportit na F030R8;\
cv11 - USB mys HID - hranie sa so smajlíkom;\
cv12 - Ethernet, TCP klient a server - pripojenie dosky do siete, založenie servra, klient čo sa pripojí na server a vypíše terminal;\
