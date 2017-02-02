////////////////////////////////////////
//
//	File : ai.c
//	CoSpace Robot
//	Version 1.0.0
//	Jan 1 2016
//	Copyright (C) 2016 CoSpace Robot. All Rights Reserved
//
//////////////////////////////////////
//
// ONLY C Code can be compiled.
//
/////////////////////////////////////

#define CsBot_AI_H//DO NOT delete this line
#ifndef CSBOT_REAL
#include <windows.h>
#include <stdio.h>
#include <math.h>
#define DLL_EXPORT extern __declspec(dllexport)
#define false 0
#define true 1
#endif//The robot ID : It must be two char, such as '00','kl' or 'Cr'.
char AI_MyID[2] = {'0','2'};

int Duration = 0;
int SuperDuration = 0;
int bGameEnd = false;
int CurAction = -1;
int CurGame = 0;
int SuperObj_Num = 0;
int SuperObj_X = 0;
int SuperObj_Y = 0;
int Teleport = 0;
int LoadedObjects = 0;
int red_number = 0;
int black_number = 0;
int green_number = 0;
int all_number = 0;
int bool_doubleE = 0;
int zz_bool_now = 0;
int zz_bool_old = 0;
int jinru = 0;
int jinru_1 = 0;
int sup_x = 0;
int sup_y = 0;
int bool_cunbao = 0;
int US_Front = 0;
int US_Left = 0;
int US_Right = 0;
int CSLeft_R = 0;
int CSLeft_G = 0;
int CSLeft_B = 0;
int CSRight_R = 0;
int CSRight_G = 0;
int CSRight_B = 0;
int PositionX = 0;
int PositionY = 0;
int TM_State = 0;
int Compass = 0;
int Time = 0;
int WheelLeft = 0;
int WheelRight = 0;
int LED_1 = 0;
int MyState = 0;
int AI_SensorNum = 13;

#define CsBot_AI_C//DO NOT delete this line

DLL_EXPORT void SetGameID(int GameID)
{
    CurGame = GameID;
    bGameEnd = 0;
}

DLL_EXPORT int GetGameID()
{
    return CurGame;
}

//Only Used by CsBot Dance Platform
DLL_EXPORT int IsGameEnd()
{
    return bGameEnd;
}

#ifndef CSBOT_REAL

DLL_EXPORT char* GetDebugInfo()
{
    char info[1024];
    sprintf(info, "Duration=%d;SuperDuration=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SuperObj_Num=%d;SuperObj_X=%d;SuperObj_Y=%d;Teleport=%d;LoadedObjects=%d;red_number=%d;black_number=%d;green_number=%d;all_number=%d;bool_doubleE=%d;zz_bool_now=%d;zz_bool_old=%d;jinru=%d;jinru_1=%d;sup_x=%d;sup_y=%d;bool_cunbao=%d;US_Front=%d;US_Left=%d;US_Right=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PositionX=%d;PositionY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;",Duration,SuperDuration,bGameEnd,CurAction,CurGame,SuperObj_Num,SuperObj_X,SuperObj_Y,Teleport,LoadedObjects,red_number,black_number,green_number,all_number,bool_doubleE,zz_bool_now,zz_bool_old,jinru,jinru_1,sup_x,sup_y,bool_cunbao,US_Front,US_Left,US_Right,CSLeft_R,CSLeft_G,CSLeft_B,CSRight_R,CSRight_G,CSRight_B,PositionX,PositionY,TM_State,Compass,Time,WheelLeft,WheelRight,LED_1,MyState);
    return info;
}
 
DLL_EXPORT char* GetTeamName()
{
     return "aoliao";
}

