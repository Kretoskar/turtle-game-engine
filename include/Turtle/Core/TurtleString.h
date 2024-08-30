#pragma once

#include "Turtle/Core/Logger.h"

#define FIND_HASH_CONFLICTS
#define SPOT_REHASHING

namespace Turtle
{
    class TurtleString
    {
    public:
        TurtleString()
            : hash(hashTableSize + 1) {}

        TurtleString(const char* s)
            : hash(Hash(s)) {}

    private:
        unsigned hash;

    public:
        const char* Get() const
        {
            return hashTable[hash];
        }

    private:
        // hash using prime numbers
        static constexpr unsigned Hash(const char* s)
        {
            unsigned h = 37;
            unsigned size = 0;

            while (*s)
            {
                h = (h * 54059) ^ (s[0] * 76963);
                size++;
                s++;
            }

            h %= hashTableSize;

            s = s - size;

#ifdef SPOT_REHASHING
            if (hashTable[h][0] != '\0')
            {
                TURTLE_LOG_WARNING("REHASHING SPOTTED")
            }
#endif

#ifdef FIND_HASH_CONFLICTS
            if (hashTable[h][0] != '\0')
            {
                for (unsigned i = 0; i < hashTableMaxStringLenght; i++)
                {
                    const char existingChar = hashTable[h][i];
                    const char newChar = *(s + i);

                    if (existingChar == newChar == '\0')
                    {
                        break;
                    }

                    if (existingChar != newChar)
                    {
                        TURTLE_LOG_ERROR("HASH CONFLICT")
                    }
                }
            }
#endif

            unsigned i = 0;

            while (*s)
            {
                hashTable[h][i] = *s;
                i++;
                s++;
            }

            return h;
        }

        static constexpr unsigned hashTableSize = 65536;
        static constexpr unsigned hashTableMaxStringLenght = 256;
        static char hashTable[hashTableSize][hashTableMaxStringLenght];

    public:
        bool operator==(TurtleString&& other) const
        {
            return other.hash == hash;
        }

        bool operator<(const TurtleString other) const
        {
            return hash < other.hash;
        }
    };
}

#undef FIND_HASH_CONFLICTS
#undef SPOT_REHASHING