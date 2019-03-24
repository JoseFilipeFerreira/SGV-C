/**
@file formating.h
\brief Módulo de formatação de texto.
*/
#ifndef ___FORMATING_H___
#define ___FORMATING_H___

#define KBLK  "\x1B[30m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KORG  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KROXO "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KGREY "\x1B[37m"
#define KWHT  "\x1B[38m"
#define BOLD  "\033[1m"
#define UNDER "\033[4m"
#define BLINK "\033[5m"

#define RESET "\033[0m"

#define HIDE_CURSOR "\x1B[?25l"
#define SHOW_CURSOR "\x1B[?25h"

#define BACK 0
#define EXIT -1
#define MAX_FILE_NAME 256

#endif
