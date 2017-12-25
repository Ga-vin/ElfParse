#ifndef ELF_H
#define ELF_H

#include "common.h"
#define   EI_NINDENT    (16)

/* The ELF file header.  This appears at the start of every ELF file */
struct _Elf32_Ehdr {
    uint8_t    e_ident[EI_NINDENT];         /* Magic number and other info       */

    Elf_Half   e_type;                      /* Object file type                  */
    Elf_Half   e_machine;                   /* Architecture                      */

    Elf_Word   e_version;                   /* Object file version               */

    Elf_Addr   e_entry;                     /* Entry point virtual address       */

    Elf_Off    e_phoff;                     /* Program header table file offset  */
    Elf_Off    e_shoff;                     /* Section header table file offset  */

    Elf_Word   e_flags;                     /* Processor-specific flags          */

    Elf_Half   e_ehsize;                    /* Elf header size in bytes          */

    Elf_Half   e_phentsize;                 /* Program header table entry size   */
    Elf_Half   e_phnum;                     /* Program header table entry count  */

    Elf_Half   e_shentsize;                 /* Section header table entry size   */
    Elf_Half   e_shnum;                     /* Section header table entry count  */
    Elf_Half   e_shstrndx;                  /* Section header string table index */
};

typedef struct _Elf32_Ehdr   Elf32_Ehdr;
typedef Elf32_Ehdr           Elf_Ehdr;

/* Section header */
struct _Elf32_Shdr {
    Elf_Word   sh_name;                     /* Section name (string tbl index)   */
    Elf_Word   sh_type;                     /* Section type                      */
    Elf_Word   sh_flags;                    /* Section flags                     */

    Elf_Addr   sh_addr;                     /* Section virtual addr at execution */
    Elf_Off    sh_offset;                   /* Section file offset               */

    Elf_Word   sh_size;                     /* Section size in bytes             */
    Elf_Word   sh_link;                     /* Link to another section           */
    Elf_Word   sh_info;                     /* Additional section information    */
    Elf_Word   sh_addralign;                /* Section alignment                 */
    Elf_Word   sh_entsize;                  /* Entry size if section holds table */
};
typedef struct _Elf32_Shdr Elf32_Shdr;
typedef Elf32_Shdr         Elf_Shdr;

/* Symbol table entry */
struct _Elf32_Sym {
    Elf_Word   st_name;                     /* Symbol name (string tbl index)    */
    Elf_Addr   st_value;                    /* Symbol value                      */
    Elf_Word   st_size;                     /* Symbol size                       */

    uint8_t    st_info;                     /* Symbol type and binding           */
    uint8_t    st_other;                    /* No defined meaning, 0             */

    Elf_Half   st_shndx;                    /* Section index                     */
};
typedef struct _Elf32_Sym Elf32_Sym;
typedef Elf32_Sym         Elf_Sym;

/* The syminfo section if available contains additional information about
   every dynamic symbol.  */
struct _Elf32_Syminfo {
    Elf_Half   si_boundto;                   /* Direct bindings, symbol bound to */
    Elf_Half   si_flags;                     /* Per symbol flags                 */
};
typedef struct _Elf32_Syminfo Elf32_Syminfo;
typedef Elf32_Syminfo         Elf_Syminfo;

/* Relocation table entry without addend (in section of type SHT_REL)            */
struct _Elf32_Rel {
    Elf_Addr   r_offset;
    Elf_Word   r_info;
};
typedef struct _Elf32_Rel     Elf32_Rel;
typedef Elf32_Rel             Elf_Rel;

/* Relocation table entry with addend (in section of type SHT_RELA)              */
struct _Elf32_Rela {
    Elf_Addr   r_offset;
    Elf_Word   r_info;
    Elf_SWord  r_addend;
};
typedef struct _Elf32_Rela    Elf32_Rela;
typedef Elf32_Rela            Elf_Rela;

/* Program segment header                                                         */
struct _Elf32_Phdr {
    Elf_Word   p_type;                       /* Segment type                      */
    Elf_Off    p_offset;                     /* Segment file offset               */
    Elf_Addr   p_vaddr;                      /* Segment virtual address           */
    Elf_Addr   p_paddr;                      /* Segment physical address          */
    Elf_Word   p_filesz;                     /* Segment size in file              */
    Elf_Word   p_memsz;                      /* Segment size in memory            */
    Elf_Word   p_flags;                      /* Segment flags                     */
    Elf_Word   p_align;                      /* Segment alignment                 */
};
typedef struct _Elf32_Phdr   Elf32_Phdr;
typedef Elf32_Phdr           Elf_Phdr;

/* How to extract and insert information held in the st_info field               */
#define    ELF32_ST_BIND(b)                 ((b)>>4)
#define    ELF32_ST_TYPE(t)                 ((t)&0xF)
#define    ELF32_ST_INFO(b, t)              (((b)<<4) + ((t)&0xF))

/* How to extract and insert information held in the st_other field              */
#define    ELF32_ST_VISIBILITY(v)           ((v)&0x3)

/* How to extract and insert information held in the r_info field                */
#define    ELF32_R_SYM(s)                   ((s)>>8)
#define    ELF32_R_TYPE(t)                  ((t)&0xFF)
#define    ELF32_R_INFO(s, t)               (((s)<<8) + ((t)&0xFF))

#endif // ELF_H
