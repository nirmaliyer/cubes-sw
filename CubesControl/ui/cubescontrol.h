/*
 *==============================================================================
 * KTH Royal Institute of Technology Stockholm
 * CUBES Control Program
 *==============================================================================
 *
 * author: Theodor Stana (theodor.stana@gmail.com)
 *
 * date of creation: 2017-02-08
 *
 * version: 1.0
 *
 * description:
 *
 * dependencies:
 *
 * references:
 *
 *==============================================================================
 * GNU LESSER GENERAL PUBLIC LICENSE
 *==============================================================================
 * This source file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version. This source is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details. You should have
 * received a copy of the GNU Lesser General Public License along with this
 * source; if not, download it from http://www.gnu.org/licenses/lgpl-2.1.html
 *==============================================================================
 * last changes:
 *    2017-02-08   theodor.stana@gmail.com     File created
 *==============================================================================
 * TODO: -
 *==============================================================================
 */

#ifndef CUBESCONTROL_H
#define CUBESCONTROL_H

#include <cubesprotouartpmod.h>
#include <commsettingsdialog.h>

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QTreeWidgetItem>
#include <QSerialPort>
#include <QTimer>
#include <QtCharts/QtCharts>

using namespace QtCharts;

namespace Ui {
class CubesControl;
}

class CommSettingsDialog;

class CubesControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit CubesControl(QWidget *parent = 0);
    ~CubesControl();

private slots:
    void on_cubes_devErrorOccured(int error);
    void on_cubes_devReadReady();

    void on_actionExit_triggered();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
    void on_actionLoadSiphraConfig_triggered();
    void on_actionSaveSiphraConfig_triggered();
    void on_actionReadSiphraReg_triggered();
    void on_actionWriteSiphraReg_triggered();
    void on_actionToggleAdcPoll_triggered();
    void on_actionToggleAdcPoll_triggered(bool checked);
    void on_actionExportHistogram_triggered();
    void on_actionImportHistogram_triggered();

    void on_anyLedCheckbox_clicked();
    void on_btnReadAllCubesRegs_clicked();
    void on_btnExpandSiphraRegTable_clicked();
    void on_btnCollapseSiphraRegTable_clicked();
    void on_btnLoadSiphraConfig_clicked();
    void on_btnSaveSiphraConfig_clicked();
    void on_btnWriteAllSiphraRegs_clicked();
    void on_btnReadAllSiphraRegs_clicked();
    void on_btnToggleAdcPoll_clicked();
    void on_btnStartStopHistogram_clicked();
    void on_btnClearHistogram_clicked();
    void on_btnExportHistogram_clicked();
    void on_btnImportHistogram_clicked();
    void on_comboboxNumBins_currentTextChanged(const QString &arg1);
    void on_checkboxPowerUpChannel_clicked();
    void on_checkboxEnableChannelTriggering_clicked();
    void on_sliderQcThreshold_valueChanged(int value);
    void on_spinboxQcThreshold_valueChanged(int arg1);
    void on_sliderQcHysteresis_valueChanged(int value);
    void on_comboboxQcHysteresis_currentIndexChanged(int index);
    void on_sliderCmisGain_valueChanged(int value);
    void on_comboboxCmisGain_currentIndexChanged(int index);
    void on_sliderCiGain_valueChanged(int value);
    void on_comboboxCiGain_currentIndexChanged(int index);
    void on_sliderShapingTime_valueChanged(int value);
    void on_comboboxShapingTime_currentIndexChanged(int index);
    void on_sliderTune_valueChanged(int value);
    void on_spinboxTune_valueChanged(int arg1);
    void on_sliderDelay_valueChanged(int value);
    void on_spinboxDelay_valueChanged(int arg1);
    void on_spinboxSiphraChannelToConfig_valueChanged(int arg1);
    void on_comboboxCbInput_currentIndexChanged(int index);
    void on_comboboxHoldSource_currentIndexChanged(int index);
    void on_comboboxHistogramRunType_currentIndexChanged(int index);
    void on_checkboxCiCompmode_clicked();
    void on_checkboxUseAdcIn_clicked(bool checked);

    void on_treeSiphraRegMap_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_treeSiphraRegMap_itemChanged(QTreeWidgetItem *item, int column);
    void on_treeSiphraRegMap_contextMenuRequested(const QPoint &p);
    void on_tabWidget_currentChanged(int index);

    void on_tmrEventRateReadout_timeout();
    void on_tmrHistogramAdcPoll_timeout();
    void on_tmrSiphraAdcPoll_timeout();

private:
    Ui::CubesControl    *ui;

    QLabel              *lblConnStatus;
    int                 connStatus;

    CubesProtoUartPmod  *cubes;
    CommSettingsDialog  *commSettings;

    QSerialPort         *serialPort;

    bool                m_changedByUser;
    QString             m_textBeforeChange;

    bool                m_readAllSiphraRegs;
    qint8               m_siphraRegAddr;
    qint32              m_siphraRegVal;

    double              m_siphraAdcValue;
    qint8               m_siphraAdcChan;
    bool                m_siphraAdcPollEnabled;

    bool                siphraVisualRegChange = false;

    QTimer              *tmrEventRateReadout;
    QTimer              *tmrHistogramAdcPoll;
    QTimer              *tmrSiphraAdcPoll;

    QVector<quint16>    histogramData;
    int                 histogramNumBins;
    bool                histogramAdcPollEnabled;
    int                 histogramRunTime;

    void    showConnStatus(int connUp);
    void    updateHistogram(bool updateAll = false);

    int     uiSiphraChannelRegValue();
    int     uiSiphraChannelConfigValue();
    int     uiSiphraReadoutModeValue();
    int     uiSiphraChannelControlValue();

    void    setUiSiphraChannelRegValue(bool powerUpChannel, bool enableTriggering,
                                       int qcThreshold, int qcHysteresis);
    void    setUiSiphraChannelConfigValue(int cmisGain, int ciGain, bool ciCompmode, int shapingTime);
    void    setUiSiphraReadoutModeValue(int thDelay, int thTune, int holdSource);
    void    setUiSiphraChannelControlValue(int cbInput);

    void    writeSiphraChannelReg(int value);
    void    writeSiphraChannelConfig(int value);
    void    writeSiphraChannelControl(int value);
    void    writeSiphraReadoutMode(int value);

    void    decodeShapingTime(int setting, int *bias, int *feedback_cap,
                              int *feedback_res, int *hold_cap,
                              int *input_cap);
    int     decodeShaperSettings(int bias, int feedback_cap, int feedback_res,
                                 int hold_cap, int input_cap);

    double  thDelayTime(int thTune, int thDelay);
};

#endif // CUBESCONTROL_H
