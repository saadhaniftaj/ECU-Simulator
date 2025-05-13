#include "MainWindow.h"
#include <QFont>
#include <sstream>
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ecu = new ECU();
    setupUI();
    
    // Set up timer for dynamic updates
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateUI);
    updateTimer->start(1000); // Update every second
}

void MainWindow::setupUI() {
    // Set application style
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    
    // Create modern dark palette
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(18, 18, 18));
    darkPalette.setColor(QPalette::WindowText, QColor(240, 240, 240));
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(35, 35, 35));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::ToolTipText, QColor(240, 240, 240));
    darkPalette.setColor(QPalette::Text, QColor(240, 240, 240));
    darkPalette.setColor(QPalette::Button, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::ButtonText, QColor(240, 240, 240));
    darkPalette.setColor(QPalette::BrightText, QColor(255, 50, 50));
    darkPalette.setColor(QPalette::Link, QColor(0, 120, 215));
    darkPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    darkPalette.setColor(QPalette::HighlightedText, QColor(240, 240, 240));
    QApplication::setPalette(darkPalette);

    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Header
    QLabel *headerLabel = new QLabel("ECU Control Center");
    headerLabel->setStyleSheet(
        "QLabel {"
        "    color: #ffffff;"
        "    font-size: 24px;"
        "    font-weight: bold;"
        "    padding: 10px;"
        "}"
    );
    mainLayout->addWidget(headerLabel);

    // Tab widget for navigation
    tabWidget = new QTabWidget();
    tabWidget->setStyleSheet(
        "QTabWidget::pane { border: 1px solid #3d3d3d; border-radius: 10px; background: #181818; }"
        "QTabBar::tab { background: #232323; color: #fff; border-radius: 8px 8px 0 0; padding: 10px 24px; font-size: 15px; }"
        "QTabBar::tab:selected { background: #0078d7; color: #fff; }"
        "QTabBar::tab:hover { background: #1084e3; }"
    );
    mainLayout->addWidget(tabWidget);

    // Dashboard panel
    dashboardPanel = new QWidget();
    QVBoxLayout *dashboardLayout = new QVBoxLayout(dashboardPanel);
    QHBoxLayout *statusCardsLayout = new QHBoxLayout();
    statusCardsLayout->setSpacing(15);

    // Create status cards
    QGroupBox *boostCard = createStatusCard("Boost Pressure", "bar", boostBar);
    QGroupBox *afrCard = createStatusCard("Air/Fuel Ratio", "ratio", afrBar);
    QGroupBox *fuelCard = createStatusCard("Fuel Pressure", "bar", fuelPressureBar);

    statusCardsLayout->addWidget(boostCard);
    statusCardsLayout->addWidget(afrCard);
    statusCardsLayout->addWidget(fuelCard);

    // System status card
    QGroupBox *systemStatusCard = new QGroupBox("System Status");
    systemStatusCard->setStyleSheet(
        "QGroupBox {"
        "    background-color: #2d2d2d;"
        "    border: 1px solid #3d3d3d;"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    margin-top: 1ex;"
        "}"
        "QGroupBox::title {"
        "    color: #ffffff;"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 5px;"
        "}"
    );
    QVBoxLayout *systemStatusLayout = new QVBoxLayout(systemStatusCard);
    statusLabel = new QLabel("System Status: OK");
    statusLabel->setStyleSheet(
        "QLabel {"
        "    color: #00ff00;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    padding: 10px;"
        "}"
    );
    systemStatusLayout->addWidget(statusLabel);

    // Control buttons container
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);

    // Create modern button for simulation only
    QString buttonStyle = 
        "QPushButton {"
        "    background-color: #0078d7;"
        "    color: white;"
        "    border: none;"
        "    padding: 12px 24px;"
        "    border-radius: 6px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #1084e3;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #006cc1;"
        "}";

    QPushButton *btnSim = new QPushButton("Run Simulation");
    btnSim->setStyleSheet(buttonStyle);
    buttonLayout->addWidget(btnSim);
    connect(btnSim, &QPushButton::clicked, this, &MainWindow::onSimulateStep);

    dashboardLayout->addLayout(statusCardsLayout);
    dashboardLayout->addWidget(systemStatusCard);
    dashboardLayout->addLayout(buttonLayout);
    dashboardLayout->addStretch();

    // Info box with modern styling
    infoBox = new QLabel(getProjectInfo());
    infoBox->setWordWrap(true);
    infoBox->setStyleSheet(
        "QLabel {"
        "    background-color: #2d2d2d;"
        "    color: #ffffff;"
        "    border-radius: 10px;"
        "    padding: 20px;"
        "    font-size: 14px;"
        "    line-height: 1.5;"
        "    border: 1px solid #3d3d3d;"
        "}"
    );

    // Add all components to main layout
    tabWidget->addTab(dashboardPanel, QIcon(), "Dashboard");

    // Sensors panel
    sensorsPanel = new QWidget();
    QVBoxLayout *sensorsLayout = new QVBoxLayout(sensorsPanel);
    sensorsLayout->setSpacing(15);
    sensorsLayout->addWidget(new QLabel("<b>Sensors</b>"));
    // Will be dynamically updated
    tabWidget->addTab(sensorsPanel, QIcon(), "Sensors");

    // Actuators panel
    actuatorsPanel = new QWidget();
    QVBoxLayout *actuatorsLayout = new QVBoxLayout(actuatorsPanel);
    actuatorsLayout->setSpacing(15);
    actuatorsLayout->addWidget(new QLabel("<b>Actuators</b>"));
    // Will be dynamically updated
    tabWidget->addTab(actuatorsPanel, QIcon(), "Actuators");

    // Engine panel
    enginePanel = new QWidget();
    QVBoxLayout *engineLayout = new QVBoxLayout(enginePanel);
    engineLayout->setSpacing(15);
    engineLayout->addWidget(new QLabel("<b>Engine Status</b>"));
    // Will be dynamically updated
    tabWidget->addTab(enginePanel, QIcon(), "Engine");

    // Logs panel
    logsPanel = new QWidget();
    QVBoxLayout *logsLayout = new QVBoxLayout(logsPanel);
    logsLayout->setSpacing(15);
    logsLayout->addWidget(new QLabel("<b>System Logs</b>"));
    logsList = new QListWidget();
    logsList->setStyleSheet(
        "QListWidget { background: #232323; color: #fff; border-radius: 8px; font-size: 13px; }"
        "QListWidget::item { padding: 10px; border-bottom: 1px solid #333; }"
        "QListWidget::item:selected { background: #0078d7; color: #fff; }"
    );
    logsLayout->addWidget(logsList);
    tabWidget->addTab(logsPanel, QIcon(), "Logs");

    // Info box
    infoBox = new QLabel(getProjectInfo());
    infoBox->setWordWrap(true);
    infoBox->setStyleSheet(
        "QLabel {"
        "    background-color: #2d2d2d;"
        "    color: #ffffff;"
        "    border-radius: 10px;"
        "    padding: 20px;"
        "    font-size: 14px;"
        "    line-height: 1.5;"
        "    border: 1px solid #3d3d3d;"
        "}"
    );
    mainLayout->addWidget(infoBox);

    setCentralWidget(central);
    setWindowTitle("Advanced ECU Simulation System");
    resize(1000, 800);
}

