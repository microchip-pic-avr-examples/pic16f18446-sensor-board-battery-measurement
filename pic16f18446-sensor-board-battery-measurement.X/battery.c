/*
 * File:   battery.c
 * Author: M19219
 *
 * Created on December 4, 2017, 2:23 PM
 */

#include "mcc_generated_files/mcc.h"
#include "battery.h"
#include "graphics.h"

uint16_t batteryMillivolts;

int16_t wpOld;

#define BATT_ADC_MEM_SIZE 128

uint16_t battAdcMem[BATT_ADC_MEM_SIZE];
int16_t bami;
uint32_t bamAcc;



void readBattery() {  
    uint32_t res;
    uint8_t i;
    
    // ADFM right; ADNREF VSS; ADPREF VDD; ADCS FOSC/32; 
    ADREF = 0x00; // ADNREF VSS; ADPREF VDD
   
    ADCC_GetSingleConversion(channel_FVR_Buffer1);
    res = ADCC_GetAccumulatorValue() >> 6;
    
    if(bami==-1) {
        bamAcc = 0;
        for(i=0; i<BATT_ADC_MEM_SIZE; i++) {
            battAdcMem[i] = res;
            bamAcc += res;
        }
        bami = 0;
    } else {
        bamAcc -= battAdcMem[bami];
        battAdcMem[bami] = res;
        bamAcc += battAdcMem[bami];
        bami++;
        bami = bami % BATT_ADC_MEM_SIZE;
    }
    
    res = bamAcc/BATT_ADC_MEM_SIZE;

    batteryMillivolts = 4194304/res;
    
  
}



uint16_t getBatteryPercentageX10() {
    int16_t a = batteryMillivolts;
    
    a = a - 2500;
    
    a = a*2;
    
    if(a < 0) {
        a = 0;
    }
    if(a > 1000) {
        a = 1000;
    }
    
    return a;
}




void drawBatteryPercentage(uint8_t x, uint8_t y, uint16_t color) {
    
    uint16_t a; // 10 x Batt%
    
    uint8_t st[16];
    
    a = getBatteryPercentageX10();
    
    
       
    st[ 0] = ((a/1000)%10) + '0';
    st[ 1] = ((a/100)%10) + '0';
    st[ 2] = ((a/10)%10) + '0';
    st[ 3] = '.';
    st[ 4] = ((a/1)%10) + '0';
    st[ 5] = ' ';  
    st[ 6] = '%';  
    st[ 7] = 0;  
    
    if(a<1000) {
        st[0] = ' ';
    }
    if(a<100) {
        st[1] = ' ';
    }
   
    GFX_DrawText(x, y, st, color, 0x0000); 
    
}



void drawBatteryVoltage(uint8_t x, uint8_t y, uint16_t color) {
    
    int16_t a;
    
    uint8_t st[16];
    
    a = batteryMillivolts;
     
    st[ 0] = ((a/1000)%10) + '0';
    st[ 1] = '.';
    st[ 2] = ((a/100)%10) + '0';
    st[ 3] = ((a/10)%10) + '0';
    st[ 4] = ((a/1)%10) + '0';
    st[ 5] = ' ';   
    st[ 6] = 'V';   
    st[ 7] = 0;  
    
    GFX_DrawText(x, y, st, color, 0x0000); 
}


void drawBatteryPercentageGraphStatic(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
    GFX_DrawTriangle(x, y, x+w, y+h, x, y+h, color);
}


void drawBatteryPercentageGraph(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
    
    uint32_t p = getBatteryPercentageX10(); // 0 .. 1000
    
    p = 1000 - p; // 1000 .. 0
    
    uint8_t wp = (p*w)/1000;
    uint16_t yp;
    
    
    uint8_t iStart = 1;
    uint8_t iStop = w;
    
    if(wpOld!=-1) {
        if(wpOld < wp) {
            iStart = wpOld;
            iStop = wp;
        } else {
            iStart = wp;
            iStop = wpOld;
        }
    }
    
    wpOld = wp;
    
    for(int8_t i=iStop-1; i>=iStart; i--) {
        
        yp = i;
        yp *= (h-1);
        yp = (uint16_t)(yp/w+0.5);
        
        if(i<wp) {
            GFX_DrawLine(x+i, y+yp+2, x+i, y+h-1, 0x0000);
        } else {
            GFX_DrawLine(x+i, y+yp+2, x+i, y+h-1, color);
        }      
    }
   
}



void drawBatteryIcon(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
    
    //  A B______________I
    //  D_|              |
    //  | C              |
    //  |_F              |
    //  E |______________|
    //    G              H
    
    uint8_t xA, yA, xB, yB, xC, yC, xD, yD, xE, yE, xF, yF, xG, yG, xH, yH, xI, yI;
    
    xA = xD = xE = x;
    yA = yB = yI = y;
    
    xB = xC = xF = xG = xA + (w*0.1 + 0.5);
    xI = xH = xA + w;
    
    yD = yC = yA + (h*0.2 + 0.5);
    yG = yH = yA + h;
    yE = yF = yG - (h*0.2 - 0.5);
    
    GFX_DrawLine(xB, yB, xC, yC, color);
    GFX_DrawLine(xC, yC, xD, yD, color);   
    GFX_DrawLine(xD, yD, xE, yE, color);   
    GFX_DrawLine(xE, yE, xF, yF, color);
    GFX_DrawLine(xF, yF, xG, yG, color);
    GFX_DrawLine(xG, yG, xH, yH, color);
    GFX_DrawLine(xH, yH, xI, yI, color);
    GFX_DrawLine(xI, yI, xB, yB, color);
    
       
    uint32_t p = getBatteryPercentageX10();
  
    p = 1000 - p;
    
    p = (p*w)/1000;
    
    for(uint8_t i=1; i<w; i++) {
        uint8_t x1 = x+i;
        uint8_t y1 = yB+1;
        uint8_t x2 = x1;
        uint8_t y2 = yG-1;
        
        if(x1<=xB) {
            y1 = yD+1;
            y2 = yE-1;
        }
        
        if(i<p) {
            // empty line
            GFX_DrawLine(x1, y1, x2, y2, 0x0000);
        } else {
            // full line
            GFX_DrawLine(x1, y1, x2, y2, color);
        }
        
    }  
}


void initBattery() {
    wpOld = -1;
    bami = -1;
}



void batteryScreenTasks() {

    readBattery();

    drawBatteryPercentage(15, 15, 0xFF00);

    drawBatteryVoltage(15, 50, 0xFF00);

    drawBatteryIcon(110, 1, 16, 8, 0xFF00);

    drawBatteryPercentageGraph(5, 85, 118, 50, 0xFF00);
}

void batteryScreenStatic() {

    GFX_DrawText(0, 0, "Battery info", 0xFF00, 0x0000);
    GFX_DrawText(0, 35, "Voltage level", 0xFF00, 0x0000);
    GFX_DrawText(0, 70, "Battery graph", 0xFF00, 0x0000);
    drawBatteryPercentageGraphStatic(5, 85, 118, 50, 0xFF00);
    GFX_DrawText(0, 140, "100", 0xFF00, 0x0000);
    GFX_DrawText(119, 140, "0", 0xFF00, 0x0000);
}
