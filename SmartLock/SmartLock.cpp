//
// Created by nikita on 16.04.23.
//

#include "SmartLock.h"

void SmartLock::open() {
    _isOpen = true;
    //updateLock в БД
}

void SmartLock::close() {
    _isOpen = false;
    //updateLock в БД
}

bool SmartLock::is_open() {
    return _isOpen;
}