DLL_EXPORT int GetCurAction()
{
    return CurAction;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT int GetTeleport()
{
    return Teleport;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT void SetSuperObj(int X, int Y, int num)
{
    SuperObj_X = X;
    SuperObj_Y = Y;
    SuperObj_Num = num;
}
//Only Used by CsBot Rescue Platform
DLL_EXPORT void GetSuperObj(int *X, int *Y, int *num)
{
    *X = SuperObj_X;
    *Y = SuperObj_Y;
    *num = SuperObj_Num;
}

#endif CSBOT_REAL

DLL_EXPORT void SetDataAI(volatile int* packet, volatile int *AI_IN)
{

    int sum = 0;

    US_Front = AI_IN[0]; packet[0] = US_Front; sum += US_Front;
    US_Left = AI_IN[1]; packet[1] = US_Left; sum += US_Left;
    US_Right = AI_IN[2]; packet[2] = US_Right; sum += US_Right;
    CSLeft_R = AI_IN[3]; packet[3] = CSLeft_R; sum += CSLeft_R;
    CSLeft_G = AI_IN[4]; packet[4] = CSLeft_G; sum += CSLeft_G;
    CSLeft_B = AI_IN[5]; packet[5] = CSLeft_B; sum += CSLeft_B;
    CSRight_R = AI_IN[6]; packet[6] = CSRight_R; sum += CSRight_R;
    CSRight_G = AI_IN[7]; packet[7] = CSRight_G; sum += CSRight_G;
    CSRight_B = AI_IN[8]; packet[8] = CSRight_B; sum += CSRight_B;
    PositionX = AI_IN[9]; packet[9] = PositionX; sum += PositionX;
    PositionY = AI_IN[10]; packet[10] = PositionY; sum += PositionY;
    TM_State = AI_IN[11]; packet[11] = TM_State; sum += TM_State;
    Compass = AI_IN[12]; packet[12] = Compass; sum += Compass;
    Time = AI_IN[13]; packet[13] = Time; sum += Time;
    packet[14] = sum;

}
DLL_EXPORT void GetCommand(int *AI_OUT)
{
    AI_OUT[0] = WheelLeft;
    AI_OUT[1] = WheelRight;
    AI_OUT[2] = LED_1;
    AI_OUT[3] = MyState;
}
void Game0()
{

    if(SuperDuration>0)
    {
        SuperDuration--;
    }
    else if(Duration>0)
    {
        Duration--;
    }
    else if(Time>=180 && Time<=1000)
    {
        Duration = 0;
        CurAction =1;
    }
    else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=200 && CSLeft_G<=255 && CSLeft_B>=40 && CSLeft_B<=80 && CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=200 && CSRight_G<=255 && CSRight_B>=40 && CSRight_B<=80)
    {
        Duration = 0;
        CurAction =2;
    }
    else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=200 && CSLeft_G<=255 && CSLeft_B>=40 && CSLeft_B<=80)
    {
        Duration = 0;
        CurAction =3;
    }
    else if(CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=200 && CSRight_G<=255 && CSRight_B>=40 && CSRight_B<=80)
    {
        Duration = 0;
        CurAction =4;
    }
    else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=200 && CSLeft_G<=255 && CSLeft_B>=0 && CSLeft_B<=20 && CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=200 && CSRight_G<=255 && CSRight_B>=0 && CSRight_B<=20&&((all_number>0)))
    {
        Duration = 0;
        CurAction =5;
    }
    else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=200 && CSLeft_G<=255 && CSLeft_B>=0 && CSLeft_B<=20&&((all_number>0)))
    {
        Duration = 0;
        CurAction =6;
    }
    else if(CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=200 && CSRight_G<=255 && CSRight_B>=0 && CSRight_B<=20&&((all_number>0)))
    {
        Duration = 1;
        CurAction =7;
    }
    else if(((CSRight_B<=255&&CSRight_B>200&&CSRight_R<=80&&CSRight_G<=120&&CSRight_G>80&&CSRight_R>20)
||(CSLeft_B<=255&&CSLeft_B>200&&CSLeft_G>80&&CSLeft_G<=120&&CSLeft_R<80&&CSLeft_R>20))&&(all_number<6&&all_number>0))
    {
        Duration = 0;
        CurAction =8;
    }
    else if((CSLeft_B<20&&CSLeft_B>=0&&CSLeft_G>70&&CSLeft_G<110&&CSLeft_R<250&&CSLeft_R>200)&&!((CSRight_B<20&&CSRight_B>=0&&CSRight_R<=255&&CSRight_G<110&&CSRight_G>70&&CSRight_R>200))
&&all_number>=3)
    {
        Duration = 0;
        CurAction =9;
    }
    else if((CSRight_B<20&&CSRight_B>=0&&CSRight_R<=255&&CSRight_G<110&&CSRight_G>70&&CSRight_R>200)&&!(CSLeft_B<20&&CSLeft_B>=0&&CSLeft_G>70&&CSLeft_G<110&&CSLeft_R<250&&CSLeft_R>200)
&&all_number>=3)
    {
        Duration = 0;
        CurAction =10;
    }
    else if(((CSRight_B<20&&CSRight_B>=0&&CSRight_R<=255&&CSRight_G<110&&CSRight_G>70&&CSRight_R>200)&&(CSLeft_B<20&&CSLeft_B>=0&&CSLeft_G>70&&CSLeft_G<110&&CSLeft_R<=255&&CSLeft_R>200)&&(all_number>=4))||(Time>180&&all_number>2)

)
    {
        Duration = 59;
        CurAction =11;
    }
    else if(US_Front>=0 && US_Front<=15)
    {
        Duration = 1;
        CurAction =12;
    }
    else if(US_Front>=0 && US_Front<=15 && US_Right>=0 && US_Right<=15)
    {
        Duration = 1;
        CurAction =13;
    }
    else if(US_Front>=0 && US_Front<=15 && US_Left>=0 && US_Left<=15 && US_Right>=0 && US_Right<=15)
    {
        Duration = 1;
        CurAction =14;
    }
    else if(US_Front>=0 && US_Front<=15 && US_Left>=0 && US_Left<=15)
    {
        Duration = 1;
        CurAction =15;
    }
    else if(CSLeft_R>=0 && CSLeft_R<=10 && CSLeft_G>=140 && CSLeft_G<=180 && CSLeft_B>=240 && CSLeft_B<=255&&((CSRight_B<=255&&CSRight_B>240&&CSRight_R<10&&CSRight_G<180&&CSRight_G>=140&&CSRight_R>=0)))
    {
        Duration = 0;
        CurAction =16;
    }
    else if(((CSRight_B<50&&CSRight_B>20&&CSRight_R<=50&&CSRight_G<=255&&CSRight_G>240&&CSRight_R>20)
||(CSLeft_B<50&&CSLeft_B>20&&CSLeft_G>240&&CSLeft_G<=255&&CSLeft_R<50&&CSLeft_R>20))&&all_number<6/*&&green_number<2*/)
    {
        Duration = 49;
        CurAction =17;
    }
    else if(((CSRight_B<50&&CSRight_B>0&&CSRight_R<=255&&CSRight_G<50&&CSRight_G>0&&CSRight_R>200)||(CSLeft_B<50&&CSLeft_B>20&&CSLeft_G>0&&CSLeft_G<50&&CSLeft_R<=255&&CSLeft_R>200))
&&(all_number<6)&&(/*red_number<2&&*/bool_doubleE==1))
    {
        Duration = 49;
        CurAction =18;
    }
    else if(((CSRight_B<50&&CSRight_B>20&&CSRight_R<50&&CSLeft_R>20&&CSRight_G<50&&CSRight_G>20)||(CSLeft_B<50&&CSLeft_B>20&&CSLeft_G>20&&CSLeft_G<50&&CSLeft_R<50&&CSLeft_R>20))&&all_number<6/*&&black_number<4*/

)
    {
        Duration = 49;
        CurAction =19;
    }
    else if(US_Left>=0 && US_Left<=8)
    {
        Duration = 0;
        CurAction =20;
    }
    else if(US_Right>=0 && US_Right<=10)
    {
        Duration = 0;
        CurAction =21;
    }
    else if(true)
    {
        Duration = 0;
        CurAction =22;
    }
    switch(CurAction)
    {
        case 1:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            all_number=0;
                    
red_number=0;
                    
black_number=0;
                    
green_number=0;
                    
LoadedObjects=0;
                    
             Teleport =1;  
            LoadedObjects = 0;
            WheelLeft = 0;  WheelRight = 0;  LED_1=0;
            Duration = 0;   SuperDuration = 0;
            break;
        case 2:
            WheelLeft=-1;
            WheelRight=-4;
            LED_1=0;
            MyState=0;
            /*if((Compass>=0&&Compass<90)||(Compass>=270&&Compass<360)||(Compass>=90&&Compass<=180)||(Compass>180&&Compass<270))
{
     WheelLeft=-5;
                    
     WheelRight=-2;
                    
}
else
{
    WheelLeft=-2;
                    
    WheelRight=-5;
                    
}*/
            break;
        case 3:
            WheelLeft=3;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            if(Duration<=1)
{
if((Compass<360&&Compass>=335)||(Compass<90&&Compass>=65)||(Compass<270&&Compass>=245)||(Compass>=155&&Compass<180))
{ WheelLeft=4;
                    
  WheelRight=0;
                    
}else if((Compass<65&&Compass>=25)||(Compass<155&&Compass>=115)||(Compass<245&&Compass>=205)&&(Compass>=295&&Compass<335))
{
  WheelLeft=4;
                    
  WheelRight=1;
                    
}
else
{ 
   WheelLeft=3;
                    
   WheelRight=1;
                    
}
} 
            break;
        case 4:
            WheelLeft=1;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            
if(Duration<=1)
{
if((Compass>270&&Compass<=295)||(Compass>0&&Compass<=25)||(Compass>180&&Compass<=205)||(Compass<=115&&Compass>90))
{
  WheelLeft=0;
                    
  WheelRight=4;
                    
}
else if((Compass>25&&Compass<=65)||(Compass>115&&Compass<=155)||(Compass>205&&Compass<=245)||(Compass<=335&&Compass>295))
{
  WheelLeft=1;
                    
  WheelRight=4;
                    
}
else
{ 
   WheelLeft=1;
                    
   WheelRight=3;
                    
}
}
            break;
        case 5:
            WheelLeft=-1;
            WheelRight=-4;
            LED_1=0;
            MyState=0;
            /*if((Compass>0&&Compass<90)||(Compass>180&&Compass<270))
{
     WheelLeft=-2;
                    
     WheelRight=-5;
                    
}
else
{
    WheelLeft=-5;
                    
    WheelRight=-2;
                    
}*/
            break;
        case 6:
            WheelLeft=3;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            if(Duration<=1)
{
if((Compass<360&&Compass>=335)||(Compass<90&&Compass>=65)||(Compass<270&&Compass>=245)||(Compass>=155&&Compass<180))
{ WheelLeft=4;
                    
  WheelRight=0;
                    
}else if((Compass<65&&Compass>=25)||(Compass<155&&Compass>=115)||(Compass<245&&Compass>=205)&&(Compass>=295&&Compass<335))
{
  WheelLeft=4;
                    
  WheelRight=1;
                    
}
else
{ 
   WheelLeft=3;
                    
   WheelRight=1;
                    
}
} 
            break;
        case 7:
            WheelLeft=1;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            
if(Duration<=1)
{
if((Compass>270&&Compass<=295)||(Compass>0&&Compass<=25)||(Compass>180&&Compass<=205)||(Compass<=115&&Compass>90))
{
  WheelLeft=0;
                    
  WheelRight=4;
                    
}
else if((Compass>25&&Compass<=65)||(Compass>115&&Compass<=155)||(Compass>205&&Compass<=245)||(Compass<=335&&Compass>295))
{
  WheelLeft=1;
                    
  WheelRight=4;
                    
}
else
{ 
   WheelLeft=1;
                    
   WheelRight=3;
                    
}
}

            break;
        case 8:
            WheelLeft=-2;
            WheelRight=-2;
            LED_1=0;
            MyState=0;
            all_number=0;
                    
green_number=0;
                    
red_number=0;
                    
black_number=0;
                    
            break;
        case 9:
            WheelLeft=1;
            WheelRight=4;
            LED_1=0;
            MyState=0;
            break;
        case 10:
            WheelLeft=4;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            break;
        case 11:
            WheelLeft=0;
            WheelRight=0;
            LED_1=2;
            MyState=0;
            if(Duration<1)
{
   green_number=0;
                    
   black_number=0;
                    
   red_number=0;
                    
   all_number=0;
                    
   WheelLeft=-2;
                    
   WheelRight=-5;
                    
   if(Time>180)
   {
     bool_cunbao=1;
                    
   }
}
            if(Duration == 1) {LoadedObjects = 0; } 
            break;
        case 12:
            WheelLeft=-4;
            WheelRight=-4;
            LED_1=0;
            MyState=0;
            if(Duration<=2)
{
    if(US_Front<10)
   {
   WheelLeft=-3;
                    
   WheelRight=-3;
                    
   }
   else
   {
      if(US_Left>US_Right)
      {
        WheelLeft=0;
                    
        WheelRight=3;
                    
       }
       else
       {
        WheelLeft=3;
                    
        WheelRight=0;
                    
        }
    }
 }/*
}
if(Duration<=1)
{
{
if(US_Left>US_Right)
{
  WheelLeft=0;
                    
  WheelRight=3;
                    
}
else
{
  WheelLeft=3;
                    
  WheelRight=0;
                    
}
}
}*/
            break;
        case 13:
            WheelLeft=-4;
            WheelRight=-4;
            LED_1=0;
            MyState=0;
            if(Duration<=2){
if(US_Front<=10&&US_Right<=10)
{
   WheelLeft=-3;
                    
   WheelRight=-3;
                    
}
else
{
   WheelLeft=0;
                    
   WheelRight=3;
                    
}
}
            break;
        case 14:
            WheelLeft=-3;
            WheelRight=-3;
            LED_1=0;
            MyState=0;
            
if(Duration<=1)
{
if(US_Left>US_Right)
{
  WheelLeft=1;
                    
  WheelRight=4;
                    
}
else
{
  WheelLeft=4;
                    
  WheelRight=1;
                    
}
}
else{
  WheelLeft=-3;
                    
  WheelRight=-3;
                    
}
            break;
        case 15:
            WheelLeft=-4;
            WheelRight=-4;
            LED_1=0;
            MyState=0;
            if(Duration<=2){
if(US_Front<=10&&US_Left<=10)
{
   WheelLeft=-3;
                    
   WheelRight=-3;
                    
}
else
{
   WheelLeft=3;
                    
   WheelRight=0;
                    
}
}
            break;
        case 16:
            WheelLeft=2;
            WheelRight=2;
            LED_1=0;
            MyState=0;
            {if(Duration<=1)
{
  bool_doubleE=1;
                    
}}
            break;
        case 17:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration==1)
{
all_number++;
                    
green_number++;
                    
WheelLeft=0;
                    
WheelRight=0;
                    
LED_1=1;
                    
}

            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 18:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration==1)
{
all_number++;
                    
red_number++;
                    
WheelLeft=0;
                    
WheelRight=0;
                    
LED_1=1;
                    
}



            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 19:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            