QGroupBox* MainWindow::createStatusCard(const QString& title, const QString& unit, QProgressBar*& progressBar) {
    QGroupBox *card = new QGroupBox(title);
    card->setStyleSheet(
        "QGroupBox {"
        "    background-color: #2d2d2d;"
        "    border: 1px solid #3d3d3d;"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    margin-top: 1ex;"
        "}"
        "QGroupBox::title {"
        "    color: #ffffff;"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 5px;"
        "}"
    );

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    
    progressBar = new QProgressBar();
    progressBar->setStyleSheet(
        "QProgressBar {"
        "    border: 1px solid #3d3d3d;"
        "    border-radius: 5px;"
        "    text-align: center;"
        "    background-color: #1d1d1d;"
        "    height: 20px;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #0078d7;"
        "    border-radius: 4px;"
        "}"
    );

    QLabel *unitLabel = new QLabel(unit);
    unitLabel->setStyleSheet("color: #888888; font-size: 12px;");
    unitLabel->setAlignment(Qt::AlignRight);

    cardLayout->addWidget(progressBar);
    cardLayout->addWidget(unitLabel);

    return card;
}

void MainWindow::updateUI() {
    updateStatusIndicators();
    updateSensorsPanel();
    updateActuatorsPanel();
    updateEnginePanel();
    updateLogsPanel();
}

void MainWindow::onTabChanged(int index) {
    updateUI();
}

