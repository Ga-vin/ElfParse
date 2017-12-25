#include <QtGui>
#include <QtCore>
#include "abselfheader.h"

AbsElfHeader::AbsElfHeader(QObject *parent) :
    QObject(parent),
    parse_ok(false)
{
    p_elf_header = new Elf_Ehdr;
    memset(p_elf_header, 0, sizeof(Elf_Ehdr));
}

AbsElfHeader::AbsElfHeader(const QByteArray byte, QObject *parent) :
    QObject(parent),
    parse_ok(false)
{
    uint8_t *bufp = (uint8_t *)(byte.data());
    parse_elf_header(bufp, sizeof(Elf_Ehdr));
}

AbsElfHeader::~AbsElfHeader()
{
    delete p_elf_header;
}

QString AbsElfHeader::get_file_class(void) const
{
    QString file_class("");

    switch ( p_elf_header->e_ident[EI_CLASS]) {

    case ELFCLASSNONE:
        file_class.append(QObject::tr("未知的类别"));
        break;

    case ELFCLASS32:
        file_class.append(QObject::tr("32位目标"));
        break;

    case ELFCLASS64:
        file_class.append(QObject::tr("64位目标"));
        break;
    }

    return (file_class);
}

QString AbsElfHeader::get_file_data(void) const
{
    QString file_data("");

    switch (p_elf_header->e_ident[EI_DATA]) {

    case ELFDATANONE:
        file_data.append(QObject::tr("非法数据编码"));
        break;

    case ELFDATA2LSB:
        file_data.append(QObject::tr("高位在前-小端模式"));
        break;

    case ELFDATA2MSB:
        file_data.append(QObject::tr("低位在前-大端模式"));
        break;
    }

    return (file_data);
}

QString AbsElfHeader::get_file_type(void) const
{
    QString file_type("");

    switch (p_elf_header->e_type) {

    case ET_NONE:
        file_type.append(QObject::tr("未知目标文件格式"));
        break;

    case ET_REL:
        file_type.append(QObject::tr("可重定位文件"));
        break;

    case ET_EXEC:
        file_type.append(QObject::tr("可执行文件"));
        break;

    case ET_DYN:
        file_type.append(QObject::tr("共享目标文件"));
        break;

    case ET_CORE:
        file_type.append(QObject::tr("Core文件（转储文件）"));
        break;

    case ET_LOPROC:
        file_type.append(QObject::tr("特定处理器文件"));
        break;

    case ET_HIPROC:
        file_type.append(QObject::tr("特定处理器文件"));
        break;
    }

    return (file_type);
}

QString AbsElfHeader::get_header_version(void) const
{
    QString header_version("");

    switch (p_elf_header->e_ident[EI_VERSION]) {

    case EV_CURRENT:
        header_version.append(QObject::tr("1（当前）"));
        break;

    default:
        header_version.append(QObject::tr("未知版本类型"));
        break;
    }

    return (header_version);
}

QString AbsElfHeader::get_os_abi(void) const
{
    QString os_abi("");

    switch (p_elf_header->e_ident[EI_OSABI]) {

    case ELFOSABI_SYSV:
        os_abi.append("UNIX System V ABI");
        break;

    case ELFOSABI_HPUX:
        os_abi.append("HP-UX");
        break;

    case ELFOSABI_NETBSD:
        os_abi.append("NetBSD");
        break;

    case ELFOSABI_SOLARIS:
        os_abi.append("Sun Solaris");
        break;

    case ELFOSABI_AIX:
        os_abi.append("AIX");
        break;

    case ELFOSABI_IRIX:
        os_abi.append("IRIX");
        break;

    case ELFOSABI_FREEBSD:
        os_abi.append("FreeBSD");
        break;

    case ELFOSABI_TRU64:
        os_abi.append("Compaq TRU64 UNIX");
        break;

    case ELFOSABI_MODESTO:
        os_abi.append("Novell Modesto");
        break;

    case ELFOSABI_OPENBSD:
        os_abi.append("Open BSD");
        break;

    case ELFOSABI_OPENNVMS:
        os_abi.append("Open VMS");
        break;

    case ELFOSABI_NSK:
        os_abi.append("Hewlett-Packard Non-Stop Kernel");
        break;

    case ELFOSABI_ARM:
        os_abi.append("ARM");
        break;

    case ELFOSABI_AROS:
        os_abi.append("Amiga Research OS");
        break;

    case ELFOSABI_STANDALONE:
        os_abi.append("Standalone (embedded) application");
        break;
    }

    return (os_abi);
}

