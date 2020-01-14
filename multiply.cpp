/* Alexis Hunter
 * Hardware Multiplication Algorithm
 * multiply.cpp
 * Based on a project in CPSC 2310
 * (taught by Dr. Nicholas Widman)
 */

#include "multiply.h"

// Default Constructor
Multiply::Multiply(): mq(0), mdr(0), carry(0), acc(0), decMPLR(0),
    decMPLC(0), binMPLR(0), binMPLC(0), step(1) { }

// Regular Constructor
Multiply::Multiply(int bMPLR, int bMPLC, int dMPLR, int dMPLC):
	mq(bMPLR), mdr(bMPLC), carry(0), acc(0),
	decMPLR(dMPLR), decMPLC(dMPLC), binMPLR(bMPLR),
        binMPLC(bMPLC), step(1) { }

// Prints initial state of registers
void Multiply::printInitial(){
  cout << "c and acc set to 0" << endl;

  cout << "mq set to multiplier    = " << decMPLR;
  cout << " decimal and ";
  prt_bin(mq);
  cout << " binary" << endl;

  cout << "mdr set to multiplicand = " << decMPLC;
  cout << " decimal and ";
  prt_bin(mdr);
  cout << " binary" << endl;

  // Printing line separating initial state
  cout << "----------------------------";
  cout << "----------------------------" << endl;
}

// Prints current step in multplication process
void Multiply::printStep() {
  // Printing step number
  cout << "step " << step << ":   ";

  // Printing registers set up for addition
  cout << carry << " ";
  prt_bin(acc); 
  cout << " ";
  prt_bin(mq);
  cout << endl << "        +   ";

  // Prints which number is added to the acc, depending on the
  // lsb of the multiplier in the mq
  if ( check_LSB() ) {
    prt_bin(mdr);
    cout << "        ^ add based on lsb=1" << endl;
    // Adding carry, acc, and mdr
    addBits();
  }
  else {
    prt_bin(0);
    cout << "        ^ no add based on lsb=0" << endl;
  }
  cout << "          ----------" << endl;

  // Printing registers after addition but before right shift
  cout << "          " << carry << " ";
  prt_bin(acc);
  cout << " ";
  prt_bin(mq);
  cout << endl;

  // Printing registers after right shift
  shiftRight();
  cout << "       >>                     shift right" << endl;

  cout << "          " << carry << " ";
  prt_bin(acc);
  cout << " ";
  prt_bin(mq);
  cout << endl;

  // Printing line separating step
  cout << "------------------------------------";
  cout << "--------------------" << endl;

  // Incrementing step counter for the next step
  step++;
}

// Prints binary number in 8-bit format
void Multiply::prt_bin(int bin) {
  cout << setfill('0') << setw(8) << bin;
}

// Checks if the least significant bit (lsb) of mq is a 1
bool Multiply::check_LSB() {
  if (mq % 2 == 0) {
    return false;
  }
   
  return true;
}

// Prints the check section to compare the binary and decimal
// representations 
void Multiply::printCheck() {
  // Printing multiplicand * multiplier in binary and decimal notation
  cout << "check:                binary   decimal" << endl;
  cout << "                    ";
  prt_bin(binMPLC);
  cout << "       " << setw(3) << setfill(' ') << decMPLC << endl;
  cout << "          x         ";
  prt_bin(binMPLR);
  cout << "  x    " << setw(3) << setfill(' ') << decMPLR << endl;
  cout << "            ----------------    ------" << endl;

  // Printing product in binary and decimal notation
  cout << "            ";
  prt_bin(acc);
  prt_bin(mq);
  cout << "    " << setw(6) << setfill(' ') << decMPLC*decMPLR << endl;
}

