#ifndef ABSELFSECTION_H
#define ABSELFSECTION_H

#include <QObject>

class AbsElfSection : public QObject
{
    Q_OBJECT
public:
    explicit AbsElfSection(QObject *parent = 0);
    

public:
    typedef enum SH_TYPES {
        SHT_NULL          = 0x0,               /* Section header table entry unused */
        SHT_PROGBITS      = 0x1,               /* Program data                      */
        SHT_SYMTAB        = 0x2,               /* Symbol table                      */
        SHT_STRTAB        = 0x3,               /* String table                      */
        SHT_RELA          = 0x4,               /* Relocation entries with addends   */
        SHT_HASH          = 0x5,               /* Symbol hash table                 */
        SHT_DYNAMIC       = 0x6,               /* Dynamic linking information       */
        SHT_NOTE          = 0x7,               /* Notes                             */
        SHT_NOBITS        = 0x8,               /* Program space with no data (bss)  */
        SHT_REL           = 0x9,               /* Relocation entries, no addends    */
        SHT_SHLIB         = 0xA,               /* Reserve                           */
        SHT_DYNSYM        = 0xB,               /* Dynamic linker symbol table       */
        SHT_INIT_ARRAY    = 0xE,               /* Array of constructors             */
        SHT_FINI_ARRAY    = 0xF,               /* Array of destructors              */
        SHT_PREINIT_ARRAY = 0x10,              /* Array of pre-constructors         */
        SHT_GROUP         = 0x11,              /* Section group                     */
        SHT_SYMTAB_SHNDX  = 0x12,              /* Extended section indices          */
        SHT_NUM           = 0x13,              /* Number of defined types           */

        SHT_LOOS          = 0x60000000,        /* Start OS-specific                 */
        SHT_LOSUNW        = 0x6FFFFFFB,        /* Sun-specific low bound            */
        SHT_SUNW_COMDAT   = 0x6FFFFFFB,
        SHT_SUNW_syminfo  = 0x6FFFFFFC,
        SHT_GNU_verdef    = 0x6FFFFFFD,        /* Version definition section        */
        SHT_GNU_verneed   = 0x6FFFFFFE,        /* Version needs section             */
        SHT_GNU_versym    = 0x6FFFFFFF,        /* Version symbol table              */
        SHT_HISUNW        = 0x6FFFFFFF,        /* Sun-specific high bound           */
        SHT_HIOS          = 0x6FFFFFFF,        /* End OS-specific type              */

        SHT_LOPROC        = 0x70000000,        /* Start of processor-specific       */
        SHT_ARM_EXIDX     = 0x70000001,        /* Exception Index table             */
        SHT_ARM_PREEMPTMAP= 0x70000002,        /* dynamic linking pre-emption map   */
        SHT_ARM_ATTRIBUTES= 0x70000003,        /* Object file compatibility attrs   */
        SHT_HIPROC        = 0x7FFFFFFF,        /* End of processor-specific         */

        SHT_LOUSER        = 0x80000000,        /* Start of application-specific     */
        SHT_HIUSER        = 0x8FFFFFFF         /* End of application-specific       */
    } SH_Types_e;

    typedef enum SH_FLAGS {
        SHF_WRITE         = 0x1,               /* Writable                          */
        SHF_ALLOC         = 0x2,               /* Occupies memory during execution  */
        SHF_EXECINSTR     = 0x4,               /* Executable                        */
        SHF_MASKPROC      = 0xF0000000,        /* Processor-specific                */
        SHF_MERGE         = 0x10,
        SHF_STRINGS       = 0x20,
        SHF_INFO_LINK     = 0x40,
        SHF_LINK_ORDER    = 0x80,
        SHF_OS_NONCONFORMING = 0x100,
        SHF_GROUP         = 0x200,
        SHF_TLS           = 0x400,
        SHF_MASKOS        = 0x0FF00000,
        SHF_ORDERED       = 0x40000000,
        SHF_EXCLUDE       = 0x80000000
    } SH_Flags_e;

