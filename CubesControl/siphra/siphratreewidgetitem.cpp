/*
 *==============================================================================
 * Source file for SIPHRA Tree Widget Item class
 *==============================================================================
 *
 * author: Theodor Stana (theodor.stana@gmail.com)
 *
 * date of creation: 2017-04-11
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
 *    2017-04-11   Theodor Stana     File created
 *==============================================================================
 * TODO: -
 *==============================================================================
 */

#include "siphratreewidgetitem.h"

#include <QTreeWidgetItem>

SiphraTreeWidgetItem::SiphraTreeWidgetItem()
    : QTreeWidgetItem(0)
    , m_registerAddress(0xff)
    , m_registerView(false)
{
}

SiphraTreeWidgetItem::SiphraTreeWidgetItem(QTreeWidget *parent,
                                           qint8 registerAddress,
                                           bool registerView)
    : QTreeWidgetItem(parent)
    , m_registerAddress(registerAddress)
    , m_registerView(registerView)
{
    /*
     * If we display a register view, there are three columns in the QTreeWidget:
     *      - Offset
     *      - Name
     *      - Value
     */
    if (registerView) {

        /* Set register's default address and value */
        setText(0, "0x" + QString::number(registerAddress, 16).rightJustified(2, QLatin1Char('0')));
        setText(2, "");
        setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);

        /* Add register bit fields and names based on address */
        switch (registerAddress) {
        case SIPHRA_CTRL_CH_01:
        case SIPHRA_CTRL_CH_02:
        case SIPHRA_CTRL_CH_03:
        case SIPHRA_CTRL_CH_04:
        case SIPHRA_CTRL_CH_05:
        case SIPHRA_CTRL_CH_06:
        case SIPHRA_CTRL_CH_07:
        case SIPHRA_CTRL_CH_08:
        case SIPHRA_CTRL_CH_09:
        case SIPHRA_CTRL_CH_10:
        case SIPHRA_CTRL_CH_11:
        case SIPHRA_CTRL_CH_12:
        case SIPHRA_CTRL_CH_13:
        case SIPHRA_CTRL_CH_14:
        case SIPHRA_CTRL_CH_15:
        case SIPHRA_CTRL_CH_16:
            /* Set register's name */
            m_registerName = "CTRL_CH_" + QString::number(registerAddress+1).rightJustified(2, QLatin1Char('0'));
            setText(1, m_registerName);
            setText(3, "Channel " + QString::number(registerAddress+1) + " configuration register");

            /* Bit fields */
            for (int i = 0; i < 8; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "25:18");
            child(0)->setText(1, "cmis_detector_voffset");
            child(0)->setText(3, "AIN input voltage offset");
            child(1)->setText(0, "17:15");
            child(1)->setText(1, "cmis_detector_ioffset");
            child(1)->setText(3, "AIN input current offset");
            child(2)->setText(0, "14");
            child(2)->setText(1, "cmis_impedance_reduction");
            child(2)->setText(3, "AIN input impedance (VBIAS)\n0 = 5uA\n1 = 10uA");
            child(3)->setText(0, "13");
            child(3)->setText(1, "cal_select_channel");
            child(3)->setText(3, "Calibration Test Enable");
            child(4)->setText(0, "12:5");
            child(4)->setText(1, "qc_threshold");
            child(4)->setText(3, "Charge comparator threshold");
            child(5)->setText(0, "4:2");
            child(5)->setText(1, "qc_hysteresis");
            child(5)->setText(3, "Charge comparator hysteresis");
            child(6)->setText(0, "1");
            child(6)->setText(1, "powerup_channel");
            child(6)->setText(3, "Power up channel");
            child(7)->setText(0, "0");
            child(7)->setText(1, "enable_triggering");
            child(7)->setText(3, "Enable channel trigger outputs");
            break;

        case SIPHRA_CTRL_CH_SUM:
            /* Set register's name */
            m_registerName = "CTRL_CH_SUM";
            setText(1, m_registerName);
            setText(3, "Summing channel configuration register");

            /* Bit fields */
            for (int i = 0; i < 5; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "13");
            child(0)->setText(1, "cal_select_channel");
            child(0)->setText(3, "Calibration Test Enable");
            child(1)->setText(0, "12:5");
            child(1)->setText(1, "qc_threshold");
            child(1)->setText(3, "Charge comparator threshold");
            child(2)->setText(0, "4:2");
            child(2)->setText(1, "qc_hysteresis");
            child(2)->setText(3, "Charge comparator hysteresis");
            child(3)->setText(0, "1");
            child(3)->setText(1, "powerup_channel");
            child(3)->setText(3, "Power up channel");
            child(4)->setText(0, "0");
            child(4)->setText(1, "enable_triggering");
            child(4)->setText(3, "Enable channel trigger outputs");
            break;

        case SIPHRA_CHANNEL_CONFIG:
            /* Set register's name */
            m_registerName = "CHANNEL_CONFIG";
            setText(1, m_registerName);
            setText(3, "Configuration register applying to all channels");

            /* Bit fields */
            for (int i = 0; i < 8; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "23:21");
            child(0)->setText(1, "cmis_gain");
            child(0)->setText(3, "CMIS gain setting\n0 = 1/10\n1 = 1/100\n3 = 1/200\n7 = 1/400");
            child(1)->setText(0, "20:19");
            child(1)->setText(1, "ci_gain");
            child(1)->setText(3, "Current integrator gain setting\n0 = 1V/30pC\n1 = 1V/27.75pC\n2 = 1V/3pC\n3 = 1V/0.75pC");
            child(2)->setText(0, "18");
            child(2)->setText(1, "ci_compmode");
            child(2)->setText(3, "Current integrator compensation mode");
            child(3)->setText(0, "17:14");
            child(3)->setText(1, "shaper_bias");
            child(3)->setText(3, "Shaper bias current");
            child(4)->setText(0, "13:10");
            child(4)->setText(1, "shaper_feedback_cap");
            child(4)->setText(3, "Shaper feedback capacitance selection");
            child(5)->setText(0, "9:7");
            child(5)->setText(1, "shaper_feedback_res");
            child(5)->setText(3, "Shaper feedback resistance selection");
            child(6)->setText(0, "6:4");
            child(6)->setText(1, "shaper_hold_cap");
            child(6)->setText(3, "Shaper hold capacitance selection");
            child(7)->setText(0, "3:0");
            child(7)->setText(1, "shaper_input_cap");
            child(7)->setText(3, "Shaper input capacitance selection");
            break;

        case SIPHRA_CHANNEL_CONTROL:
            /* Set register's name */
            m_registerName = "CHANNEL_CONTROL";
            setText(1, m_registerName);
            setText(3, "Configuration register applying to all channels");

            /* Bit fields */
            for (int i = 0; i < 8; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "22:15");
            child(0)->setText(1, "ci_feedback_dac");
            child(0)->setText(3, "Current integrator high-impedance feedback DAC (decay time)");
            child(1)->setText(0, "14");
            child(1)->setText(1, "ci_use_reset");
            child(1)->setText(3, "Current integrator reset use\n0 = don't use reset\n1 = use readout reset");
            child(2)->setText(0, "13");
            child(2)->setText(1, "th_select_input");
            child(2)->setText(3, "Track and hold\n0 = Select Shaper\n1 = Select Current Integrator");
            child(3)->setText(0, "12:11");
            child(3)->setText(1, "cb_select_input");
            child(3)->setText(3, "Select input to AOUT channel buffers\n0 = TH\n1 = SHA\n2 = CI");
            child(4)->setText(0, "10");
            child(4)->setText(1, "ms_select_input");
            child(4)->setText(3, "Trigger Buffer source\n0 = Use QT\n1 = Use CT");
            child(5)->setText(0, "9");
            child(5)->setText(1, "cc_enable_dcc");
            child(5)->setText(3, "Enable current comparator dark current compensation");
            child(6)->setText(0, "8:1");
            child(6)->setText(1, "cc_threshold");
            child(6)->setText(3, "Current Comparator reference threshold");
            child(7)->setText(0, "0");
            child(7)->setText(1, "pt100_enable_excitation");
            child(7)->setText(3, "Enable PT100 preamplifier 0.5mA excitation current");
            break;

        case SIPHRA_ADC_CONFIG:
            /* Set register's name */
            m_registerName = "ADC_CONFIG";
            setText(1, m_registerName);
            setText(3, "ADC configuration register");

            /* Bit fields */
            for (int i = 0; i < 3; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "5");
            child(0)->setText(1, "analog_readout_mode");
            child(0)->setText(3, "1 = Disable ADC;\ncaptured analog data presented for adc_sample_duration clock cycles;\nTXD is '1' during first SYSCLK cycle of first data presented");
            child(1)->setText(0, "4:1");
            child(1)->setText(1, "adc_sample_duration");
            child(1)->setText(3, "ADC sampling duration in clock cycles (default = 4)");
            child(2)->setText(0, "0");
            child(2)->setText(1, "adc_mode");
            child(2)->setText(3, "0 = standby & automatic wakeup\n1 = always on");
            break;

        case SIPHRA_CAL_DAC:
            /* Set register's name */
            m_registerName = "CAL_DAC";
            setText(1, m_registerName);
            setText(3, "Gain Calibration Unit, Voltage DAC setting");

            /* Bit fields */
            insertChild(0, new QTreeWidgetItem(this));
            child(0)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
            child(0)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
            child(0)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
            child(0)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
            child(0)->setText(0, "7:0");
            child(0)->setText(1, "cal_dac_voltage");
            child(0)->setText(2, "");
            child(0)->setText(3, "DAC voltage setting");
            break;

        case SIPHRA_POWER_MODULES:
            /* Set register's name */
            m_registerName = "POWER_MODULES";
            setText(1, m_registerName);
            setText(3, "Module power up register");

            /* Bit fields */
            for (int i = 0; i < 18; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "17");
            child(0)->setText(1, "sum_cc");
            child(0)->setText(3, "Power up Summing Current Comparator");
            child(1)->setText(0, "16");
            child(1)->setText(1, "sum_ci");
            child(1)->setText(3, "Power up Summing Current Integrator");
            child(2)->setText(0, "15");
            child(2)->setText(1, "sum_sha");
            child(2)->setText(3, "Power up Summing Shaper");
            child(3)->setText(0, "14");
            child(3)->setText(1, "sum_th");
            child(3)->setText(3, "Power up Summing Track and Hold");
            child(4)->setText(0, "13");
            child(4)->setText(1, "sum_qc");
            child(4)->setText(3, "Power up Summing Charge Comparator");
            child(5)->setText(0, "12");
            child(5)->setText(1, "sum_cb");
            child(5)->setText(3, "Power up Summing Channel Buffer");
            child(6)->setText(0, "11");
            child(6)->setText(1, "cmis");
            child(6)->setText(3, "Power up CMIS");
            child(7)->setText(0, "10");
            child(7)->setText(1, "cc");
            child(7)->setText(3, "Power up Current Comparator");
            child(8)->setText(0, "9");
            child(8)->setText(1, "ci_fb_dac");
            child(8)->setText(3, "Power up VFP DAC for Current Integrator");
            child(9)->setText(0, "8");
            child(9)->setText(1, "ci");
            child(9)->setText(3, "Power up Current Integrator");
            child(10)->setText(0, "7");
            child(10)->setText(1, "sha");
            child(10)->setText(3, "Power up Shaper");
            child(11)->setText(0, "6");
            child(11)->setText(1, "th");
            child(11)->setText(3, "Power up Track and Hold");
            child(12)->setText(0, "5");
            child(12)->setText(1, "qc");
            child(12)->setText(3, "Power up Charge Comparator");
            child(13)->setText(0, "4");
            child(13)->setText(1, "cb");
            child(13)->setText(3, "Power up Channel Buffer");
            child(14)->setText(0, "3");
            child(14)->setText(1, "trigger_output_enable");
            child(14)->setText(3, "Trigger Buffer\n0 = Powerdown/High-Z\n1 = Enable (only functional if CB is also powered down)");
            child(15)->setText(0, "2");
            child(15)->setText(1, "adc_ref");
            child(15)->setText(3, "Power up ADC reference");
            child(16)->setText(0, "1");
            child(16)->setText(1, "pt100");
            child(16)->setText(3, "Power up PT100 preamplifier");
            child(17)->setText(0, "0");
            child(17)->setText(1, "mb");
            child(17)->setText(3, "Power up Multiplexer Buffer");
            break;

        case SIPHRA_CAL_CTRL:
            /* Set register's name */
            m_registerName = "CAL_CTRL";
            setText(1, m_registerName);
            setText(3, "Gain Calibration Unit control register");

            /* Bit fields */
            for (int i = 0; i < 5; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "5");
            child(0)->setText(1, "cal_cv_range_low");
            child(0)->setText(3, "Enable Low Charge Range calibration (7.8fC to 526fC)");
            child(1)->setText(0, "4");
            child(1)->setText(1, "cal_cv_range_mid");
            child(1)->setText(3, "Enable Mid Charge Range calibration (78fC to 5.26pC)");
            child(2)->setText(0, "3");
            child(2)->setText(1, "cal_cv_range_high");
            child(2)->setText(3, "Enable High Charge Range calibration (780fC to 52.6pC)");
            child(3)->setText(0, "2");
            child(3)->setText(1, "cal_trigger_select");
            child(3)->setText(3, "Select trigger type\n0 = External (via DCAL_I)\n1 = Internal");
            child(4)->setText(0, "1:0");
            child(4)->setText(1, "cal_mode");
            child(4)->setText(3, "Gain Calibration Unit mode\n0 = off\n1 = internal capacitor/voltage\n2 = external voltage/internal capacitor\n3 = external voltage/capacitor");
            break;

        case SIPHRA_READOUT_FIXED_LIST:
            /* Set register's name */
            m_registerName = "READOUT_FIXED_LIST";
            setText(1, m_registerName);
            setText(3, "Enable fixed list readout mode");

            /* Bit fields */
            for (int i = 0; i < 19; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "18");
            child(0)->setText(1, "adc_in");
            child(0)->setText(3, "Enable ADC_IN for fixed-list readout mode");
            child(1)->setText(0, "17");
            child(1)->setText(1, "ch_sum");
            child(1)->setText(3, "Enable summing channel for fixed-list readout mode");
            child(2)->setText(0, "16");
            child(2)->setText(1, "ch_16");
            child(2)->setText(3, "Enable channel 16 for fixed-list readout mode");
            child(3)->setText(0, "15");
            child(3)->setText(1, "ch_15");
            child(3)->setText(3, "Enable channel 15 for fixed-list readout mode");
            child(4)->setText(0, "14");
            child(4)->setText(1, "ch_14");
            child(4)->setText(3, "Enable channel 14 for fixed-list readout mode");
            child(5)->setText(0, "13");
            child(5)->setText(1, "ch_13");
            child(5)->setText(3, "Enable channel 13 for fixed-list readout mode");
            child(6)->setText(0, "12");
            child(6)->setText(1, "ch_12");
            child(6)->setText(3, "Enable channel 12 for fixed-list readout mode");
            child(7)->setText(0, "11");
            child(7)->setText(1, "ch_11");
            child(7)->setText(3, "Enable channel 11 for fixed-list readout mode");
            child(8)->setText(0, "10");
            child(8)->setText(1, "ch_10");
            child(8)->setText(3, "Enable channel 10 for fixed-list readout mode");
            child(9)->setText(0, "9");
            child(9)->setText(1, "ch_9");
            child(9)->setText(3, "Enable channel 9 for fixed-list readout mode");
            child(10)->setText(0, "8");
            child(10)->setText(1, "ch_8");
            child(10)->setText(3, "Enable channel 8 for fixed-list readout mode");
            child(11)->setText(0, "7");
            child(11)->setText(1, "ch_7");
            child(11)->setText(3, "Enable channel 7 for fixed-list readout mode");
            child(12)->setText(0, "6");
            child(12)->setText(1, "ch_6");
            child(12)->setText(3, "Enable channel 6 for fixed-list readout mode");
            child(13)->setText(0, "5");
            child(13)->setText(1, "ch_5");
            child(13)->setText(3, "Enable channel 5 for fixed-list readout mode");
            child(14)->setText(0, "4");
            child(14)->setText(1, "ch_4");
            child(14)->setText(3, "Enable channel 4 for fixed-list readout mode");
            child(15)->setText(0, "3");
            child(15)->setText(1, "ch_3");
            child(15)->setText(3, "Enable channel 3 for fixed-list readout mode");
            child(16)->setText(0, "2");
            child(16)->setText(1, "ch_2");
            child(16)->setText(3, "Enable channel 2 for fixed-list readout mode");
            child(17)->setText(0, "1");
            child(17)->setText(1, "ch_1");
            child(17)->setText(3, "Enable channel 1 for fixed-list readout mode");
            child(18)->setText(0, "0");
            child(18)->setText(1, "pt100");
            child(18)->setText(3, "Enable PT100 for fixed-list readout mode");
            break;

        case SIPHRA_READOUT_MODE:
            /* Set register's name */
            m_registerName = "READOUT_MODE";
            setText(1, m_registerName);
            setText(3, "Readout mode configuration register");

            /* Bit fields */
            for (int i = 0; i < 7; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "14:10");
            child(0)->setText(1, "int_hold_tune");
            child(0)->setText(3, "Internal Hold Delay linear tuning");
            child(1)->setText(0, "9:6");
            child(1)->setText(1, "int_hold_delay");
            child(1)->setText(3, "Internal Hold Delay 1/x setting");
            child(2)->setText(0, "5:4");
            child(2)->setText(1, "int_hold_source");
            child(2)->setText(3, "Source for internal HOLD signal\n0 = OR(CT[15:0],CTS)\n1 = CTS\n2 = OR(QT[15:0],QTS)\n3 = QTS");
            child(3)->setText(0, "3");
            child(3)->setText(1, "list_mode");
            child(3)->setText(3, "0 = List-mode only\n1 = List-mode+triggered channels");
            child(4)->setText(0, "2");
            child(4)->setText(1, "en_spi_forced_start");
            child(4)->setText(3, "Enable SPI forced readout command");
            child(5)->setText(0, "1");
            child(5)->setText(1, "en_ext_hold_start");
            child(5)->setText(3, "Enable external HOLD to start forced readout");
            child(6)->setText(0, "0");
            child(6)->setText(1, "en_int_hold_start");
            child(6)->setText(3, "Enable internal HOLD to start auto-triggered readout");
            break;

        case SIPHRA_AMUX_CTRL:
            /* Set register's name */
            m_registerName = "AMUX_CTRL";
            setText(1, m_registerName);
            setText(3, "Source selection for ADC input");

            /* Bit fields */
            for (int i = 0; i < 2; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "5:1");
            child(0)->setText(1, "adc_source_select");
            child(0)->setText(3, "Channel selection for manual readout mode");
            child(1)->setText(0, "0");
            child(1)->setText(1, "adc_enable_manual_selection");
            child(1)->setText(3, "Enable manual selection mode");
            break;

        case SIPHRA_ADC_CLK_DIV_FACTOR:
            /* Set register's name */
            m_registerName = "ADC_CLK_DIV_FACTOR";
            setText(1, m_registerName);
            setText(3, "ADC clock divider register");

            /* Bit fields */
            insertChild(0, new QTreeWidgetItem(this));
            child(0)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
            child(0)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
            child(0)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
            child(0)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
            child(0)->setText(0, "7:0");
            child(0)->setText(1, "adc_clk_div_factor");
            child(0)->setText(2, "");
            child(0)->setText(3, "Divide frequency by adc_clk_div_factor+1");
            break;

        case SIPHRA_SYSCLOCK_CTRL:
            /* Set register's name */
            m_registerName = "SYSCLOCK_CTRL";
            setText(1, m_registerName);
            setText(3, "System clock control register");

            /* Bit fields */
            for (int i = 0; i < 2; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "1");
            child(0)->setText(1, "sysclk_disable");
            child(0)->setText(3, "Disable SYS_CLK");
            child(1)->setText(0, "0");
            child(1)->setText(1, "sysclk_standby");
            child(1)->setText(3, "Standby, disable SYS_CLK between readouts");
            break;

        case SIPHRA_CMD_DCAL:
            /* Set register's name */
            m_registerName = "CMD_DCAL";
            setText(1, m_registerName);
            setText(3, "Trigger internal DCAL");

            /* Bit fields */
            insertChild(0, new QTreeWidgetItem(this));
            child(0)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
            child(0)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
            child(0)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
            child(0)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
            child(0)->setText(0, "0");
            child(0)->setText(1, "trigger_dcal");
            child(0)->setText(2, "");
            child(0)->setText(3, "Write '0' then '1' to trigger internal DCAL with a positive charge. Write '1' then '0' to use a negative charge.");
            break;

        case SIPHRA_CMD_READOUT:
            /* Set register's name */
            m_registerName = "CMD_READOUT";
            setText(1, m_registerName);
            setText(3, "Start forced readout");

            /* Bit fields */
            insertChild(0, new QTreeWidgetItem(this));
            child(0)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
            child(0)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
            child(0)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
            child(0)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
            child(0)->setText(0, "0");
            child(0)->setText(1, "readout_spi_force_start");
            child(0)->setText(2, "");
            child(0)->setText(3, "Write '1' to start forced readout");
            break;

        case SIPHRA_TRIGGER_LATCHES:
            /* Set register's name */
            m_registerName = "TRIGGER_LATCHES";
            setText(1, m_registerName);
            setText(3, "____TBD: CC trig flags???_____ Trigger flags. NB: Reset after readout.");

            /* Bit fields */
            for (int i = 0; i < 17; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "16");
            child(0)->setText(1, "qt_ch_sum");
            child(0)->setText(3, "Summing channel triggered");
            child(1)->setText(0, "15");
            child(1)->setText(1, "qt_ch_16");
            child(1)->setText(3, "Channel 16 triggered");
            child(2)->setText(0, "14");
            child(2)->setText(1, "qt_ch_15");
            child(2)->setText(3, "Channel 15 triggered");
            child(3)->setText(0, "13");
            child(3)->setText(1, "qt_ch_14");
            child(3)->setText(3, "Channel 14 triggered");
            child(4)->setText(0, "12");
            child(4)->setText(1, "qt_ch_13");
            child(4)->setText(3, "Channel 13 triggered");
            child(5)->setText(0, "11");
            child(5)->setText(1, "qt_ch_12");
            child(5)->setText(3, "Channel 12 triggered");
            child(6)->setText(0, "10");
            child(6)->setText(1, "qt_ch_11");
            child(6)->setText(3, "Channel 11 triggered");
            child(7)->setText(0, "9");
            child(7)->setText(1, "qt_ch_10");
            child(7)->setText(3, "Channel 10 triggered");
            child(8)->setText(0, "8");
            child(8)->setText(1, "qt_ch_9");
            child(8)->setText(3, "Channel 9 triggered");
            child(9)->setText(0, "7");
            child(9)->setText(1, "qt_ch_8");
            child(9)->setText(3, "Channel 8 triggered");
            child(10)->setText(0, "6");
            child(10)->setText(1, "qt_ch_7");
            child(10)->setText(3, "Channel 7 triggered");
            child(11)->setText(0, "5");
            child(11)->setText(1, "qt_ch_6");
            child(11)->setText(3, "Channel 6 triggered");
            child(12)->setText(0, "4");
            child(12)->setText(1, "qt_ch_5");
            child(12)->setText(3, "Channel 5 triggered");
            child(13)->setText(0, "3");
            child(13)->setText(1, "qt_ch_4");
            child(13)->setText(3, "Channel 4 triggered");
            child(14)->setText(0, "2");
            child(14)->setText(1, "qt_ch_3");
            child(14)->setText(3, "Channel 3 triggered");
            child(15)->setText(0, "1");
            child(15)->setText(1, "qt_ch_2");
            child(15)->setText(3, "Channel 2 triggered");
            child(16)->setText(0, "0");
            child(16)->setText(1, "qt_ch_1");
            child(16)->setText(3, "Channel 1 triggered");
            break;

        case SIPHRA_ADC_OUT:
            /* Set register's name */
            m_registerName = "ADC_OUT";
            setText(1, m_registerName);
            setText(3, "ADC output value");

            /* Bit fields */
            insertChild(0, new QTreeWidgetItem(this));
            child(0)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
            child(0)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
            child(0)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
            child(0)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
            child(0)->setText(0, "11:0");
            child(0)->setText(1, "adc_value");
            child(0)->setText(2, "");
            break;

        case SIPHRA_PARITY_ERR_REG:
            /* Set register's name */
            m_registerName = "PARITY_ERR_REG";
            setText(1, m_registerName);
            setText(3, "Parity error flags");

            /* Bit fields */
            for (int i = 0; i < 28; i++) {
                insertChild(i, new QTreeWidgetItem(this));
                child(i)->setTextAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(1, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setTextAlignment(2, Qt::AlignTop|Qt::AlignHCenter);
                child(i)->setTextAlignment(3, Qt::AlignTop|Qt::AlignLeft);
                child(i)->setText(2, "");
            }
            child(0)->setText(0, "27");
            child(0)->setText(1, "perr_sysclock_ctrl");
            child(1)->setText(0, "26");
            child(1)->setText(1, "perr_adc_clk_div_factor");
            child(2)->setText(0, "25");
            child(2)->setText(1, "perr_amux_ctrl");
            child(3)->setText(0, "24");
            child(3)->setText(1, "perr_readout_mode");
            child(4)->setText(0, "23");
            child(4)->setText(1, "perr_readout_fixed_list");
            child(5)->setText(0, "22");
            child(5)->setText(1, "perr_cal_ctrl");
            child(6)->setText(0, "21");
            child(6)->setText(1, "perr_power_modules");
            child(7)->setText(0, "20");
            child(7)->setText(1, "perr_cal_dac");
            child(8)->setText(0, "19");
            child(8)->setText(1, "perr_adc_config");
            child(9)->setText(0, "18");
            child(9)->setText(1, "perr_channel_control");
            child(10)->setText(0, "17");
            child(10)->setText(1, "perr_channel_config");
            child(11)->setText(0, "16");
            child(11)->setText(1, "perr_ctrl_ch_sum");
            child(12)->setText(0, "15");
            child(12)->setText(1, "perr_ctrl_ch_16");
            child(13)->setText(0, "14");
            child(13)->setText(1, "perr_ctrl_ch_15");
            child(14)->setText(0, "13");
            child(14)->setText(1, "perr_ctrl_ch_14");
            child(15)->setText(0, "12");
            child(15)->setText(1, "perr_ctrl_ch_13");
            child(16)->setText(0, "11");
            child(16)->setText(1, "perr_ctrl_ch_12");
            child(17)->setText(0, "10");
            child(17)->setText(1, "perr_ctrl_ch_11");
            child(18)->setText(0, "9");
            child(18)->setText(1, "perr_ctrl_ch_10");
            child(19)->setText(0, "8");
            child(19)->setText(1, "perr_ctrl_ch_09");
            child(20)->setText(0, "7");
            child(20)->setText(1, "perr_ctrl_ch_08");
            child(21)->setText(0, "6");
            child(21)->setText(1, "perr_ctrl_ch_07");
            child(22)->setText(0, "5");
            child(22)->setText(1, "perr_ctrl_ch_06");
            child(23)->setText(0, "4");
            child(23)->setText(1, "perr_ctrl_ch_05");
            child(24)->setText(0, "3");
            child(24)->setText(1, "perr_ctrl_ch_04");
            child(25)->setText(0, "2");
            child(25)->setText(1, "perr_ctrl_ch_03");
            child(26)->setText(0, "1");
            child(26)->setText(1, "perr_ctrl_ch_02");
            child(27)->setText(0, "0");
            child(27)->setText(1, "perr_ctrl_ch_01");
            break;

        default:
            break;
        }
    }
}