/* Puts the values of the register in a 2D array to keep
   track of bit positions in order to perform addition 
   Checks each corresponding bit in the bit positions to 
   determine what the sum and carry out will be
   Changes acc and carry based on the sum 
*/
void Multiply::addBits() {
  int sum = 0;
  int shift = 1;  
  int a = acc;
  int b = mdr;

  // Creating a temporary 2D array to store carry, acc, and mdr
  // row 0 (c) = carry, row 1 (a) = acc, row 2 (b) = mdr
  int arr[3][9] = {0};

  arr[0][8] = carry;

  if (a != 0) {
    for(int i = 8; i > 8 - numLength(acc); i--) {
      arr[1][i] = a % 2;
      a /= 10;
    }
  }

  if (b != 0) {
    for(int j = 8; j > 8 - numLength(mdr); j--) {
      arr[2][j] = b % 2;
      b /= 10;
    }
  }

  /* Full Adder:
     Checking each bit position to determine what the sum and carry out
     will be
     arr[0] (Cin/Cout) = carry, arr[1] (A) = acc, arr[2] (B) = mdr
  */
  for(int i = 8; i > 0; i--) {
    // If Cin = 1, A = 0, and B = 0, Then Cout = 0, S = 1
    if( (arr[0][i] == 1) && (arr[1][i] == 0) && (arr[2][i] == 0) ) {
      sum += shift;
    }
    // If Cin = 0, A = 1, and B = 0, Then Cout = 0, S = 1
    if( (arr[0][i] == 0) && (arr[1][i] == 1) && (arr[2][i] == 0) ) {
      sum += shift;
    }
    // If Cin = 1, A = 1, and B = 0, Then Cout = 1, S = 0
    if( (arr[0][i] == 1) && (arr[1][i] == 1) && (arr[2][i] == 0) ) {
      arr[0][i-1] = 1;
    }
    // If Cin = 0, A = 0, and B = 1, Then Cout = 0, S = 1
    if( (arr[0][i] == 0) && (arr[1][i] == 0) && (arr[2][i] == 1) ) {
      sum += shift;
    }
    // If Cin = 1, A = 0, and B = 1, Then Cout = 1, S = 0
    if( (arr[0][i] == 1) && (arr[1][i] == 0) && (arr[2][i] == 1) ) {
      arr[0][i-1] = 1;
    }
    // If Cin = 0, A = 1, and B = 1, Then Cout = 1, S = 0
    if( (arr[0][i] == 0) && (arr[1][i] == 1) && (arr[2][i] == 1) ) {
      arr[0][i-1] = 1;
    }
    // If Cin = 1, A = 1, and B = 1, Then Cout = 1, S = 1
    if( (arr[0][i] == 1) && (arr[1][i] == 1) && (arr[2][i] == 1) ) {
      arr[0][i-1] = 1;
      sum += shift;
    }

    // Shift moves to the next bit position to the left
    shift *= 10;
  }
  
  // carry becomes the last Cout value (0 or 1)
  carry = arr[0][0];
  // acc now holds the sum
  acc = sum;
}

// Finds the number of digits of the input number
int Multiply::numLength(int num) {
  int length = 1;

  // Parses through each decimal place and increments as it goes
  // until the number is 0
  if (num > 0) {
    for (length = 0; num > 0; length++) {
      num /= 10;
    }
  } 

  return length;
}

// Shifts the bits of carry, acc, and mq to the right by one
void Multiply::shiftRight() {
  // Will be placed in the msb of the next number
  // Storing carry to be placed in the msb of acc
  int carryOver = carry;
  
  // Will store shifted value of original
  int tempNum = 0;

  // bit position 8
  int msb = 10000000;

  // Shifting carry to the right by 1
  carry = 0;

  // Storing shifted value of acc
  tempNum = acc / 10;  
  // Places carryOver in msb (bit position 8) of tempNum
  tempNum += carryOver * msb;   
  // Storing the lsb of acc to be carried over to mq  
  carryOver = acc % 2;
  // acc is now shifted right by 1
  acc = tempNum;

  // Storing shifted value of mq
  tempNum = mq / 10;  
  // Places carryOver in msb (bit position 8) of tempNum
  tempNum += carryOver * msb;   
  // mq is now shifted right by 1
  mq = tempNum; 
}
