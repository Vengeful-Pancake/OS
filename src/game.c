#include "printf.h"
#include "uart.h"
#include "mbox.h"
#include "framebf.h"
#include "AI.h"
#include "../src/gamefile/Drago.h"
#include "../src/gamefile/Pris.h"
#include "../src/gamefile/Roy.h"
#include "../src/gamefile/map.h"
#include "../src/gamefile/char.h"
#include "../src/gamefile/generic.h"
#include "../src/gamefile/intro.h"
#include "../src/gamefile/mapcheck.h"
//run the game



// about the map, it is basically like this:
// we draw map bit by bit according to their position in the array,
// when it go to the desired position for a specific sprite (character or so), it replace that bit of the map.
// so, when you see "if (i == (Ry*map_width + Rx + i%36 +(y-Ry)*map_width) && (y-Ry) < 37 && (y-Ry) >= 0)", it is sprite check.
// Ry*map_width + Rx is the initial coordinate, + i%36 is because 36*36 is sprite limite, and the way the map designed make it always works
// +(y-Ry)*map_width) && (y-Ry) < 37 && (y-Ry) >= 0 is to bound the sprite into a square shape, or else, it would bugging out.
// hence, we got the map.
// Why am I not slap the map on first, then the character for easier coding?
// because all characters are flickering in that instance. 