SiphraTreeWidgetItem::~SiphraTreeWidgetItem()
{

}

void SiphraTreeWidgetItem::setRegisterValue(qint32 value)
{
    /* No value column if not in register table view mode */
    if (!m_registerView) {
        return;
    }

    /*
     * Adapt the value to the appropriate number of bits inside the register.
     * If this is not done, the fact that the SIPHRA outputs 1s for unused bits,
     * will lead to incorrect hex values being written in the register field box.
     */
    switch (m_registerAddress) {
    case SIPHRA_CTRL_CH_01:
    case SIPHRA_CTRL_CH_02:
    case SIPHRA_CTRL_CH_03:
    case SIPHRA_CTRL_CH_04:
    case SIPHRA_CTRL_CH_05:
    case SIPHRA_CTRL_CH_06:
    case SIPHRA_CTRL_CH_07:
    case SIPHRA_CTRL_CH_08:
    case SIPHRA_CTRL_CH_09:
    case SIPHRA_CTRL_CH_10:
    case SIPHRA_CTRL_CH_11:
    case SIPHRA_CTRL_CH_12:
    case SIPHRA_CTRL_CH_13:
    case SIPHRA_CTRL_CH_14:
    case SIPHRA_CTRL_CH_15:
    case SIPHRA_CTRL_CH_16:
        value &= 0x3fffffff;
        break;

    case SIPHRA_CTRL_CH_SUM:
        value &= 0x00003fff;
        break;

    case SIPHRA_CHANNEL_CONFIG:
        value &= 0x00ffffff;
        break;

    case SIPHRA_CHANNEL_CONTROL:
        value &= 0x007fffff;
        break;

    case SIPHRA_ADC_CONFIG:
        value &= 0x0000003f;
        break;

    case SIPHRA_CAL_CTRL:
        value &= 0x0000003f;
        break;

    case SIPHRA_READOUT_MODE:
        value &= 0x00007fff;
        break;

    case SIPHRA_AMUX_CTRL:
        value &= 0x0000003f;
        break;

    /* Registers with single multiple-bit field */
    case SIPHRA_CAL_DAC:
    case SIPHRA_ADC_CLK_DIV_FACTOR:
        value &= 0x000000ff;
        break;

    case SIPHRA_ADC_OUT:
        value &= 0x00000fff;
        break;

    /* Registers with multiple single-bit fields */
    case SIPHRA_POWER_MODULES:
        value &= 0x0003ffff;
        break;

    case SIPHRA_READOUT_FIXED_LIST:
        value &= 0x0007ffff;
        break;

    case SIPHRA_TRIGGER_LATCHES:
        value &= 0x0001ffff;
        break;

    case SIPHRA_PARITY_ERR_REG:
        value &= 0x0fffffff;
        break;

    case SIPHRA_SYSCLOCK_CTRL:
        value &= 0x00000003;
        break;

    /* Registers with single single-bit field */
    case SIPHRA_CMD_DCAL:
    case SIPHRA_CMD_READOUT:
        value &= 0x00000001;
        break;

    default:
        break;
    }

    /* Set register hex value  */
    setText(2, "0x" + QString::number(value & 0xffffffff, 16).rightJustified(8, '0').toUpper());
    updateRegisterBitFields();
}

