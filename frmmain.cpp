#include "frmmain.h"
#include "ui_frmmain.h"
#include "frmabout.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <QDebug>

FrmMain::FrmMain(QWidget *parent) : QMainWindow(parent), ui(new Ui::FrmMain)
{
    ui->setupUi(this);
    initialize();
}

FrmMain::~FrmMain()
{
    delete ui;
}

/**
 * @brief Open File menu item click event
 */
void FrmMain::on_actnOpenFile_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open .Obj File"), "", tr("Obj Files (*.obj)"));

    if(filePath.isEmpty())
    {
        qDebug() << "Info: Open file dialog was closed";
        return;
    }

    Model model;

    if(!model.loadFromFile(filePath))
    {
        qDebug() << "Error: Failed to open/process file:" << filePath;
        showMessageBox("Error: Failed to open/process file", cWindowTitle, QMessageBox::Critical);
        return;
    }

    qDebug() << "Info: Model loaded successfully";

    ui->modelViewer->setModel(model);

    ui->dsbPositionX->setValue(model.position().x());
    ui->dsbPositionY->setValue(model.position().y());
    ui->dsbRotationX->setValue(model.rotation().x());
    ui->dsbRotationY->setValue(model.rotation().y());
    ui->dsbRotationY->setValue(model.rotation().y());
    ui->dsbZoom->setValue(ui->modelViewer->zoomAmount());

    setWindowTitle(cWindowTitle + " (" + filePath + ")");
    ui->statusBar->showMessage("Loaded " + QString::number(model.vertexCount()) + " vertices.");
}

/**
 * @brief Exit menu item click event
 */
void FrmMain::on_actnExit_triggered()
{
    QApplication::quit();
}

/**
 * @brief Background Colour menu item click event
 */
void FrmMain::on_actnBackgroundColour_triggered()
{
    QColor colour = QColorDialog::getColor(ui->modelViewer->backgroundColour(), nullptr, "Background Colour");

    if(!colour.isValid())
    {
        qDebug() << "Info: Background colour dialog was closed";
        return;
    }

    ui->modelViewer->setBackgroundColour(colour);
}

/**
 * @brief Foreground Colour menu item click event
 */
void FrmMain::on_actnForegroundColour_triggered()
{
    QColor colour = QColorDialog::getColor(ui->modelViewer->foregroundColour(), nullptr, "Foreground Colour");

    if(!colour.isValid())
    {
        qDebug() << "Info: Foreground colour dialog was closed";
        return;
    }

    ui->modelViewer->setForegroundColour(colour);
}

/**
 * @brief About menu item click event
 */
void FrmMain::on_actnAbout_triggered()
{
    FrmAbout* frmAbout = new FrmAbout(this);
    frmAbout->show();
}

/**
 * @brief Opens a QMessageBox of the desired specification
 * @param message message
 * @param caption caption
 * @param icon icon
 */
void FrmMain::showMessageBox(const QString &message, const QString &caption, const QMessageBox::Icon &icon)
{
    QMessageBox messageBox;

    messageBox.setText(message);
    messageBox.setWindowTitle(caption);
    messageBox.setIcon(icon);

    messageBox.exec();
}

void FrmMain::disableActionChecks()
{
    ui->actPointSize1->setChecked(false);
    ui->actPointSize2->setChecked(false);
    ui->actPointSize3->setChecked(false);
    ui->actPointSize4->setChecked(false);
    ui->actPointSize5->setChecked(false);
}

void FrmMain::initialize()
{
    Model model;
    GLfloat zoomAmount = 3.75;
    QVector3D position(-0.15f, -1.5f, 0.0f);
    model.loadFromFile(":/objs/objs/teapot.obj");
    model.setPosition(position);
    ui->modelViewer->setModel(model);
    ui->modelViewer->setZoomAmount(zoomAmount);
    ui->dsbZoom->setValue(zoomAmount);
    ui->dsbPositionY->setValue(position.y());
    ui->dsbPositionX->setValue(position.x());
    ui->statusBar->showMessage("Ready.");
    setWindowTitle(cWindowTitle);
}

/**
 * @brief X Position spin box value changed event
 * @param value new value
 */
