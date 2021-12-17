#ifndef __STALE_H__
#define __STALE_H__

#define FALSE 0
#define TRUE 1
#define EOL '\n'
#define EOS '\0'

/* size definitions */

#define ID_STRING_LENGTH 32 /* max length of a line */
#define MAX_LINE_LENGTH 132 /* max length of a line */
#define TOKEN_SIZE 32       /* max length of a token */
#define MAX_SYMBOL 100      /* size of symbol table */
#define NONE -1             /* default token attribute */

#define DEBUG



#ifdef DEBUG
#define D_LN(x) std::cout << x << endl
#define D(x) std::cout << x

#endif // DEBUG
#ifndef DEBUG
#define D_LN(x) 
#define D(x) 
#endif // !DEBUG

#endif // __STALE_H__