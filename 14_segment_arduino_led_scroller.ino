/*
 *  Project     Segmented LED Display String Scroller
 *  @author     JohnnyGalto
 *  @link       github.com/JohnnyGalto/14_segment_arduino_led_scroller
 *  @license    MIT - Copyright (c) 2018 JohnnyGalto
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS= IN
 * THE SOFTWARE.
 *
 */

/*
 * TODO: 
 *  Ensure FIRST_PIN & LAST_PIN are defined correctly
 *  Software assumes pins used for displays start at FIRST_PIN and continue continuously to LAST_PIN
 *  Modify xxxxx_DISPLAY to use correct pins and also correct number of displays
 *  Modify SEG_x to use correct pins
 *  Modify INIT_DISPLAY to 0 for no segment check or any other value to modify the amount of time the segments stay lit
 *  Modify displayPin array to match actual number of displays
 * 
 */
#include "14_Segment_ASCII_HEX.h"

#define FIRST_PIN         0 ////Physical pin number of first pin used on Arduino(used for pin initialization). Assumes pins are contiguous.
#define LAST_PIN          16 //Physical pin number of last pin used on Arduino(used for pin initialization). Assumes pins are contiguous.
#define NUM_DISPLAYS      3 //Number of display units

/*
 *Physical pin number of common-anode for each display
 *Modify to allow more displays
 */
#define FIRST_DISPLAY   14 
#define SECOND_DISPLAY  15
#define THIRD_DISPLAY   16

/*
 *Physical pin number of segments
 */
#define SEG_A     0
#define SEG_B     1
#define SEG_C     2
#define SEG_D     3
#define SEG_E     4
#define SEG_F     5
#define SEG_G1    6
#define SEG_G2    7
#define SEG_H     8
#define SEG_I     9
#define SEG_J     10
#define SEG_K     11
#define SEG_L     12
#define SEG_M     13

#define ALL_SEGS  ('z'+6) //Macro to light all segments on a display

#define INIT_DELAY  4000 //Number of loops to wait while displaying all segments(segment check)

/*
 * Allows addressing of particular display as a zero-based array
 * Modify to allow more displays
 */
unsigned char displayPin[3]
{
  FIRST_DISPLAY,
  SECOND_DISPLAY,
  THIRD_DISPLAY
};

/*
 * Function prototypes
 */
void loop(void);
void setup(void);
void scrollString(char[], unsigned char, unsigned int);
void printCharacter(unsigned char, unsigned char);
void clearDisplays(void);

/*
 * Erases all displays leaving them in a known state
 */
void clearDisplays()
{
  
  for(unsigned char j=0; j<NUM_DISPLAYS; j++)
      digitalWrite(displayPin[j],HIGH);
        
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_C, HIGH);
  digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_E, HIGH);
  digitalWrite(SEG_F, HIGH);
  digitalWrite(SEG_G1, HIGH);
  digitalWrite(SEG_G2, HIGH);
  digitalWrite(SEG_H, HIGH);
  digitalWrite(SEG_I, HIGH);
  digitalWrite(SEG_J, HIGH);
  digitalWrite(SEG_K, HIGH);
  digitalWrite(SEG_L, HIGH);
  digitalWrite(SEG_M, HIGH);
}

/*
 * Displays an ASCII character on a given display
 */
void printCharacter(unsigned char character, unsigned char charNum)
{

  clearDisplays();
  
  if(character>=32&&character<=128) //characters must remain within ASCII printable characters defined in array 
  {
    digitalWrite(charNum, LOW);
    digitalWrite(SEG_A, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_A)))?LOW:HIGH);
    digitalWrite(SEG_B, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_B)))?LOW:HIGH);
    digitalWrite(SEG_C, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_C)))?LOW:HIGH);
    digitalWrite(SEG_D, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_D)))?LOW:HIGH);
    digitalWrite(SEG_E, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_E)))?LOW:HIGH);
    digitalWrite(SEG_F, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_F)))?LOW:HIGH);
    digitalWrite(SEG_G1, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_G1)))?LOW:HIGH);
    digitalWrite(SEG_G2, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_G2)))?LOW:HIGH);
    digitalWrite(SEG_H, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_H)))?LOW:HIGH);
    digitalWrite(SEG_I, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_I)))?LOW:HIGH);
    digitalWrite(SEG_J, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_J)))?LOW:HIGH);
    digitalWrite(SEG_M, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_K)))?LOW:HIGH); //To accomodate different numbering scheme(switch wires to make permanent)
    digitalWrite(SEG_L, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_L)))?LOW:HIGH);
    digitalWrite(SEG_K, (FourteenSegmentASCII[character-32]&((unsigned int)pow(2,SEG_M)))?LOW:HIGH); //To accomodate different numbering scheme(switch wires to make permanent)
  }
}

/*
 * Scroll a string across displays 
 * Includes fade in where string starts on right-most display preceded by blank space
 * and scrolls left. This also includes a fade out where characters travel off the left
 * display followed by blank space
 */
void scrollString(char string[], unsigned char numChars, unsigned int scrollDelay)
{
  unsigned int stringIndex=0;
  unsigned char displayIterator=0;
  
  /*
   * Allow for scrolling fewer letters than physical displays, not the other way around
   */
  if(numChars>NUM_DISPLAYS) 
  {
    clearDisplays();
    return; 
  }
  
  numChars--; //shift for zero-based loops
  
  /*
   * Fade in and display to last character on last display 
   */
  while(string[stringIndex])
  { 
    if(stringIndex==0xFFFF) stringIndex==0x0000; //Prevent integer overruns for too long strings
    
    for(unsigned int i=0; i<scrollDelay; i++)
    {  
      for(displayIterator=0; displayIterator<=numChars; displayIterator++)
        printCharacter(((stringIndex+displayIterator)<numChars)?' ':string[stringIndex-numChars+displayIterator], displayPin[displayIterator]);    
    }
    stringIndex++;
 }
 
 /*
  * Fade out to blank on first display
  */
 for(unsigned char j=numChars; j>0; j--)
 {  
  for(unsigned int i=0; i<scrollDelay; i++)
  {  
    for(displayIterator=0; displayIterator<=numChars; displayIterator++)
      printCharacter(displayIterator>=j?' ':string[stringIndex-numChars+displayIterator], displayPin[displayIterator]);    
  }
  stringIndex++;
 }
}

/*
 * Initialize our output pins
 * Assign known values to pins
 */
void setup() 
{
  for(unsigned char x=FIRST_PIN; x<=LAST_PIN; x++)
    pinMode(x,OUTPUT);

  clearDisplays();
  
  /*
   * Initialize display with all segments lit to check for missing segments
   */
  for(unsigned int i=0; i<INIT_DELAY; i++)
  {
    for(unsigned int j=0; j<NUM_DISPLAYS; j++)
      printCharacter(ALL_SEGS, displayPin[j]);
  }
}

void loop() 
{
  scrollString("HELLO WORLD", NUM_DISPLAYS, 2000);
}
