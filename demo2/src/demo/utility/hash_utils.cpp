// hash_utils.cpp
#include "demo/utility/hash_utils.h"

namespace demo
{

namespace util
{

uint32 HashUtils::fnv1a( const String& value )
{
    uint32 hashCode = FNV_OFFSET_32;
    uint32 i;

    for ( i = 0; i < value.length(); ++i )
    {
        hashCode ^= value[i];
        hashCode *= FNV_PRIME_32;
    }

    return hashCode;
}

} // End nspc util

} // End nspc demo