void MainWindow::updateStatusIndicators() {
    // Update progress bars with current values
    double boost = ecu->getSensorValue(3); // MAP/Boost sensor
    double afr = ecu->getSensorValue(1);   // AFR sensor
    double fuelPressure = ecu->getSensorValue(4); // Fuel Pressure sensor

    // Set ranges and values
    boostBar->setRange(0, 3000); // 0-3 bar in mbar
    afrBar->setRange(1000, 2000); // 10.0-20.0 AFR * 100
    fuelPressureBar->setRange(0, 5000); // 0-5 bar in mbar

    boostBar->setValue(boost * 1000);
    afrBar->setValue(afr * 100);
    fuelPressureBar->setValue(fuelPressure * 1000);

    // Update status label
    bool boostOk = boost < 2.0;
    bool afrOk = afr > 10.0 && afr < 16.0;
    QString status = (boostOk && afrOk) ? "OK" : "WARNING";
    statusLabel->setText("System Status: " + status);
    QString color = (status == "OK") ? "#00ff00" : "#ff0000";
    statusLabel->setStyleSheet(QString("QLabel { color: %1; font-weight: bold; font-size: 16px; padding: 10px; } ").arg(color));
}

void MainWindow::onSimulateStep() {
    ecu->simulateStep();
    updateUI();
}

void MainWindow::updateSensorsPanel() {
    QLayout *layout = sensorsPanel->layout();
    // Remove old widgets except the title
    while (layout->count() > 1) {
        QLayoutItem *item = layout->takeAt(1);
        if (item->widget()) delete item->widget();
        delete item;
    }
    QStringList sensors = QString::fromStdString(ecu->getSensorsInfo()).split("\n");
    for (const QString &line : sensors) {
        if (!line.trimmed().isEmpty() && !line.contains("===")) {
            QLabel *lbl = new QLabel(line.trimmed());
            lbl->setStyleSheet("color: #fff; background: #232323; border-radius: 6px; padding: 8px; margin-bottom: 4px; font-size: 14px;");
            layout->addWidget(lbl);
        }
    }
}

void MainWindow::updateActuatorsPanel() {
    QLayout *layout = actuatorsPanel->layout();
    while (layout->count() > 1) {
        QLayoutItem *item = layout->takeAt(1);
        if (item->widget()) delete item->widget();
        delete item;
    }
    QStringList actuators = QString::fromStdString(ecu->getActuatorsInfo()).split("\n");
    for (const QString &line : actuators) {
        if (!line.trimmed().isEmpty() && !line.contains("===")) {
            QLabel *lbl = new QLabel(line.trimmed());
            lbl->setStyleSheet("color: #fff; background: #232323; border-radius: 6px; padding: 8px; margin-bottom: 4px; font-size: 14px;");
            layout->addWidget(lbl);
        }
    }
}

void MainWindow::updateEnginePanel() {
    QLayout *layout = enginePanel->layout();
    while (layout->count() > 1) {
        QLayoutItem *item = layout->takeAt(1);
        if (item->widget()) delete item->widget();
        delete item;
    }
    QStringList engine = QString::fromStdString(ecu->getEngineStatusInfo()).split("\n");
    for (const QString &line : engine) {
        if (!line.trimmed().isEmpty() && !line.contains("===")) {
            QLabel *lbl = new QLabel(line.trimmed());
            lbl->setStyleSheet("color: #fff; background: #232323; border-radius: 6px; padding: 8px; margin-bottom: 4px; font-size: 14px;");
            layout->addWidget(lbl);
        }
    }
}

void MainWindow::updateLogsPanel() {
    logsList->clear();
    QStringList logs = QString::fromStdString(ecu->getLogsInfo()).split("\n");
    for (const QString &line : logs) {
        if (!line.trimmed().isEmpty() && !line.contains("===")) {
            QListWidgetItem *item = new QListWidgetItem(line.trimmed());
            item->setForeground(QColor("#fff"));
            logsList->addItem(item);
        }
    }
}

QString MainWindow::getProjectInfo() const {
    return "<b>Advanced ECU Simulation System with Dynamic Engine Management</b><br>"
           "<b>Team Members:</b> Mustafa Ahmad Khan (2024509), Abdullah bin Zubair (2024036), Ammad Ali (2024098), Shaheer Akhtar (2024573)<br>"
           "<b>Description:</b> Simulates a full-featured automotive ECU using C++ OOP, including sensors, actuators, engine logic, safety features, and real-time logging.";
} 