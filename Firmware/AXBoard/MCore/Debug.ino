/*************************************
  Debug - YamaX Arduino Core v3.0
  debug block
  made by coord.e, Y-modify
  Copyright © 2016 Y-modify All Rights Reserved.
*************************************/

#include <stdarg.h>

#define BUFFSIZE 128

void print_c(char *fmt, ... ) {
  if (encout) {
    char buf[BUFFSIZE]; // resulting string limited to 128 chars
    va_list args;
    va_start (args, fmt );
    vsnprintf(buf, 128, fmt, args);
    va_end (args);
    console += String(buf);
    Serial.print(buf);
  }
}