void SiphraTreeWidgetItem::setRegisterValue(qint8 bitFieldIndex, qint32 value)
{
    /* No value column if not in register table view mode */
    if (!m_registerView) {
        return;
    }

    /* Don't execute if specified bit field greater than number of children */
    if (bitFieldIndex >= childCount()) {
        return;
    }

    /* Truncate values according to bit field width */
    switch (m_registerAddress) {
    case SIPHRA_CTRL_CH_01:
    case SIPHRA_CTRL_CH_02:
    case SIPHRA_CTRL_CH_03:
    case SIPHRA_CTRL_CH_04:
    case SIPHRA_CTRL_CH_05:
    case SIPHRA_CTRL_CH_06:
    case SIPHRA_CTRL_CH_07:
    case SIPHRA_CTRL_CH_08:
    case SIPHRA_CTRL_CH_09:
    case SIPHRA_CTRL_CH_10:
    case SIPHRA_CTRL_CH_11:
    case SIPHRA_CTRL_CH_12:
    case SIPHRA_CTRL_CH_13:
    case SIPHRA_CTRL_CH_14:
    case SIPHRA_CTRL_CH_15:
    case SIPHRA_CTRL_CH_16:
        switch (bitFieldIndex) {
        case 0:
        case 4:
            if (value > 0xff) {
                value = 0xff;
            }
            break;
        case 1:
        case 5:
            if (value > 0x07) {
                value = 0x07;
            }
            break;
        case 2:
        case 3:
        case 6:
        case 7:
            if (value > 0x01) {
                value = 0x01;
            }
            break;
        default:
            break;
        }
        break;

    case SIPHRA_CTRL_CH_SUM:
        switch (bitFieldIndex) {
        case 0:
        case 3:
        case 4:
            if (value > 0x01) {
                value = 0x01;
            }
            break;
        case 1:
            if (value > 0xff) {
                value = 0xff;
            }
            break;
        case 2:
            if (value > 0x07) {
                value = 0x07;
            }
            break;
        default:
            break;
        }
        break;

    case SIPHRA_CHANNEL_CONFIG:
        switch (bitFieldIndex) {
        case 0:
        case 5:
        case 6:
            if (value > 0x07) {
                value = 0x07;
            }
            break;
        case 1:
            if (value > 0x03) {
                value = 0x03;
            }
            break;
        case 2:
            if (value > 0x01) {
                value = 0x01;
            }
            break;
        case 3:
        case 4:
        case 7:
            if (value > 0x0f) {
                value = 0x0f;
            }
            break;
        default:
            break;
        }
        break;

    case SIPHRA_CHANNEL_CONTROL:
        switch (bitFieldIndex) {
        case 0:
        case 6:
            if (value > 0xff) {
                value = 0xff;
            }
            break;
        case 1:
        case 2:
        case 4:
        case 5:
        case 7:
            if (value > 0x01) {
                value = 0x01;
            }
            break;
        case 3:
            if (value > 0x03) {
                value = 0x03;
            }
            break;
        default:
            break;
        }
        break;

    case SIPHRA_ADC_CONFIG:
        switch (bitFieldIndex) {
        case 0:
        case 2:
            if (value > 0x01) {
                value = 0x01;
            }
            break;
        case 1:
            if (value > 0x0f) {
                value = 0x0f;
            }
            break;
        default:
            break;
        }
        break;

    case SIPHRA_CAL_CTRL:
        switch (bitFieldIndex) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (value > 0x01) {
                value = 0x01;
            }
            break;
        case 4:
            if (value > 0x03) {
                value = 0x03;
            }
            break;
        default:
            break;
        }
        break;

    case SIPHRA_READOUT_MODE:
        switch (bitFieldIndex) {
        case 0:
            if (value > 0x1f) {
                value = 0x1f;
            }
            break;
        case 1:
            if (value > 0x0f) {
                value = 0x0f;
            }
            break;
        case 2:
            if (value > 0x03) {
                value = 0x03;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
            if (value > 0x01) {
                value = 0x01;
            }
            break;
        default:
            break;
        }
        break;

    case SIPHRA_AMUX_CTRL:
        switch (bitFieldIndex) {
        case 0:
            if (value > 0x1f) {
                value = 0x1f;
            }
            break;
        case 1:
            if (value > 0x01) {
                value = 0x01;
            }
            break;
        default:
            break;
        }
        break;

    /* Registers with single multiple-bit field */
    case SIPHRA_CAL_DAC:
    case SIPHRA_ADC_CLK_DIV_FACTOR:
        if (value > 0xff) {
            value = 0xff;
        }
        break;

    case SIPHRA_ADC_OUT:
        if (value > 0xfff) {
            value = 0xfff;
        }
        break;

    /* Registers with single-bit fields */
    case SIPHRA_POWER_MODULES:
    case SIPHRA_READOUT_FIXED_LIST:
    case SIPHRA_TRIGGER_LATCHES:
    case SIPHRA_PARITY_ERR_REG:
    case SIPHRA_SYSCLOCK_CTRL:
    case SIPHRA_CMD_DCAL:
    case SIPHRA_CMD_READOUT:
        if (value > 0x01) {
            value = 0x01;
        }
        break;
    default:
        break;
    }

    /* Finally, set the value */
    child(bitFieldIndex)->setText(2, QString::number(value));
    updateRegisterValue();
}

