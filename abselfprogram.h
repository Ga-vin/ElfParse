#ifndef ABSELFPROGRAM_H
#define ABSELFPROGRAM_H

#include <QObject>
#include "elf.h"

class AbsElfProgram : public QObject
{
    Q_OBJECT
public:
    explicit AbsElfProgram(QObject *parent = 0);
    AbsElfProgram(Elf_Phdr phdr, QObject *parent = 0);
    AbsElfProgram(const AbsElfProgram &phdr, QObject *parent = 0);
    ~AbsElfProgram();

    QString get_type(void) const;
    QString get_offset(void) const;
    QString get_virtaddr(void) const;
    QString get_phyaddr(void) const;
    QString get_file_size(void) const;
    QString get_mem_size(void) const;
    QString get_flag(void) const;
    QString get_align(void) const;

    static void byte_to_phdr(const uint8_t *p_start, Elf_Phdr *phdr);

    AbsElfProgram &operator=(const AbsElfProgram &phdr);
    bool           operator==(const AbsElfProgram &phdr);

private:
    void parse_program_header(Elf_Phdr phdr);
    bool is_program_header_ok(void);

public:
    typedef enum PT_TYPE_VALUES {
        PT_NULL                  = 0x0,        /* Program header table entry unused */
        PT_LOAD                  = 0x1,        /* Loadable program segment          */
        PT_DYNAMIC               = 0x2,        /* Dynamic linking information       */
        PT_INTERP                = 0x3,        /* Program interpreter               */
        PT_NOTE                  = 0x4,        /* Auxiliary informatio              */
        PT_SHLIB                 = 0x5,        /* Reserved                          */
        PT_PHDR                  = 0x6,        /* Entry for header table itself     */
        PT_TLS                   = 0x7,        /* Number of defined types           */
        PT_LOOS                  = 0x60000000, /* Start of OS-specific              */
        PT_HIOS                  = 0x6FFFFFFF, /* End of OS-specific                */
        PT_LOPROC                = 0x70000000, /* Start of processor-specific       */
        PT_HIPROC                = 0x7FFFFFFF, /* End of processor-specific         */
        PT_GNU_EH_FRAME          = 0x6474E550,
        PT_GNU_STACK             = (PT_LOOS + 0x474E551)
    } PT_Type_Values_e;

    typedef enum PT_FLAG_VALUES {
        PF_X                     = 0x1,        /* Segment is executable             */
        PF_W                     = 0x2,        /* Segment is writable               */
        PF_R                     = 0x4,        /* Segment is readable               */
        PF_MASKPROC              = 0xF0000000  /* Processor-specific                */
    } PT_Flag_Values_e;

signals:
    
public slots:

public:
    QString type;
    QString offset;
    QString virt_addr;
    QString phy_addr;
    QString file_size;
    QString mem_size;
    QString flag;
    QString align;
    
    bool is_ok;
};

#endif // ABSELFPROGRAM_H
