# 14-segment LED Multi-Display String Scroller

This project is intended to serve as a practical example of displaying scrolling text on a 14 segment display with an arduino. The code can be easily modified to accomodate displays with more or less segments and to suit different types of displays(common cathode) or drivers. 

The project includes a 14 segment ASCII library created by David Madison (https://github.com/dmadison/LED-Segment-ASCII/blob/master/14-Segment/14-Segment-ASCII_HEX.txt). His repository includes 7 segment and 16 segment libraries that can be easily dropped in with only a slight modification to include a segment-testing character.

The project requires all pins used to drive the displays to be contiguous but may start and end on any available pins. It is important to properly define the proper pin for each segment and you may refer to David Madison's diagram for the relevant ordering:

![LED Segment Legend](https://github.com/dmadison/LED-Segment-ASCII/blob/master/Images/Segment-Labels.png "LED segment legend. Left to right: sixteen, fourteen, and seven-segment displays.")
