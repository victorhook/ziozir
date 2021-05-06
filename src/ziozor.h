#ifndef ZIOZOR_H
#define ZIOZOR_H

/*
                       +------+                                                                       
                       | RAM  |                                                                       
                       +---+--+                                                                       
                           |                             +--------------+                             
                           |                             |              |                             
                           |                            -+   Keyboard   |                             
+----------+      +--------+-------+                 --/ |              |                             
|          |      |                |     +-----+ ---/    +--------------+                             
|  FLASH   +------+      CPU       +------ IO  -\                                                     
|          |      |                |     +-----+ ---\    +----------------+           +--------------+
+----------+      +--------+-------+                 --\ |                |           |              |
                           |                            -+  GraphicsCard  +-----------+   Monitor    |
                           |                             |                |           |              |
                           |                             +----------------+           +--------------+
                           |                                                                          
                      +----+----+                                                                     
                      |         |                                                                     
                      | EEPROM  |                                                                     
                      |         |                                                                     
                      +---------+                                                                     

+------------------+ 
|  Register file   |
+------------------+ 
|       R0         |
|       R1         |
|       R2         |
|       R3         |
|       R4         |
|       R5         |
|       R6         |
|       R7         |
|       SP         |
|       PC         |
|      SREG        |
+------------------+ 

*/



#endif /* ZIOZOR_H */
