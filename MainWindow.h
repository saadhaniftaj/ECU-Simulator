#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QGroupBox>
#include <QListWidget>
#include "ECU.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onSimulateStep();
    void updateUI();
    void onTabChanged(int index);

private:
    void setupUI();
    void updateStatusIndicators();
    void updateSensorsPanel();
    void updateActuatorsPanel();
    void updateEnginePanel();
    void updateLogsPanel();
    QString getProjectInfo() const;
    QGroupBox* createStatusCard(const QString& title, const QString& unit, QProgressBar*& progressBar);

    ECU *ecu;
    QTabWidget *tabWidget;
    QWidget *dashboardPanel;
    QWidget *sensorsPanel;
    QWidget *actuatorsPanel;
    QWidget *enginePanel;
    QWidget *logsPanel;
    QLabel *infoBox;
    QProgressBar *boostBar;
    QProgressBar *afrBar;
    QProgressBar *fuelPressureBar;
    QLabel *statusLabel;
    QTimer *updateTimer;
    QListWidget *logsList;
};

#endif // MAINWINDOW_H 