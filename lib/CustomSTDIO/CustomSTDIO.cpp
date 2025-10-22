#include "CustomSTDIO.h"

static FILE *StdioStream;

static int PutChar(char ch, FILE *f)
{
    return Serial.write(ch);
}

static int GetChar(FILE *f)
{
    while (!Serial.available());
    return Serial.read();
}

void StdioSerialSetup(void)
{
    Serial.begin(9600);
    StdioStream = fdevopen(PutChar, GetChar);
    stdin  = StdioStream;
    stdout = StdioStream;
}

void printFloat(const char* label, float value, const char* suffix) {
  char buf[24];
  dtostrf(value, 0, 2, buf);// 2 signs after ,
  printf("%s%s%s\r\n", label, buf, suffix);
}

bool stdioHasData(){
    return Serial.available() > 0;
}

String stdioGetString(){
    return Serial.readStringUntil('\n');
}