#include <QtGui>
#include <QtCore>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QTextCodec>
#include "maindialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDlg),
    file_name("")
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));

    make_connections();
    setWindowTitle(QObject::tr("ELF文件解析工具"));
    setWindowIcon(QIcon(":images/elf_main.ico"));
}

void MainDialog::parse_program_header(int offset, int num, unsigned char *start)
{
    for (int i = 0; i < num; ++i) {

    }
}

QString MainDialog::choose_file(void ) const
{
    QString file_name = QFileDialog::getOpenFileName(0,
                                                     QObject::tr("选择将要查看的ELF文件"),
                                                     QDir::currentPath());
    if ( file_name.isEmpty()) {
        QMessageBox::warning(0,
                             QObject::tr("警告"),
                             QObject::tr("还没有选择一个ELF文件"));

        return QString("");
    } else {
        ui->p_line_file_path->clear();
        ui->p_line_file_path->setText(file_name);
    }

    return (file_name);
}

void MainDialog::do_parse_file(void)
{
    QByteArray byte = open_file(ui->p_line_file_path->text());

    /* 解析ELF文件头 */
    elf_header = new AbsElfHeader(byte);

    if ( elf_header->is_parse_ok()) {
        display_elf_header();
    }

    /* 解析程序头部 */
}

void MainDialog::make_connections()
{
    QObject::connect(ui->p_btn_open_file, SIGNAL(clicked()), this, SLOT(choose_file()));
    QObject::connect(ui->p_btn_parse, SIGNAL(clicked()), this, SLOT(do_parse_file()));
}

QByteArray MainDialog::open_file(const QString file_name) const
{
    QByteArray byte;
    byte.resize(0);

    if ( file_name.isEmpty()) {
        QMessageBox::warning(0,
                             QObject::tr("警告"),
                             QObject::tr("还没有选择一个ELF文件"));

        return (byte);
    }

    QFile file(file_name);
    if ( !file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(0,
                             QObject::tr("警告"),
                             QObject::tr("打开ELF文件失败"));

        return (byte);
    } else {
        byte = file.readAll();

        return (byte);
    }
}

void MainDialog::display_elf_header()
{
    ui->p_line_ident->setText(elf_header->get_magic_number());
    ui->p_line_file_class->setText(elf_header->get_file_class());
    ui->p_line_file_data->setText(elf_header->get_file_data());
    ui->p_line_etype->setText(elf_header->get_file_type());
    ui->p_line_header_version->setText(elf_header->get_header_version());
    ui->p_line_osabi->setText(elf_header->get_os_abi());
    ui->p_line_abi_version->setText(elf_header->get_os_abi_version());
    ui->p_line_flags->setText(elf_header->get_cpu_flags());
    ui->p_line_header_size->setText(elf_header->get_header_size());
    ui->p_line_machine->setText(elf_header->get_machine());
    ui->p_line_version->setText(elf_header->get_version());
    ui->p_line_ph_offset->setText(elf_header->get_ph_offset());
    ui->p_line_ph_size->setText(elf_header->get_ph_item_size());
    ui->p_line_ph_num->setText(elf_header->get_ph_item_cnt());
    ui->p_line_entry->setText(elf_header->get_entry());
    ui->p_line_sh_offset->setText(elf_header->get_sh_offset());
    ui->p_line_sh_size->setText(elf_header->get_sh_item_size());
    ui->p_line_sh_num->setText(elf_header->get_sh_item_cnt());
    ui->p_line_sh_str_index->setText(elf_header->get_sh_str_item_index());
}
