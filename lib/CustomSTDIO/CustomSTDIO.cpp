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

void StdioSerialInit(void)
{
    Serial.begin(9600);
    StdioStream = fdevopen(PutChar, GetChar);
    stdin  = StdioStream;
    stdout = StdioStream;
}