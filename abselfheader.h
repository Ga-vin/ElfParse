#ifndef ABSELFHEADER_H
#define ABSELFHEADER_H

#include <QObject>
#include "elf.h"

class AbsElfHeader : public QObject
{
    Q_OBJECT
public:
    explicit AbsElfHeader(QObject *parent = 0);
    AbsElfHeader(const QByteArray byte, QObject *parent = 0);
    ~AbsElfHeader();

    QString get_file_class(void) const;
    QString get_file_data(void) const;
    QString get_file_type(void) const;
    QString get_header_version(void) const;
    QString get_os_abi(void) const;
    QString get_os_abi_version(void) const;
    QString get_cpu_flags(void) const;
    QString get_header_size(void) const;
    QString get_machine(void) const;
    QString get_version(void) const;

    QString get_entry(void) const;
    QString get_ph_offset(void) const;
    QString get_ph_item_size(void) const;
    QString get_ph_item_cnt(void) const;

    QString get_sh_offset(void) const;
    QString get_sh_item_size(void) const;
    QString get_sh_item_cnt(void) const;
    QString get_sh_str_item_index(void) const;

    QString get_magic_number(void) const;

    bool    is_parse_ok(void) const;

public:
    typedef enum EI_MAG_INDEX {
        EI_MAG0             = 0x0,
        EI_MAG1             = 0x1,
        EI_MAG2             = 0x2,
        EI_MAG3             = 0x3,
        EI_CLASS            = 0x4,
        EI_DATA             = 0x5,
        EI_VERSION          = 0x6,
        EI_OSABI            = 0x7,
        EI_ABIVERSION       = 0x8,
        EI_PAD              = 0x9,
        EI_MAG16            = 0x10
    } EI_Mag_Index_e;

    typedef enum EI_MAG_VALUES {
        ELFMAG0             = 0x7F,
        ELFMAG1             = 'E',
        ELFMAG2             = 'L',
        ELFMAG3             = 'F'
    } EI_Mag_Values_e;

    typedef enum EI_CLASS_VALUES {
        ELFCLASSNONE        = 0x0,
        ELFCLASS32          = 0x1,
        ELFCLASS64          = 0x2,
        ELFCLASSNUM         = 0x3
    } EI_Class_Values_e;

    typedef enum EI_DATA_VALUES {
        ELFDATANONE         = 0x0,
        ELFDATA2LSB         = 0x1,
        ELFDATA2MSB         = 0x2,
        ELFDATANUM          = 0x3
    } EI_Data_Values_e;

    typedef enum EI_OSABI_VALUES {
        ELFOSABI_SYSV       = 0x0,
        ELFOSABI_HPUX       = 0x1,
        ELFOSABI_NETBSD     = 0x2,
        ELFOSABI_SOLARIS    = 0x6,
        ELFOSABI_AIX        = 0x7,
        ELFOSABI_IRIX       = 0x8,
        ELFOSABI_FREEBSD    = 0x9,
        ELFOSABI_TRU64      = 0xA,
        ELFOSABI_MODESTO    = 0xB,
        ELFOSABI_OPENBSD    = 0xC,
        ELFOSABI_OPENNVMS   = 0xD,
        ELFOSABI_NSK        = 0xE,
        ELFOSABI_ARM        = 0x61,
        ELFOSABI_AROS       = 0xF,
        ELFOSABI_STANDALONE = 0xFF
    } EI_OSAbi_Values_e;

    typedef enum ET_TYPE {
        ET_NONE             = 0x0,
        ET_REL              = 0x1,
        ET_EXEC             = 0x2,
        ET_DYN              = 0x3,
        ET_CORE             = 0x4,
        ET_NUM              = 0x5,
        ET_LOPROC           = 0xFF00,
        ET_HIPROC           = 0xFFFF,

        SHN_UNDEF           = 0x0
    } ET_Type_e;

