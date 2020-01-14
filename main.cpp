/* Alexis Hunter
 * Hardware Multiplication Algorithm
 * main.cpp
 * Based on a project in CPSC 2310
 * (taught by Dr. Nicholas Widman)
 */

/* Mimics the hardware multiplication process
   Prints the initial step, the multiplication steps, and the 
   final check, comparing the binary and decimal representations
   of the multiplicand and the multiplier
*/

#include "multiply.h"

/* Converts a decimal number into its binary representation
   (base 10 to base 2)
*/
int decToBin(int x) {
  int binary = 0;	// binary number returned
  int rem = 0;		// remainder
  int dividend = x;
  int divisor = 2;
  int quotient = 0;

  /* Allows binary to be an int instead of using an array
     Represents the place value (binary to decimal) 
     (1 = 1, 2 = 10,...)
  */
  int shift = 1;	

  // Repeat the process while the divident != 0 
  while (dividend > 0) {
    quotient = dividend / divisor;
    rem = dividend % divisor;

    // Placing a 1 in the corresponding bit position
    if (rem == 1) {
      binary += rem * shift;
    }    

    // Move to the next place value (right to left)
    shift *= 10;

    // For the next iteration
    dividend = quotient;
  }

  return binary;
}

int main() {
  int mplc = 0;			// multiplicand
  int mplr = 0;			// multiplier
  bool askAgain = true;   	// Used to loop while input is not in range

  // Asking for multiplicand while input is not in range (0 - 255)
  while (askAgain) {
    cout << "multiplicand: ";
    cin >> mplc;

    // If input is in range, stop looping
    if ( (mplc >= 0) && (mplc <= 255) ) {
      askAgain = false;
    }
  }

  // Setting to true to loop for multiplier
  askAgain = true;
  
  // Asking for multiplier while input is not in range (0 - 255)
  while (askAgain) {
    cout << "multiplier: ";
    cin >> mplr;

    // If input is in range, stop looping
    if ( (mplr >= 0) && (mplr <= 255) ) {
      askAgain = false;
    }
  }

  // Storing the binary representation of the multiplicand
  // and the multiplier
  int binMPLC = decToBin(mplc);
  int binMPLR = decToBin(mplr);

  // Creating the registers that will be used in the
  // multiplication process
  Multiply mul(binMPLR, binMPLC, mplr, mplc);

  cout << endl;

  // Printing the initial state of the registers
  mul.printInitial();

  // Printing the 8 steps of the multiplication process
  for (int i = 0; i < 8; i++) {
    mul.printStep();
  }

  // Printing the final check
  mul.printCheck();

  return 0;
}
