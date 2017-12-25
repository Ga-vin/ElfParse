#ifndef ABSELFPROGRAM_H
#define ABSELFPROGRAM_H

#include <QObject>

class AbsElfProgram : public QObject
{
    Q_OBJECT
public:
    explicit AbsElfProgram(QObject *parent = 0);
    

public:
    typedef enum PT_TYPE_VALUES {
        PT_NULL                  = 0x0,        /* Program header table entry unused */
        PT_LOAD                  = 0x1,        /* Loadable program segment          */
        PT_DYNAMIC               = 0x2,        /* Dynamic linking information       */
        PT_INTERP                = 0x3,        /* Program interpreter               */
        PT_NOTE                  = 0x4,        /* Auxiliary informatio              */
        PT_SHLIB                 = 0x5,        /* Reserved                          */
        PT_PHDR                  = 0x6,        /* Entry for header table itself     */
        PT_NUM                   = 0x7,        /* Number of defined types           */
        PT_LOOS                  = 0x60000000, /* Start of OS-specific              */
        PT_HIOS                  = 0x6FFFFFFF, /* End of OS-specific                */
        PT_LOPROC                = 0x70000000, /* Start of processor-specific       */
        PT_HIPROC                = 0x7FFFFFFF  /* End of processor-specific         */
    } PT_Type_Values_e;

    typedef enum PT_FLAG_VALUES {
        PF_X                     = 0x1,        /* Segment is executable             */
        PF_W                     = 0x2,        /* Segment is writable               */
        PF_R                     = 0x4,        /* Segment is readable               */
        PF_MASKPROC              = 0xF0000000  /* Processor-specific                */
    } PT_Flag_Values_e;

signals:
    
public slots:
    
};

#endif // ABSELFPROGRAM_H