qint8 SiphraTreeWidgetItem::registerAddress()
{
    return m_registerAddress;
}

qint32 SiphraTreeWidgetItem::registerValue()
{
    bool ok;
    qint32 val = text(2).toInt(&ok, 16);

    return (ok ? val : -1);
}

qint32 SiphraTreeWidgetItem::registerValue(qint8 bitFieldIndex)
{
    bool ok;
    qint32 val = child(bitFieldIndex)->text(2).toInt(&ok);

    return (ok ? val : -1);
}

QString& SiphraTreeWidgetItem::registerName()
{
    return m_registerName;
}

void SiphraTreeWidgetItem::updateRegisterValue()
{
    qint32 regval = 0;

    switch (m_registerAddress) {

    case SIPHRA_CTRL_CH_01:
    case SIPHRA_CTRL_CH_02:
    case SIPHRA_CTRL_CH_03:
    case SIPHRA_CTRL_CH_04:
    case SIPHRA_CTRL_CH_05:
    case SIPHRA_CTRL_CH_06:
    case SIPHRA_CTRL_CH_07:
    case SIPHRA_CTRL_CH_08:
    case SIPHRA_CTRL_CH_09:
    case SIPHRA_CTRL_CH_10:
    case SIPHRA_CTRL_CH_11:
    case SIPHRA_CTRL_CH_12:
    case SIPHRA_CTRL_CH_13:
    case SIPHRA_CTRL_CH_14:
    case SIPHRA_CTRL_CH_15:
    case SIPHRA_CTRL_CH_16:
        regval = (child(0)->text(2).toInt() << 18) |
                 (child(1)->text(2).toInt() << 15) |
                 (child(2)->text(2).toInt() << 14) |
                 (child(3)->text(2).toInt() << 13) |
                 (child(4)->text(2).toInt() <<  5) |
                 (child(5)->text(2).toInt() <<  2) |
                 (child(6)->text(2).toInt() <<  1) |
                 (child(7)->text(2).toInt());
        break;

    case SIPHRA_CTRL_CH_SUM:
        regval = (child(0)->text(2).toInt() << 13) |
                 (child(1)->text(2).toInt() <<  5) |
                 (child(2)->text(2).toInt() <<  2) |
                 (child(3)->text(2).toInt() <<  1) |
                 (child(4)->text(2).toInt());
        break;

    case SIPHRA_CHANNEL_CONFIG:
        regval = (child(0)->text(2).toInt() << 21) |
                 (child(1)->text(2).toInt() << 19) |
                 (child(2)->text(2).toInt() << 18) |
                 (child(3)->text(2).toInt() << 14) |
                 (child(4)->text(2).toInt() << 10) |
                 (child(5)->text(2).toInt() <<  7) |
                 (child(6)->text(2).toInt() <<  4) |
                 (child(7)->text(2).toInt());
        break;

    case SIPHRA_CHANNEL_CONTROL:
        regval = (child(0)->text(2).toInt() << 15) |
                 (child(1)->text(2).toInt() << 14) |
                 (child(2)->text(2).toInt() << 13) |
                 (child(3)->text(2).toInt() << 11) |
                 (child(4)->text(2).toInt() << 10) |
                 (child(5)->text(2).toInt() <<  9) |
                 (child(6)->text(2).toInt() <<  1) |
                 (child(7)->text(2).toInt());
        break;

    case SIPHRA_ADC_CONFIG:
        regval = (child(0)->text(2).toInt() << 5) |
                 (child(1)->text(2).toInt() << 1) |
                 (child(2)->text(2).toInt());
        break;

    case SIPHRA_CAL_CTRL:
        regval = (child(0)->text(2).toInt() << 5) |
                 (child(1)->text(2).toInt() << 4) |
                 (child(2)->text(2).toInt() << 3) |
                 (child(3)->text(2).toInt() << 2) |
                 (child(4)->text(2).toInt());
        break;

    case SIPHRA_READOUT_MODE:
        regval = (child(0)->text(2).toInt() << 10) |
                 (child(1)->text(2).toInt() <<  6) |
                 (child(2)->text(2).toInt() <<  4) |
                 (child(3)->text(2).toInt() <<  3) |
                 (child(4)->text(2).toInt() <<  2) |
                 (child(5)->text(2).toInt() <<  1) |
                 (child(6)->text(2).toInt());
        break;

    case SIPHRA_AMUX_CTRL:
        regval = (child(0)->text(2).toInt() << 1) |
                 (child(1)->text(2).toInt());
        break;

    /* Registers with single multiple-bit field */
    case SIPHRA_CAL_DAC:
    case SIPHRA_ADC_CLK_DIV_FACTOR:
    case SIPHRA_ADC_OUT:
        regval = child(0)->text(2).toInt();
        break;

    /* Registers with single-bit fields */
    case SIPHRA_POWER_MODULES:
    case SIPHRA_READOUT_FIXED_LIST:
    case SIPHRA_TRIGGER_LATCHES:
    case SIPHRA_PARITY_ERR_REG:
    case SIPHRA_SYSCLOCK_CTRL:
    case SIPHRA_CMD_DCAL:
    case SIPHRA_CMD_READOUT:
        for (int i = 0; i < childCount(); i++) {
            regval |= child(i)->text(2).toInt() << (childCount()-1 - i);
        }
        break;
    default:
        break;
    }

    /* Finally, set the text */
    setText(2, "0x" + QString::number(regval, 16).rightJustified(8, '0').toUpper());
}