void FrmMain::on_dsbPositionX_valueChanged(double value)
{
    Model& model = ui->modelViewer->model();

    if(!model.isLoaded())
    {
        return;
    }

    model.setPosition(QVector3D(value, model.position().y(), model.position().z()));

    ui->modelViewer->updateGL();
}

/**
 * @brief Y Position spin box value changed event
 * @param value new value
 */
void FrmMain::on_dsbPositionY_valueChanged(double value)
{
    Model& model = ui->modelViewer->model();

    if(!model.isLoaded())
    {
        return;
    }

    model.setPosition(QVector3D(model.position().x(), value, model.position().z()));

    ui->modelViewer->updateGL();
}

/**
 * @brief X Rotation spin box value changed event
 * @param value new value
 */
void FrmMain::on_dsbRotationX_valueChanged(double value)
{
    Model& model = ui->modelViewer->model();

    if(!model.isLoaded())
    {
        return;
    }

    model.setRotation(QVector3D(value, model.rotation().y(), model.rotation().z()));

    ui->modelViewer->updateGL();
}


/**
 * @brief Y Rotation spin box value changed event
 * @param value new value
 */
void FrmMain::on_dsbRotationY_valueChanged(double value)
{
    Model& model = ui->modelViewer->model();

    if(!model.isLoaded())
    {
        return;
    }

    model.setRotation(QVector3D(model.rotation().x(), value, model.rotation().z()));

    ui->modelViewer->updateGL();
}

/**
 * @brief Z Rotation spin box value changed event
 * @param value new value
 */
void FrmMain::on_dsbRotationZ_valueChanged(double value)
{
    Model& model = ui->modelViewer->model();

    if(!model.isLoaded())
    {
        return;
    }

    model.setRotation(QVector3D(model.rotation().x(), model.rotation().y(), value));

    ui->modelViewer->updateGL();
}

/**
 * @brief Zoom spin box value changed event
 * @param value new value
 */
void FrmMain::on_dsbZoom_valueChanged(double value)
{
    ui->modelViewer->setZoomAmount(value);
    ui->modelViewer->update();
}

/**
 * @brief Point Cloud radio dialog button toggle event
 * @param checked new state
 */
void FrmMain::on_rdbPointCloud_toggled(bool state)
{
    if(!state)
    {
        return;
    }

    ui->modelViewer->setRenderMode(ui->modelViewer->ePointCloud);
    ui->modelViewer->updateGL();
}

/**
 * @brief Wireframe radio dialog button toggle event
 * @param checked new state
 */
void FrmMain::on_rdbWireframe_toggled(bool state)
{
    if(!state)
    {
        return;
    }

    ui->modelViewer->setRenderMode(ui->modelViewer->eWireframe);
    ui->modelViewer->updateGL();
}

/**
 * @brief Sets the ModelViewer's point size to 1
 */
void FrmMain::on_actPointSize1_triggered()
{
    disableActionChecks();
    ui->actPointSize1->setChecked(true);
    ui->modelViewer->setPointSize(1.0f);
    ui->modelViewer->updateGL();
}

/**
 * @brief Sets the ModelViewer's point size to 2
 */
void FrmMain::on_actPointSize2_triggered()
{
    disableActionChecks();
    ui->actPointSize2->setChecked(true);
    ui->modelViewer->setPointSize(2.0f);
    ui->modelViewer->updateGL();
}

/**
 * @brief Sets the ModelViewer's point size to 3
 */
void FrmMain::on_actPointSize3_triggered()
{
    disableActionChecks();
    ui->actPointSize3->setChecked(true);
    ui->modelViewer->setPointSize(3.0f);
    ui->modelViewer->updateGL();
}

/**
 * @brief Sets the ModelViewer's point size to 4
 */
void FrmMain::on_actPointSize4_triggered()
{
    disableActionChecks();
    ui->actPointSize4->setChecked(true);
    ui->modelViewer->setPointSize(4.0f);
    ui->modelViewer->updateGL();
}

/**
 * @brief Sets the ModelViewer's point size to 5
 */
void FrmMain::on_actPointSize5_triggered()
{
    ui->actPointSize5->setChecked(true);
    ui->modelViewer->setPointSize(5.0f);
    ui->modelViewer->updateGL();
}
