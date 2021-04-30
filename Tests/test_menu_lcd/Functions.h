#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
using namespace std;

String mid(String str, int start, int len) {
   int t = 0;
   String u = ""; 
   
   for (t = 0; t < len;t++) {
    u = u + str.charAt(t+start-1);
   }
   return u;
}

int inStrRev(String str,String chr) {
  int t = str.length()-1;
  int u = 0;
   while (t>-1) {
    if (str.charAt(t)==chr.charAt(0)) {
      u = t+1;t = -1;
    }
    t = t - 1;
   }
  return u;
}

int len(String str) {
  return str.length();
}

#endif
