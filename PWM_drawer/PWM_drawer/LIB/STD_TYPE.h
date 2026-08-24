#ifndef STD_TYPE_H
#define STD_TYPE_H


// unsigned data
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;
typedef unsigned long long int u64;


// signed data
typedef char s8;
typedef short int s16;
typedef long int s32;
typedef long long int s64;


// floating-point data
typedef float f32;
typedef double f64;


// Boolean
typedef enum {F, T} Bool;


// null, nul
#define null ((void*)0)
#define nul '\0'


#endif
