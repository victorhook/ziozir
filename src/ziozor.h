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
                      |  BIOS   |                                                                     
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

Memory mapped I/O

RAM:  8192
BIOS: 512



-- Memory mapped I/O --
RAM addr  |   Periperal
0 - Keyboard
1 - mouseX
2 - mouseY
3 - mouseClick
4 - 
#define MONITOR_WIDTH 144
#define MONITOR_HEIGHT 166

*/



#endif /* ZIOZOR_H */