    typedef enum EM_MACHINE {
        EM_NONE             = 0x0,
        EM_M32              = 0x1,
        EM_SPARC            = 0x2,
        EM_386              = 0x3,
        EM_68K              = 0x4,
        EM_88K              = 0x5,
        EM_486              = 0x6,
        EM_860              = 0x7,
        EM_MIPS             = 0x8,
        EM_S370             = 0x9,
        EM_MIPS_RS4_BE      = 0xA,
        EM_RS6000           = 0xB,

        EM_PARISC           = 0xF,
        EM_nCUBE            = 0x10,
        EM_VPP500           = 0x11,
        EM_SPARC32PLUS      = 0x12,
        EM_960              = 0x13,
        EM_PPC              = 0x14,
        EM_PPC64            = 0x15,
        EM_S390             = 0x16,

        EM_V800             = 0x24,
        EM_FR20             = 0x25,
        EM_RH32             = 0x26,
        EM_RCE              = 0x27,
        EM_ARM              = 0x28,
        EM_FAKE_ALPHA       = 0x29,
        EM_SH               = 0x2A,
        EM_SPARCV9          = 0x2B,
        EM_TRICORE          = 0x2C,
        EM_ARC              = 0x2D,
        EM_H8_300           = 0x2E,
        EM_H8_300H          = 0x2F,
        EM_H8S              = 0x30,
        EM_H8_500           = 0x31,
        EM_IA_64            = 0x32,
        EM_MIPS_X           = 0x33,
        EM_COLDFIRE         = 0x34,
        EM_68HC12           = 0x35,
        EM_MMA              = 0x36,
        EM_PCP              = 0x37,
        EM_NCPU             = 0x38,
        EM_NDR1             = 0x39,
        EM_STARCORE         = 0x3A,
        EM_ME16             = 0x3B,
        EM_ST100            = 0x3C,
        EM_TINYJ            = 0x3D,
        EM_X86_64           = 0x3E,
        EM_PDSP             = 0x3F,

        EM_FX66             = 0x42,
        EM_ST9PLUS          = 0x43,
        EM_ST7              = 0x44,
        EM_68HC16           = 0x45,
        EM_68HC11           = 0x46,
        EM_68HC08           = 0x47,
        EM_68HC05           = 0x48,
        EM_SVX              = 0x49,
        EM_ST19             = 0x4A,
        EM_VAX              = 0x4B,
        EM_CRIS             = 0x4C,
        EM_JAVELIN          = 0x4D,
        EM_FIREPATH         = 0x4E,
        EM_ZSP              = 0x4F,
        EM_MMIX             = 0x50,
        EM_HUANY            = 0x51,
        EM_PRISM            = 0x52,
        EM_AVR              = 0x53,
        EM_FR30             = 0x54,
        EM_D10V             = 0x55,
        EM_D30V             = 0x56,
        EM_V850             = 0x57,
        EM_M32R             = 0x58,
        EM_MN10300          = 0x59,
        EM_MN10200          = 0x5A,
        EM_PJ               = 0x5B,
        EM_OPENRISC         = 0x5C,
        EM_ARC_A5           = 0x5D,
        EM_XTENSA           = 0x5E,
        EM_VIDEOCORE        = 0x5F,
        EM_TMM_GPP          = 0x60,
        EM_NS32K            = 0x61,
        EM_TPC              = 0x62,
        EM_SNP1K            = 0x63,
        EM_ST200            = 0x64,
        EM_IP2K             = 0x65,
        EM_MAX              = 0x66,
        EM_CR               = 0x67,
        EM_F2MC16           = 0x68,
        EM_MSP430           = 0x69,
        EM_BLACKFIN         = 0x6A,
        EM_SE_C33           = 0x6B,
        EM_SEP              = 0x6C,
        EM_ARCA             = 0x6D,
        EM_UNICORE          = 0x6E,

        EM_ALPHA            = 0x9026,
        EM_C60              = 0x9C60
    } EM_Machine_e;

    typedef enum EV_VERSION_VALUES {
        EV_NONE             = 0x0,
        EV_CURRENT          = 0x1,
        EV_NUM              = 0x2
    } EV_Version_Values_e;
    
signals:
    
public slots:
    
private:
    void parse_elf_header(uint8_t *pbuf, int32_t len);

private:
    Elf_Ehdr *p_elf_header;
    bool      parse_ok;
};

#endif // ABSELFHEADER_H
