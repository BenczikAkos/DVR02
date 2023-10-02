#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qstatusbar.h"
#include "QtCore/QTime"
#include "chartdialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{ parent },
    ui {new Ui::MainWindow},
    reader{ std::make_unique<VolumeDataReader>() }
{

    ui->setupUi(this);
    updateFrameRateTimer.setRemainingTime(100);
    populateModesComboBox();
    populateDataTypesComboBox();


    QObject::connect(this, SIGNAL(AABBChangedX(float)), ui->openGLWidget, SLOT(setAABBScaleX(float)));
    QObject::connect(this, SIGNAL(AABBChangedY(float)), ui->openGLWidget, SLOT(setAABBScaleY(float)));
    QObject::connect(this, SIGNAL(AABBChangedZ(float)), ui->openGLWidget, SLOT(setAABBScaleZ(float)));
    //max value slider and its combobox
    QObject::connect(this, SIGNAL(intensityMaxChanged(int)), ui->openGLWidget, SLOT(setIntensityMax(int)));
    QObject::connect(this, SIGNAL(intensityMaxChanged(int)), ui->maxValueSpinbox, SLOT(setValue(int)));
    QObject::connect(ui->maxValueSpinbox, SIGNAL(valueChanged(int)), ui->intensityMaxSlider, SLOT(setValue(int)));
    //min value slider and its combobox
    QObject::connect(this, SIGNAL(intensityMinChanged(int)), ui->openGLWidget, SLOT(setIntensityMin(int)));
    QObject::connect(this, SIGNAL(intensityMinChanged(int)), ui->minValueSpinbox, SLOT(setValue(int)));
    QObject::connect(ui->minValueSpinbox, SIGNAL(valueChanged(int)), ui->intensityMinSlider, SLOT(setValue(int)));

    QObject::connect(ui->stepLengthSpinBox, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(setStepLength(double)));

    QObject::connect(ui->modeComboBox, SIGNAL(currentIndexChanged(int)), ui->openGLWidget, SLOT(setMode(int)));
    setVolumeDataReaderSlots();
}

void MainWindow::populateModesComboBox() {
    ui->modeComboBox->addItem("MIP");
    ui->modeComboBox->addItem("Accumulate");
    ui->modeComboBox->addItem("Average");
    ui->modeComboBox->addItem("Isosurface");
}

void MainWindow::populateDataTypesComboBox() {
    ui->dataTypeComboBox->addItem("uint8");
    ui->dataTypeComboBox->addItem("uint16");
    ui->dataTypeComboBox->addItem("uint32");
    ui->dataTypeComboBox->addItem("int8");
    ui->dataTypeComboBox->addItem("int16");
    ui->dataTypeComboBox->addItem("int32");
    ui->dataTypeComboBox->addItem("float");
}

void MainWindow::setVolumeDataReaderSlots() {
    QObject::connect(ui->dataTypeComboBox, SIGNAL(currentIndexChanged(int)), reader.get(), SLOT(setDataType(int)));
    QObject::connect(ui->datasetSize_x, SIGNAL(valueChanged(int)), reader.get(), SLOT(setXTextureSize(int)));
    QObject::connect(ui->datasetSize_y, SIGNAL(valueChanged(int)), reader.get(), SLOT(setYTextureSize(int)));
    QObject::connect(ui->datasetSize_z, SIGNAL(valueChanged(int)), reader.get(), SLOT(setZTextureSize(int)));
    QObject::connect(ui->precomputeGradientsCheckBox, SIGNAL(stateChanged(int)), reader.get(), SLOT(setPrecomputeGradients(int)));
    QObject::connect(ui->littleEndianCheckBox, SIGNAL(stateChanged(int)), reader.get(), SLOT(setLittleEndian(int)));
}

void MainWindow::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    int thisPaint = QTime::currentTime().msecsSinceStartOfDay();
    if (updateFrameRateTimer.hasExpired()) {
        int diff = thisPaint - lastPaint;
        QStatusBar* StatusBar = statusBar();
        if (StatusBar != nullptr && diff != 0) {
            StatusBar->clearMessage();
            StatusBar->showMessage(QString("Elapsed time: %1 ms FPS: %2").arg(QString::number(diff), QString::number(1000/diff)));
        }
        updateFrameRateTimer.setRemainingTime(300);
    }
    lastPaint = thisPaint;
    update();
}

VolumeDataReader* MainWindow::getReader() const
{
    return reader.get();
}

QChart* MainWindow::generateChart() const
{
    return ui->openGLWidget->generateChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadVolumeButton_clicked(bool checked)
{
    Q_UNUSED(checked)
    ui->openGLWidget->openFile();
}

void MainWindow::on_chartButton_clicked(bool checked)
{
    Q_UNUSED(checked)
    auto graphDialog = new ChartDialog(this);
    graphDialog->show();
    graphDialog->raise();
}

void MainWindow::on_transferFunctionButton_clicked(bool checked)
{
    Q_UNUSED(checked)
    std::unique_ptr<TransferFuncEditorDialog> transfunc = std::make_unique<TransferFuncEditorDialog>(this);
    transfunc->show();
}

float MainWindow::normalizeSliderValue(const QSlider& slider, int value) const
{
    int minValue = slider.minimum();
    int maxValue = slider.maximum();
    return (static_cast<float>(value)) / (maxValue - minValue);

}

void MainWindow::on_AABBScale_x_valueChanged(int value)
{
    float normValue = normalizeSliderValue(*ui->AABBScale_x, value); 
    emit AABBChangedX(normValue); 
}

void MainWindow::on_AABBScale_y_valueChanged(int value) 
{ 
    float normValue = normalizeSliderValue(*ui->AABBScale_y, value); 
    emit AABBChangedY(normValue); 
}

void MainWindow::on_AABBScale_z_valueChanged(int value) 
{ 
    float normValue = normalizeSliderValue(*ui->AABBScale_z, value); 
    emit AABBChangedZ(normValue); 
}

void MainWindow::on_intensityMinSlider_valueChanged(int value)
{
    emit intensityMinChanged(value);
}

void MainWindow::on_intensityMaxSlider_valueChanged(int value)
{
    emit intensityMaxChanged(value);
}