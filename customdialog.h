#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QString>


namespace Ui {
class CCustomDialog;
}

class CCustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CCustomDialog(QWidget *parent = nullptr);
    ~CCustomDialog();
    static QList<QPair<QString, int>>MapInfoPair();
    QList<QPair<QString, int>> getMapInfo();

private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();


private:
    Ui::CCustomDialog *ui;
    QList<QPair<QString, int>> m_map_info;
};

#endif // CUSTOMDIALOG_H
