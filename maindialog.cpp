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

    init_system();
    make_connections();
    setWindowTitle(QObject::tr("ELF�ļ���������"));
    setWindowIcon(QIcon(":images/elf_main.ico"));
}

void MainDialog::parse_program_header(int offset, int num, int size, unsigned char *start)
{
    unsigned char *p_data = start + offset;

#ifdef __DEBUG_PRINT
    qDebug() << "offset: " << offset << "num: " << num << "size: " << size;
#endif
    if ( size != sizeof(Elf_Phdr)) {
        QMessageBox::warning(0,
                             QObject::tr("����"),
                             QObject::tr("����ͷ����С��ELF�ļ�ͷ���м�¼��һ��"));

        return ;
    }

    for (int i = 0; i < num; ++i) {
        Elf_Phdr phdr;
        AbsElfProgram::byte_to_phdr(p_data, &phdr);
        AbsElfProgram ph(phdr);
        phdr_list.append(ph);
        p_data += size;
    }
#ifdef __DEBUG_PRINT
    qDebug() << "list size: " << phdr_list.size();
    qDebug() << "list[0] type: " << phdr_list.at(0).get_type() << "offset: " << phdr_list.at(0).get_offset();
    qDebug() << "list[1] type: " << phdr_list.at(1).get_type() << "offset: " << phdr_list.at(1).get_offset();
    qDebug() << "list[2] type: " << phdr_list.at(2).get_type() << "offset: " << phdr_list.at(2).get_offset();
    qDebug() << "list[3] type: " << phdr_list.at(3).get_type() << "offset: " << phdr_list.at(3).get_offset();
#endif
}

QString MainDialog::choose_file(void ) const
{
    QString file_name = QFileDialog::getOpenFileName(0,
                                                     QObject::tr("ѡ��Ҫ�鿴��ELF�ļ�"),
                                                     QDir::currentPath());
    if ( file_name.isEmpty()) {
        QMessageBox::warning(0,
                             QObject::tr("����"),
                             QObject::tr("��û��ѡ��һ��ELF�ļ�"));

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

    /* ����ELF�ļ�ͷ */
    elf_header = new AbsElfHeader(byte);

    if ( elf_header->is_parse_ok()) {
        display_elf_header();
    }
#ifdef __DEBUG_PRINT
    qDebug() << "offset: " << elf_header->get_ph_offset() << "cnt: " << elf_header->get_ph_item_cnt() <<
                "size: " << elf_header->get_ph_item_size();
#endif

    /* ��������ͷ�� */
    this->parse_program_header(elf_header->get_ph_offset().toInt(0, 16),
                               elf_header->get_ph_item_cnt().toInt(0, 16),
                               elf_header->get_ph_item_size().toInt(0, 16),
                               (unsigned char *)byte.data());
    this->display_program_header();

    /* ���������� */
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
                             QObject::tr("����"),
                             QObject::tr("��û��ѡ��һ��ELF�ļ�"));

        return (byte);
    }

    QFile file(file_name);
    if ( !file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(0,
                             QObject::tr("����"),
                             QObject::tr("��ELF�ļ�ʧ��"));

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

void MainDialog::display_program_header(void)
{
    int row_cnt;

    this->make_phdr_table_empty();

    for (int i = 0; i < phdr_list.size(); ++i) {
        row_cnt = this->ui->p_tab_phdr->rowCount();
        this->ui->p_tab_phdr->insertRow(row_cnt);

        this->ui->p_tab_phdr->setItem(row_cnt, 0, new QTableWidgetItem(QString("%1").arg(phdr_list.at(i).get_type())));
        this->ui->p_tab_phdr->setItem(row_cnt, 1, new QTableWidgetItem(QString("%1").arg(phdr_list.at(i).get_offset())));
        this->ui->p_tab_phdr->setItem(row_cnt, 2, new QTableWidgetItem(QString("%1").arg(phdr_list.at(i).get_virtaddr())));
        this->ui->p_tab_phdr->setItem(row_cnt, 3, new QTableWidgetItem(QString("%1").arg(phdr_list.at(i).get_phyaddr())));
        this->ui->p_tab_phdr->setItem(row_cnt, 4, new QTableWidgetItem(QString("%1").arg(phdr_list.at(i).get_file_size())));
        this->ui->p_tab_phdr->setItem(row_cnt, 5, new QTableWidgetItem(QString("%1").arg(phdr_list.at(i).get_mem_size())));
        this->ui->p_tab_phdr->setItem(row_cnt, 6, new QTableWidgetItem(QString("%1").arg(phdr_list.at(i).get_flag())));
        this->ui->p_tab_phdr->setItem(row_cnt, 7, new QTableWidgetItem(QString("%1").arg(phdr_list.at(i).get_align())));
    }
    this->ui->p_tab_phdr->selectRow(row_cnt);
}

void MainDialog::init_system()
{
    //this->ui->p_tab_phdr->horizontalHeader()->setStretchLastSection(true);
    this->ui->p_tab_phdr->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    this->ui->p_tab_shdr->horizontalHeader()->setStretchLastSection(true);

    this->ui->p_tab_phdr->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->p_tab_shdr->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->ui->p_tab_phdr->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->p_tab_shdr->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainDialog::make_phdr_table_empty(void)
{
    for (int i = 0; i < this->ui->p_tab_phdr->rowCount(); ++i) {
        this->ui->p_tab_phdr->removeRow(i);
    }
}
