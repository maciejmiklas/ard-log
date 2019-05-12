/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef ARD_LOG_H
#define ARD_LOG_H

#include "Arduino.h"
#include "stdarg.h"
#include "ArdLogSetup.h"

#if ENABLE_LOGGER

void log_setup();
void log_cycle();

#if LOG_FREE_RAM
void log_freeRAM(char const *msg);
#endif

void log(const __FlashStringHelper *ifsh, ...);

#if ENABLE_LOGGER
void logc(char val);
void logs(const __FlashStringHelper *ifsh, const char* msg, uint8_t size);
void logs(const __FlashStringHelper *ifsh, char* msg, uint8_t size);
void logs(const char* msg, uint8_t size);
#endif

#endif // ENABLE_LOGGER

#endif /* ARD_LOG_H */