void SiphraTreeWidgetItem::updateRegisterBitFields()
{
    switch (m_registerAddress) {

    case SIPHRA_CTRL_CH_01:
    case SIPHRA_CTRL_CH_02:
    case SIPHRA_CTRL_CH_03:
    case SIPHRA_CTRL_CH_04:
    case SIPHRA_CTRL_CH_05:
    case SIPHRA_CTRL_CH_06:
    case SIPHRA_CTRL_CH_07:
    case SIPHRA_CTRL_CH_08:
    case SIPHRA_CTRL_CH_09:
    case SIPHRA_CTRL_CH_10:
    case SIPHRA_CTRL_CH_11:
    case SIPHRA_CTRL_CH_12:
    case SIPHRA_CTRL_CH_13:
    case SIPHRA_CTRL_CH_14:
    case SIPHRA_CTRL_CH_15:
    case SIPHRA_CTRL_CH_16:
        child(0)->setText(2, QString::number((registerValue() >> 18) & 0xff));
        child(1)->setText(2, QString::number((registerValue() >> 15) & 0x07));
        child(2)->setText(2, QString::number((registerValue() >> 14) & 0x01));
        child(3)->setText(2, QString::number((registerValue() >> 13) & 0x01));
        child(4)->setText(2, QString::number((registerValue() >>  5) & 0xff));
        child(5)->setText(2, QString::number((registerValue() >>  2) & 0x07));
        child(6)->setText(2, QString::number((registerValue() >>  1) & 0x01));
        child(7)->setText(2, QString::number((registerValue())       & 0x01));
        break;

    case SIPHRA_CTRL_CH_SUM:
        child(0)->setText(2, QString::number((registerValue() >> 13) & 0x01));
        child(1)->setText(2, QString::number((registerValue() >>  5) & 0xff));
        child(2)->setText(2, QString::number((registerValue() >>  2) & 0x07));
        child(3)->setText(2, QString::number((registerValue() >>  1) & 0x01));
        child(4)->setText(2, QString::number((registerValue())       & 0x01));
        break;

    case SIPHRA_CHANNEL_CONFIG:
        child(0)->setText(2, QString::number((registerValue() >> 21) & 0x07));
        child(1)->setText(2, QString::number((registerValue() >> 19) & 0x03));
        child(2)->setText(2, QString::number((registerValue() >> 18) & 0x01));
        child(3)->setText(2, QString::number((registerValue() >> 14) & 0x0f));
        child(4)->setText(2, QString::number((registerValue() >> 10) & 0x0f));
        child(5)->setText(2, QString::number((registerValue() >>  7) & 0x07));
        child(6)->setText(2, QString::number((registerValue() >>  4) & 0x07));
        child(7)->setText(2, QString::number((registerValue())       & 0x0f));
        break;

    case SIPHRA_CHANNEL_CONTROL:
        child(0)->setText(2, QString::number((registerValue() >> 15) & 0xff));
        child(1)->setText(2, QString::number((registerValue() >> 14) & 0x01));
        child(2)->setText(2, QString::number((registerValue() >> 13) & 0x01));
        child(3)->setText(2, QString::number((registerValue() >> 11) & 0x03));
        child(4)->setText(2, QString::number((registerValue() >> 10) & 0x01));
        child(5)->setText(2, QString::number((registerValue() >>  9) & 0x01));
        child(6)->setText(2, QString::number((registerValue() >>  1) & 0xff));
        child(7)->setText(2, QString::number((registerValue())       & 0x01));
        break;

    case SIPHRA_ADC_CONFIG:
        child(0)->setText(2, QString::number((registerValue() >>  5) & 0x01));
        child(1)->setText(2, QString::number((registerValue() >>  1) & 0x0f));
        child(2)->setText(2, QString::number((registerValue())       & 0x01));
        break;

    case SIPHRA_CAL_CTRL:
        child(0)->setText(2, QString::number((registerValue() >>  5) & 0x01));
        child(1)->setText(2, QString::number((registerValue() >>  4) & 0x01));
        child(2)->setText(2, QString::number((registerValue() >>  3) & 0x01));
        child(3)->setText(2, QString::number((registerValue() >>  2) & 0x01));
        child(4)->setText(2, QString::number((registerValue())       & 0x03));
        break;

    case SIPHRA_READOUT_MODE:
        child(0)->setText(2, QString::number((registerValue() >> 10) & 0x1f));
        child(1)->setText(2, QString::number((registerValue() >>  6) & 0x0f));
        child(2)->setText(2, QString::number((registerValue() >>  4) & 0x03));
        child(3)->setText(2, QString::number((registerValue() >>  3) & 0x01));
        child(4)->setText(2, QString::number((registerValue() >>  2) & 0x01));
        child(5)->setText(2, QString::number((registerValue() >>  1) & 0x01));
        child(6)->setText(2, QString::number((registerValue())       & 0x01));
        break;

    case SIPHRA_AMUX_CTRL:
        child(0)->setText(2, QString::number((registerValue() >> 1) & 0x1f));
        child(1)->setText(2, QString::number((registerValue())      & 0x01));
        break;

    /* Registers with single multiple-bit field */
    case SIPHRA_CAL_DAC:
    case SIPHRA_ADC_CLK_DIV_FACTOR:
        child(0)->setText(2, QString::number(registerValue() & 0xff));
        break;

    case SIPHRA_ADC_OUT:
        child(0)->setText(2, QString::number(registerValue() & 0xfff));
        break;

    /* Registers with multiple single-bit fields */
    case SIPHRA_POWER_MODULES:
    case SIPHRA_READOUT_FIXED_LIST:
    case SIPHRA_TRIGGER_LATCHES:
    case SIPHRA_PARITY_ERR_REG:
    case SIPHRA_SYSCLOCK_CTRL:
    case SIPHRA_CMD_DCAL:
    case SIPHRA_CMD_READOUT:
        for (int i = 0; i < childCount(); i++) {
            child(i)->setText(2, QString::number((registerValue() >> (childCount()-1 - i)) & 0x01));
        }
        break;
    default:
        break;
    }
}
