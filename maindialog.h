#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "ui_maindialog.h"
#include "abselfheader.h"


class MainDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MainDialog(QWidget *parent = 0);
    
signals:
    
public slots:
    QString choose_file(void) const;
    void    do_parse_file(void);
    
private:
    void       make_connections(void);
    QByteArray open_file(const QString file_name) const;
    void       display_elf_header(void);

private:
    Ui::MainDlg  *ui;
    QString       file_name;
    AbsElfHeader *elf_header;
};

#endif // MAINDIALOG_H