if(Duration==1)
{
all_number++;
                    
black_number++;
                    
WheelLeft=0;
                    
WheelRight=0;
                    
LED_1=1;
                    
}

            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 20:
            WheelLeft=3;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            break;
        case 21:
            WheelLeft=1;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            break;
        case 22:
            WheelLeft=3;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            {
if(Time<60)
{
   WheelLeft=2;
                    
   WheelRight=2;
                    
}
bool_doubleE=0;
                    
}
            break;
        default:
            break;
    }

}

void Game1()
{

    if(SuperDuration>0)
    {
        SuperDuration--;
    }
    else if(Duration>0)
    {
        Duration--;
    }
    else if(PositionX>=20 && PositionX<=340 && PositionY>=20 && PositionY<=250&&((all_number==6&&!(US_Front<=15)&&!((US_Front<15)&&(US_Left<=15||US_Right<=15))&&!((CSRight_B<20&&CSRight_B>=0&&CSRight_R<=255&&CSRight_G<110&&CSRight_G>70&&CSRight_R>200)||(CSLeft_B<20&&CSLeft_B>=0&&CSLeft_G>70&&CSLeft_G<110&&CSLeft_R<=255&&CSLeft_R>200))&&!((CSLeft_B<=20&&CSLeft_B>=0&&CSLeft_G>=200&&CSLeft_G<=255&&CSLeft_R>=200&&CSLeft_R<=255)||(CSRight_B<=20&&CSRight_B>=0&&CSRight_G<=255&&CSRight_G>=200&&CSRight_R>=200&&CSRight_R<=255))&&!((CSLeft_B<=210&&CSLeft_B>=160&&CSLeft_G>=120&&CSLeft_G<=180&&CSLeft_R>=120&&CSLeft_R<=170)||(CSRight_B<=210&&CSRight_B>=160&&CSRight_G<=180&&CSRight_G>=120&&CSRight_R>=120&&CSRight_R<=170)))||(Time>440&&all_number>2)||(red_number>0&&black_number>0&&green_number>0)
))
    {
        Duration = 0;
        CurAction =1;
    }
    else if(CSLeft_R>=120 && CSLeft_R<=170 && CSLeft_G>=120 && CSLeft_G<=180 && CSLeft_B>=160 && CSLeft_B<=210 && CSRight_R>=120 && CSRight_R<=170 && CSRight_G>=120 && CSRight_G<=180 && CSRight_B>=160 && CSRight_B<=210 && Time>=920 && Time<=1000&&((PositionY>24&&PositionY<244)&&!(US_Front<=15)&&!((US_Front<15)&&(US_Left<=15||US_Right<=15))&&!((CSRight_B<20&&CSRight_B>=0&&CSRight_R<=255&&CSRight_G<110&&CSRight_G>70&&CSRight_R>200)||(CSLeft_B<20&&CSLeft_B>=0&&CSLeft_G>70&&CSLeft_G<110&&CSLeft_R<=255&&CSLeft_R>200))&&!((CSLeft_B<=20&&CSLeft_B>=0&&CSLeft_G>=200&&CSLeft_G<=255&&CSLeft_R>=200&&CSLeft_R<=255)||(CSRight_B<=20&&CSRight_B>=0&&CSRight_G<=255&&CSRight_G>=200&&CSRight_R>=200&&CSRight_R<=255))&&!((CSLeft_B<=50&&CSLeft_B>=0&&CSLeft_G>=0&&CSLeft_G<=50&&CSLeft_R>=0&&CSLeft_R<=50)||(CSRight_B<=50&&CSRight_B>=0&&CSRight_G<=50&&CSRight_G>=0&&CSRight_R>=0&&CSRight_R<=50))&&!((CSLeft_B<=50&&CSLeft_B>=0&&CSLeft_G>=0&&CSLeft_G<=50&&CSLeft_R>=200&&CSLeft_R<=255)||(CSRight_B<=50&&CSRight_B>=0&&CSRight_G<=50&&CSRight_G>=0&&CSRight_R>=200&&CSRight_R<=255))&&!((CSLeft_B<=50&&CSLeft_B>=0&&CSLeft_G>=230&&CSLeft_G<=255&&CSLeft_R>=0&&CSLeft_R<=50)||(CSRight_B<=50&&CSRight_B>=0&&CSRight_G<=255&&CSRight_G>=230&&CSRight_R>=0&&CSRight_R<=50))&&zz_bool_old==1&&zz_bool_now==1))
    {
        Duration = 0;
        CurAction =2;
    }
    else if((CSLeft_B<20&&CSLeft_B>=0&&CSLeft_G>70&&CSLeft_G<110&&CSLeft_R<250&&CSLeft_R>200)&&!((CSRight_B<20&&CSRight_B>=0&&CSRight_R<=255&&CSRight_G<110&&CSRight_G>70&&CSRight_R>200))
&&all_number>=3)
    {
        Duration = 0;
        CurAction =3;
    }
    else if((CSRight_B<20&&CSRight_B>=0&&CSRight_R<=255&&CSRight_G<110&&CSRight_G>70&&CSRight_R>200)&&!(CSLeft_B<20&&CSLeft_B>=0&&CSLeft_G>70&&CSLeft_G<110&&CSLeft_R<250&&CSLeft_R>200)
&&all_number>=3)
    {
        Duration = 0;
        CurAction =4;
    }
    else if((CSRight_B<20&&CSRight_B>=0&&CSRight_R<=255&&CSRight_G<110&&CSRight_G>70&&CSRight_R>200)&&(CSLeft_B<20&&CSLeft_B>=0&&CSLeft_G>70&&CSLeft_G<110&&CSLeft_R<=255&&CSLeft_R>200)&&((all_number>=4||(Time>440&&all_number>2))||(red_number>0&&green_number>0&&black_number>0)))
    {
        Duration = 59;
        CurAction =5;
    }
    else if(PositionX>=25 && PositionX<=335 && PositionY>=244 && PositionY<=270&&(((Compass>=0&&Compass<90)||(Compass<=360&&Compass>270))))
    {
        Duration = 0;
        CurAction =6;
    }
    else if(PositionX>=26 && PositionX<=335 && PositionY>=1 && PositionY<=30 && Compass>=90 && Compass<=270)
    {
        Duration = 0;
        CurAction =7;
    }
    else if(PositionX>=1 && PositionX<=20 && PositionY>=25 && PositionY<=245 && Compass>=0 && Compass<=180)
    {
        Duration = 0;
        CurAction =8;
    }
    else if(PositionX>=340 && PositionX<=360 && PositionY>=26 && PositionY<=245 && Compass>=180 && Compass<=360)
    {
        Duration = 0;
        CurAction =9;
    }
    else if(PositionX>=336 && PositionX<=360 && PositionY>=1 && PositionY<=25)
    {
        Duration = 1;
        CurAction =10;
    }
    else if(PositionX>=1 && PositionX<=24 && PositionY>=1 && PositionY<=24)
    {
        Duration = 1;
        CurAction =11;
    }
    else if(PositionX>=336 && PositionX<=360 && PositionY>=246 && PositionY<=270)
    {
        Duration = 1;
        CurAction =12;
    }
    else if(PositionX>=1 && PositionX<=24 && PositionY>=246 && PositionY<=270)
    {
        Duration = 1;
        CurAction =13;
    }
    else if(SuperObj_Num!=0)
    {
        Duration = 0;
        CurAction =14;
    }
    else if(sup_x!=0&&sup_y!=0&&(PositionX>=(sup_x+5)||PositionX<=(sup_x-5))&&(PositionY>10&&PositionY<260&&PositionX>10&&PositionX<350)/*&&!(US_Front<=15)&&!((US_Front<15)&&(US_Left<=15||US_Right<=15))*/&&!((CSLeft_B>=200&&CSLeft_B<=255&&CSLeft_G>=0&&CSLeft_G<=50&&CSLeft_R>=200&&CSLeft_R<=255)||(CSRight_B>=200&&CSRight_B<=255&&CSRight_G>=0&&CSRight_G<=50&&CSRight_R>=200&&CSRight_R<=255))/*&&!((CSLeft_B>=160&&CSLeft_B<=210&&CSLeft_G>=120&&CSLeft_G<=180&&CSLeft_R>=160&&CSLeft_R<=210)||(CSRight_B<=210&&CSRight_B>=160&&CSRight_G>=120&&CSRight_G<=180&&CSRight_R>=120&&CSRight_R<=170))*/&&(Time<460)
)
    {
        Duration = 0;
        CurAction =15;
        if((PositionY>10&&PositionY<260&&PositionX>10&&PositionX<350)&&(US_Front<=15)&&((US_Front<15)&&(US_Left<=15||US_Right<=15)))
        {
            Duration = 0;
            CurAction =16;
        }
    }
    else if(sup_x!=0&&sup_y!=0&&((PositionY>=(sup_y+5))||(PositionY<=(sup_y-5)))&&(PositionY>10&&PositionY<260&&PositionX>10&&PositionX<350)/*&&!(US_Front<=15)&&!((US_Front<15)&&(US_Left<=15||US_Right<=15))*/&&!((CSLeft_B>=200&&CSLeft_B<=255&&CSLeft_G>=0&&CSLeft_G<=50&&CSLeft_R>=200&&CSLeft_R<=255)||(CSRight_B>=200&&CSRight_B<=255&&CSRight_G>=0&&CSRight_G<=50&&CSRight_R>=200&&CSRight_R<=255))/*&&!((CSLeft_B>=160&&CSLeft_B<=210&&CSLeft_G>=120&&CSLeft_G<=180&&CSLeft_R>=160&&CSLeft_R<=210)||(CSRight_B<=210&&CSRight_B>=160&&CSRight_G>=120&&CSRight_G<=180&&CSRight_R>=120&&CSRight_R<=170))*/&&(Time<460)
)
    {
        Duration = 0;
        CurAction =17;
        if((PositionY>10&&PositionY<260&&PositionX>10&&PositionX<350)&&(US_Front<=15)&&((US_Front<15)&&(US_Left<=15||US_Right<=15)))
        {
            Duration = 0;
            CurAction =18;
        }
    }
    else if((CSLeft_B>=200&&CSLeft_B<=255&&CSLeft_G>0&&CSLeft_G<=50&&CSLeft_R>200&&CSLeft_R<255)||(CSRight_B>=200&&CSRight_B<=255&&CSRight_G>0&&CSRight_G<=50&&CSRight_R>200&&CSRight_R<255))
    {
        Duration = 49;
        CurAction =19;
    }
    else if(CSLeft_R>=120 && CSLeft_R<=170 && CSLeft_G>=120 && CSLeft_G<=180 && CSLeft_B>=160 && CSLeft_B<=210 && CSRight_R>=120 && CSRight_R<=170 && CSRight_G>=120 && CSRight_G<=180 && CSRight_B>=160 && CSRight_B<=210)
    {
        Duration = 0;
        CurAction =20;
    }
    else if(CSLeft_R>=120 && CSLeft_R<=170 && CSLeft_G>=120 && CSLeft_G<=180 && CSLeft_B>=160 && CSLeft_B<=210&&(!(CSRight_B<=210&&CSRight_B>=160&&CSRight_G>=120&&CSRight_G<=180&&CSRight_R>=120&&CSRight_R<=170)))
    {
        Duration = 1;
        CurAction =21;
    }
    else if(CSRight_R>=120 && CSRight_R<=170 && CSRight_G>=120 && CSRight_G<=180 && CSRight_B>=160 && CSRight_B<=210&&(!(CSLeft_B<=210&&CSLeft_B>=160&&CSLeft_G>=120&&CSLeft_G<=180&&CSLeft_R>=120&&CSLeft_R<=170)))
    {
        Duration = 1;
        CurAction =22;
    }
    else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=200 && CSLeft_G<=255 && CSLeft_B>=0 && CSLeft_B<=20 && CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=200 && CSRight_G<=255 && CSRight_B>=0 && CSRight_B<=20&&((all_number>0)))
    {
        Duration = 0;
        CurAction =23;
    }
    else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=200 && CSLeft_G<=255 && CSLeft_B>=0 && CSLeft_B<=20&&((all_number>0)))
    {
        Duration = 0;
        CurAction =24;
    }
    else if(CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=200 && CSRight_G<=255 && CSRight_B>=0 && CSRight_B<=20&&((all_number>0)))
    {
        Duration = 1;
        CurAction =25;
    }
    else if(((CSRight_B<=255&&CSRight_B>200&&CSRight_R<=80&&CSRight_G<=120&&CSRight_G>80&&CSRight_R>20)
||(CSLeft_B<=255&&CSLeft_B>200&&CSLeft_G>80&&CSLeft_G<=120&&CSLeft_R<80&&CSLeft_R>20))&&(all_number<6&&all_number>0))
    {
        Duration = 0;
        CurAction =26;
    }
    else if(US_Front>=0 && US_Front<=15)
    {
        Duration = 1;
        CurAction =27;
    }
    else if(US_Front>=0 && US_Front<=15 && US_Left>=0 && US_Left<=15 && US_Right>=0 && US_Right<=15)
    {
        Duration = 1;
        CurAction =28;
    }
    else if(US_Front>=0 && US_Front<=15 && US_Left>=0 && US_Left<=15)
    {
        Duration = 1;
        CurAction =29;
    }
    else if(US_Front>=0 && US_Front<=15 && US_Right>=0 && US_Right<=15)
    {
        Duration = 1;
        CurAction =30;
    }
    else if(CSLeft_R>=0 && CSLeft_R<=10 && CSLeft_G>=140 && CSLeft_G<=180 && CSLeft_B>=240 && CSLeft_B<=255&&((CSRight_B<=255&&CSRight_B>240&&CSRight_R<10&&CSRight_G<180&&CSRight_G>=140&&CSRight_R>=0)))
    {
        Duration = 0;
        CurAction =31;
    }
    else if(((CSRight_B<50&&CSRight_B>20&&CSRight_R<=50&&CSRight_G<=255&&CSRight_G>240&&CSRight_R>20)
||(CSLeft_B<50&&CSLeft_B>20&&CSLeft_G>240&&CSLeft_G<=255&&CSLeft_R<50&&CSLeft_R>20))&&((all_number<6&&sup_x==0&&sup_y==0&&green_number<3)||(sup_x!=0&&sup_y!=0&&all_number<5)))
    {
        Duration = 49;
        CurAction =32;
    }
    else if(((CSRight_B<50&&CSRight_B>0&&CSRight_R<=255&&CSRight_G<50&&CSRight_G>0&&CSRight_R>200)||(CSLeft_B<50&&CSLeft_B>20&&CSLeft_G>0&&CSLeft_G<50&&CSLeft_R<=255&&CSLeft_R>200))
&&((all_number<6&&sup_x==0&&sup_y==0)/*&&(red_number<2&&bool_doubleE==1)*/||(sup_x!=0&&sup_y!=0&&all_number<5)))
    {
        Duration = 49;
        CurAction =33;
    }
    else if(((CSRight_B<50&&CSRight_B>20&&CSRight_R<50&&CSLeft_R>20&&CSRight_G<50&&CSRight_G>20)||(CSLeft_B<50&&CSLeft_B>20&&CSLeft_G>20&&CSLeft_G<50&&CSLeft_R<50&&CSLeft_R>20))&&((all_number<6&&sup_x==0&&sup_y==0)&&black_number<2||(sup_x!=0&&sup_y!=0&&all_number<5))

)
    {
        Duration = 49;
        CurAction =34;
    }
    else if(US_Left>=0 && US_Left<=8)
    {
        Duration = 0;
        CurAction =35;
    }
    else if(US_Right>=0 && US_Right<=10)
    {
        Duration = 0;
        CurAction =36;
    }
    else if(PositionX>=290 && PositionX<=330 && PositionY>=200 && PositionY<=240 && Compass>=180 && Compass<=270)
    {
        Duration = 0;
        CurAction =37;
    }
    else if(PositionX>=30 && PositionX<=60 && PositionY>=30 && PositionY<=60 && Compass>=180 && Compass<=270)
    {
        Duration = 0;
        CurAction =38;
    }
    else if(PositionX>=300 && PositionX<=330 && PositionY>=210 && PositionY<=240 && Compass>=0 && Compass<=90)
    {
        Duration = 0;
        CurAction =39;
    }
    else if(PositionX>=30 && PositionX<=60 && PositionY>=30 && PositionY<=60 && Compass>=0 && Compass<=90)
    {
        Duration = 0;
        CurAction =40;
    }
    else if(true)
    {
        Duration = 0;
        CurAction =41;
    }
    switch(CurAction)
    {
        case 1:
            WheelLeft=2;
            WheelRight=2;
            LED_1=0;
            MyState=0;
            if((PositionX-15>345-PositionX)&&(PositionY-15>255-PositionY))
{
   if(((355-PositionX)/(255-PositionY)<1.4))
   {
       if(Compass>270&&Compass<360)
       {
           WheelLeft=1;
                    
           WheelRight=2;
                    
       }

   }
   else
   {
       if(Compass>=270&&Compass<360)
       {
           WheelLeft=2;
                    
           WheelRight=1;
                    
       }
   }
        if(Compass>=0&&Compass<90)
       {
           WheelLeft=3;
                    
           WheelRight=1;
                    
       }
       if(Compass>=90&&Compass<180)
       {
           WheelLeft=3;
                    
           WheelRight=-3;
                    
       }
       if(Compass>=180&&Compass<270)
       {
           WheelLeft=1;
                    
           WheelRight=3;
                    
        }
}
if((345-PositionX>PositionX-15)&&(PositionY-15>255-PositionY))
{
   if(((PositionX-15)/(255-PositionY)>1.4))
   {
       if(Compass>=0&&Compass<45)
       {
           WheelLeft=4;
                    
           WheelRight=1;
                    
       }
       if(Compass>=45&&Compass<90)
       {
           WheelLeft=3;
                    
           WheelRight=1;
                    
       }
       if(Compass>=270&&Compass<360)
       {
           WheelLeft=1;
                    
           WheelRight=3;
                    
       }
       if(Compass>=180&&Compass<270)
       {
           WheelLeft=1;
                    
           WheelRight=3;
                    
       }  
   }
   else
   {
       if(Compass>=0&&Compass<45)
       {
           WheelLeft=1;
                    
           WheelRight=3;
                    
       }
       if(Compass>=45&&Compass<90)
       {
           WheelLeft=1;
                    
           WheelRight=4;
                    
       }
       if(Compass>=90&&Compass<180)
       {
           WheelLeft=1;
                    
           WheelRight=3;
                    
       }
       if(Compass>=180&&Compass<270)
       {
           WheelLeft=3;
                    
           WheelRight=1;
                    
       }
   }
}
if((PositionX-15<345-PositionX)&&(PositionY-15<255-PositionY))
{
   if(((PositionX-15)/(PositionY-15))<1.4)
   {
       if(Compass>90&&Compass<180)
       {
           WheelLeft=1;
                    
           WheelRight=2;
                    
       }

   }
   else
   {
       if(Compass>=90&&Compass<180)
       {
           WheelLeft=2;
                    
           WheelRight=1;
                    
       }
   }
       if(Compass>=0&&Compass<90)
       {
           WheelLeft=1;
                    
           WheelRight=3;
                    
       }
       if(Compass>=180&&Compass<270)
       {
           WheelLeft=3;
                    
           WheelRight=1;
                    
       }
       if(Compass>=270&&Compass<360)
       {
           WheelLeft=-3;
                    
           WheelRight=3;
                    
       }
}/*   HAVE ERROR 
if((345-PositionX<PositionX-15)&&(PositionY-15<255-PositionY))
{
   if(((345-PositionX)/(PositionY-15)<1.4))
   {
       if(Compass>=0&&Compass<45)
       {
           WheelLeft=4;
                    
           WheelRight=1;
                    
       }
       if(Compass>=45&&Compass<90)
       {
           WheelLeft=3;
                    
           WheelRight=1;
                    
       }
       if(Compass>=270&&Compass<360)
       {
           WheelLeft=1;
                    
           WheelRight=3;
                    
       }
       if(Compass>=180&&Compass<270)
       {
           WheelLeft=1;
                    
           WheelRight=3;
                    
       }  
   }
   else
   {
       if(Compass>=0&&Compass<45)
       {
           WheelLeft=1;
                    
           WheelRight=3;
                    
       }
       if(Compass>=45&&Compass<90)
       {
           WheelLeft=1;
                    
           WheelRight=4;
                    
       }
       if(Compass>=90&&Compass<180)
       {
           WheelLeft=1;
                    
           WheelRight=3;
                    
       }
       if(Compass>=180&&Compass<270)
       {
           WheelLeft=3;
                    
           WheelRight=1;
                    
       }
   } 
}*/

            break;
        case 2:
            WheelLeft=5;
            WheelRight=5;
            LED_1=0;
            MyState=0;
            zz_bool_old=1;
                    
            break;
        case 3:
            WheelLeft=1;
            WheelRight=4;
            LED_1=0;
            MyState=0;
            break;
        case 4:
            WheelLeft=4;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            break;
        case 5:
            WheelLeft=0;
            WheelRight=0;
            LED_1=2;
            MyState=0;
            if(Duration<1)
{
   green_number=0;
                    
   black_number=0;
                    
   red_number=0;
                    
   all_number=0;
                    
   WheelLeft=-5;
                    
   WheelRight=-2;
                    
}
            if(Duration == 1) {LoadedObjects = 0; } 
            break;
        case 6:
            WheelLeft=-1;
            WheelRight=-4;
            LED_1=0;
            MyState=0;
            
if(Duration<=1)
{/*
if(PositionX>330&&PositionX<360)
{
  if(Compass<315&&Compass>270)
  {
    WheelLeft=5;
                    
    WheelRight=0;
                    
  }
  if(Compass<360&&Compass>=315)
  {
    WheelLeft=0;
                    
    WheelRight=5;
                    
  }
}
else*/ 
{
if(Compass<356&&Compass>=354)
{
   WheelLeft=5;
                    
   WheelRight=0;
                    
}
else if(Compass<354&&Compass>=350)
{  WheelLeft=5;
                    
   WheelRight=1;
                    
}
else if(Compass>270&&Compass<350)
{ 
   WheelLeft=3;
                    
   WheelRight=1;
                    
}
else if(Compass>6&&Compass<=10)
{
  WheelLeft=1;
                    
  WheelRight=5;
                    
}
else if(Compass>4&&Compass<=6)
{
  WheelLeft=0;
                    
  WheelRight=5;
                    
}
else if(Compass>=356&&Compass<=360)
{
   WheelLeft=-2;
                    
   WheelRight=-5;
                    
}
else if(Compass>0&&Compass<=4)
{
  WheelLeft=-5;
                    
  WheelRight=-2;
                    
}
else
{ 
   WheelLeft=1;
                    
   WheelRight=3;
                    
}
}

}

            break;
        case 7:
            WheelLeft=4;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            
if(Duration<=1)
{
if(!((CSLeft_B<=210&&CSLeft_B>=160&&CSLeft_G>=120&&CSLeft_G<180&&CSLeft_R>120&&CSLeft_R<=170)||(CSRight_B>=160&&CSRight_B<=210&&CSRight_G>=120&&CSRight_G<=180&&CSRight_R>=120&&CSRight_R<=170)))
if(Compass<176&&Compass>=174)
{
   WheelLeft=5;
                    
   WheelRight=0;
                    
}
else if(Compass<174&&Compass>=170)
{  WheelLeft=5;
                    
   WheelRight=1;
                    
}
else if(Compass>90&&Compass<170)
{ 
   WheelLeft=3;
                    
   WheelRight=1;
                    
}
else if(Compass>186&&Compass<=190)
{
  WheelLeft=1;
                    
  WheelRight=5;
                    
}
else if(Compass>184&&Compass<=186)
{
  WheelLeft=0;
                    
  WheelRight=5;
                    
}
else if(Compass>=176&&Compass<=180)
{
   WheelLeft=-2;
                    
   WheelRight=-5;
                    
}
else if(Compass>180&&Compass<=184)
{ 
  WheelLeft=-5;
                    
  WheelRight=-2;
                    
}
else
{ 
   WheelLeft=1;
                    
   WheelRight=3;
                    
}
}


            break;
        case 8:
            WheelLeft=1;
            WheelRight=4;
            LED_1=0;
            MyState=0;
            
if(Duration<=1)
{
if(Compass<86&&Compass>=84)
{
   WheelLeft=5;
                    
   WheelRight=0;
                    
}
else if(Compass<84&&Compass>=80)
{  WheelLeft=5;
                    
   WheelRight=1;
                    
}
else if(Compass>0&&Compass<80)
{ 
   WheelLeft=3;
                    
   WheelRight=1;
                    
}
else if(Compass>96&&Compass<=100)
{
  WheelLeft=1;
                    
  WheelRight=5;
                    
}
else if(Compass>94&&Compass<=96)
{
  WheelLeft=0;
                    
  WheelRight=5;
                    
}
else if(Compass>=86&&Compass<=90)
{
   WheelLeft=-2;
                    
   WheelRight=-5;
                    
}
else if(Compass>90&&Compass<=94)
{
  WheelLeft=-5;
                    
  WheelRight=-2;
                      
}
else
{ 
   WheelLeft=1;
                    
   WheelRight=3;
                    
}
}


            break;
        case 9:
            WheelLeft=-5;
            WheelRight=-5;
            LED_1=0;
            MyState=0;
            
if(Duration<=1)
{
if(Compass<266&&Compass>=264)
{
   WheelLeft=5;
                    
   WheelRight=0;
                    
}
else if(Compass<264&&Compass>=260)
{  WheelLeft=5;
                    
   WheelRight=1;
                    
}
else if(Compass>180&&Compass<260)
{ 
   WheelLeft=3;
                    
   WheelRight=1;
                    
}
else if(Compass>276&&Compass<=280)
{
  WheelLeft=1;
                    
  WheelRight=5;
                    
}
else if(Compass>274&&Compass<=276)
{
  WheelLeft=0;
                    
  WheelRight=5;
                    
}
else if(Compass>=264&&Compass<=270)
{
   WheelLeft=-2;
                    
   WheelRight=-5;
                    
}
else if(Compass>270&&Compass<=274)
{
  WheelLeft=-5;
                    
  WheelRight=-2;
                      
}
else
{ 
   WheelLeft=1;
                    
   WheelRight=3;
                    
}
}



            break;
        case 10:
            WheelLeft=-5;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            /*if(Duration<=1)
{
    WheelLeft=5;
                    
    WheelRight=5;
                    
}*/

            break;
        case 11:
            WheelLeft=-2;
            WheelRight=-5;
            LED_1=0;
            MyState=0;
            if(Compass<225&&Compass>135)
{
    WheelLeft=-5;
                    
    WheelRight=-2;
                    
}
else
{
    WheelLeft=-2;
                    
   WheelRight=-5;
                    
}
            break;
        case 12:
            WheelLeft=-5;
            WheelRight=-2;
            LED_1=0;
            MyState=0;
            if(Compass<315&&Compass>225)
{
     WheelLeft=-2;
                    
     WheelRight=-5;
                    
}
else
{
     WheelRight=-2;
                    
     WheelLeft=-5;
                    
}
            break;
        case 13:
            WheelLeft=-2;
            WheelRight=-5;
            LED_1=0;
            MyState=0;
            if(Compass>45&&Compass<135)
{
   WheelLeft=-5;
                    
   WheelRight=-2;
                    
}
else
{
   WheelLeft=-2;
                    
   WheelRight=-5;
                    
}
            break;
        case 14:
            WheelLeft=2;
            WheelRight=2;
            LED_1=0;
            MyState=0;
            sup_x=SuperObj_X;
                    
sup_y=SuperObj_Y;
                    

            break;
        case 15:
            WheelLeft=-5;
            WheelRight=-5;
            LED_1=0;
            MyState=0;
            if(PositionX==0&&PositionY==0)
  {
      WheelLeft=3;
                    
      WheelRight=3;
                    
  }
  else if(PositionX>=(sup_x+5)) 
  {
      if(Compass>82&&Compass<98)
      {
           WheelLeft=4;
                    
           WheelRight=4;
                    
      }
      else if(Compass<270&&Compass>=98)
      {
          WheelLeft=3;
                    
          WheelRight=-2;
                    
      }
      else
      {
          WheelRight=3;
                     
          WheelLeft=-2;
                    
      }
  }
  else
  {
      if(Compass>262&&Compass<278)
      {
           WheelLeft=4;
                    
           WheelRight=4;
                    
      }
      else if(Compass<=262&&Compass>90)
      {
          WheelLeft=-2;
                    
          WheelRight=3;
                    
      }
      else
      {
          WheelRight=-2;
                     
          WheelLeft=3;
                    
      }
}
            break;
        case 16:
            WheelLeft=-5;
            WheelRight=-5;
            LED_1=0;
            MyState=0;
            if(US_Front<15)
{}
if(US_Front<15&&US_Left<15)
{
    if(Duration<=2){
if(US_Front<=10&&US_Left<=10)
{
   WheelLeft=-3;
                    
   WheelRight=-3;
                    
}
else
{
   WheelLeft=3;
                    
   WheelRight=0;
                    
}
}

}
if(US_Front<15&&US_Right<15)
{
   if(Duration<=2){
if(US_Front<=10&&US_Right<=10)
{
   WheelLeft=-3;
                    
   WheelRight=-3;
                    
}
else
{
   WheelLeft=0;
                    
   WheelRight=3;
                    
}
}

}
if(US_Front<15&&US_Left<15&&US_Right<15)
{
    
if(Duration<=1)
{
if(US_Left>US_Right)
{
  WheelLeft=1;
                    
  WheelRight=4;
                    
}
else
{
  WheelLeft=4;
                    
  WheelRight=1;
                    
}}else{
  WheelLeft=-3;
                    
  WheelRight=-3;
                    
}

}
            break;
        case 17:
            WheelLeft=-5;
            WheelRight=-5;
            LED_1=0;
            MyState=0;
              if(PositionX==0&&PositionY==0)
  {
      WheelLeft=3;
                    
      WheelRight=3;
                    
  }
  else if(PositionY>=(sup_y+5)) 
  {
      if(Compass>170&&Compass<190)
      {
           WheelLeft=4;
                    
           WheelRight=4;
                    
      }
      else if(Compass<360&&Compass>190)
      {
          WheelLeft=3;
                    
          WheelRight=-2;
                    
      }
      else
      {
          WheelRight=3;
                     
          WheelLeft=-2;
                    
      }
  }
  else
  {
       if((Compass>0&&Compass<=8)||(Compass<=360&&Compass>=352))
      { 
           WheelLeft=4;
                    
           WheelRight=4;
                    
      }
      else if(Compass<352&&Compass>180)
      {
          WheelLeft=-2;
                    
          WheelRight=3;
                    
      }
      else
      {
          WheelRight=-2;
                     
          WheelLeft=3;
                    
      }
 }

            break;
        case 18:
            WheelLeft=-5;
            WheelRight=-5;
            LED_1=0;
            MyState=0;
            if(US_Front<15)
{}
if(US_Front<15&&US_Left<15)
{
    if(Duration<=2){
if(US_Front<=10&&US_Left<=10)
{
   WheelLeft=-3;
                    
   WheelRight=-3;
                    
}
else
{
   WheelLeft=3;
                    
   WheelRight=0;
                    
}
}

}
if(US_Front<15&&US_Right<15)
{
   if(Duration<=2){
if(US_Front<=10&&US_Right<=10)
{
   WheelLeft=-3;
                    
   WheelRight=-3;
                    
}
else
{
   WheelLeft=0;
                    
   WheelRight=3;
                    
}
}

}
if(US_Front<15&&US_Left<15&&US_Right<15)
{
    
if(Duration<=1)
{
if(US_Left>US_Right)
{
  WheelLeft=1;
                    
  WheelRight=4;
                    
}
else
{
  WheelLeft=4;
                    
  WheelRight=1;
                    
}}else{
  WheelLeft=-3;
                    
  WheelRight=-3;
                    
}

}
            break;
        case 19:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration==1)
{
all_number++;
                    
sup_x=0;
                    
sup_y=0;
                    
}
            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 20:
            WheelLeft=-5;
            WheelRight=-2;
            LED_1=0;
            MyState=0;
            jinru=1-jinru;
                    

            break;
        case 21:
            WheelLeft=5;
            WheelRight=-5;
            LED_1=0;
            MyState=0;
            /*if(Duration<=1)
/*{
if((Compass<360&&Compass>=335)||(Compass<90&&Compass>=65)||(Compass<270&&Compass>=245)||(Compass>=155&&Compass<180))
{ WheelLeft=4;
                    
  WheelRight=0;
                    
}else if((Compass<65&&Compass>=25)||(Compass<155&&Compass>=115)||(Compass<245&&Compass>=205)&&(Compass>=295&&Compass<335))
{
  WheelLeft=4;
                    
  WheelRight=0;
                    
}
else
{ 
   WheelLeft=3;
                    
   WheelRight=0;
                    
}
} */
            break;
        case 22:
            WheelLeft=-5;
            WheelRight=5;
            LED_1=0;
            MyState=0;
            /*if(Duration<=1)
{
if((Compass>270&&Compass<=295)||(Compass>0&&Compass<=25)||(Compass>180&&Compass<=205)||(Compass<=115&&Compass>90))
{
  WheelLeft=0;
                    
  WheelRight=4;
                    
}
else if((Compass>25&&Compass<=65)||(Compass>115&&Compass<=155)||(Compass>205&&Compass<=245)||(Compass<=335&&Compass>295))
{
  WheelLeft=0;
                    
  WheelRight=4;
                    
}
else
{ 
   WheelLeft=0;
                    
   WheelRight=3;
                    
}
}
*/
            break;
        case 23:
            WheelLeft=-1;
            WheelRight=-4;
            LED_1=0;
            MyState=0;
            /*if((Compass>0&&Compass<90)||(Compass>180&&Compass<270))
{
     WheelLeft=-1;
                    
     WheelRight=-4;
                    
}
else
{
    WheelLeft=-4;
                    
    WheelRight=-1;
                    
}*/
            break;
        case 24:
            WheelLeft=4;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            if(Duration<=1)
{
if((Compass<360&&Compass>=335)||(Compass<90&&Compass>=65)||(Compass<270&&Compass>=245)||(Compass>=155&&Compass<180))
{ WheelLeft=4;
                    
  WheelRight=0;
                    
}else if((Compass<65&&Compass>=25)||(Compass<155&&Compass>=115)||(Compass<245&&Compass>=205)&&(Compass>=295&&Compass<335))
{
  WheelLeft=4;
                    
  WheelRight=1;
                    
}
else
{ 
   WheelLeft=3;
                    
   WheelRight=1;
                    
}
} 

            break;
        case 25:
            WheelLeft=1;
            WheelRight=4;
            LED_1=0;
            MyState=0;
            