//randomizer
int randomizer(int seed){
    static unsigned int g_seed;
    g_seed = seed;
    // Compute a pseudorandom integer.
    // Output value in range [0, 32767]
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
    

}
//handling map in selected stag (sl=1)
void selected(int map, int character, int position,int Roy, int Pris, int Drago, int movement, int stage, unsigned int generics[], int lastcursor, int alive){
    int x, y, Px,Py, i, attr, temp,nx,ny,Dx,Dy,Rx,Ry,a1,a2,a3,a4, lx,ly;
    //position stored like this:1204, 12 is x-coordinate, 04 is y-coordinate, so...
    nx=position/100*36;
    ny=position%100*36;
    Px=Pris/100*36;
    Py=Pris%100*36;
    Rx=Roy/100*36;
    Ry=Roy%100*36;
    Dx=Drago/100*36;
    Dy=Drago%100*36;
    lx=position/100-lastcursor/100;
    ly=position%100-lastcursor%100;

    
    //this is to boost speed of selected character 3 times faster than idle ones (in game_engine, this variable is i)
    i = 0;

    for (y = 0 ; y < map_height; y++){
        for (x = 0; x < map_width; x++ ){
            if(map==1){attr = map1[i];}
            if(map==2){attr = map2[i];}
            if(map==3){attr = map3[i];}
            //other characters
            if (i == (ny*map_width + nx + i%36 +(y-ny)*map_width) && (y-ny) < 37 && (y-ny) >= 0){
                temp = i%36+(y-ny)*36;
                if(character==1){
                    if(stage==1 || stage==3 || stage==5){
                        if (ly==1 || position == lastcursor ){
                            if (R_f3[temp] != 0x00000000 && temp < 36*36){
                                attr = R_f3[temp];
                            }
                        }
                        if (lx==1){
                            if (R_r3[temp] != 0x00000000 && temp < 36*36){
                                attr = R_r3[temp];
                            }
                        }
                        if (lx==-1){
                            if (R_l3[temp] != 0x00000000 && temp < 36*36){
                                attr = R_l3[temp];
                            }
                        }
                        if (ly==-1){
                            if (R_b3[temp] != 0x00000000 && temp < 36*36){
                                attr = R_b3[temp];
                            }
                        }

                        
                    }
                    if(stage == 2 || stage == 4 || stage == 6){
                        if (ly==1 || position == lastcursor ){
                            if (R_f2[temp] != 0x00000000 && temp < 36*36){
                                attr = R_f2[temp];
                            };
                        }
                        if (lx==1){
                            if (R_r2[temp] != 0x00000000 && temp < 36*36){
                                attr = R_r2[temp];
                            }
                        }
                        if (lx==-1){
                            if (R_l2[temp] != 0x00000000 && temp < 36*36){
                                attr = R_l2[temp];
                            }
                        }
                        if (ly==-1){
                            if (R_b2[temp] != 0x00000000 && temp < 36*36){
                                attr = R_b2[temp];
                            }
                        }
                    };
                };
                if(character==2){
                    if(stage==1 || stage==3 || stage==5){
                        if (ly==1 || position == lastcursor ){
                            if (P_f3[temp] != 0x00000000 && temp < 36*36){
                                attr = P_f3[temp];
                            };
                        }
                        if (lx==1){
                            if (P_r3[temp] != 0x00000000 && temp < 36*36){
                                attr = P_r3[temp];
                            }
                        }
                        if (lx==-1){
                            if (P_l3[temp] != 0x00000000 && temp < 36*36){
                                attr = P_l3[temp];
                            }
                        }
                        if (ly==-1){
                            if (P_b3[temp] != 0x00000000 && temp < 36*36){
                                attr = P_b3[temp];
                            }
                        }
                    };
                    if(stage == 2 || stage == 4 || stage == 6){
                        if (ly==1 || position == lastcursor ){
                            if (P_f2[temp] != 0x00000000 && temp < 36*36){
                                attr = P_f2[temp];
                            };
                        }
                        if (lx==1){
                            if (P_r2[temp] != 0x00000000 && temp < 36*36){
                                attr = P_r2[temp];
                            }
                        }
                        if (lx==-1){
                            if (P_l2[temp] != 0x00000000 && temp < 36*36){
                                attr = P_l2[temp];
                            }
                        }
                        if (ly==-1){
                            if (P_b2[temp] != 0x00000000 && temp < 36*36){
                                attr = P_b2[temp];
                            }
                        }
                    };
                };
                if(character==3){
                    if(stage==1 || stage==3 || stage==5){
                        if (ly==1 || position == lastcursor ){
                            if (D_f3[temp] != 0x00000000 && temp < 36*36){
                                attr = D_f3[temp];
                            };
                        }
                        if (lx==1){
                            if (D_r3[temp] != 0x00000000 && temp < 36*36){
                                attr = D_r3[temp];
                            }
                        }
                        if (lx==-1){
                            if (D_l3[temp] != 0x00000000 && temp < 36*36){
                                attr = D_l3[temp];
                            }
                        }
                        if (ly==-1){
                            if (D_b3[temp] != 0x00000000 && temp < 36*36){
                                attr = D_b3[temp];
                            }
                        }
                    };
                    if(stage == 2 || stage == 4 || stage == 6){
                        if (ly==1 || position == lastcursor ){
                            if (D_f2[temp] != 0x00000000 && temp < 36*36){
                                attr = D_f2[temp];
                            };
                        }
                        if (lx==1){
                            if (D_r2[temp] != 0x00000000 && temp < 36*36){
                                attr = D_r2[temp];
                            }
                        }
                        if (lx==-1){
                            if (D_l2[temp] != 0x00000000 && temp < 36*36){
                                attr = D_l2[temp];
                            }
                        }
                        if (ly==-1){
                            if (D_b3[temp] != 0x00000000 && temp < 36*36){
                                attr = D_b2[temp];
                            }
                        }
                    };
                };
            };

            //cursor frame
            if (i == (ny*map_width + nx + i%36 +(y-ny)*map_width) && (y-ny) < 37 && (y-ny) >= 0){
                temp = i%36+(y-ny)*36;
                
                if(stage==1 || stage==3 || stage==5){
                    if (cursor1[temp] != 0x00000000 && temp < 36*36){
                        attr = cursor1[temp];
                    };
                };
                if(stage==2 || stage==4 || stage==6){
                    if (cursor2[temp] != 0x00000000 && temp < 36*36){
                        attr = cursor2[temp];
                    };
                };
            };

            // this is other characters, still in idling stage
            if (character!=1 && alive/100==1){
                if (i == (Ry*map_width + Rx + i%36 +(y-Ry)*map_width) && (y-Ry) < 37 && (y-Ry) >= 0){
                    temp = i%36+(y-Ry)*36;
                    
                    if(stage == 1 || stage == 2 || stage == 3){
                        if (R_f3[temp] != 0x00000000 && temp < 36*36){
                            attr = R_f3[temp];
                        };
                        };
                    if(stage == 4 || stage == 5 || stage == 6){
                        if (R_f2[temp] != 0x00000000 && temp < 36*36){
                            attr = R_f2[temp];
                        };
                    };
                };
            };
            if (character!=3 && alive%10==1){
                if (i == (Dy*map_width + Dx + i%36 +(y-Dy)*map_width) && (y-Dy) < 37 && (y-Dy) >= 0){
                    temp = i%36+(y-Dy)*36;
                    
                    if(stage == 1 || stage == 2 || stage == 3){
                        if (D_f3[temp] != 0x00000000 && temp < 36*36){
                            attr = D_f3[temp];
                        };
                    };
                    if(stage == 4 || stage == 5 || stage == 6){
                        if (D_f2[temp] != 0x00000000 && temp < 36*36){
                            attr = D_f2[temp];
                        };
                    };
                };
            };
            if (character!=2 && (alive/10)%10==1){
                if (i == (Py*map_width + Px + i%36 +(y-Py)*map_width) && (y-Py) < 37 && (y-Py) >= 0){
                    temp = i%36+(y-Py)*36;
                    
                    if(stage == 1 || stage == 2 || stage == 3){
                        if (P_f3[temp] != 0x00000000 && temp < 36*36){
                            attr = P_f3[temp];
                        };
                    };
                    if(stage == 4 || stage == 5 || stage == 6){
                        if (P_f2[temp] != 0x00000000 && temp < 36*36){
                            attr = P_f2[temp];
                        };
                    };
                };
            };
            
            //generics
            for (a1=0; a1<5; a1++){
                if (generics[a1]!=0!=0){
                    a2 = ((generics[a1]/100)%100)*36;
                    a3 = (generics[a1]%100)*36;
                    a4 = generics[a1]/10000;
                    if (i == (a3*map_width + a2 + i%36 +(y-a3)*map_width) && (y-a3) < 37){
                        temp = i%36+(y-a3)*36;
                        if (a4 == 1){
                            
                            if(stage == 1 || stage == 2 || stage == 3){
                                if (babarian_f3[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = babarian_f3[temp];
                                }
                            }
                            if(stage == 4 || stage == 5 || stage == 6){
                                if (babarian_f2[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = babarian_f2[temp];
                                }
                            }
                        }
                        if (a4 == 2){
                            if(stage == 1 || stage == 2 || stage == 3){
                                if (archer_f3[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = archer_f3[temp];
                                }
                            }
                            if(stage == 4 || stage == 5 || stage == 6){
                                if (archer_f2[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = archer_f2[temp];
                                }
                            }
                        }
                        if (a4 == 3){
                            
                            if(stage == 1 || stage == 2 || stage == 3){
                                if (myrmidon_f3[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = myrmidon_f3[temp];
                                };
                            };
                            if(stage == 4 || stage == 5 || stage == 6){
                                if (myrmidon_f3[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = myrmidon_f3[temp];
                                }
                            }
                        }
                    }
                }
            }
            i++;
            drawPixelARGB32(x, y,attr);
        }
    }
}

// not in the game, mainly cutscene and shit
void intro(int stage){
    uart_init();
    framebf_init();
    int attr;
    int x,y;
    int i = 0;

    if (stage == 0){
        for (y = 0 ; y < Intro_height; y++){
            for (x = 0; x < Intro_width; x++ )
            {
                attr = Intro0[i];
                if (attr != 0x00000000){
                    drawPixelARGB32(x, y,attr);
                }
                i++;
            }
        }
    }
    if (stage == 1){
        for (y = 0 ; y < Intro_height; y++){
            for (x = 0; x < Intro_width; x++ )
            {
                attr = Intro1[i];
                if (attr != 0x00000000){
                    drawPixelARGB32(x, y,attr);
                }
                i++;
            }
        }
    }
    if (stage == 2){
        for (y = 0 ; y < Intro_height; y++){
            for (x = 0; x < Intro_width; x++ )
            {
                attr = Intro2[i];
                if (attr != 0x00000000){
                    drawPixelARGB32(x, y,attr);
                }
                i++;
            }
        }
    }
    if (stage == 3){
        for (y = 0 ; y < Intro_height; y++){
            for (x = 0; x < Intro_width; x++ )
            {
                attr = Intro3[i];
                if (attr != 0x00000000){
                    drawPixelARGB32(x, y,attr);
                }
                i++;
            }
        }
    }
    if (stage == 4){
        for (y = 0 ; y < Intro_height; y++){
            for (x = 0; x < Intro_width; x++ )
            {
                attr = Epilogue[i];
                if (attr != 0x00000000){
                    drawPixelARGB32(x, y,attr);
                }
                i++;
            }
        }
    }
}

//handle input
int inputhandler(int input, int pos){
    // Do I really need to explain this? No, I don't
    int wl;
    if(input==119){
        wl = (pos-1);
        if (wl%100 >= 0 && wl%100 != 99){
            return wl ;
        }
    }
    if(input==97){
        wl = (pos-100);
        if (wl/100 >=0 && wl>=0 ){
            return wl;
        }
    }
    if(input==115){
        wl = (pos+1);
        if (wl%100 <= 19){
            return wl = (pos+1);
        }
    }
    if(input==100){
        wl = (pos+100);
        if (wl/100 <= 19){
            return wl = (pos+100);
        }
    }
    return pos;
}

//handling idle map, used when it is in idle stage(sl=0)
void drawn(int stage, int Roy_pos, int Drago_pos, int Pris_pos, int cursor_pos, int map, unsigned int generics[], int alive){
    int Px = ((Pris_pos/100)%100)*36;
    int Py = (Pris_pos%100)*36;
    int Dx = ((Drago_pos/100)%100)*36;
    int Dy = (Drago_pos%100)*36;
    int Rx = ((Roy_pos/100)%100)*36;
    int Ry = (Roy_pos%100)*36;
    int Cx = ((cursor_pos/100)%100)*36;
    int Cy = (cursor_pos%100)*36;
    int mmmm;
    int a1=0;
    int a2=0;
    int a3=0;
    int a4=0;
    
    unsigned int y,x;
    unsigned i = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    unsigned attr;
    int temp;
    i = 0;
    for (y = 0 ; y < map_height; y++){
        for (x = 0; x < map_width; x++ ){
            if(map==1){
                attr = map1[i];
            }
            if(map==2){
                attr = map2[i];
            }
            if(map==3){
                attr = map3[i];
            }
            if (i == (Ry*map_width + Rx + i%36 +(y-Ry)*map_width) && (y-Ry) < 37 && alive/100==1){
                temp = i%36+(y-Ry)*36;
                if (stage==0){
                    if (R_f3[temp] != 0x00000000 && temp < 36*36){
                        attr = R_f3[temp];
                    };
                };
                if (stage==1){
                    if (R_f2[temp] != 0x00000000 && temp < 36*36){
                        attr = R_f2[temp];
                    };
                };
            };
            if (i == (Dy*map_width + Dx + i%36 +(y-Dy)*map_width) && (y-Dy) < 37 && alive%10==1){
                temp = i%36+(y-Dy)*36;
                if (stage==0){
                    if (D_f3[temp] != 0x00000000 && temp < 36*36){
                        attr = D_f3[temp];
                    };
                };
                if (stage==1){
                    if (D_f2[temp] != 0x00000000 && temp < 36*36){
                        attr = D_f2[temp];
                    };
                };
            };
            if (i == (Py*map_width + Px + i%36 +(y-Py)*map_width) && (y-Py) < 37 && (alive/10)%10==1){
                temp = i%36+(y-Py)*36;
                if (stage==0){
                    if (P_f3[temp] != 0x00000000 && temp < 36*36){
                        attr = P_f3[temp];
                    };
                };
                if (stage==1){
                    if (P_f2[temp] != 0x00000000 && temp < 36*36){
                        attr = P_f2[temp];
                    };
                };
            };
            if (i == (Cy*map_width + Cx + i%36 +(y-Cy)*map_width) && (y-Cy) < 37){
                temp = i%36+(y-Cy)*36;
                if (stage==0){
                    if (cursor1[temp] != 0x00000000 && temp < 36*36){
                        attr = cursor1[temp];
                    };
                };
                if (stage==1){
                    if (cursor2[temp] != 0x00000000 && temp < 36*36){
                        attr = cursor2[temp];
                    };
                };
            };
            for (a1=0; a1<5; a1++){
                a2 = ((generics[a1]/100)%100)*36;
                a3 = (generics[a1]%100)*36;
                a4 = generics[a1]/10000;
                if (i == (a3*map_width + a2 + i%36 +(y-a3)*map_width) && (y-a3) < 37){
                    temp = i%36+(y-a3)*36;
                    if (a4 == 1){
                        if (stage==0){
                            if (babarian_f2[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                attr = babarian_f2[temp];
                            };
                        };
                        if (stage==1){
                            if (babarian_f3[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                attr = babarian_f3[temp];
                            };
                        };
                    };
                    if (a4 == 2){
                        if (stage==0){
                            if (archer_f2[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                attr = archer_f2[temp];
                            };
                        };
                        if (stage==1){
                            if (archer_f3[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                attr = archer_f3[temp];
                            };
                        };
                    };
                    if (a4 == 3){
                        if (stage==0){
                            if (myrmidon_f2[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                attr = myrmidon_f2[temp];
                            };
                        };
                        if (stage==1){
                            if (myrmidon_f3[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                attr = myrmidon_f3[temp];
                            };
                        };
                    };
                };
            };
            i++;
            drawPixelARGB32(x, y, attr);
        }
    }
}

int combat(int character, int enemy, int hp, int map, int attacker, int seed, int seed2, int stg){
    int atk, mag, spd, skl, def, res, mhp, ehp, hitt,n;
    int eatk, emag, espd, eskl, edef, eres,x;
    int damage, hit, crit;
    int random;
    if (map==1){x=5; n=1;}
    if(map==2){x=0; n=0;}
    if (map==3){x=-2; n=-1;}
    if(character==1){
        res= Roy_init%100;
        def=(Roy_init/100)%100;
        skl=(Roy_init/10000)%100;
        spd=(Roy_init/1000000)%100;
        mag=(Roy_init/100000000)%100;
        atk=(Roy_init/10000000000)%100;
        mhp =(Roy_init/1000000000000)%100;
    }
    if(character==2){
        res= Pris_init%100;
        def=(Pris_init/100)%100;
        skl=(Pris_init/10000)%100;
        spd=(Pris_init/1000000)%100;
        mag=(Pris_init/100000000)%100;
        atk=(Pris_init/10000000000)%100;
        mhp =(Pris_init/1000000000000)%100;
    }
    if(character==3){
        res= Drago_init%100;
        def=(Drago_init/100)%100;
        skl=(Drago_init/10000)%100;
        spd=(Drago_init/1000000)%100;
        mag=(Drago_init/100000000)%100;
        atk=(Drago_init/10000000000)%100;
        mhp =(Drago_init/1000000000000)%100;
    }
    if(enemy==1){
        eres=Roy_init%100-x;
        edef=(Roy_init/100)%100-x;
        eskl=(Roy_init/10000)%100-x;
        espd=(Roy_init/1000000)%100-x;
        emag=(Roy_init/100000000)%100-x;
        eatk=(Roy_init/10000000000)%100-x;
        ehp=(Roy_init/1000000000000)%100-10*n;
    }
    if(enemy==2){
        eres=Roy_init%100-x;
        edef=(Roy_init/100)%100;
        eskl=(Roy_init/10000)%100;
        espd=(Roy_init/1000000)%100;
        emag=(Roy_init/100000000)%100;
        eatk=(Drago_init/10000000000)%100;
        ehp=(Roy_init/1000000000000)%100-10*n;
    }
    if(enemy==3){
        eres=Roy_init%100-x;
        edef=(Pris_init/100)%100-x;
        eskl=(Roy_init/10000)%100-x;
        espd=(Drago_init/1000000)%100-x;
        emag=(Roy_init/100000000)%100-x;
        eatk=(Drago_init/10000000000)%100-x;
        ehp=(Roy_init/1000000000000)%100-10*n;
    }
    if (attacker==1){
        damage = atk*1.5-edef;
        if (character==2){
            damage=mag*1.5-eres;
        }
        hit = 60+skl*2+spd-espd-eskl*1.5;
        crit = skl*4-eskl*1.5;
    }
    if (attacker==0){
        damage = eatk*1.5-def;
        hit = 60+eskl*2+espd-spd-skl*1.5;
        crit = eskl*4-skl*1.5;
    }

    if(stg==0){return mhp;}
    if(stg==1){return atk;}
    if(stg==2){return mag;}
    if(stg==3){return spd;}
    if(stg==4){return skl;}
    if(stg==5){return def;}
    if(stg==6){return res;}
    if(stg==7){return eatk;}
    if(stg==8){return emag;}
    if(stg==9){return espd;}
    if(stg==10){return eskl;}
    if(stg==11){return edef;}
    if(stg==12){return eres;}
    
    if(stg==13){return hit;}
    if(stg==14){return crit;}
    if(stg==15){return damage;}
    if(stg==16){return ehp;}

    random=randomizer(seed)%100;
    
    if (random<hit){
        hitt = 1;
    }
    else{
        hitt=0;
        damage=0;
        uart_puts("\nmiss!!!\n");    
    }

    if (hitt == 1){
        hp=hp-damage;
        random=randomizer(seed2)%100;
        if (random<crit){
            damage=damage*3;
            uart_puts("\ncritical! damage*3!!!\n");
        }
    }
    
    if(hp<=0){
        hp=0;
        printf("\nhp= %d\n", hp);
        return hp;
    }
    printf("\nhp= %d\n", hp);
    return hp;


}

// side bar
void sidedraw(int character, int enemy, int gag, int movement, int truehp, int thp){
    //, int stat[], int move
    int x, y;
    int attr;
    int i = 0;
    int Vx = 20;
    int Vy = 25;
    int temp;
    for (y = 0 ; y < side_height; y++){
        for (x = 0; x < side_width; x++ ){
            attr = side[i];
            if (enemy == 1 && babarian_avt[i] != 0x00000000){
                attr=babarian_avt[i];
            }
            if (enemy == 2 && archer_avt[i] != 0x00000000){
                attr=archer_avt[i];
            }
            if (enemy == 3 && myrmidon_avt[i] != 0x00000000){
                attr=myrmidon_avt[i];
            }
            if (i == (Vy*side_width + Vx + ((i-y*360-Vx)%108) +(y-Vy)*side_width) && (y-Vy) < 109 && (y-Vy) >=0 && i > Vx + y * side_width){
                temp = (i-y*360-20)%108+(y-Vy)*108;
                if(character == 1){
                    if (R_avatar[temp] != 0x00000000 && temp < 108*108){
                        attr = R_avatar[temp];
                    }
                }
                if(character == 2){
                    if (P_avatar[temp] != 0x00000000 && temp < 108*108){
                        attr = P_avatar[temp];
                    };
                };
                if(character == 3){
                    if (D_avatar[temp] != 0x00000000 && temp < 108*108){
                        attr = D_avatar[temp];
                };
                }
            }
            i++;
            drawPixelARGB32(x+720, y, attr);
        }
    }
    drawStringARGB32(900,80,"hp: %",0xffffffff, thp);
    drawStringARGB32(745,160,"atk: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,1));
    drawStringARGB32(745,180,"mag: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,2));
    drawStringARGB32(745,200,"spd: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,3));
    drawStringARGB32(745,220,"skl: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,4));
    drawStringARGB32(745,240,"def: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,5));
    drawStringARGB32(745,260,"res: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,6));
    drawStringARGB32(745,280,"mov: %",0xffffffff,movement);
    if(enemy!=0){
        drawStringARGB32(745,480,"hp: %",0xffffffff, truehp);
        drawStringARGB32(900,520,"atk: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,7));
        drawStringARGB32(900,540,"mag: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,8));
        drawStringARGB32(900,560,"spd: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,9));
        drawStringARGB32(900,580,"skl: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,10));
        drawStringARGB32(900,600,"def: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,11));
        drawStringARGB32(900,620,"res: %",0xffffffff, combat(character, enemy, 10, 1, 1, 10,10,12));
    }
    
    
}

void action(int map, int character, int position,int Roy, int Pris, int Drago, int movement, int stage, unsigned int generics[], int lastcursor, int act){
    int x, y, Px,Py,attr, temp,nx,ny,Dx,Dy,Rx,Ry,a1,a2,a3,a4;
    //position stored like this:1204, 12 is x-coordinate, 04 is y-coordinate, so...
    nx=position/100*36;
    ny=position%100*36;
    Px=Pris/100*36;
    Py=Pris%100*36;
    Rx=Roy/100*36;
    Ry=Roy%100*36;
    Dx=Drago/100*36;
    Dy=Drago%100*36;
    int i=0;
    for (y = 0 ; y < map_height; y++){
        for (x = 0; x < map_width; x++ ){
            if(map==1){attr = map1[i];}
            if(map==2){attr = map2[i];}
            if(map==3){attr = map3[i];}
            if (i == (ny*map_width + nx + i%36 +(y-ny)*map_width) && (y-ny) < 37 && (y-ny) >= 0){
                temp = i%36+(y-ny)*36;
                if(character==1){
                    if(stage==1 || stage==3 || stage==5){
                        if (R_f3[temp] != 0x00000000 && temp < 36*36){
                            attr = R_f3[temp];
                        }
                    }
                    if(stage == 2 || stage == 4 || stage == 6){
                        if (R_f2[temp] != 0x00000000 && temp < 36*36){
                            attr = R_f2[temp];
                        };
                    };
                };
                if(character==2){
                    if(stage==1 || stage==3 || stage==5){
                        if (P_f3[temp] != 0x00000000 && temp < 36*36){
                            attr = P_f3[temp];
                        };
                    };
                    if(stage == 2 || stage == 4 || stage == 6){
                        if (P_f2[temp] != 0x00000000 && temp < 36*36){
                            attr = P_f2[temp];
                        };
                    };
                };
                if(character==3){
                    if(stage==1 || stage==3 || stage==5){
                        if (D_f3[temp] != 0x00000000 && temp < 36*36){
                            attr = D_f3[temp];
                        };
                    };
                    if(stage == 2 || stage == 4 || stage == 6){
                        if (D_f2[temp] != 0x00000000 && temp < 36*36){
                            attr = D_f2[temp];
                        };
                    };
                };
            };

            //cursor frame
            if (i == (ny*map_width + nx + i%36 +(y-ny)*map_width) && (y-ny) < 37 && (y-ny) >= 0){
                temp = i%36+(y-ny)*36;
                
                if(stage==1 || stage==3 || stage==5){
                    if (cursor1[temp] != 0x00000000 && temp < 36*36){
                        attr = cursor1[temp];
                    };
                };
                if(stage==2 || stage==4 || stage==6){
                    if (cursor2[temp] != 0x00000000 && temp < 36*36){
                        attr = cursor2[temp];
                    };
                };
            };

            // this is other characters, still in idling stage
            if (character!=1){
                if (i == (Ry*map_width + Rx + i%36 +(y-Ry)*map_width) && (y-Ry) < 37 && (y-Ry) >= 0){
                    temp = i%36+(y-Ry)*36;
                    
                    if(stage == 1 || stage == 2 || stage == 3){
                        if (R_f3[temp] != 0x00000000 && temp < 36*36){
                            attr = R_f3[temp];
                        };
                        };
                    if(stage == 4 || stage == 5 || stage == 6){
                        if (R_f2[temp] != 0x00000000 && temp < 36*36){
                            attr = R_f2[temp];
                        };
                    };
                };
            };
            if (character!=3){
                if (i == (Dy*map_width + Dx + i%36 +(y-Dy)*map_width) && (y-Dy) < 37 && (y-Dy) >= 0){
                    temp = i%36+(y-Dy)*36;
                    
                    if(stage == 1 || stage == 2 || stage == 3){
                        if (D_f3[temp] != 0x00000000 && temp < 36*36){
                            attr = D_f3[temp];
                        };
                    };
                    if(stage == 4 || stage == 5 || stage == 6){
                        if (D_f2[temp] != 0x00000000 && temp < 36*36){
                            attr = D_f2[temp];
                        };
                    };
                };
            };
            if (character!=2){
                if (i == (Py*map_width + Px + i%36 +(y-Py)*map_width) && (y-Py) < 37 && (y-Py) >= 0){
                    temp = i%36+(y-Py)*36;
                    
                    if(stage == 1 || stage == 2 || stage == 3){
                        if (P_f3[temp] != 0x00000000 && temp < 36*36){
                            attr = P_f3[temp];
                        };
                    };
                    if(stage == 4 || stage == 5 || stage == 6){
                        if (P_f2[temp] != 0x00000000 && temp < 36*36){
                            attr = P_f2[temp];
                        };
                    };
                };
            };
            //generics

            for (a1=0; a1<5; a1++){
                if (generics[a1]!=0){
                    a2 = ((generics[a1]/100)%100)*36;
                    a3 = (generics[a1]%100)*36;
                    a4 = generics[a1]/10000;
                    if (i == (a3*map_width + a2 + i%36 +(y-a3)*map_width) && (y-a3) < 37){
                        temp = i%36+(y-a3)*36;
                        if (a4 == 1){
                            if(stage == 1 || stage == 2 || stage == 3){
                                if (babarian_f3[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = babarian_f3[temp];
                                }
                            }
                            if(stage == 4 || stage == 5 || stage == 6){
                                if (babarian_f2[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = babarian_f2[temp];
                                }
                            }
                        }
                        if (a4 == 2){
                            if(stage == 1 || stage == 2 || stage == 3){
                                if (archer_f3[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = archer_f3[temp];
                                }
                            }
                            if(stage == 4 || stage == 5 || stage == 6){
                                if (archer_f2[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = archer_f2[temp];
                                }
                            }
                        }
                        if (a4 == 3){
                            
                            if(stage == 1 || stage == 2 || stage == 3){
                                if (myrmidon_f3[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = myrmidon_f3[temp];
                                };
                            };
                            if(stage == 4 || stage == 5 || stage == 6){
                                if (myrmidon_f3[temp] != 0x00000000 && temp < 36*36 && temp >= 0){
                                    attr = myrmidon_f3[temp];
                                }
                            }
                        }
                    }
                }
            }
            if (act==0){
                if (fight[i] != 0x00ffffff ){
                    attr = fight[i];
                };
            };
            if (act==1){
                if (fight[i] != 0x00ffffff ){
                    attr = heal[i];
                };
            };
            if (act==2){
                if (fight[i] != 0x00ffffff ){
                    attr = item[i];
                };
            };
            if (act==3){
                if (fight[i] != 0x00ffffff ){
                    attr = wait[i];
                };
            };
            i++;
            drawPixelARGB32(x, y, attr);
        }
    }
}

void *memcpy(void *dest, const void *src, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

int abss(int x){
    if(x<0){
        int c;
        return c = (x*-1);
    }
}

void game_engine(){
    int random;
    int i = 1;
    uart_init();
    uart_puts("hello from game");
    int Roy_pos = Roypos;
    int Drago_pos = Dragopos;
    int Pris_pos = Prispos;
    int map = 1;
    int cursor_pos = Roy_pos;
    int ddd,dd,xnn,ynn, ddt,dtt,kt, mod1,mod2,mod3;
    int sl = 0;
    int sstg=0;
    int sss=0;
    intro(1);
    uart_getc();
    intro(2);
    uart_getc();
    intro(3);
    uart_getc();
    int input,checkpos,apv, cppt;
    int kkk;
    int k=0;
    int sh=0;
    int cp;
    int lastcursortemp, lastcursor;
    int alive;
    int ca=0;
    int move = 4;
    unsigned int bluearea[41]={-400, -301, -300, -299, -202, -201, -200, -199, -198, -103, -102, -101, -100, -99, -98, -97, -4, -3, -2, -1, 0, 1, 2, 3, 4, 97, 98, 99, 100, 101, 102, 103, 198, 199, 200, 201, 202, 299, 300, 301, 400};
    
    int eu;
    int turn;
    int mturn;
    int Rhp=(Roy_init/1000000000000)%100;
    int Php=(Pris_init/1000000000000)%100;
    int Dhp=(Drago_init/1000000000000)%100;
    int seed = 1;
    int seed2 = 2;
    alive=111;
    mod1=1;
    mod2=1;
    mod3=1;
    mturn=1;
    int g1[5]={generics1[0],generics1[1],generics1[2],generics1[3],generics1[4]};
    int hp1[5]={15,15,15,15,15};
    //this is map 1... duh
    while (map == 1){
        int target;
        int jar=0;
        int n1=-1;
        int n2=-1;
        int n3=-1;
        int n4=-1;
        int lx;
        int ly;
        int pddf=cursor_pos;
        int dksf;
        int truhp;
        if (mturn==1){
            seed++;
            seed2++;
            seed=seed+seed2;
            if (seed>1000000000){
                seed=0;
            }
            if(seed2>10000000000){
                seed2=0;
            }
            eu=0;
            input = '\0';
            //check input
            input = uart_game_getc();
            //save last cursor(developing on progress)
            //input assigned
            lastcursortemp = cursor_pos;
            cursor_pos = inputhandler(input, cursor_pos);
            kkk=0;
            //check the last input
            if (lastcursortemp!=cursor_pos){
                lastcursor = lastcursortemp;
                lastcursortemp = cursor_pos;
            }
            //sl=3 -> fight or item
            if (sl==3){               
                action(map, ddd, cp, Roy_pos, Pris_pos, Drago_pos, 4, i,g1, lastcursor,sstg);
                if (input=='k'){
                    sl = 0;
                    sh=0;
                    cursor_pos=cp;
                    ca=0;
                    dksf=0;
                }
                int num=0;
                for (checkpos=0; checkpos<5;checkpos++){
                    if (g1[num]%10000-cp==-1){
                        n1=num;
                    }
                    if (g1[num]%10000-cp==1){
                        n2=num;
                    }
                    if (g1[num]%10000-cp==-100){
                        n3=num;
                    }
                    if (g1[num]%10000-cp==100){
                        n4=num;
                    }
                    num++;
                }
                
                if ((n1!=-1 && input =='w') || dksf==1){
                    drawRectARGB32(cp/100*36,(cp%100-1)*36, cp/100*36+36,(cp%100-1)*36+36, 0x000000ff,1);
                    dksf=1;
                    k=g1[n1]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                            truhp=Rhp;
                        }
                        if (ddd==2){
                            truhp=Php;
                        }
                        if (ddd==3){
                            truhp=Dhp;
                        }
                        sidedraw(ddd,k,0,0, hp1[n1], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g1[n1]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g1[n1]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g1[n1]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp1[n1]=combat(ddd, g1[n1]/10000, hp1[n1], 1, 1, seed, seed2, 20);
                        lx=1;
                        sl = 0;
                        sh=0;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if ((n2!=-1 && input == 's')|| dksf==2){
                    drawRectARGB32(cp/100*36,(cp%100+1)*36, cp/100*36+36,(cp%100+1)*36+36, 0x000000ff,1);
                    dksf=2;
                    k=g1[n2]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                            truhp=Rhp;
                        }
                        if (ddd==2){
                            truhp=Php;
                        }
                        if (ddd==3){
                            truhp=Dhp;
                        }
                        sidedraw(ddd,k,0,0, hp1[n2], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g1[n2]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g1[n2]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g1[n2]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp1[n2]=combat(ddd, g1[n1]/10000, hp1[n2], 1, 1, seed, seed2, 20);
                        sl = 0;
                        lx=2;
                        sh=0;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if ((n3!=-1 && input =='a')|| dksf==3){
                    drawRectARGB32((cp/100-1)*36,cp%100*36, (cp/100-1)*36+36,cp%100*36+36, 0x000000ff,1);
                    dksf=3;
                    k=g1[n3]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                            truhp=Rhp;
                        }
                        if (ddd==2){
                            truhp=Php;
                        }
                        if (ddd==3){
                            truhp=Dhp;
                        }
                        sidedraw(ddd,k,0,0, hp1[n3], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g1[n3]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g1[n3]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g1[n3]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp1[n3]=combat(ddd, g1[n1]/10000, hp1[n1], 1, 1, seed, seed2, 20);
                        sl = 0;
                        lx=3;
                        sh=0;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if ((n4!=-1 && input == 'd')|| dksf==4){
                    drawRectARGB32((cp/100+1)*36,cp%100*36, (cp/100+1)*36+36,cp%100*36+36, 0x000000ff,1);
                    dksf=4;
                    k=g1[n4]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                        truhp=Rhp;
                    }
                    if (ddd==2){
                        truhp=Php;
                    }
                    if (ddd==3){
                        truhp=Dhp;
                    }
                        sidedraw(ddd,k,0,0, hp1[n4], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g1[n4]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g1[n4]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g1[n4]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp1[n4]=combat(ddd, g1[n4]/10000, hp1[n4], 1, 1, seed, seed2, 20);
                        sl = 0;
                        sh=0;
                        lx=4;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if(n1==-1 && n2==-1 && n3==-1 && n4==-1){sl=2;}
                if (sl==0){
                    if(ddd==1){mod1=0;Roy_pos=cp;}
                    if(ddd==2){mod2=0;Pris_pos=cp;}
                    if(ddd==3){mod3=0;Drago_pos=cp;}
                }
            }
            //sl=2 -> choosing action stage, in this stage, choose what to do.
            if (sl == 2){
                if (sh==0){
                    sh++;
                    cp=cursor_pos;
                }
                if (input == 'a'){
                    sstg--;
                }
                if (input == 'd'){
                    sstg++;
                }
                if (sstg<0){
                    sstg=3;
                }
                if (sstg>3){
                    sstg=0;
                }
                action(map, ddd, cp, Roy_pos, Pris_pos, Drago_pos, 4, i,g1, lastcursor,sstg);
                if (input=='k'){
                    sl = 0;
                    sh=0;
                    cursor_pos=cp;
                    ca=0;
                }
                //wait
                if(input =='j' && sstg == 0 && eu==0){
                    int jar=0;
                    sl=3;
                    if(jar==1){
                        sl=0;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod3=0;
                        jar=0;
                    }

                    eu=1;
                }
                if(input =='j' && sstg == 1 && eu==0){
                    if (ddd==2){
                        sl=0;
                        Pris_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod2=0;
                    }
                }
                if(input =='j' && sstg == 2 && eu==0){
                    int jar=0;
                    sl=3;
                    if(jar==1){
                        sl=0;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod3=0;
                        jar=0;
                    }

                    eu=1;
                }
                
                if(input =='j' && sstg == 3 && eu==0){
                    if (ddd==1){
                        sl=0;
                        Roy_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod1=0;
                    }
                    if (ddd==2){
                        sl=0;
                        Pris_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod2=0;
                    }
                    if (ddd==3){
                        sl=0;
                        Drago_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos = cp;
                        mod3=0;
                    }

                    eu=1;
                }
            };
            //check alive character
            if (alive/100==0){
                mod3=0;
            }
            if ((alive/10)%10==0){
                mod2=0;
            }
            if (alive%10==0){
                mod1=0;
            }
            //sl=1 -> selected stage, in this stage, cursor carries character around
            if (sl==1){
                for(checkpos=0;checkpos<129;checkpos++){
                    if (cursor_pos==map1_checc[checkpos]){
                        apv=1;
                        break;
                    }
                }
                if(ca==0){
                    ca=cursor_pos;
                }
                for(cppt=0;cppt<41;cppt++){
                    if (cursor_pos==bluearea[cppt]+ca && cursor_pos==map1_checc[checkpos]){
                        apv=1;
                        break;
                    }else{
                        apv=0;
                    }
                }
                for(checkpos=0;checkpos<5;checkpos++){
                    if(cursor_pos==g1[checkpos]%10000){
                        apv=0;
                    }
                }
                if(cursor_pos==Roy_pos && ddd!=1){
                    apv=0;
                }
                if(cursor_pos==Pris_pos && ddd!=2){
                    apv=0;
                }
                if(cursor_pos==Drago_pos && ddd!=3){
                    apv=0;
                }
                if(apv==0){
                    cursor_pos=lastcursor;
                }
                if (abss(ca/100-cursor_pos/100)+abss(ca%100-cursor_pos%100)>4){
                    apv=0;
                }
                apv=0;
                selected(map, ddd, cursor_pos, Roy_pos, Pris_pos, Drago_pos, 4, i,g1,lastcursor, alive);
                if (input == 'j' && ddd != 0 && eu == 0){
                    sl=2;
                    eu = 1;
                }
                if (input=='k'){
                    sl = 0;
                    ca=0;
                }
            };
            //sl=0 -> idle stage, noone move in this stage
            if (sl==0){
                if (i==1||i==2||i==3){
                    drawn(0,Roy_pos, Drago_pos, Pris_pos, cursor_pos, map, g1, alive);
                };
                if (i==4||i==5||i==6){
                    drawn(1,Roy_pos, Drago_pos, Pris_pos, cursor_pos, map, g1, alive);
                };
                if (cursor_pos == Roy_pos){
                    dd=1;
                    if (input=='j'&& eu==0 && mod1==1){
                        sl=1;
                        ddd=1;
                    };
                }
                if (cursor_pos == Pris_pos){
                    dd=2;
                    if (input=='j'&& eu==0 && mod2==1){
                        sl=1;
                        ddd=2;
                    };
                }
                if (cursor_pos == Drago_pos ){
                    dd=3;
                    if (input=='j' && eu==0 && mod3==1){
                        sl=1;
                        eu=1;
                        ddd=3;
                    };
                }
                //this is enemy positions, we stored it in array
                for (kkk=0; kkk<5; kkk++){
                    if (cursor_pos == g1[kkk]%10000){
                        k=g1[kkk]/10000;
                        break;
                    }
                };
            }
            // side bar handle, in this tap, move cursor to specific unit to see its stats, item, description
            if (sl==0){
                if (ddt!=cursor_pos){
                    ddt=cursor_pos;
                    if (ddd==1){
                        truhp=Rhp;
                    }
                    if (ddd==2){
                        truhp=Php;
                    }
                    if (ddd==3){
                        truhp=Dhp;
                    }
                    sidedraw(dd,k,0, 4, hp1[kkk], truhp);
                }
            };
            if (sl==1){
                //calculate movement
                int ssr = cursor_pos/100-ca/100;
                if (ssr<0){
                    ssr=ssr*-1;
                }
                int ur = cursor_pos%100-ca%100;
                if (ur<0){
                    ur = ur*-1;
                }
                int uur =  ssr + ur;
                uur=4-uur;
                if(uur>4){uur=4;}

                //side bar
                if (ddt!=cursor_pos){
                    ddt=cursor_pos;
                    if (ddd==1){
                        truhp=Rhp;
                    }
                    if (ddd==2){
                        truhp=Php;
                    }
                    if (ddd==3){
                        truhp=Dhp;
                    }
                    
                    sidedraw(ddd,k,0, uur, hp1[kkk], truhp);
                }
            };
            //this is just to check
            if (input != '\0'){
                uart_puts("\ninput: ");
                printf("%c\n", input);
            }
            //pause and quit
            if (input == 'p'){
                while(1){
                    
                    intro(0);
                    input = uart_getc();
                    if (input == 'l'){
                        map = 0;
                        break;
                    }
                    if (input == 'p'){
                        break;
                    }
                }
            }
            // this is action count
            i += 1;
            if(i > 6 ){
                i=1;
            };
            //your turn ends when 3 characters done
            if (mod1==0 && mod2 ==0 && mod3==0){
                mturn=0;
            }
            //if all enemy defeated, you can advance.
            for (checkpos=0;checkpos<5;checkpos++){
                if(hp1[checkpos]==0){
                    g1[checkpos]=0;
                }
            }
            for (checkpos=0;checkpos<5;checkpos++){
                if(g1[checkpos]!=0){
                    map=1;
                    break;
                }else{map=2;}
            }
            if (Rhp==0){Roy_pos=0;}
            if (Php==0){Pris_pos=0;}
            if (Dhp==0){Drago_pos=0;}
            if (Rhp==0 && Php==0 && Dhp==0){
                map=0;
                break;
            }
        }else{
            printf("enemy turn!\n");
            int i=1;
            int sam, sun, sin;
            sin=0;
            int j,k,l;
            while (1){
                i++;
                
                
                if(i<4){
                    drawn(1, Roy_pos, Drago_pos, Pris_pos, cursor_pos, map, g1, alive);
                }else{
                    drawn(0, Roy_pos, Drago_pos, Pris_pos, cursor_pos, map, g1, alive);
                }
                if (i==6){
                    sin++;
                    i=1;
                    //AI here, make every enemy move first, can you make them move 1 by 1?
                    for (sam=0; sam<5; sam++){
                        g1[sam]=thunking(Roy_pos, Pris_pos, Drago_pos,g1,sam, map1_checc, 129);
                        //g1[sam] =(g1[sam]/10000)*10000+k; 
                        printf("%d", g1[sam]);
                    }
                    // if adjacent, attack
                }
                if (sin==5){
                    for (sam=0; sam<5; sam++){
                        j=g1[sam]%10000;
                        if(j-Roy_pos==1 || j-Roy_pos==-1 || j-Roy_pos==100 || j-Roy_pos==-100){
                            Rhp=combat(1, g1[sam]/10000, Rhp, map, 0, seed, seed2, 20);
                        }
                        if(j-Pris_pos==1 || j-Pris_pos==-1 || j-Pris_pos==100 || j-Pris_pos==-100){
                            Php=combat(2, g1[sam]/10000, Php, map, 0, seed, seed2, 20);
                        }
                        if(j-Drago_pos==1 || j-Drago_pos==-1 || j-Drago_pos==100 || j-Drago_pos==-100){
                            Dhp=combat(3, g1[sam]/10000, Dhp, map, 0, seed, seed2, 20);
                        }
                    }
                    break;
                }
            }
            mod1=1;
            mod2=1;
            mod3=1;
            mturn=1;
        }
    };
















    k=0;
    sh=0;
    alive=111;
    mod1=1;
    mod2=1;
    mod3=1;
    mturn=1;
    Roy_pos = Roypos2;
    Drago_pos = Dragopos2;
    Pris_pos = Prispos2;
    cursor_pos = Roy_pos;
    int g2[5]={generics2[0],generics2[1],generics2[2],generics2[3],generics2[4]};
    int hp2[5]={25,25,25,25,25};
    Rhp=(Roy_init/1000000000000)%100;
    Php=(Pris_init/1000000000000)%100;
    Dhp=(Drago_init/1000000000000)%100;
    while (map == 2){
        int target;
        int jar=0;
        int n1=-1;
        int n2=-1;
        int n3=-1;
        int n4=-1;
        int lx;
        int ly;
        int pddf=cursor_pos;
        int dksf;
        int truhp;
        if (mturn==1){
            seed++;
            seed2++;
            seed=seed+seed2;
            if (seed>1000000000){
                seed=0;
            }
            if(seed2>10000000000){
                seed2=0;
            }
            eu=0;
            input = '\0';
            //check input
            input = uart_game_getc();
            //save last cursor(developing on progress)
            //input assigned
            lastcursortemp = cursor_pos;
            cursor_pos = inputhandler(input, cursor_pos);
            kkk=0;
            //check the last input
            if (lastcursortemp!=cursor_pos){
                lastcursor = lastcursortemp;
                lastcursortemp = cursor_pos;
            }
            //sl=3 -> fight or item
            if (sl==3){               
                action(map, ddd, cp, Roy_pos, Pris_pos, Drago_pos, 4, i,g2, lastcursor,sstg);
                if (input=='k'){
                    sl = 0;
                    sh=0;
                    cursor_pos=cp;
                    ca=0;
                    dksf=0;
                }
                int num=0;
                for (checkpos=0; checkpos<5;checkpos++){
                    if (g2[num]%10000-cp==-1){
                        n1=num;
                    }
                    if (g2[num]%10000-cp==1){
                        n2=num;
                    }
                    if (g2[num]%10000-cp==-100){
                        n3=num;
                    }
                    if (g2[num]%10000-cp==100){
                        n4=num;
                    }
                    num++;
                }
                
                if ((n1!=-1 && input =='w') || dksf==1){
                    drawRectARGB32(cp/100*36,(cp%100-1)*36, cp/100*36+36,(cp%100-1)*36+36, 0x000000ff,1);
                    dksf=1;
                    k=g2[n1]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                            truhp=Rhp;
                        }
                        if (ddd==2){
                            truhp=Php;
                        }
                        if (ddd==3){
                            truhp=Dhp;
                        }
                        sidedraw(ddd,k,0,0, hp2[n1], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g2[n1]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g2[n1]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g2[n1]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp2[n1]=combat(ddd, g2[n1]/10000, hp2[n1], 1, 1, seed, seed2, 20);
                        lx=1;
                        sl = 0;
                        sh=0;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if ((n2!=-1 && input == 's')|| dksf==2){
                    drawRectARGB32(cp/100*36,(cp%100+1)*36, cp/100*36+36,(cp%100+1)*36+36, 0x000000ff,1);
                    dksf=2;
                    k=g2[n2]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                            truhp=Rhp;
                        }
                        if (ddd==2){
                            truhp=Php;
                        }
                        if (ddd==3){
                            truhp=Dhp;
                        }
                        sidedraw(ddd,k,0,0, hp2[n2], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g2[n2]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g2[n2]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g2[n2]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp2[n2]=combat(ddd, g2[n1]/10000, hp2[n2], 1, 1, seed, seed2, 20);
                        sl = 0;
                        lx=2;
                        sh=0;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if ((n3!=-1 && input =='a')|| dksf==3){
                    drawRectARGB32((cp/100-1)*36,cp%100*36, (cp/100-1)*36+36,cp%100*36+36, 0x000000ff,1);
                    dksf=3;
                    k=g2[n3]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                            truhp=Rhp;
                        }
                        if (ddd==2){
                            truhp=Php;
                        }
                        if (ddd==3){
                            truhp=Dhp;
                        }
                        sidedraw(ddd,k,0,0, hp2[n3], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g2[n3]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g2[n3]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g2[n3]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp2[n3]=combat(ddd, g2[n1]/10000, hp2[n1], 1, 1, seed, seed2, 20);
                        sl = 0;
                        lx=3;
                        sh=0;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if ((n4!=-1 && input == 'd')|| dksf==4){
                    drawRectARGB32((cp/100+1)*36,cp%100*36, (cp/100+1)*36+36,cp%100*36+36, 0x000000ff,1);
                    dksf=4;
                    k=g2[n4]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                        truhp=Rhp;
                    }
                    if (ddd==2){
                        truhp=Php;
                    }
                    if (ddd==3){
                        truhp=Dhp;
                    }
                        sidedraw(ddd,k,0,0, hp2[n4], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g2[n4]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g2[n4]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g2[n4]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp2[n4]=combat(ddd, g2[n4]/10000, hp2[n4], 1, 1, seed, seed2, 20);
                        sl = 0;
                        sh=0;
                        lx=4;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if(n1==-1 && n2==-1 && n3==-1 && n4==-1){sl=2;}
                if (sl==0){
                    if(ddd==1){mod1=0;Roy_pos=cp;}
                    if(ddd==2){mod2=0;Pris_pos=cp;}
                    if(ddd==3){mod3=0;Drago_pos=cp;}
                }
            }
            //sl=2 -> choosing action stage, in this stage, choose what to do.
            if (sl == 2){
                if (sh==0){
                    sh++;
                    cp=cursor_pos;
                }
                if (input == 'a'){
                    sstg--;
                }
                if (input == 'd'){
                    sstg++;
                }
                if (sstg<0){
                    sstg=3;
                }
                if (sstg>3){
                    sstg=0;
                }
                action(map, ddd, cp, Roy_pos, Pris_pos, Drago_pos, 4, i,g2, lastcursor,sstg);
                if (input=='k'){
                    sl = 0;
                    sh=0;
                    cursor_pos=cp;
                    ca=0;
                }
                //wait
                if(input =='j' && sstg == 0 && eu==0){
                    int jar=0;
                    sl=3;
                    if(jar==1){
                        sl=0;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod3=0;
                        jar=0;
                    }

                    eu=1;
                }
                if(input =='j' && sstg == 1 && eu==0){
                    if (ddd==2){
                        sl=0;
                        Pris_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod2=0;
                    }
                }
                if(input =='j' && sstg == 2 && eu==0){
                    int jar=0;
                    sl=3;
                    if(jar==1){
                        sl=0;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod3=0;
                        jar=0;
                    }

                    eu=1;
                }
                
                if(input =='j' && sstg == 3 && eu==0){
                    if (ddd==1){
                        sl=0;
                        Roy_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod1=0;
                    }
                    if (ddd==2){
                        sl=0;
                        Pris_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod2=0;
                    }
                    if (ddd==3){
                        sl=0;
                        Drago_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos = cp;
                        mod3=0;
                    }

                    eu=1;
                }
            };
            //check alive character
            if (alive/100==0){
                mod3=0;
            }
            if ((alive/10)%10==0){
                mod2=0;
            }
            if (alive%10==0){
                mod1=0;
            }
            //sl=1 -> selected stage, in this stage, cursor carries character around
            if (sl==1){
                for(checkpos=0;checkpos<296;checkpos++){
                    if (cursor_pos==map1_checc[checkpos]){
                        apv=1;
                        break;
                    }
                }
                if(ca==0){
                    ca=cursor_pos;
                }
                for(cppt=0;cppt<41;cppt++){
                    if (cursor_pos==bluearea[cppt]+ca && cursor_pos==map1_checc[checkpos]){
                        apv=1;
                        break;
                    }else{
                        apv=0;
                    }
                }
                for(checkpos=0;checkpos<5;checkpos++){
                    if(cursor_pos==g2[checkpos]%10000){
                        apv=0;
                    }
                }
                if(cursor_pos==Roy_pos && ddd!=1){
                    apv=0;
                }
                if(cursor_pos==Pris_pos && ddd!=2){
                    apv=0;
                }
                if(cursor_pos==Drago_pos && ddd!=3){
                    apv=0;
                }
                if(apv==0){
                    cursor_pos=lastcursor;
                }
                if (abss(ca/100-cursor_pos/100)+abss(ca%100-cursor_pos%100)>4){
                    apv=0;
                }
                apv=0;
                selected(map, ddd, cursor_pos, Roy_pos, Pris_pos, Drago_pos, 4, i,g2,lastcursor, alive);
                if (input == 'j' && ddd != 0 && eu == 0){
                    sl=2;
                    eu = 1;
                }
                if (input=='k'){
                    sl = 0;
                    ca=0;
                }
            };
            //sl=0 -> idle stage, noone move in this stage
            if (sl==0){
                if (i==1||i==2||i==3){
                    drawn(0,Roy_pos, Drago_pos, Pris_pos, cursor_pos, map, g2, alive);
                };
                if (i==4||i==5||i==6){
                    drawn(1,Roy_pos, Drago_pos, Pris_pos, cursor_pos, map, g2, alive);
                };
                if (cursor_pos == Roy_pos){
                    dd=1;
                    if (input=='j'&& eu==0 && mod1==1){
                        sl=1;
                        ddd=1;
                    };
                }
                if (cursor_pos == Pris_pos){
                    dd=2;
                    if (input=='j'&& eu==0 && mod2==1){
                        sl=1;
                        ddd=2;
                    };
                }
                if (cursor_pos == Drago_pos ){
                    dd=3;
                    if (input=='j' && eu==0 && mod3==1){
                        sl=1;
                        eu=1;
                        ddd=3;
                    };
                }
                //this is enemy positions, we stored it in array
                for (kkk=0; kkk<5; kkk++){
                    if (cursor_pos == g2[kkk]%10000){
                        k=g2[kkk]/10000;
                        break;
                    }
                };
            }
            // side bar handle, in this tap, move cursor to specific unit to see its stats, item, description
            if (sl==0){
                if (ddt!=cursor_pos){
                    ddt=cursor_pos;
                    if (ddd==1){
                        truhp=Rhp;
                    }
                    if (ddd==2){
                        truhp=Php;
                    }
                    if (ddd==3){
                        truhp=Dhp;
                    }
                    sidedraw(dd,k,0, 4, hp2[kkk], truhp);
                }
            };
            if (sl==1){
                //calculate movement
                int ssr = cursor_pos/100-ca/100;
                if (ssr<0){
                    ssr=ssr*-1;
                }
                int ur = cursor_pos%100-ca%100;
                if (ur<0){
                    ur = ur*-1;
                }
                int uur =  ssr + ur;
                uur=4-uur;
                if(uur>4){uur=4;}

                //side bar
                if (ddt!=cursor_pos){
                    ddt=cursor_pos;
                    if (ddd==1){
                        truhp=Rhp;
                    }
                    if (ddd==2){
                        truhp=Php;
                    }
                    if (ddd==3){
                        truhp=Dhp;
                    }
                    
                    sidedraw(ddd,k,0, uur, hp2[kkk], truhp);
                }
            };
            //this is just to check
            if (input != '\0'){
                uart_puts("\ninput: ");
                printf("%c\n", input);
            }
            //pause and quit
            if (input == 'p'){
                while(1){
                    
                    intro(0);
                    input = uart_getc();
                    if (input == 'l'){
                        map = 0;
                        break;
                    }
                    if (input == 'p'){
                        break;
                    }
                }
            }
            // this is action count
            i += 1;
            if(i > 6 ){
                i=1;
            };
            //your turn ends when 3 characters done
            if (mod1==0 && mod2 ==0 && mod3==0){
                mturn=0;
            }
            //if all enemy defeated, you can advance.
            for (checkpos=0;checkpos<5;checkpos++){
                if(hp2[checkpos]==0){
                    g2[checkpos]=0;
                }
            }
            for (checkpos=0;checkpos<5;checkpos++){
                if(g2[checkpos]!=0){
                    map=2;
                    break;
                }else{map=3;}
            }
            if (Rhp==0){Roy_pos=0;}
            if (Php==0){Pris_pos=0;}
            if (Dhp==0){Drago_pos=0;}
            if (Rhp==0 && Php==0 && Dhp==0){
                map=0;
                break;
            }
        }else{
            printf("enemy turn!\n");
            int i=1;
            int sam, sun, sin;
            sin=0;
            int j,k,l;
            while (1){
                i++;
                
                
                if(i<4){
                    drawn(1, Roy_pos, Drago_pos, Pris_pos, cursor_pos, map, g2, alive);
                }else{
                    drawn(0, Roy_pos, Drago_pos, Pris_pos, cursor_pos, map, g2, alive);
                }
                if (i==6){
                    sin++;
                    i=1;
                    //AI here, make every enemy move first, can you make them move 1 by 1?
                    for (sam=0; sam<5; sam++){
                        g2[sam]=thunking(Roy_pos, Pris_pos, Drago_pos,g2,sam, map2_checc, 296);
                        //g2[sam] =(g2[sam]/10000)*10000+k; 
                        printf("%d", g2[sam]);
                    }
                    // if adjacent, attack
                }
                if (sin==5){
                    for (sam=0; sam<5; sam++){
                        j=g2[sam]%10000;
                        if(j-Roy_pos==1 || j-Roy_pos==-1 || j-Roy_pos==100 || j-Roy_pos==-100){
                            Rhp=combat(1, g2[sam]/10000, Rhp, map, 0, seed, seed2, 20);
                        }
                        if(j-Pris_pos==1 || j-Pris_pos==-1 || j-Pris_pos==100 || j-Pris_pos==-100){
                            Php=combat(2, g2[sam]/10000, Php, map, 0, seed, seed2, 20);
                        }
                        if(j-Drago_pos==1 || j-Drago_pos==-1 || j-Drago_pos==100 || j-Drago_pos==-100){
                            Dhp=combat(3, g2[sam]/10000, Dhp, map, 0, seed, seed2, 20);
                        }
                    }
                    break;
                }
            }
            mod1=1;
            mod2=1;
            mod3=1;
            mturn=1;
        }
    }

















    Roy_pos = Roypos3;
    Drago_pos = Dragopos3;
    Pris_pos = Prispos3;
    cursor_pos = Roy_pos;
    alive=111;
    mod1=1;
    mod2=1;
    mod3=1;
    mturn=1;
    Rhp=(Roy_init/1000000000000)%100;
    Php=(Pris_init/1000000000000)%100;
    Dhp=(Drago_init/1000000000000)%100;
    int g3[5]={generics3[0],generics3[1],generics3[2],generics3[3],generics3[4]};
    int hp3[5]={35,35,35,35,35};
    while (map == 3){
        int target;
        int jar=0;
        int n1=-1;
        int n2=-1;
        int n3=-1;
        int n4=-1;
        int lx;
        int ly;
        int dksf;
        int truhp;
        if (ddd==1){
            truhp=Rhp;
        }
        if (ddd==2){
            truhp=Php;
        }
        if (ddd==3){
            truhp=Dhp;
        }
        if (mturn==1){
            seed++;
            seed2++;
            seed=seed+seed2;
            if (seed>1000000000){
                seed=0;
            }
            if(seed2>10000000000){
                seed2=0;
            }
            eu=0;
            input = '\0';
            //check input
            input = uart_game_getc();
            //save last cursor(developing on progress)
            //input assigned
            lastcursortemp = cursor_pos;
            cursor_pos = inputhandler(input, cursor_pos);
            kkk=0;
            //check the last input
            if (lastcursortemp!=cursor_pos){
                lastcursor = lastcursortemp;
                lastcursortemp = cursor_pos;
            }
            //sl=3 -> fight or item
            if (sl==3){               
                action(map, ddd, cp, Roy_pos, Pris_pos, Drago_pos, 4, i,g3, lastcursor,sstg);
                if (input=='k'){
                    sl = 0;
                    sh=0;
                    cursor_pos=cp;
                    ca=0;
                    dksf=0;
                }
                int num=0;
                for (checkpos=0; checkpos<5;checkpos++){
                    if (g3[num]%10000-cp==-1){
                        n1=num;
                    }
                    if (g3[num]%10000-cp==1){
                        n2=num;
                    }
                    if (g3[num]%10000-cp==-100){
                        n3=num;
                    }
                    if (g3[num]%10000-cp==100){
                        n4=num;
                    }
                    num++;
                }
                
                if ((n1!=-1 && input =='w') || dksf==1){
                    drawRectARGB32(cp/100*36,(cp%100-1)*36, cp/100*36+36,(cp%100-1)*36+36, 0x000000ff,1);
                    dksf=1;
                    k=g3[n1]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                            truhp=Rhp;
                        }
                        if (ddd==2){
                            truhp=Php;
                        }
                        if (ddd==3){
                            truhp=Dhp;
                        }

                        sidedraw(ddd,k,0,0, hp3[n1], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g3[n1]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g3[n1]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g3[n1]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp3[n1]=combat(ddd, g3[n1]/10000, hp3[n1], 1, 1, seed, seed2, 20);
                        lx=1;
                        sl = 0;
                        sh=0;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if ((n2!=-1 && input == 's')|| dksf==2){
                    drawRectARGB32(cp/100*36,(cp%100+1)*36, cp/100*36+36,(cp%100+1)*36+36, 0x000000ff,1);
                    dksf=2;
                    k=g3[n2]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                            truhp=Rhp;
                        }
                        if (ddd==2){
                            truhp=Php;
                        }
                        if (ddd==3){
                            truhp=Dhp;
                        }
                        sidedraw(ddd,k,0,0, hp3[n2], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g3[n2]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g3[n2]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g3[n2]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp3[n2]=combat(ddd, g3[n1]/10000, hp3[n2], 1, 1, seed, seed2, 20);
                        sl = 0;
                        lx=2;
                        sh=0;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if ((n3!=-1 && input =='a')|| dksf==3){
                    drawRectARGB32((cp/100-1)*36,cp%100*36, (cp/100-1)*36+36,cp%100*36+36, 0x000000ff,1);
                    dksf=3;
                    k=g3[n3]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                            truhp=Rhp;
                        }
                        if (ddd==2){
                            truhp=Php;
                        }
                        if (ddd==3){
                            truhp=Dhp;
                        }
                        sidedraw(ddd,k,0,0, hp3[n3], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g3[n3]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g3[n3]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g3[n3]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp3[n3]=combat(ddd, g3[n1]/10000, hp3[n1], 1, 1, seed, seed2, 20);
                        sl = 0;
                        lx=3;
                        sh=0;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if ((n4!=-1 && input == 'd')|| dksf==4){
                    drawRectARGB32((cp/100+1)*36,cp%100*36, (cp/100+1)*36+36,cp%100*36+36, 0x000000ff,1);
                    dksf=4;
                    k=g3[n4]/10000;
                    if(dksf!=target){
                        if (ddd==1){
                            truhp=Rhp;
                        }
                        if (ddd==2){
                            truhp=Php;
                        }
                        if (ddd==3){
                            truhp=Dhp;
                        }
                        sidedraw(ddd,k,0,0, hp3[n4], truhp);
                    }
                    target=dksf;
                    drawStringARGB32(745 + 200,160,"hit: %",0xffffffff, combat(ddd, g3[n4]/10000, 10, 1, 1, 10,10,13));
                    drawStringARGB32(745 + 200,180,"crit: %",0xffffffff, combat(ddd, g3[n4]/10000, 10, 1, 1, 10,10,14));
                    drawStringARGB32(745 + 200,200,"dam: %",0xffffffff, combat(ddd, g3[n4]/10000, 10, 1, 1, 10,10,15));
                    if (input =='j'){
                        hp3[n4]=combat(ddd, g3[n4]/10000, hp3[n4], 1, 1, seed, seed2, 20);
                        sl = 0;
                        sh=0;
                        lx=4;
                        cursor_pos=cp;
                        ca=0;
                        dksf=0;
                    }
                }
                if(n1==-1 && n2==-1 && n3==-1 && n4==-1){sl=2;}
                if (sl==0){
                    if(ddd==1){mod1=0;Roy_pos=cp;}
                    if(ddd==2){mod2=0;Pris_pos=cp;}
                    if(ddd==3){mod3=0;Drago_pos=cp;}
                }
            }
            if (alive/100==0){
                mod3=0;
            }
            if ((alive/10)%10==0){
                mod2=0;
            }
            if (alive%10==0){
                mod1=0;
            }
            //sl=2 -> choosing action stage, in this stage, choose what to do.
            if (sl == 2){
                if (sh==0){
                    sh++;
                    cp=cursor_pos;
                }
                if (input == 'a'){
                    sstg--;
                }
                if (input == 'd'){
                    sstg++;
                }
                if (sstg<0){
                    sstg=3;
                }
                if (sstg>3){
                    sstg=0;
                }
                action(map, ddd, cp, Roy_pos, Pris_pos, Drago_pos, 4, i,g3, lastcursor,sstg);
                if (input=='k'){
                    sl = 0;
                    sh=0;
                    cursor_pos=cp;
                    ca=0;
                }
                //wait
                if(input =='j' && sstg == 0 && eu==0){
                    int jar=0;
                    sl=3;
                    if(jar==1){
                        sl=0;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod3=0;
                        jar=0;
                    }

                    eu=1;
                }
                if(input =='j' && sstg == 1 && eu==0){
                    if (ddd==2){
                        sl=0;
                        Pris_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod2=0;
                    }
                }
                if(input =='j' && sstg == 2 && eu==0){
                    int jar=0;
                    sl=3;
                    if(jar==1){
                        sl=0;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod3=0;
                        jar=0;
                    }

                    eu=1;
                }
                
                if(input =='j' && sstg == 3 && eu==0){
                    if (ddd==1){
                        sl=0;
                        Roy_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod1=0;
                    }
                    if (ddd==2){
                        sl=0;
                        Pris_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos=cp;
                        mod2=0;
                    }
                    if (ddd==3){
                        sl=0;
                        Drago_pos = cp;
                        ca=0;
                        sh=0;
                        cursor_pos = cp;
                        mod3=0;
                    }

                    eu=1;
                }
            };
            
            //sl=1 -> selected stage, in this stage, cursor carries character around
            if (sl==1){
                for(checkpos=0;checkpos<364;checkpos++){
                    if (cursor_pos==map3_checc[checkpos]){
                        apv=1;
                        break;
                    }
                }
                if(ca==0){
                    ca=cursor_pos;
                }
                for(cppt=0;cppt<41;cppt++){
                    if (cursor_pos==bluearea[cppt]+ca && cursor_pos==map3_checc[checkpos]){
                        apv=1;
                        break;
                    }else{
                        apv=0;
                    }
                }
                for(checkpos=0;checkpos<5;checkpos++){
                    if(cursor_pos==g3[checkpos]%10000){
                        apv=0;
                    }
                }
                if(cursor_pos==Roy_pos && ddd!=1){
                    apv=0;
                }
                if(cursor_pos==Pris_pos && ddd!=2){
                    apv=0;
                }
                if(cursor_pos==Drago_pos && ddd!=3){
                    apv=0;
                }
                if(apv==0){
                    cursor_pos=lastcursor;
                }
                if (abss(ca/100-cursor_pos/100)+abss(ca%100-cursor_pos%100)>4){
                    apv=0;
                }
                apv=0;
                selected(map, ddd, cursor_pos, Roy_pos, Pris_pos, Drago_pos, 4, i,g3,lastcursor, alive);
                if (input == 'j' && ddd != 0 && eu == 0){
                    sl=2;
                    eu = 1;
                }
                if (input=='k'){
                    sl = 0;
                    ca=0;
                }
            };
            //sl=0 -> idle stage, noone move in this stage
            if (sl==0){
                if (i==1||i==2||i==3){
                    drawn(0,Roy_pos, Drago_pos, Pris_pos, cursor_pos, 1, g3, alive);
                };
                if (i==4||i==5||i==6){
                    drawn(1,Roy_pos, Drago_pos, Pris_pos, cursor_pos, 1, g3, alive);
                };
                if (cursor_pos == Roy_pos){
                    dd=1;
                    if (input=='j'&& eu==0 && mod1==1){
                        sl=1;
                        ddd=1;
                    };
                }
                if (cursor_pos == Pris_pos){
                    dd=2;
                    if (input=='j'&& eu==0 && mod2==1){
                        sl=1;
                        ddd=2;
                    };
                }
                if (cursor_pos == Drago_pos ){
                    dd=3;
                    if (input=='j' && eu==0 && mod3==1){
                        sl=1;
                        eu=1;
                        ddd=3;
                    };
                }
                //this is enemy positions, we stored it in array
                for (kkk=0; kkk<5; kkk++){
                    if (cursor_pos == g3[kkk]%10000){
                        k=g3[kkk]/10000;
                        break;
                    }
                };
            }
            // side bar handle, in this tap, move cursor to specific unit to see its stats, item, description
            if (sl==0){
                if (ddt!=cursor_pos){
                    ddt=cursor_pos;
                    if (ddd==1){
                        truhp=Rhp;
                    }
                    if (ddd==2){
                        truhp=Php;
                    }
                    if (ddd==3){
                        truhp=Dhp;
                    }
                    sidedraw(dd,k,0, 4, hp3[kkk], truhp);
                }
            };
            if (sl==1){
                //calculate movement
                int ssr = cursor_pos/100-ca/100;
                if (ssr<0){
                    ssr=ssr*-1;
                }
                int ur = cursor_pos%100-ca%100;
                if (ur<0){
                    ur = ur*-1;
                }
                int uur =  ssr + ur;
                uur=4-uur;
                char uuu= (char) uur;
                if(uur>4){uur=4;}

                //side bar
                if (ddt!=cursor_pos){
                    ddt=cursor_pos;
                    if (ddd==1){
                        truhp=Rhp;
                    }
                    if (ddd==2){
                        truhp=Php;
                    }
                    if (ddd==3){
                        truhp=Dhp;
                    }
                    
                    sidedraw(ddd,k,0, uur, hp3[kkk], truhp);
                }
            };
            //this is just to check
            if (input != '\0'){
                uart_puts("\ninput: ");
                printf("%c\n", input);
            }
            //pause and quit
            if (input == 'p'){
                while(1){
                    intro(0);
                    input = uart_getc();
                    if (input == 'l'){
                        map = 0;
                        break;
                    }
                    if (input == 'p'){
                        break;
                    }
                }
            }
            
            // this is action count
            i += 1;
            if(i > 6 ){
                i=1;
            };
            //your turn ends when 3 characters done
            if (mod1==0 && mod2 ==0 && mod3==0){
                mturn=0;
            }
            //if all enemy defeated, you can advance.
            for (checkpos=0;checkpos<5;checkpos++){
                if(hp3[checkpos]==0){
                    g3[checkpos]=0;
                }
            }
            for (checkpos=0;checkpos<5;checkpos++){
                if(g3[checkpos]!=0){
                    map=3;
                    break;
                }else{
                    intro(4);
                    uart_getc();
                    break;
                }
            }
            if (Rhp==0){Roy_pos=0;}
            if (Php==0){Pris_pos=0;}
            if (Dhp==0){Drago_pos=0;}
        }else{
            printf("enemy turn!\n");
            int i=1;
            int sam, sun, sin;
            sin=0;
            int j,k,l;
            while (1){
                printf("\n1dddd\n");
                i++;
                
                
                if(i<4){
                    drawn(1, Roy_pos, Drago_pos, Pris_pos, cursor_pos, map, g3, alive);
                }else{
                    drawn(0, Roy_pos, Drago_pos, Pris_pos, cursor_pos, map, g3, alive);
                }
                if (i==6){
                    sin++;
                    i=1;
                    //AI here, make every enemy move first, can you make them move 1 by 1?
                    for (sam=0; sam<5; sam++){
                        g3[sam]=thunking(Roy_pos, Pris_pos, Drago_pos,g3,sam, map3_checc, 364);
                        //g2[sam] =(g2[sam]/10000)*10000+k; 
                        printf("%d", g2[sam]);
                    }
                    // if adjacent, attack
                }
                if (sin==5){
                    for (sam=0; sam<5; sam++){
                        j=g3[sam]%10000;
                        if(j-Roy_pos==1 || j-Roy_pos==-1 || j-Roy_pos==100 || j-Roy_pos==-100){
                            Rhp=combat(1, g3[sam]/10000, Rhp, map, 0, seed, seed2, 20);
                        }
                        if(j-Pris_pos==1 || j-Pris_pos==-1 || j-Pris_pos==100 || j-Pris_pos==-100){
                            Php=combat(2, g3[sam]/10000, Php, map, 0, seed, seed2, 20);
                        }
                        if(j-Drago_pos==1 || j-Drago_pos==-1 || j-Drago_pos==100 || j-Drago_pos==-100){
                            Dhp=combat(3, g3[sam]/10000, Dhp, map, 0, seed, seed2, 20);
                        }
                    }
                    break;
                }
            }
            mod1=1;
            mod2=1;
            mod3=1;
            mturn=1;
        }
    };
    
}