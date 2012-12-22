#ifndef RAINBOW_H
#define RAINBOW_H

#include <stdio.h>

// a chain is made of a status byte, a hash and a string
// the length of a chain is therefore 1+hlen+slen (sizeofChain)

typedef unsigned char u8;
typedef unsigned int  u32;

typedef struct
{
	u32   n_chains;    // number of currently active chains
	u32   a_chains;    // space available for 'a_chains' chains
	u32   sizeofChain; // memory size of a chain
	char* chains;      // data (chain array)

	u32   hlen;
	u32   slen;
	char* charset;
	u32   clen;
	u32   l_chains;

	char* bufstr1;
	char* bufstr2;
	char* bufhash;
	char* bufchain;
} RTable;

// generation
RTable* RTable_New      (u32 length, char* chars, u32 depth, u32 count);
void    RTable_Delete   (RTable* rt);
char    RTable_AddChain (RTable* rt, char* hash, char* str);
void    RTable_Transfer (RTable* rt1, RTable* rt2);
char    RTable_FindChain(RTable* rt);
void    RTable_Sort     (RTable* rt);

// loading and storing
void    RTable_ToFile   (RTable* rt, FILE* f);
RTable* RTable_FromFile (u32 slen, char* charset, u32 l_chains, FILE* f);
void    RTable_ToFileN  (RTable* rt, const char* filename);
RTable* RTable_FromFileN(u32 slen, char* charset, u32 l_chains, const char* filename);

// misc
RTable* RTable_Merge    (RTable* rt1, RTable* rt2);
void    RTable_Print    (RTable* rt);
char    RTable_Reverse  (RTable* rt, char* target, char* dest);

// internal use
void RTable_Mask (RTable* rt, u32 step, char* hash, char* str); // hash to str "mask function"
void RTable_QSort(RTable* rt, u32 left, u32 right);    // quick sort
int  RTable_BFind(RTable* rt, char* hash);                               // binary search
u32  RTable_HFind(RTable* rt, char* str);                                // hash table search

// useful functions
char bstrncmp   (char* a, char* b, int n);
void hex2hash   (char* hex, char* hash, u32 hlen);
void printHash  (char* hash, u32 hlen);
void printString(char* str, u32 slen);

#endif