if(Duration<=1)
{
if((Compass>270&&Compass<=295)||(Compass>0&&Compass<=25)||(Compass>180&&Compass<=205)||(Compass<=115&&Compass>90))
{
  WheelLeft=0;
                    
  WheelRight=4;
                    
}
else if((Compass>25&&Compass<=65)||(Compass>115&&Compass<=155)||(Compass>205&&Compass<=245)||(Compass<=335&&Compass>295))
{
  WheelLeft=1;
                    
  WheelRight=4;
                    
}
else
{ 
   WheelLeft=1;
                    
   WheelRight=3;
                    
}
}

            break;
        case 26:
            WheelLeft=-2;
            WheelRight=-2;
            LED_1=0;
            MyState=0;
            all_number=0;
                    
green_number=0;
                    
red_number=0;
                    
black_number=0;
                    
            break;
        case 27:
            WheelLeft=-4;
            WheelRight=-4;
            LED_1=0;
            MyState=0;
            if(Duration<=2)
{
    if(US_Front<10)
   {
   WheelLeft=-3;
                    
   WheelRight=-3;
                    
   }
   else
   {
      if(US_Left>US_Right)
      {
        WheelLeft=0;
                    
        WheelRight=3;
                    
       }
       else
       {
        WheelLeft=3;
                    
        WheelRight=0;
                    
        }
    }
 }/*
}
if(Duration<=1)
{
{
if(US_Left>US_Right)
{
  WheelLeft=0;
                    
  WheelRight=3;
                    
}
else
{
  WheelLeft=3;
                    
  WheelRight=0;
                    
}
}
}*/
            break;
        case 28:
            WheelLeft=-3;
            WheelRight=-3;
            LED_1=0;
            MyState=0;
            
