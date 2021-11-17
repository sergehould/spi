/* 
 * File:   main.cpp for lab 5
 * 
 * Author       Date        Description
 * 
 */

#include <xc.h>
#include "initBoard.h"
#include "oled_init.h"


int main(void) {
    /* When using the OLED, the following line MUST always be the first line 
     * to run when entering the main                                        */
    //oled_init();  // Uncomment this line part 2 and part 3 only

    initIOs();

    /* Super loop*/
    while(1){
        
    }
    return 0;
}


