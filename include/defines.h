#ifndef _DEFINES_H
#define _DEFINES_H

#define CATALOGUE_SIZE 10
#define CART_MAX_VALUE 50000

#ifdef _WIN32
    #define BOX_TOPLEFT L"\u2554"
    #define BOX_TOPRIGHT L"\u2557"
    #define BOX_HLINE L"\u2550"
    #define BOX_VLINE L"\u2551"
     #define BOX_BOTTOMLEFT L"\u255A"
    #define BOX_BOTTOMRIGHT L"\u255D"
#else
    #define wprintf printf
    #define BOX_TOPLEFT "\u2554"
    #define BOX_TOPRIGHT "\u2557"
    #define BOX_HLINE "\u2550"
    #define BOX_VLINE "\u2551"
    #define BOX_BOTTOMLEFT "\u255A"
    #define BOX_BOTTOMRIGHT "\u255D"
#endif

#endif