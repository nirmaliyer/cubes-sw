/*
 *==============================================================================
 * Source file for CUBES Command class
 *==============================================================================
 *
 * author: Theodor Stana (theodor.stana@gmail.com)
 *
 * date of creation: 2017-04-07
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
 *    2017-04-07   Theodor Stana     File created
 *==============================================================================
 * TODO: -
 *==============================================================================
 */

#include "cubescommand.h"

CubesCommand::CubesCommand()
{
    decode(0);
}

CubesCommand::CubesCommand(const quint8 code)
{
    decode(code);
}

quint8 CubesCommand::setCommand(const quint8 code)
{
    return decode(code);
}

quint8 CubesCommand::code()
{
    return m_code;
}

qint32 CubesCommand::dataBytes()
{
    return m_dataBytes;
}

qint32 CubesCommand::dataDirection()
{
    return m_dataDirection;
}

QString& CubesCommand::description()
{
    return m_description;
}

quint8 CubesCommand::decode(const quint8 code)
{
    m_code = code;

    switch (code) {
    case CMD_READ_ALL_REGS:
        m_dataBytes = 784;
        m_dataDirection = Read;
        m_description = "Request housekeeping data";
        break;
    case CMD_GET_CUBES_ID:
        m_dataBytes = 8;
        m_dataDirection = Read;
        m_description = "Get ID";
        break;
    case CMD_SET_LEDS:
        m_dataBytes = 4;
        m_dataDirection = Write;
        m_description = "Set LED reg.";
        break;
    case CMD_GET_LEDS:
        m_dataBytes = 4;
        m_dataDirection = Read;
        m_description = "Get LED reg.";
        break;
    case CMD_SIPHRA_REG_OP:
        m_dataBytes = 8;
        m_dataDirection = Write;
        m_description = "SIPHRA register operation";
        break;
    case CMD_GET_SIPHRA_DATAR:
        m_dataBytes = 4;
        m_dataDirection = Read;
        m_description = "Get SIPHRA data register value";
        break;
    case CMD_GET_SIPHRA_ADCR:
        m_dataBytes = 4;
        m_dataDirection = Read;
        m_description = "Get SIPHRA ADC register value";
        break;
    case CMD_GET_CH01_REGS:
    case CMD_GET_CH02_REGS:
    case CMD_GET_CH03_REGS:
    case CMD_GET_CH04_REGS:
    case CMD_GET_CH05_REGS:
    case CMD_GET_CH06_REGS:
    case CMD_GET_CH07_REGS:
    case CMD_GET_CH08_REGS:
    case CMD_GET_CH09_REGS:
    case CMD_GET_CH10_REGS:
    case CMD_GET_CH11_REGS:
    case CMD_GET_CH12_REGS:
    case CMD_GET_CH13_REGS:
    case CMD_GET_CH14_REGS:
    case CMD_GET_CH15_REGS:
    case CMD_GET_CH16_REGS:
        m_dataBytes = 4;
        m_dataDirection = Read;
        m_description = "Read channel registers";
        break;
    default:
        return -1;
    }

    return code;
}
