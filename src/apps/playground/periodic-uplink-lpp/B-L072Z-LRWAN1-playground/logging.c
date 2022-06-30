#include <stdio.h>

#include <board.h>

#include "logging.h"

void _log_printf( bool line_begin, const char *format, ... )
{
    if ( line_begin == true ) {
        printf( "%08lu : ", BoardGetTimeMs() );
    }

    va_list args;
    va_start( args, format );
    vprintf( format, args );
    va_end( args );
}