QString AbsElfHeader::get_os_abi_version(void) const
{
    return (QString("%1").arg(p_elf_header->e_ident[EI_ABIVERSION]));
}

void AbsElfHeader::parse_elf_header(uint8_t *pbuf, int32_t len)
{
    uint8_t *ptmp = pbuf;
    if ( len < sizeof(Elf_Ehdr)) {
        QMessageBox::warning(0,
                             QObject::tr("警告"),
                             QObject::tr("ELF文件头部长度不合法"));
        parse_ok = false;
        return ;
    }

    p_elf_header = new Elf_Ehdr;
    if ( !p_elf_header) {
        QMessageBox::warning(0,
                             QObject::tr("警告"),
                             QObject::tr("分配对象失败"));

        parse_ok = false;
        return ;
    }

    memcpy(p_elf_header->e_ident, ptmp, sizeof(uint8_t) * EI_NINDENT);
    ptmp += EI_NINDENT;

    if ( (ELFMAG0 != p_elf_header->e_ident[EI_MAG0]) ||
         (ELFMAG1 != p_elf_header->e_ident[EI_MAG1]) ||
         (ELFMAG2 != p_elf_header->e_ident[EI_MAG2]) ||
         (ELFMAG3 != p_elf_header->e_ident[EI_MAG3])) {
        QMessageBox::warning(0,
                             QObject::tr("警告"),
                             QObject::tr("该文件不是合法的ELF文件"));

        parse_ok = false;
        return ;
    }

    p_elf_header->e_type      = (ptmp[0]<<8) | (ptmp[1]<<0);
    ptmp += 2;

    p_elf_header->e_machine   = (ptmp[0]<<8) | (ptmp[1]<<0);
    ptmp += 2;

    p_elf_header->e_version   = (ptmp[0]<<24) | (ptmp[1]<<16) | (ptmp[2]<<8) | (ptmp[3]<<0);
    ptmp += 4;

    p_elf_header->e_entry     = (ptmp[0]<<24) | (ptmp[1]<<16) | (ptmp[2]<<8) | (ptmp[3]<<0);
    ptmp += 4;

    p_elf_header->e_phoff     = (ptmp[0]<<24) | (ptmp[1]<<16) | (ptmp[2]<<8) | (ptmp[3]<<0);
    ptmp += 4;

    p_elf_header->e_shoff     = (ptmp[0]<<24) | (ptmp[1]<<16) | (ptmp[2]<<8) | (ptmp[3]<<0);
    ptmp += 4;

    p_elf_header->e_flags     = (ptmp[0]<<24) | (ptmp[1]<<16) | (ptmp[2]<<8) | (ptmp[3]<<0);
    ptmp += 4;

    p_elf_header->e_ehsize    = (ptmp[0]<<8) | (ptmp[1]<<0);
    ptmp += 2;

    p_elf_header->e_phentsize = (ptmp[0]<<8) | (ptmp[1]<<0);
    ptmp += 2;

    p_elf_header->e_phnum     = (ptmp[0]<<8) | (ptmp[1]<<0);
    ptmp += 2;

    p_elf_header->e_shentsize = (ptmp[0]<<8) | (ptmp[1]<<0);
    ptmp += 2;

    p_elf_header->e_shnum     = (ptmp[0]<<8) | (ptmp[1]<<0);
    ptmp += 2;

    p_elf_header->e_shstrndx  = (ptmp[0]<<8) | (ptmp[1]<<0);

    parse_ok = true;
}

