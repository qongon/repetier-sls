/*
    This file is part of Repetier-Firmware.

    Repetier-Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Repetier-Firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Repetier-Firmware.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef IO_TARGET
#error You need to set IO_TARGET before calling this file!
#endif

#undef SENSOR_DHT_22

#if IO_TARGET == IO_TARGET_PERIODICAL_ACTIONS

#define SENSOR_DHT_22(name, signalPin) \
    if ((CPU_ARCH != ARCH_AVR) || digitalPinToInterrupt(signalPin::pin()) > -1) { \
        name.process(); \
    }

#elif IO_TARGET == IO_TARGET_INIT

#define SENSOR_DHT_22(name, signalPin) \
    name.reattachIntFunc = +[] { \
        attachInterrupt( \
            (CPU_ARCH != ARCH_AVR) ? signalPin::pin() : digitalPinToInterrupt(signalPin::pin()), \
            [] { \
                name.pinInterrupt(); \
            }, \
            CHANGE); \
    };

#elif IO_TARGET == IO_TARGET_CLASS_DEFINITION

#define SENSOR_DHT_22(name, signalPin) \
    extern SensorDHT22<signalPin> name;

#elif IO_TARGET == IO_TARGET_DEFINE_VARIABLES

#define SENSOR_DHT_22(name, signalPin) \
    SensorDHT22<signalPin> name;

#elif IO_TARGET == IO_TARGET_TOOLS_TEMPLATES

#define SENSOR_DHT_22(name, signalPin) \
    template class SensorDHT22<signalPin>;

#endif

#ifndef SENSOR_DHT_22
#define SENSOR_DHT_22(name, signalPin)
#endif
