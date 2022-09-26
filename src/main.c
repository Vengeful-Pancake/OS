#include "uart.h"
#include "mbox.h"
#include "framebf.h"
#include "game.h"
#include "../src/desktop.h"
#include "../src/gamefile/intro.h"

void main()
{
    // set up serial console
	uart_init();

	// say hello
	uart_puts("\n\nHello World!\n");

	// Initialize frame buffer
	framebf_init();
	int stage = 1;
	while(1){
		int x,y, attr;
		char n;
		int i=0;
		for (y = 0; y < Intro_height; y++){
        	for (x = 0; x < Intro_width; x++ ){
					attr = Desk_bg[i];
					if (stage==1){	
						if (Desk_game[i] != 0x00000000){
							attr = Desk_game[i];
						};
					}
					if (stage==2){	
						if (Desk_video[i] != 0x00000000){
							attr = Desk_video[i];
						};
					}
					if (stage==3){	
						if (Desk_photo[i] != 0x00000000){
							attr = Desk_photo[i];
						};
					}
					drawPixelARGB32(x,y,attr);
					i++;
				}   
    	}
		wait_cycles(30000000);
		n = uart_getc();
		if (n == 'a'){
			stage++;
			if (stage>3){
				stage=1;
			}
		}
		if (n == 'd'){
			stage--;
			if (stage<1){
				stage=3;
			}
		}
		if (n == '\n' && stage==1){
			game_engine();
		}
	}
}
