/*
 * Copyright (C) 2016 Andrew E. Bruno <aeb@qnot.org>
 *
 * This file is part of AngelFish.
 * 
 * AngelFish is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AngelFish is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AngelFish.  If not, see <http://www.gnu.org/licenses/>. 
 */

#include "service.h"

AngelService::AngelService(QObject *parent)
{
    _sensor = NULL;
}

void AngelService::setSensor(GatoPeripheral *sensor) {
    _sensor = sensor;
    connect(_sensor, SIGNAL(characteristicsDiscovered(GatoService)),
            this, SLOT(handleCharacteristics(GatoService)));
    connect(_sensor, SIGNAL(valueUpdated(GatoCharacteristic,QByteArray)),
            this, SLOT(handleValueUpdated(GatoCharacteristic,QByteArray)));
}
