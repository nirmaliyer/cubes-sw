/*
 *==============================================================================
 * Source file for Communication Settings Dialog box
 *==============================================================================
 *
 * author: Theodor Stana (theodor.stana@gmail.com)
 *
 * date of creation: 2017-03-24
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
 *    2017-03-24   Theodor Stana     File created
 *==============================================================================
 * TODO: -
 *==============================================================================
 */

#include <commsettingsdialog.h>
#include <ui_commsettingsdialog.h>

#include <QSerialPortInfo>
#include <QMessageBox>

static const QString stringNotAvailable = "N/A";

CommSettingsDialog::CommSettingsDialog(QWidget *parent) :
    QDialog{parent},
    ui{new Ui::CommSettingsDialog}
{
    ui->setupUi(this);

    ui->lblName->setText("");
    ui->lblDescription->setText("");
    ui->lblManufacturer->setText("");
    ui->lblProductIdent->setText("");
    ui->lblVendor->setText("");
    ui->btnConnect->setEnabled(false);
    ui->btnCancel->setEnabled(false);

    ui->commSettingsPage->setCurrentIndex(0);

    m_serialPortInfos = QSerialPortInfo::availablePorts();

    for (auto &info : m_serialPortInfos) {
        ui->cbPort->addItem(info.portName() + " : " + info.description());
    }

    addCommTypes();

    m_commSettings = new CommSettings;
    m_commSettings->type = None;
}

CommSettingsDialog::~CommSettingsDialog()
{
    delete m_commSettings;
    delete ui;
}

CommSettingsDialog::CommSettings* CommSettingsDialog::getSettings()
{
    return m_commSettings;
}

void CommSettingsDialog::addCommTypes()
{
    ui->cbCommType->addItem("<Select...>");

    ui->cbCommType->addItem("Serial Port");
}

void CommSettingsDialog::on_btnConnect_clicked()
{
    updateSettings();
    QDialog::accept();
//    hide();
}

void CommSettingsDialog::on_btnCancel_clicked()
{
    QDialog::reject();
//    hide();
}

void CommSettingsDialog::on_cbCommType_currentIndexChanged(int index)
{
    populateCommSettings(index);
}

void CommSettingsDialog::on_cbPort_currentIndexChanged(int index)
{
    populateSerialPortInfo(index);
}

void CommSettingsDialog::on_btnRefreshPorts_clicked()
{
    if (ui->cbPort->count()) {
        ui->cbPort->clear();
    }
    if (m_serialPortInfos.count()) {
        m_serialPortInfos.clear();
    }
    m_serialPortInfos = QSerialPortInfo::availablePorts();
    if (m_serialPortInfos.count()) {
        for (auto &info : m_serialPortInfos) {
            ui->cbPort->addItem(info.portName() + " : " + info.description());
        }
    } else {
        QMessageBox box;
        box.setWindowTitle("Error");
        box.setText("No COM ports detected! Please connect one and click Refresh.");
        box.exec();
        ui->lblName->setText("");
        ui->lblDescription->setText("");
        ui->lblManufacturer->setText("");
        ui->lblProductIdent->setText("");
        ui->lblVendor->setText("");
        ui->btnConnect->setEnabled(false);
        ui->btnCancel->setEnabled(false);
    }
}

void CommSettingsDialog::populateCommSettings(int commType)
{
    if ((int)m_commType == commType)
        return;

    m_commType = (enum CommType)commType;

    ui->commSettingsPage->setCurrentIndex(commType);

    switch (commType) {
    case None:
    {
        break;
    }
    case SerialPort:
    {
        populateSerialPortInfo(ui->cbPort->currentIndex());
        break;
    }
    default:
        break;
    }
}

void CommSettingsDialog::populateSerialPortInfo(int selectedPort)
{
    if (selectedPort == -1)
        return;

    const auto &info = m_serialPortInfos[selectedPort];

    ui->lblName->setText(info.portName());
    ui->lblDescription->setText(info.description());
    ui->lblManufacturer->setText(info.manufacturer());
    ui->lblProductIdent->setText(QString::number(info.productIdentifier(), 16));
    ui->lblVendor->setText(QString::number(info.vendorIdentifier(), 16));

    ui->btnConnect->setEnabled(true);
    ui->btnCancel->setEnabled(true);
}

void CommSettingsDialog::updateSettings()
{
    m_commSettings->type = (enum CommType) ui->cbCommType->currentIndex();

    switch (m_commSettings->type) {
    case None:
        m_commSettings->port = "";
        m_commSettings->baud = 0;
        break;
    case SerialPort:
        m_commSettings->port = m_serialPortInfos[ui->cbPort->currentIndex()].portName();
        m_commSettings->baud = ui->cbBaud->currentText().toInt();
    }
}
