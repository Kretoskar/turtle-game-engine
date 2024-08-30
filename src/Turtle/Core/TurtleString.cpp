#include "Turtle/Core/TurtleString.h"

char Turtle::TurtleString::hashTable[Turtle::TurtleString::hashTableSize][hashTableMaxStringLenght] = { {'\0'} };