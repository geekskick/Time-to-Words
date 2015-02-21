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
#include <assert.h>

//macro gets the number of elements in an array
#define NUMELEMS(x) (sizeof(x)/sizeof(x[0]))

#define TRUE 1
#define FALSE 0

//void unitToWords(int number, char str[]);
void getTime(int* hours, int*minutes, int *minutescopy,int*hourcopy);
//void testPrint(int *hours, int *minutes);
void splitTime(int splitTime[],int *minutes);
//void minutesToWords(int time[],char strMinP1[], char strMinP2[],char *minsTest);


int main() {
    //Normals ints
    int initialHours=0, initialMinutes = 0, minutes = 0, hour = 0;
    
    //Points to ints
    int *pHours = &initialHours, *pMins = &initialMinutes, *pMinsCopy = &minutes, *pHourCopy = &hour;
    
    int minutes_digits[2] = {0,0}; // array used for holding minutes
    //                   {tens,units}
    
    //strngs for: hours, then the two parts of minutes phrase ie "twenty+one",
    //str_dir == past/to the hour, finally whether to display minutes or not
    char str_hours[10], str_minutesp1[10], str_minutesp2[10],str_dir[] = "past", minsTest = TRUE;
    
    //LUTs for the different words, 0th element must be in there for certain cases in which I don't want anything to be displayed
    //such as when you don't want 'zero one minutes ...' displayed
    const char *tenminuteswords[]={"\0","twenty","thirty","fourty","fifty"};
    const char *unitswords[] = {"\0","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve"};
    const char *teenswords[] = {"\0","ten","eleven","twelve","thirteen","fourteen","quarter","sixteen","seventeen","eighteen","nineteen"};
    
    //Do while ensures user enters a valid time
    do {
    // pass the function the address of the variables
    getTime(pHours ,pMins,pMinsCopy,pHourCopy);
    } while ( initialHours > 12  || initialHours < 1 || initialMinutes < 0 || initialMinutes > 59) ;
    
    //test to see if its a 'something to' or a 'something past', invert the number is it's a 'something to'
    if (initialMinutes>30){
        minutes = 60-initialMinutes;
        hour+=1;
        strcpy(str_dir, "to");
    }
        
    //split the time into its component parts
    splitTime(minutes_digits,pMinsCopy);

    // turn the hour value into words
    strcpy(str_hours,unitswords[hour]);
    
    //assert breaks out of program if i'm trying to access an element which is too high in array, ie element 15 of a 9 long array
    assert(minutes_digits[0]<=NUMELEMS(tenminuteswords)+2);
    assert(minutes_digits[1]<=NUMELEMS(unitswords));
    
    //if it's a 'teen' value
    if(minutes_digits[0] == 1){
        //makes sure the word 'minutes' isnt displayed if it's a 'quarter' past or to
        if (minutes_digits[1] == 5 || minutes_digits[1]==0){
            minsTest=FALSE;
        }
        //needs to be +1 to accounnt for 'blank' element of LUT
        strcpy(str_minutesp1,teenswords[minutes_digits[1]+1]);
        minutes_digits[1] = 0;
    }
    
    //not a 'teen' value
    else{
        strcpy(str_minutesp1,tenminuteswords[minutes_digits[0]]);
    }
    
    //convert the 'units' part of the minutes to a word
    strcpy(str_minutesp2,unitswords[minutes_digits[1]]);
    
    //if time is on the hour
    if(initialMinutes==0){
        printf("The time is %s o'clock.", str_hours);
    }
    
    // if its a half hour
    else if (initialMinutes == 30){
        printf("The time is half past %s", str_hours);
    }
    
    else{
        printf("The time is %s %s %s %s %s.",str_minutesp1, str_minutesp2,minsTest==TRUE?"minutes":"",str_dir,str_hours);
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
    splitTime[1] = *minutes; //starred because im referring to the contents rather than the address
}

// stars indicate they are addresses
void getTime(int* hours, int*minutes, int *minutescopy,int*hourcopy){
    printf("Hours:");
    scanf("%i",hours); //no need to use & because it's already an address

    printf("Minutes:");
    scanf("%i",minutes); //no need to use & because it's already an address
    
    //make a copy of the user input for manipulating
    *hourcopy = *hours;
    *minutescopy = *minutes; //starred because im referring to the contents rather than the address
}