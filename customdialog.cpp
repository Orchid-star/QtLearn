#include "customdialog.h"
#include "ui_customdialog.h"

CCustomDialog::CCustomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCustomDialog)
{
    ui->setupUi(this);
}

CCustomDialog::~CCustomDialog()
{
    delete ui;
}

//static function
QList<QPair<QString, int> > CCustomDialog::MapInfoPair()
{
    CCustomDialog dlg;
    if(dlg.exec() == QDialog::Accepted){
        return dlg.getMapInfo();
    }
    return  QList<QPair<QString, int> >();
}

QList<QPair<QString, int>> CCustomDialog::getMapInfo()
{
    QPair<QString, int> pair1 = {ui->lineEdit_1->text(), ui->spinBox_1->value()};
    QPair<QString, int> pair2 = {ui->lineEdit_2->text(), ui->spinBox_2->value()};
    QPair<QString, int> pair3 = {ui->lineEdit_3->text(), ui->spinBox_3->value()};
    QPair<QString, int> pair4 = {ui->lineEdit_4->text(), ui->spinBox_4->value()};

    m_map_info.clear();
    m_map_info.append(pair1);
    m_map_info.append(pair2);
    m_map_info.append(pair3);
    m_map_info.append(pair4);

    return m_map_info;
}

void CCustomDialog::on_btnOK_clicked()
{
    accept();
}

void CCustomDialog::on_btnCancel_clicked()
{
    reject();
}
