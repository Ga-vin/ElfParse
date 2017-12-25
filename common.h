#ifndef COMMON_H
#define COMMON_H

typedef unsigned int       uint32_t;
typedef unsigned short int uint16_t;
typedef unsigned char      uint8_t;

typedef signed int         int32_t;
typedef signed short int   int16_t;
typedef signed char        int8_t;
//typedef char               int8_t;

typedef unsigned int       Elf32_Addr;
typedef unsigned short     Elf32_Half;
typedef unsigned int       Elf32_Off;
typedef unsigned int       Elf32_SWord;
typedef unsigned int       Elf32_Word;
typedef unsigned short     Elf32_Section;
typedef unsigned int       Elf32_Symndx;

typedef Elf32_Addr         Elf_Addr;
typedef Elf32_Half         Elf_Half;
typedef Elf32_Off          Elf_Off;
typedef Elf32_SWord        Elf_SWord;
typedef Elf32_Word         Elf_Word;
typedef Elf32_Section      Elf_Section;
typedef Elf32_Symndx       Elf_Symndx;

#endif // COMMON_H
