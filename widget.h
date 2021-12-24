#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qwizard.h"

class QErrorMessage;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    void show_color_dialog();
    void show_file_dialog();
    void show_font_dialog();
    void show_input_dialog();
    void show_messgae_box();
    void show_progress_dialog();
    void show_error_message_dialog();
    void show_wizard_dialog();

    QErrorMessage* p_err_dlg;
};
#endif // WIDGET_H