    typedef enum SH_SECTION_INDEX {
        SHN_UNDEF         = 0x0,               /* Undefined section                 */
        SHN_LORESERVE     = 0xFF00,            /* Start of reserved indices         */
        SHN_LOPROC        = 0xFF00,            /* Start of processor-specific       */
        SHN_HIPROC        = 0xFF1F,            /* End of processor-specific         */
        SHN_ABS           = 0xFFF1,            /* Associated symbol is absolute     */
        SHN_COMMON        = 0xFFF2,            /* Associated symbol is common       */
        SHN_HIRESERVE     = 0xFFFF             /* End of reserved indices           */
    } SH_Section_Index_e;

    typedef enum SH_ST_INFO {
        STB_LOCAL         = 0x0,               /* Local symbol                      */
        STB_GLOBAL        = 0x1,               /* Global symbol                     */
        STB_WEEK          = 0x2,               /* Weak symbol                       */
        STB_NUM           = 0x3,               /* Number of defined types           */
        STB_LOOS          = 0xA,               /* Start of OS-specific              */
        STB_HIOS          = 0xC,               /* End of OS-specific                */
        STB_LOPROC        = 0xD,               /* Start of processor-specific       */
        STB_HIPROC        = 0xF                /* End of processor-specific         */
    } SH_St_Info_e;

    typedef enum SH_BT_BIND {
        SYMINFO_BT_SELF   = 0xFFFF,            /* Symbol bound to self              */
        SYMINFO_BT_PARENT = 0xFFFE,            /* Symbol bound to parent            */
        SYMINFO_BT_LOWRESERVE = 0xFF00         /* Beginning of reserved entries     */
    } SH_Bt_Bind_e;

    typedef enum SH_BT_FLAGS {
        SYMINFO_FLG_DIRECT= 0x0001,            /* Direct bound symbol               */
        SYMINFO_FLG_PASSTHRU = 0x0002,         /* Pass-thru symbol for translator   */
        SYMINFO_FLG_COPY  = 0x0003,            /* Symbol is a copy-reloc            */
        SYMINFO_FLG_LAZYLOAD = 0x0004,         /* Symbol bound to object to be lazy loaded */

        SYMINFO_NONE      = 0x0,
        SYMINFO_CURRENT   = 0x1,
        SYMINFO_NUM       = 0x2
    } SH_Bt_Flags_e;

    typedef enum SH_ST_TYPE {
        STT_NOTYPE        = 0x0,               /* Symbol type is unspecified        */
        STT_OBJECT        = 0x1,               /* Symbol is a data object           */
        STT_FUNC          = 0x2,               /* Symbol is a code object           */
        STT_SECTION       = 0x3,               /* Symbol associated with a section  */
        STT_FILE          = 0x4,               /* Symbol's name is file name        */
        STT_NUM           = 0x5,               /* Number of defined types           */
        STT_GNU_IFUNC     = 0xA,               /* Symbol is a indirect code object  */
        STT_LOOS          = 0xB,               /* Start of OS-specific              */
        STT_HIOS          = 0xC,               /* End of OS-specific                */
        STT_LOPROC        = 0xD,               /* Start of processor-specific       */
        STT_HIPROC        = 0xF                /* End of processor-specific         */
    } SH_St_Type_e;

    typedef enum SH_ST_VISIBILITY {
        STV_DEFAULT       = 0x0,               /* Default symbol visibility rule    */
        STV_INTERNAL      = 0x1,               /* Processor specific hidden class   */
        STV_HIDDEN        = 0x2,               /* Sym unavailable in other modules  */
        STV_PROTECTED     = 0x3                /* Not preemptible, not exported     */
    } SH_St_Visibility_e;

signals:
    
public slots:
    
};

#endif // ABSELFSECTION_H
