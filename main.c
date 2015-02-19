//
//  main.c
//  Time to Words
//  BIOS challenge 1997 round one.
//  Created by Patrick Mintram on 19/02/2015.
//  Copyright (c) 2015 Patrick Mintram. All rights reserved.
//
//  The program converts a number into it's word equivalents
//
//

#include <string.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

void unitToWords(int number, char str[]);
void getTime(int* hours, int*minutes, int *minutescopy,int*hourcopy);
void testPrint(int *hours, int *minutes);
void splitTime(int splitTime[],int *minutes);
void minutesToWords(int time[],char strMinP1[], char strMinP2[],char *minsTest);


int main() {
    //Normals ints
    int initialHours=0, initialMinutes = 0, minutes = 0, hour = 0;
    
    //Points to ints
    int *pHours = &initialHours, *pMins = &initialMinutes, *pMinsCopy = &minutes, *pHourCopy = &hour;
    
    //arrays of ints
    int time[2] = {0,0}; // array used for holding minutes
    //          tens,units}
    
    //hours, then the two parts of minutes phrase, strDir == past/to the hour, whether to display minutes or not
    char strHours[10], strMinP1[10], strMinP2[10],strDir[] = "past", minsTest = TRUE;
    
    //pointer to a char
    char *pMinsTest = &minsTest;
    
    //Do while ensures user enters a valid time
    do{
    // pass the function the address of the variables
    getTime(pHours ,pMins,pMinsCopy,pHourCopy);
    }while(initialHours >12  || initialHours < 1 || initialMinutes <0 || initialMinutes >59);
    
    //test to see if its a 'something to' or a 'something past', invert the number is it's a 'something to'
    if (initialMinutes>30){
        minutes = 60-initialMinutes;
        hour+=1;
        strcpy(strDir, "to");
    }
        
    //split the time into its component parts
    splitTime(time,pMinsCopy);

    // turn the hour value into words
    unitToWords(hour, strHours);
    
    //turn the minutes into words
    minutesToWords(time,strMinP1, strMinP2, pMinsTest);
    
    //if time is on the hour
    if(initialMinutes==0)
        printf("The time is %s o'clock.", strHours);
    
    // if its a half hour
    else if (initialMinutes == 30)
        printf("The time is half past %s", strHours);
    
    else
    //Display time in desired format
        printf("The time is %s %s %s %s %s.",strMinP1, strMinP2,minsTest==TRUE?"minutes":"",strDir,strHours);
    
}


void minutesToWords(int time[], char strMinP1[], char strMinP2[],char *minsTest)
{
switch(time[0]){
    case 1:
        switch(time[1]){
            case 1:
                strcpy(strMinP1,"eleven");
                break;
            case 2:
                strcpy(strMinP1,"twelve");
                break;
            case 3:
                strcpy(strMinP1,"thirteen");
                break;
            case 4:
                strcpy(strMinP1,"fourteen");
                break;
            case 5:
                strcpy(strMinP1,"quarter");
                *minsTest = FALSE;
                break;
            case 6:
                strcpy(strMinP1,"sixteen");
                break;
            case 7:
                strcpy(strMinP1,"seventeen");
                break;
            case 8:
                strcpy(strMinP1,"seventeen");
                break;
            case 9:
                strcpy(strMinP1,"nineteen");
                break;
            case 0:
                strcpy(strMinP1, "ten");
                break;
        }
        
        time[1] = 0;
        break;
    case 2:
        strcpy(strMinP1,"twenty");
        break;
    case 3:
        strcpy(strMinP1,"thirty");
        break;
    case 4:
        strcpy(strMinP1,"quarter");
        *minsTest = FALSE;
        break;
    case 5:
        strcpy(strMinP1,"fifty");
        break;
    case 0:
        strcpy(strMinP1,"");
        break;
    default:
        printf("Error");
        break;
    }
    unitToWords(time[1],  strMinP2);
}


//LUT for units to their word equivelents
void unitToWords(int number, char str[10]){
    switch(number){
        case 1:
            strcpy(str,"one");
            break;
        case 2:
            strcpy(str,"two");
            break;
        case 3:
            strcpy(str,"three");
            break;
        case 4:
            strcpy(str,"four");
            break;
        case 5:
            strcpy(str,"five");
            break;
        case 6:
            strcpy(str,"six");
            break;
        case 7:
            strcpy(str,"seven");
            break;
        case 8:
            strcpy(str,"eight");
            break;
        case 9:
            strcpy(str,"nine");
            break;
        case 10:
            strcpy(str,"ten");
            break;
        case 11:
            strcpy(str,"eleven");
            break;
        case 12:
            strcpy(str,"twelve");
            break;
        case 0:
            strcpy(str,"");
            break;
        default:
            break;
    }
}

//passing an array is already a pointer therefore no need to fanny about with starts etc
void splitTime(int splitTime[2], int *minutes){
    //Break the user input into tens and units
    if(*minutes /10 >0){
        
        //divide initial minutes by ten,
        int divideTen = *minutes/10;
        
        //subtract th number of whole tens from the initial minutes
        *minutes -= divideTen*10;
        
        //remainder will now be in the initial minutes
        splitTime[0] = divideTen;
    }
    splitTime[1] = *minutes;
}

// stars indicate they are addresses
void getTime(int* hours, int*minutes, int *minutescopy,int*hourcopy){
    printf("Hours:");
    scanf("%i",hours);
    *hourcopy = *hours;

    printf("Minutes:");
    scanf("%i",minutes); //no need to use & because it's already an address
    
    //make a copy of the user imput for manipulating
    *minutescopy = *minutes; //start because im referring to the contents rather than the address
}

void testPrint(int *hours, int *minutes)
{
    printf("%i, %i", *hours, *minutes); //Stars are need to turn it from an address to the contents of the address

}