/*==============================================================================
 * KTH Royal Institute of Technology Stockholm
 * CUBES Protocol UART Pmod implementation
 *==============================================================================
 *
 * author: Theodor Stana (theodor.stana@gmail.com)
 *
 * date of creation: 2017-02-15
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
 *    2017-02-15   theodor.stana@gmail.com     File created
 *==============================================================================
 * TODO: -
 *==============================================================================
 */

#include "cubesprotouartpmod.h"

#include <cubescommand.h>

#include <QObject>
#include <QSerialPort>

CubesProtoUartPmod::CubesProtoUartPmod(QSerialPort *device, QObject *parent) :
    QObject(parent),
    m_device{device}
{
    QObject::connect(m_device, &QSerialPort::readyRead,
                     this, &CubesProtoUartPmod::on_serialPort_readReady);
    QObject::connect(m_device, &QSerialPort::errorOccurred,
                     this, &CubesProtoUartPmod::devErrorOccured);

    m_currentCommand = new CubesCommand;
}

CubesProtoUartPmod::~CubesProtoUartPmod()
{
    delete m_device;
    delete m_currentCommand;
}

QSerialPort* CubesProtoUartPmod::dev()
{
    return m_device;
}

bool CubesProtoUartPmod::devOpen(QSerialPort::OpenMode mode)
{
    return m_device->open(mode);
}

void CubesProtoUartPmod::devClose()
{
    m_device->close();
}

QString CubesProtoUartPmod::devName()
{
    return m_device->portName();
}

int CubesProtoUartPmod::devError()
{
    return m_device->error();
}

void CubesProtoUartPmod::on_serialPort_readReady()
{
    m_bytesLeft -= m_device->bytesAvailable();
    if (m_bytesLeft <= 0) {
        emit devReadReady();
    }
}

qint64 CubesProtoUartPmod::sendCommand(quint8 cmdCode, QByteArray &cmdData)
{
    QByteArray      data;
    int             numDataBytes;
    char            read, write;

    /* Bail out if unknown command */
    if (m_currentCommand->setCommand(cmdCode) != cmdCode) {
        return -1;
    }

    /*
     * Create I2C R/nW ('1' = Read, '0' = Write) bit based on current command's
     * data direction, and assign number of data bytes and I2C Address + R/nW
     * byte to mimic an I2C transfer over UART.
     */
    write = 0x1 & (~m_currentCommand->dataDirection());
    read = 0x1 & (~write);
    m_bytesLeft = m_currentCommand->dataBytes();

    numDataBytes = 2 + (cmdData.size() * write);
    data.resize(numDataBytes);

    data[0] = (CUBES_I2C_ADDRESS << 1) | (read);
    data[1] = cmdCode;
    for (int i = 0; i < numDataBytes-2; i++)
        data[i+2] = cmdData[i];

    /* Clear data buffers and issue command */
    return m_device->write(data);
}

CubesCommand* CubesProtoUartPmod::currentCommand()
{
    return m_currentCommand;
}

qint64 CubesProtoUartPmod::write(QByteArray &data)
{
    return m_device->write(data);
}

QByteArray CubesProtoUartPmod::readAll()
{
    return m_device->readAll();
}
