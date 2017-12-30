#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QList>
#include "ui_maindialog.h"
#include "abselfheader.h"
#include "abselfprogram.h"


class MainDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MainDialog(QWidget *parent = 0);
    
    void parse_program_header(int offset, int num, int size, unsigned char *start);
signals:
    
public slots:
    QString choose_file(void) const;
    void    do_parse_file(void);
    
private:
    void       make_connections(void);
    QByteArray open_file(const QString file_name) const;
    void       display_elf_header(void);
    void       display_program_header(void);
    void       init_system(void);
    void       make_phdr_table_empty(void);

private:
    Ui::MainDlg         *ui;
    QString              file_name;
    AbsElfHeader        *elf_header;

    QList<AbsElfProgram> phdr_list;
};

#endif // MAINDIALOG_H