QString AbsElfHeader::get_cpu_flags(void) const
{
    return (QString("0x%1").arg(p_elf_header->e_flags, 0, 16));
}

QString AbsElfHeader::get_header_size(void) const
{
    return (QString("0x%1").arg(p_elf_header->e_ehsize, 0, 16));
}

QString AbsElfHeader::get_machine(void) const
{
    QString machine_name("");

    switch (p_elf_header->e_machine) {

    case EM_NONE:
        machine_name.append(QObject::tr("不可识别的ELF文件"));
        break;
    case EM_M32:
        machine_name.append("AT&T WE 32100");
        break;
    case EM_SPARC:
        machine_name.append("SPARC");
        break;
    case EM_386:
        machine_name.append("Intel 80386");
        break;
    case EM_68K:
        machine_name.append("Motorola 68000");
        break;
    case EM_88K:
        machine_name.append("Motorola 88000");
        break;
    case EM_486:
        machine_name.append("Intel 80480");
        break;
    case EM_860:
        machine_name.append("Intel 80860");
        break;
    case EM_MIPS:
        machine_name.append("MIPS I Architecture");
        break;
    case EM_S370:
        machine_name.append("IBM System/370 Processor");
        break;
    case EM_MIPS_RS4_BE:
        machine_name.append("MIPS R4000 big-endian");
        break;
    case EM_RS6000:
        machine_name.append("RS6000");
        break;
    case EM_PARISC:
        machine_name.append("Hewlett-Packard PA-RISC");
        break;
    case EM_nCUBE:
        machine_name.append("nCUBE");
        break;
    case EM_VPP500:
        machine_name.append("Fujitsu VPP500");
        break;
    case EM_SPARC32PLUS:
        machine_name.append("Enhanced instruction set SPARC");
        break;
    case EM_960:
        machine_name.append("Intel 80960");
        break;
    case EM_PPC:
        machine_name.append("PowerPC");
        break;
    case EM_PPC64:
        machine_name.append("64-bit PowerPC");
        break;
    case EM_S390:
        machine_name.append("IBM System/390 Processor");
        break;
    case EM_V800:
        machine_name.append("NEC V800");
        break;
    case EM_FR20:
        machine_name.append("Fujitsu FR20");
        break;
    case EM_RH32:
        machine_name.append("TRW RH-32");
        break;
    case EM_RCE:
        machine_name.append("Motorola RCE");
        break;
    case EM_ARM:
        machine_name.append("Advanced RISC Machines ARM");
        break;
    case EM_FAKE_ALPHA:
        machine_name.append("Digital Alpha");
        break;
    case EM_SH:
        machine_name.append("Hitachi SH");
        break;
    case EM_SPARCV9:
        machine_name.append("SPARC Version 9");
        break;
    case EM_TRICORE:
        machine_name.append("Siemens TriCore embedded processor");
        break;
    case EM_ARC:
        machine_name.append("Argonaut RISC Core, Argonaut Technologies Inc.");
        break;
    case EM_H8_300:
        machine_name.append("Hitachi H8/300");
        break;
    case EM_H8_300H:
        machine_name.append("Hitachi H8/300H");
        break;
    case EM_H8S:
        machine_name.append("Hitachi H8S");
        break;
    case EM_H8_500:
        machine_name.append("Hitachi H8/500");
        break;
    case EM_IA_64:
        machine_name.append("Intel IA-64 processor architecture");
        break;
    case EM_MIPS_X:
        machine_name.append("Stanford MIPS-X");
        break;
    case EM_COLDFIRE:
        machine_name.append("Motorola ColdFire");
        break;
    case EM_68HC12:
        machine_name.append("Motorola M68HC12");
        break;
    case EM_MMA:
        machine_name.append("Fujitsu MMA Multimedia Accelerator");
        break;
    case EM_PCP:
        machine_name.append("Siemens PCP");
        break;
    case EM_NCPU:
        machine_name.append("Sony nCPU embedded RISC processor");
        break;
    case EM_NDR1:
        machine_name.append("Denso NDR1 microprocessor");
        break;
    case EM_STARCORE:
        machine_name.append("Motorola Star*Core processor");
        break;
    case EM_ME16:
        machine_name.append("Toyota ME16 processor");
        break;
    case EM_ST100:
        machine_name.append("STMicroelectronics ST100 processor");
        break;
    case EM_TINYJ:
        machine_name.append("Advanced Logic Corp. TinyJ embedded processor family");
        break;
    case EM_X86_64:
        machine_name.append("AMD x86-64 architecture");
        break;
    case EM_PDSP:
        machine_name.append("Sony DSP Processor");
        break;
    case EM_FX66:
        machine_name.append("Siemens FX66 microcontroller");
        break;
    case EM_ST9PLUS:
        machine_name.append("STMicroelectronics ST9+ 8/16 bit microcontroller");
        break;
    case EM_ST7:
        machine_name.append("STMicroelectronics ST7 8-bit microcontroller");
        break;
    case EM_68HC16:
        machine_name.append("Motorola MC68HC16 Microcontroller");
        break;
    case EM_68HC11:
        machine_name.append("Motorola MC68HC11 Microcontroller");
        break;
    case EM_68HC08:
        machine_name.append("Motorola MC68HC08 Microcontroller");
        break;
    case EM_68HC05:
        machine_name.append("Motorola MC68HC05 Microcontroller");
        break;
    case EM_SVX:
        machine_name.append("Silicon Graphics SVx");
        break;
    case EM_ST19:
        machine_name.append("STMicroelectronics ST19 8-bit microcontroller");
        break;
    case EM_VAX:
        machine_name.append("Digital VAX");
        break;
    case EM_CRIS:
        machine_name.append("Axis Communications 32-bit embedded processor");
        break;
    case EM_JAVELIN:
        machine_name.append("Infineon Technologies 32-bit embedded processor");
        break;
    case EM_FIREPATH:
        machine_name.append("Element 14 64-bit DSP Processor");
        break;
    case EM_ZSP:
        machine_name.append("LSI Logic 16-bit DSP Processor");
        break;
    case EM_MMIX:
        machine_name.append("Donald Knuth's educational 64-bit processor");
        break;
    case EM_HUANY:
        machine_name.append("Harvard University machine-independent object files");
        break;
    case EM_PRISM:
        machine_name.append("SiTera Prism");
        break;
    case EM_AVR:
        machine_name.append("Atmel AVR 8-bit microcontroller");
        break;
    case EM_FR30:
        machine_name.append("Fujitsu FR30");
        break;
    case EM_D10V:
        machine_name.append("Mitsubishi D10V");
        break;
    case EM_D30V:
        machine_name.append("Mitsubishi D30V");
        break;
    case EM_V850:
        machine_name.append("NEC v850");
        break;
    case EM_M32R:
        machine_name.append("Mitsubishi M32R");
        break;
    case EM_MN10300:
        machine_name.append("Matsushita MN10300");
        break;
    case EM_MN10200:
        machine_name.append("Matsushita MN10200");
        break;
    case EM_PJ:
        machine_name.append("picoJava");
        break;
    case EM_OPENRISC:
        machine_name.append("OpenRISC 32-bit embedded processor");
        break;
    case EM_ARC_A5:
        machine_name.append("ARC Cores Tangent-A5");
        break;
    case EM_XTENSA:
        machine_name.append("Tensilica Xtensa Architecture");
        break;
    case EM_VIDEOCORE:
        machine_name.append("Alphamosaic VideoCore processor");
        break;
    case EM_TMM_GPP:
        machine_name.append("Thompson Multimedia General Purpose Processor");
        break;
    case EM_NS32K:
        machine_name.append("National Semiconductor 32000 series");
        break;
    case EM_TPC:
        machine_name.append("Tenor Network TPC processor");
        break;
    case EM_SNP1K:
        machine_name.append("Trebia SNP 1000 processor");
        break;
    case EM_ST200:
        machine_name.append("STMicroelectronics (www.st.com) ST200 microcontroller");
        break;
    case EM_IP2K:
        machine_name.append("Ubicom IP2xxx microcontroller family");
        break;
    case EM_MAX:
        machine_name.append("MAX Processor");
        break;
    case EM_CR:
        machine_name.append("National Semiconductor CompactRISC microprocessor");
        break;
    case EM_F2MC16:
        machine_name.append("Fujitsu F2MC16");
        break;
    case EM_MSP430:
        machine_name.append("Texas Instruments embedded microcontroller msp430");
        break;
    case EM_BLACKFIN:
        machine_name.append("Analog Devices Blackfin (DSP) processor");
        break;
    case EM_SE_C33:
        machine_name.append("S1C33 Family of Seiko Epson processors");
        break;
    case EM_SEP:
        machine_name.append("Sharp embedded microprocessor");
        break;
    case EM_ARCA:
        machine_name.append("Arca RISC Microprocessor");
        break;
    case EM_UNICORE:
        machine_name.append("Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University");
        break;
    case EM_ALPHA:
        machine_name.append("New type");
        break;
    case EM_C60:
        machine_name.append("New type");
        break;
    default:
        machine_name.append("未知类型");
        break;
    }

    return (machine_name);
}