if(Duration<=1)
{
if(US_Left>US_Right)
{
  WheelLeft=1;
                    
  WheelRight=4;
                    
}
else
{
  WheelLeft=4;
                    
  WheelRight=1;
                    
}}else{
  WheelLeft=-3;
                    
  WheelRight=-3;
                    
}
            break;
        case 29:
            WheelLeft=-4;
            WheelRight=-4;
            LED_1=0;
            MyState=0;
            if(Duration<=2){
if(US_Front<=10&&US_Left<=10)
{
   WheelLeft=-3;
                    
   WheelRight=-3;
                    
}
else
{
   WheelLeft=3;
                    
   WheelRight=0;
                    
}
}
            break;
        case 30:
            WheelLeft=-4;
            WheelRight=-4;
            LED_1=0;
            MyState=0;
            if(Duration<=2){
if(US_Front<=10&&US_Right<=10)
{
   WheelLeft=-3;
                    
   WheelRight=-3;
                    
}
else
{
   WheelLeft=0;
                    
   WheelRight=3;
                    
}
}
            break;
        case 31:
            WheelLeft=3;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            {if(Duration<=1)
{
  bool_doubleE=1;
                    
}}
            break;
        case 32:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration==1)
{
all_number++;
                    
green_number++;
                    
WheelLeft=0;
                    
WheelRight=0;
                    
LED_1=1;
                    
}

            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 33:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration==1)
{
all_number++;
                    
red_number++;
                    
WheelLeft=0;
                    
WheelRight=0;
                    
LED_1=1;
                    
}



            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 34:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            
