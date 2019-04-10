/**
@file formating.h
\brief Módulo de formatação de texto.
*/
#ifndef ___FORMATING_H___
#define ___FORMATING_H___

/**
@brief Change print color to blank
*/
#define KBLK  "\x1B[30m"
/**
@brief Change print color to red
*/
#define KRED  "\x1B[31m"
/**
@brief Change print color to green
*/
#define KGRN  "\x1B[32m"
/**
@brief Change print color to orange
*/
#define KORG  "\x1B[33m"
/**
@brief Change print color to blue
*/
#define KBLU  "\x1B[34m"
/**
@brief Change print color to purple
*/
#define KROXO "\x1B[35m"
/**
@brief Change print color to cyan
*/
#define KCYN  "\x1B[36m"
/**
@brief Change print color to grey
*/
#define KGREY "\x1B[37m"
/**
@brief Change print color to white
*/
#define KWHT  "\x1B[38m"
/**
@brief Change print to bold
*/
#define BOLD  "\033[1m"
/**
@brief Change print to under
*/
#define UNDER "\033[4m"
/**
@brief Change print to blinking
*/
#define BLINK "\033[5m"

/**
@brief Reset print color and formating
*/
#define RESET "\033[0m"

/**
@brief Hide cursor
*/
#define HIDE_CURSOR "\x1B[?25l"
/**
@brief show cursor
*/
#define SHOW_CURSOR "\x1B[?25h"

/**
@brief return back
*/
#define BACK 0
/**
@brief return exit
*/
#define EXIT -1
/**
@brief biggest file name in fat-32
*/
#define MAX_FILE_NAME 256

#endif