QString AbsElfHeader::get_version(void) const
{
    return (QString("0x%1").arg(p_elf_header->e_version, 4, 16));
}

QString AbsElfHeader::get_entry(void) const
{
    return (QString("0x%1").arg(p_elf_header->e_entry, 0, 16));
}

QString AbsElfHeader::get_ph_offset(void) const
{
    if ( !(p_elf_header->e_phoff)) {
        return (QString("%1").arg(QObject::tr("无程序头部表")));
    } else {
        return (QString("0x%1%2").arg(p_elf_header->e_phoff, 0, 16).arg(QObject::tr("字节")));
    }
}

QString AbsElfHeader::get_ph_item_size(void) const
{
    return (QString("0x%1%2").arg(p_elf_header->e_phentsize, 0, 16).arg(QObject::tr("字节")));
}

QString AbsElfHeader::get_ph_item_cnt(void) const
{
    if ( !(p_elf_header->e_phnum)) {
        return (QString(QObject::tr("无程序头部表")));
    } else {
        return (QString("0x%1").arg(p_elf_header->e_phnum, 0, 16));
    }
}

QString AbsElfHeader::get_sh_offset(void) const
{
    if ( !(p_elf_header->e_shoff)) {
        return (QString("%1").arg(QObject::tr("无节区头部表")));
    } else {
        return (QString("0x%1%2").arg(p_elf_header->e_shoff, 0, 16).arg(QObject::tr("字节")));
    }
}

QString AbsElfHeader::get_sh_item_size(void) const
{
    return (QString("0x%1%2").arg(p_elf_header->e_shentsize, 0, 16).arg(QObject::tr("字节")));
}

QString AbsElfHeader::get_sh_item_cnt() const
{
    if ( !(p_elf_header->e_shnum)) {
        return (QString(QObject::tr("无节区头部表")));
    } else {
        return (QString("0x%1").arg(p_elf_header->e_shnum, 0, 16));
    }
}

QString AbsElfHeader::get_sh_str_item_index(void) const
{
    if ( SHN_UNDEF == p_elf_header->e_shstrndx) {
        return (QString(QObject::tr("无节区名称字符串表")));
    } else {
        return (QString("%1").arg(p_elf_header->e_shstrndx));
    }
}

QString AbsElfHeader::get_magic_number(void) const
{
    QString magic_number("");

    for (int i = 0; i < EI_NINDENT; ++i) {
        magic_number.append(QString("%1 ").arg(p_elf_header->e_ident[i], 2, 16));
    }

    return (magic_number.toUpper());
}

bool AbsElfHeader::is_parse_ok() const
{
    return (parse_ok);
}
