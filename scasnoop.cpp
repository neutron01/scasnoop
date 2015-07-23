/* scasnoop.cpp
 *
 * Revision History
 * scasnoop.cpp, read file, output peak waveforms
 * 
 * Usage
 * scasnoop (level, decimal) (no. samples, int) (separator, C or N) (filename)
 * $ ./scasnoop 0.35 C U235_400ug_24s_2.5k_r02.lvm
 *
 * Compile
 * $ g++ scasnoop.cpp -o scasnoop
 *
 * Author
 * rocampo 6/12/2015
 */
#include <stdlib.h>
#include <math.h>       // trunc
#include <string.h>     // strtok
#include <iostream>     // ifstream
#include <fstream>      // getline
using namespace std;

int main(int argc, char *argv[]) {
  // called correctly?
  if (argc != 5) {
    cout << "usage: ./scasnoop 0.35 C U235_400ug_24s_2.5k_r02.lvm" << endl;
    return 1;
  }
    
  const int size = 40;
  char separator[3] = ", ";
  if (!strcmp(argv[2], "N"))
    strcpy(separator, "\n");
  ifstream infile(argv[3]);         // filename
  char data[size], *temp;
  double level = atof(argv[1]);     // level of discriminator
  int total = 0;
  int line = 1;
  double signal;
    
  // skip over Labview header info
  for (int i = 0; i < 23; i++) {
    infile.getline(data, size);
  }
  
  while (infile) {
    infile.getline(data, size);
    signal = atof(data);
    if (signal > level) {
      cout << line << separator << signal << separator;
    }
    line++;
  } 
  cout << endl;
  infile.close();
  return 0;
}
