
#include "AI.h"



int thunking(int MainPo1, int MainPo2, int MainPo3, unsigned int theRest[], int Turn, unsigned int ForInfoMap[], int OrderMap)
{
    unsigned int MainCharY[3] = {MainPo1 % 100,MainPo2 % 100,MainPo3 % 100};
    unsigned int MainCharX[3] = {((MainPo1 - MainCharY[0])/100) % 100,((MainPo2 - MainCharY[1])/100) % 100,((MainPo3 - MainCharY[2])/100) % 100};
    int num = 0;
    unsigned int TheReX[5];
    unsigned int TheReY[5];
    unsigned int TheReBoth[5];
    unsigned int TheReState[5];
    while (num < 5){
        TheReY[num] = theRest[num] % 100;
        TheReX[num] = ((theRest[num] - TheReY[num])/100) % 100;
        TheReBoth[num] = theRest[num] % 10000;
        TheReState[num] = theRest[num] / 10000;
        num ++;
    }
    unsigned int MappoChecku[OrderMap];
    num = 0;
    int mapech, nummap;
    while (num < OrderMap)
    {
        mapech = 0;
        if (MainPo1 == ForInfoMap[num] || MainPo2 == ForInfoMap[num] || MainPo3 == ForInfoMap[num]){
            mapech ++;
        }
        nummap = 0;
        //while ( nummap < 5){
            //if (TheReBoth[nummap] == ForInfoMap[num]){
            //    mapech ++;
            //}
            //nummap ++;
        //}
        if(mapech == 0){
            MappoChecku[num] = ForInfoMap[num];
        }
        else{
            MappoChecku[num] = 0;
        }
        num++;
    }
    
    int CurY = TheReY[Turn];
    int CurX = TheReX[Turn];
    unsigned int Sume[3];
    unsigned int Direc[3];
    num = 0;
    int sumer = 0;
    while (num < 3){
        sumer = 0;
        if (MainCharX[num] >= CurX){
            sumer += (MainCharX[num] - CurX);
            Direc[num] = 10;
        }
        else{
            sumer += (CurX - MainCharX[num]);
            Direc[num] = 0;
        }
        if (MainCharY[num] >= CurY){
            sumer += (MainCharY[num] - CurY);
            Direc[num] = Direc[num] + 1;
        }
        else{
            sumer += (CurY - MainCharY[num]);
            Direc[num] = Direc[num] + 0;
        }
        Sume[num] = sumer;
        num++;
    }
    int FlX, FlY;
    if (Sume[0] <= Sume[1] && Sume[0] <= Sume[2]){
        num = 0;
    }
    else if(Sume[1] <= Sume[0] && Sume[1] <= Sume[2]){
        num = 1;
    }
    else{
        num = 2;
    }
    //num = 0;
    FlX = MainCharX[num];
    FlY = MainCharY[num];
    int FlBoth = (FlX*100) + FlY;
    int Ways = Direc[num];
    num = 0;
    int num2 = 0;
    int cal = 0;
    int resu;
    unsigned int AroPo[8] = {0,0,0,0,0,0,0,0};
    unsigned int pocal[3] = {0,1,2};
    while (num < 3){
        num2 = 0;
        while (num2 < 3){
            if (!(pocal[num2] == 0 && pocal[num] == 0)){
                resu = 0;
                if (pocal[num] == 1){
                    resu += ((FlX - 1)*100);
                }
                else if(pocal[num] == 2){
                    resu += ((FlX + 1)*100);
                }
                else{
                    resu += ((FlX)*100);
                }
                if (pocal[num2] == 1){
                    resu += ((FlY - 1));
                }
                else if(pocal[num2] == 2){
                    resu += ((FlY + 1));
                }
                else{
                    resu += ((FlY));
                }
                AroPo[cal] = resu;
                cal ++;
            }
            
            num2 ++;
        }
        num ++;
    }
    num = 0;
    mapech = 0;
    int mapbepo;
    while (num < OrderMap)
    {
        nummap = 0;
        while (nummap < 8){
            if (MappoChecku[num] == AroPo[nummap]){
                num2 = 0;
                if (AroPo[nummap]/100 >= CurX){
                    num2 += ((AroPo[nummap]/100) - CurX);
                }
                else{
                    num2 += (CurX - (AroPo[nummap]/100));
                }
                if (AroPo[nummap]%100 >= CurY){
                    num2 += ((AroPo[nummap]%100) - CurY);
                }
                else{
                    num2 += (CurY - (AroPo[nummap]%100));
                }
                if (mapech == 0){
                    mapech = AroPo[nummap];
                    num2 = 0;
                    if (mapech/100 >= CurX){
                        num2 += ((mapech/100) - CurX);
                    }
                    else{
                        num2 += (CurX - (mapech/100));
                    }
                    if (mapech%100 >= CurY){
                        num2 += ((mapech%100) - CurY);
                    }
                    else{
                        num2 += (CurY - (mapech%100));
                    }
                    mapbepo = num2;
                }
                else if(mapbepo > num2){
                    mapech = AroPo[nummap];
                    num2 = 0;
                    if (mapech/100 >= CurX){
                        num2 += ((mapech/100) - CurX);
                    }
                    else{
                        num2 += (CurX - (mapech/100));
                    }
                    if (mapech%100 >= CurY){
                        num2 += ((mapech%100) - CurY);
                    }
                    else{
                        num2 += (CurY - (mapech%100));
                    }
                    mapbepo = num2;
                }
            }
            nummap ++;
        }
        num++;
    }
    FlX = mapech / 100;
    FlY = mapech % 100;
    FlBoth = mapech;
    if (FlX >= CurX){
        Ways = 10;
    }
    else{
        Ways = 0;
    }
    if (FlY >= CurY){
        Ways = Ways + 1;
    }
    else{
        Ways = Ways + 0;
    }
    num = 0;
    cal = 0;
    resu = 0;
    int checke2 = 0;
    unsigned int fiste[5] = {0,0,0,0,0};
    while (num < OrderMap){
        num2 = 1;
        while (num2 < 5){
            checke2 = 0;
            if (Ways > 2){
                cal = (CurX + num2)*100;
                if((CurX + num2) > FlX){
                    checke2 = 1;
                }
            }
            else{
                cal = (CurX - num2)*100;
                if((CurX - num2) < FlX){
                    checke2 = 1;
                }
            }
            cal += (CurY);
            if (checke2 == 0 && MappoChecku[num] == cal){
                fiste[num2-1] = cal;
            }
            num2 ++;
        }
        num ++;
    }
    num = 0;
    num2 = 0;
    int num3 = 0;
    int Donne = 0;
    while(num < 4){
        if (num == num2 && fiste[num] != 0){
            num2++;
            if (fiste[num] == FlBoth){
                Donne = 1;
            }
        }
        num++;
    }
    if (Ways > 2){
        num3 = FlX - CurX;
    }
    else{
        num3 = CurX - FlX;
    }
    int resuFi = fiste[0];
    int resure;
    if (num2 < 3 && Donne == 0 && (num2 != num3 || num3 == 0 || (num2 == num3 && (CurY - FlY) != 0))){
        num = 0;
        resu = 0;
        int cal2, resu2;
        unsigned int fiste[5] = {0,0,0,0,0};
        unsigned int fiste2[5] = {0,0,0,0,0};
        unsigned int reco[5] = {0,0,0,0,0};
        unsigned int reco2[5] = {0,0,0,0,0};
        num3 = 0;
        int num4;
        int Lage1 = 0;
        int Lage2 = 0;
        int LageCo1 = 0;
        int LageCo2 = 0;
        int chema1 = 0;
        int chema2 = 0;
        while (num < OrderMap){
            num2 = 1;
            while (num2 < 5){
                cal = (CurX)*100;
                cal += (CurY + num2);         
                if ( MappoChecku[num] == cal){
                    fiste[num2-1] = cal;
                    num3 = 0;
                    unsigned int checke[5] = {0,0,0,0,0};
                    while(num3 < OrderMap){
                        num4 = 1;
                        while (num4 < 5){
                            if (Ways > 2){
                                cal2 = (CurX+num4)*100;
                            }
                            else{
                                cal2 = (CurX-num4)*100;
                            }
                            cal2 += (CurY + num2);
                            if ( MappoChecku[num3] == cal2){
                                reco[num2-1] = 1;
                                checke[num4-1] = 1;
                            }
                            num4++;
                        }
                        num3 ++;    
                    }
                    num3 = 0;
                    num4 = 0;
                    while(num3 < 4){
                        if (num3 == num4 && checke[num3] != 0){
                            num4++;
                        }
                        num3 ++;
                    }
                    if (Lage1 < num4)
                    {
                        Lage1 = num4;
                        LageCo1 = num2;
                    }
                         
                }
                num2 ++;
            }
            num2 = 1;
            while (num2 < 5){
                cal = (CurX)*100;
                cal += (CurY - num2);             
                if ( MappoChecku[num] == cal){
                    fiste2[num2-1] = cal;
                    num3 = 0;
                    unsigned int checke[5] = {0,0,0,0,0};
                    while(num3 < OrderMap){
                        num4 = 1;
                        while (num4 < 5){
                            if (Ways > 2){
                                cal2 = (CurX+num4)*100;
                            }
                            else{
                                cal2 = (CurX-num4)*100;
                            }
                            cal2 += (CurY + num2);
                            if ( MappoChecku[num3] == cal2){
                                reco2[num2-1] = 1;
                                checke[num4-1] = 1;
                            }
                            num4++;
                        }
                        num3 ++;    
                    }
                    num3 = 0;
                    num4 = 0;
                    while(num3 < 4){
                        if (num3 == num4 && checke[num3] != 0){
                            num4++;
                        }
                        num3 ++;
                    }
                    if (Lage2 < num4)
                    {
                        Lage2 = num4;
                        LageCo2 = num2;
                    }     
                }
                num2 ++;
            }
            num ++;
        }
        num = 0;
        num2 = 0;
        num3 = 0;
        while (num < 4){
            if (FlBoth == fiste[num]){
                chema1 = 1;
            }
            if (num == num2 && reco[num] == 1){               
                num2 ++;
                if (FlBoth == fiste[num]){
                    chema1 = 1;
                }
            }
            
            if (num == num3 && reco2[num] == 1){
                num3 ++;
                if (FlBoth == fiste2[num]){
                    chema2 = 1;
                }
            }
            num ++;
        }
        if ((Ways%10) == 1){
                cal = FlY - (fiste[0]%100);
                cal2 = FlY - (fiste2[0]%100);
        }
        else{
                cal = (fiste[0]%100) - FlY;
                cal2 = (fiste2[0]%100) - FlY;
        }
        if (resuFi != 0 && num2 < 2 && num3 < 2) {
            resure = resuFi;
        }
        else {
            if (fiste[0] != 0 && chema2 == 0 && (chema1 == 1 || (((cal2 != 0 || LageCo2 > num3)&& (cal < cal2 || num2 >= num3 || Lage1 >= Lage2)) || fiste2[0] == 0))){
                resure = fiste[0];
            }
            else{
                resure = fiste2[0];
            }
        }
    }
    else{
        resure = resuFi;
    }
    if (resure == 0){
        return theRest[Turn];
    }
    else{
        return (TheReState[Turn] * 10000)+ resure;
    }
}
                