if(Duration==1)
{
all_number++;
                    
black_number++;
                    
WheelLeft=0;
                    
WheelRight=0;
                    
LED_1=1;
                    
}

            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 35:
            WheelLeft=3;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            break;
        case 36:
            WheelLeft=1;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            break;
        case 37:
            WheelLeft=1;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            break;
        case 38:
            WheelLeft=3;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            break;
        case 39:
            WheelLeft=3;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            break;
        case 40:
            WheelLeft=1;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            break;
        case 41:
            WheelLeft=3;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            {
bool_doubleE=0;
                    
zz_bool_old=zz_bool_now;
                    
if(((CSRight_B<=210&&CSRight_B>=160&&CSRight_G>=120&&CSRight_G<=180&&CSRight_R>=120&&CSRight_R<=170))&&((CSLeft_B<=210&&CSLeft_B>=160&&CSLeft_G>=120&&CSLeft_G<=180&&CSLeft_R>=120&&CSLeft_R<=170)))
{
    zz_bool_now=1;
                    
}
else
{
    zz_bool_now=0;
                    
}
}
            break;
        default:
            break;
    }

}


DLL_EXPORT void OnTimer()
{
    switch (CurGame)
    {
        case 9:
            break;
        case 10:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            break;
        case 0:
            Game0();
            break;
        case 1:
            Game1();
            break;
        default:
            break;
    }
}

