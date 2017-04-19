#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>

namespace Ui
{
    class FrmMain;
}

class FrmMain : public QMainWindow
{
    Q_OBJECT

public:

    explicit FrmMain(QWidget *parent = 0);
    ~FrmMain();

private slots:

    void on_actnOpenFile_triggered();

    void on_actnExit_triggered();

    void on_actnBackgroundColour_triggered();

    void on_actnForegroundColour_triggered();

    void on_actnAbout_triggered();

    void on_dsbPositionX_valueChanged(double value);

    void on_dsbPositionY_valueChanged(double value);

    void on_dsbRotationX_valueChanged(double value);

    void on_dsbRotationY_valueChanged(double value);

    void on_dsbRotationZ_valueChanged(double value);

    void on_dsbZoom_valueChanged(double value);

    void on_rdbPointCloud_toggled(bool state);

    void on_rdbWireframe_toggled(bool state);

    void on_actPointSize1_triggered();

    void on_actPointSize5_triggered();

    void on_actPointSize2_triggered();

    void on_actPointSize3_triggered();

    void on_actPointSize4_triggered();

private:

    Ui::FrmMain *ui;

    const QString cWindowTitle = "The Little Teapot";

    void showMessageBox(const QString& message, const QString& caption, const QMessageBox::Icon& icon);
    void disableActionChecks();

    void initialize();

};

#endif // FRMMAIN_H
