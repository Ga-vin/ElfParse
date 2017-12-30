#include "abselfprogram.h"
#include <QtCore/qmath.h>

AbsElfProgram::AbsElfProgram(QObject *parent) :
    QObject(parent),
    type(""),
    offset(""),
    virt_addr(""),
    phy_addr(""),
    file_size(""),
    mem_size(""),
    flag(""),
    align(""),
    is_ok(false)
{

}

AbsElfProgram::AbsElfProgram(Elf_Phdr phdr, QObject *parent) :
    QObject(parent)
{
    this->parse_program_header(phdr);
    this->is_ok = true;
}

AbsElfProgram::AbsElfProgram(const AbsElfProgram &phdr, QObject *parent) :
    QObject(parent)
{
    type      = phdr.get_type();
    offset    = phdr.get_offset();
    virt_addr = phdr.get_virtaddr();
    phy_addr  = phdr.get_phyaddr();
    file_size = phdr.get_file_size();
    mem_size  = phdr.get_mem_size();
    flag      = phdr.get_flag();
    align     = phdr.get_align();
    is_ok     = true;
}

AbsElfProgram::~AbsElfProgram()
{

}

QString AbsElfProgram::get_type(void) const
{
    return (this->type);
}

QString AbsElfProgram::get_offset(void) const
{
    return (this->offset);
}

QString AbsElfProgram::get_virtaddr(void) const
{
    return (this->virt_addr);
}

QString AbsElfProgram::get_phyaddr(void) const
{
    return (this->phy_addr);
}

QString AbsElfProgram::get_file_size(void) const
{
    return (this->file_size);
}

QString AbsElfProgram::get_mem_size(void) const
{
    return (this->mem_size);
}

QString AbsElfProgram::get_flag(void) const
{
    return (this->flag);
}

QString AbsElfProgram::get_align(void) const
{
    return (this->align);
}

void AbsElfProgram::byte_to_phdr(const uint8_t *p_start, Elf_Phdr *phdr)
{
    unsigned char *p_tmp = (unsigned char *)p_start;

    phdr->p_type   = (*p_tmp << 24) | (*(p_tmp+1) << 16) | (*(p_tmp+2) << 8) | (*(p_tmp+3) << 0);
    p_tmp         += 4;
    phdr->p_offset = (*p_tmp << 24) | (*(p_tmp+1) << 16) | (*(p_tmp+2) << 8) | (*(p_tmp+3) << 0);
    p_tmp         += 4;
    phdr->p_vaddr  = (*p_tmp << 24) | (*(p_tmp+1) << 16) | (*(p_tmp+2) << 8) | (*(p_tmp+3) << 0);
    p_tmp         += 4;
    phdr->p_paddr  = (*p_tmp << 24) | (*(p_tmp+1) << 16) | (*(p_tmp+2) << 8) | (*(p_tmp+3) << 0);
    p_tmp         += 4;
    phdr->p_filesz = (*p_tmp << 24) | (*(p_tmp+1) << 16) | (*(p_tmp+2) << 8) | (*(p_tmp+3) << 0);
    p_tmp         += 4;
    phdr->p_memsz  = (*p_tmp << 24) | (*(p_tmp+1) << 16) | (*(p_tmp+2) << 8) | (*(p_tmp+3) << 0);
    p_tmp         += 4;
    phdr->p_flags  = (*p_tmp << 24) | (*(p_tmp+1) << 16) | (*(p_tmp+2) << 8) | (*(p_tmp+3) << 0);
    p_tmp         += 4;
    phdr->p_align  = (*p_tmp << 24) | (*(p_tmp+1) << 16) | (*(p_tmp+2) << 8) | (*(p_tmp+3) << 0);
}

AbsElfProgram &AbsElfProgram::operator =(const AbsElfProgram &phdr)
{
    if ( *this == phdr) {
        return (*this);
    }

    type      = phdr.get_type();
    offset    = phdr.get_offset();
    virt_addr = phdr.get_virtaddr();
    phy_addr  = phdr.get_phyaddr();
    file_size = phdr.get_file_size();
    mem_size  = phdr.get_mem_size();
    flag      = phdr.get_flag();
    align     = phdr.get_align();
    is_ok     = true;
}

bool AbsElfProgram::operator ==(const AbsElfProgram &phdr)
{
    if ( (this->get_type() == phdr.get_type()) &&
         (this->get_offset() == phdr.get_offset()) &&
         (this->get_virtaddr() == phdr.get_virtaddr()) &&
         (this->get_phyaddr() == phdr.get_phyaddr()) &&
         (this->get_file_size() == phdr.get_file_size()) &&
         (this->get_mem_size() == phdr.get_mem_size()) &&
         (this->get_flag() == phdr.get_flag()) &&
         (this->get_align() == phdr.get_align())) {
        return (true);
    } else {
        return (false);
    }
}

void AbsElfProgram::parse_program_header(Elf_Phdr phdr)
{
    switch (phdr.p_type) {
    case PT_NULL:
        this->type = "NULL";
        break;

    case PT_LOAD:
        this->type = "LOAD";
        break;

    case PT_DYNAMIC:
        this->type = "DYNAMIC";
        break;

    case PT_INTERP:
        this->type = "INTERP";
        break;

    case PT_NOTE:
        this->type = "NOTE";
        break;

    case PT_SHLIB:
        this->type = "SHLIB";
        break;

    case PT_PHDR:
        this->type = "PHDR";
        break;

    case PT_TLS:
        this->type = "NUM";
        break;

    case PT_LOOS:
        this->type = "LOOS";
        break;

    case PT_HIOS:
        this->type = "HIOS";
        break;

    case PT_LOPROC:
        this->type = "LOPROC";
        break;

    case PT_HIPROC:
        this->type = "HIPROC";
        break;

    case PT_GNU_EH_FRAME:
        this->type = "EH_FRAME";
        break;

    case PT_GNU_STACK:
        this->type = "STACK";
        break;

    default:
        this->type = "UNKNOWN";
        break;
    }

    this->offset    = QString("0x%1").arg(phdr.p_offset, 0, 16);
    this->virt_addr = QString("0x%1").arg(phdr.p_vaddr, 0, 16);
    this->phy_addr  = QString("0x%1").arg(phdr.p_paddr, 0, 16);
    this->file_size = QString("0x%1").arg(phdr.p_filesz, 0, 16);
    this->mem_size  = QString("0x%1").arg(phdr.p_memsz, 0, 16);

    switch (phdr.p_flags) {
    case PF_X:
        this->flag = QString("E");
        break;

    case PF_R:
        this->flag = QString("R");
        break;

    case PF_W:
        this->flag = QString("W");
        break;

    case (PF_W | PF_R):
        this->flag = QString("RW");
        break;

    case (PF_X | PF_R):
        this->flag = QString("RX");
        break;

    case (PF_X | PF_W):
        this->flag = QString("WX");
        break;

    case (PF_X | PF_R | PF_W):
        this->flag = QString("RWX");
        break;

    case PF_MASKPROC:
        this->flag = QString("MASKPROC");
        break;

    default:
        this->flag = QString(" ");
        break;
    }

    this->align = QString("2**%1").arg((int)(qLn(phdr.p_align) / qLn(2)));
}

bool AbsElfProgram::is_program_header_ok()
{
    return (this->is_ok);
}
