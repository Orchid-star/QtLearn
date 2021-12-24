#include "widget.h"
#include "ui_widget.h"
#include "customdialog.h"
#include "qdebug.h"
#include "qcolor.h"
#include "qcolordialog.h"
#include "qfiledialog.h"
#include "qfontdialog.h"
#include "qinputdialog.h"
#include "qlineedit.h"
#include "qmessagebox.h"
#include "qprogressdialog.h"
#include "qerrormessage.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,p_err_dlg(nullptr)
{
    ui->setupUi(this);

    //自定义对话框
    QList<QPair<QString, int>> info = CCustomDialog::MapInfoPair();
    qDebug() << info;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    int index = ui->comboBox->currentIndex();

    switch (index) {
        case 0: {
            show_color_dialog();
            break;
        }
        case 1: {
            show_file_dialog();
            break;
        }
        case 2: {
            show_font_dialog();
            break;
        }
        case 3: {
            show_input_dialog();
            break;
        }
        case 4: {
            show_messgae_box();
            break;
        }
        case 5: {
            show_progress_dialog();
            break;
        }
        case 6: {
            show_error_message_dialog();
            break;
        }
        case 7: {
            show_wizard_dialog();
            break;
        }
    }
}

void Widget::show_color_dialog()
{
    //方式1
    QColor color = QColorDialog::getColor(Qt::red, this, tr("颜色对话框"));
    qDebug() << "color:" << color;
    //方式2
    color = QColorDialog::getColor(Qt::red, this, tr("颜色对话框"), QColorDialog::ShowAlphaChannel);
    qDebug() << "color:" << color;
    //方式3
    QColorDialog dlg(Qt::red, this);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    dlg.exec();
    color = dlg.currentColor();
    qDebug() << "color:" << color;
}

void Widget::show_file_dialog()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("文件对话框"), "G:", tr("所有文件(*.*)"));
    qDebug() << "fileName:" << filename;

    filename = QFileDialog::getOpenFileName(this, tr("文件对话框"), "G:", tr("图片文件(*.png *.jpg)"));
    qDebug() << "fileName:" << filename;

    filename = QFileDialog::getOpenFileName(this, tr("文件对话框"), "G:", tr("图片文件(*.png *.jpg);;文本文件(*.txt)"));
    qDebug() << "fileName:" << filename;

    QStringList ls_file = QFileDialog::getOpenFileNames(this, tr("文件对话框"), "G:", tr("图片文件(*.png *.jpg)"));
    qDebug() << "list fileName:" << ls_file;
}

void Widget::show_font_dialog()
{
    //ok用于标记是否单击了OK按钮
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok){
        qDebug() << "font:" << font;
    }
}

void Widget::show_input_dialog()
{
    bool ok;
    //获取字符串
    QString str = QInputDialog::getText(this, tr("输入字符对话框"), tr("请输入用户名:"), QLineEdit::Normal, tr("admin"), &ok);
    if(ok){
        qDebug() << "获取字符串:" << str;
    }

    //获取整数
    int value = QInputDialog::getInt(this, tr("输入整数对话框"), tr("请输入-100到100之间的数值"),100,-1000,1000,10,&ok);
    if(ok){
        qDebug() << "value:" << value;
    }

    //获取浮点数
    double value2 = QInputDialog::getDouble(this, tr("输入浮点数对话框"), tr("请输入-10到10之间的数值"),1,-10,10,1,&ok);
    if(ok){
        qDebug() << "value2:" << value2;
    }

    //获取条目
    QStringList items;
    items << tr("条目1") << tr("条目2");
    QString item = QInputDialog::getItem(this, tr("输入条目对话框"), tr("请选择或输入一个条目"),items, 0, true, &ok);
    if(ok){
        qDebug() << "item:" << item;
    }
}

void Widget::show_messgae_box()
{
    //问题对话框
    int ret1 = QMessageBox::question(this, tr("问题对话框"),tr("你了解Qt吗？"),QMessageBox::Yes,QMessageBox::No);
    if(ret1 == QMessageBox::Yes) qDebug() << tr("问题!");

    //提示对话框
    int ret2 = QMessageBox::information(this, tr("提示对话框"), tr("这是Qt书籍!"), QMessageBox::Ok);
    if(ret2 == QMessageBox::Ok) qDebug() << tr("提示!");

    //警告对话框
    int ret3 = QMessageBox::warning(this, tr("警告对话框"), tr("不能提前结束!"),QMessageBox::Abort);
    if(ret3 == QMessageBox::Abort) qDebug() << tr("警告!");

    //错误对话框
    int ret4 = QMessageBox::critical(this, tr("严重错误对话框"), tr("发现严重错误!"),QMessageBox::YesAll);
    if(ret4 == QMessageBox::YesAll) qDebug() << tr("错误!");

    //关于对话框
    QMessageBox::about(this, tr("关于对话框"), tr("yafeilinux致力于Qt及Qt Creator的普及工作"));
}

void Widget::show_progress_dialog()
{
    QProgressDialog dlg(tr("文件复制进度"), tr("取消"), 0, 500000, this);

    dlg.setWindowTitle(tr("进度对话框")); //设置窗口标题
    dlg.setWindowModality(Qt::WindowModal); //将对话框设置为模态
    dlg.show();
    for(int i = 0; i < 500000; i++){     //演示复制进度
        dlg.setValue(i);    //设置进度条的当前值
        QCoreApplication::processEvents();  //避免界面冻结
        if(dlg.wasCanceled()) break;    //按下取消按钮则中断
    }
    dlg.setValue(500000); //显示100%
    qDebug() << tr("复制结束");
}

void Widget::show_error_message_dialog()
{
    if(p_err_dlg == nullptr){
        p_err_dlg = new QErrorMessage(this);
    }

    p_err_dlg->setWindowTitle(tr("错误信息对话框"));
    p_err_dlg->showMessage(tr("这里是出错信息!"));
}

void Widget::show_wizard_dialog()
{
    QWizard wizard(this);
    wizard.setWindowTitle(tr("向导对话框"));
    //page1
    QWizardPage page1, page2, page3;
    page1.setTitle(tr("介绍"));
    page2.setTitle(tr("用户信息选择"));
    page3.setTitle(tr("结束"));
    wizard.addPage(&page1);
    wizard.addPage(&page2);
    wizard.addPage(&page3);
    if(wizard.exec() == QDialog::Accepted){
        qDebug() << "wizard finish!";
    }
}
