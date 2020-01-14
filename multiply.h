/* Alexis Hunter
 * Hardware Multiplication Algorithm
 * multiply.h
 * Based on a project in CPSC 2310
 * (taught by Dr. Nicholas Widman)
 */

#ifndef MULTIPLY_H
#define MULTIPLY_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Multiply {
  private:
    int mq;	   // multiplier (binary)
    int mdr;	   // multiplicand (binary)
    int carry;     // value in carry register
    int acc;	   // value in accumulator

    int decMPLR;   // decimal multiplier
    int decMPLC;   // decimal multiplicand

    int binMPLR;   // binary multiplier
    int binMPLC;   // binary multiplicand

    int step;   // step number in multiplication process

  public:
    // Default Constructor
    Multiply();

    // Regular Constructor
    Multiply(int bMPLR, int bMPLC, int dMPLR, int dMPLC);

    // Prints initial state of registers
    void printInitial();

    // Prints current step in multplication process
    void printStep();

    // Prints binary number in 8-bit format
    void prt_bin(int bin);

    // Checks if the least significant bit (lsb) of mq is a 1
    bool check_LSB();

    // Prints the check section to compare the binary and decimal
    // representations 
    void printCheck();

    /* Puts the values of the register in a 2D array to keep
       track of bit positions in order to perform addition 
       Checks each corresponding bit in the bit positions to 
       determine what the sum and carry out will be
       Changes acc and carry based on the sum 
    */
    void addBits();

    // Finds the number of digits in the input number
    int numLength(int num);

    // Shifts the bits of carry, acc, and mq to the right by one
    void shiftRight();
};

#endif
