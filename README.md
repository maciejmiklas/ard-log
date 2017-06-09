**ArdLog** is simple logger for Arduino that creates formatted messages over Serial:
* each log message has timestamp,
* each message within single loop has the same timestamp (configurable), so that you can logically connect activities together,
* messages can be formatted using *sprintf* syntax,
* text for the messages is being held in PROGMEM,
* unsused functionality can be disabled to free up RAM.

# Installation
In order to install *ArdLog* you have to download desired release and unpack in into folder containing Arduino libraries. The is the result on MacOS:
``` bash
$ pwd
/Users/fred/Documents/Arduino/libraries/ArdLog

$ ls
ArdLog.cpp ArdLog.h ArdLogSetup.h  LICENSE    README.md 
```

# Configuration (*ArdLogSetup.h*)
* Logger is enabled by default, in order to disable it set *LOG* or *TRACE* to false.
* To free up RAM you can completly disable logger by setting *ENABLE_LOGGER* to false. In this case all methods and variables will not be compiled at all.
* Messages are created over default *Serial* port. You can choose alternative port by setrting one of: *USE_SERIAL_1*, *USE_SERIAL_2* or *USE_SERIAL_3* to true.
* In order to print current time for each log message set *USE_CURRENT_TIME* to true. By default logger will sample time only once at the beginning of each loop.
* There are two formats of timestamp - full(*LOG_FULL_TIME*) and short (*LOG_SHORT_TIME*). Full  is enabled by default.
* Each log message is using *sprintf* format. Meaning that there is a message template and corresponding parameters. Message template lenght is limited by it's buffer (*PGBUF_SIZE*). This also applyies to formated message that will be printed (*SBUF_SIZE*). Make sure to NOT overflow one of those buffers, oterwise Arduino will propably crash.
* It's possible to log free RAM, this can be enabled by setting *LOG_FREE_RAM* to true. Log message will be only created once during initialization and afterwards when RAM amount changes.

# Getting up an running
1. Choose suitable configuration in *ArdLogSetup.h*. In most cases you should be fine with default
2. Call *log_setup()* in *setup()* method - this will initialize serial port.
3. Call  *log_cycle()* at the beginning of each *loop()* - it will sample current time.
4. Put log messages into *#if LOG log(F("....") #endif* - once logger is disabled, it will not waste RAM and CUP.

```cpp
#include <ArdLog.h>

uint16_t loopIdex = 0;

void setup() {
  log_setup();
}

void loop() {
  log_cycle();

  loopIdex++;

  #if LOG
    log(F("**** Loop %d ****"), loopIdex);
    log(F("T1 = %ld"), millis());
  #endif

  delay(100);

  #if LOG
    log(F("T2 = %ld"), millis());
  #endif

  delay(1000);
}
```

This is output created by example above:
```
>>[000-00:00:00,000]-> Logger initialized, free RAM: 1537
>>[000-00:00:00,003]-> Free RAM: 1527
>>[000-00:00:00,003]-> **** Loop 1 ****
>>[000-00:00:00,003]-> T1 = 9
>>[000-00:00:00,003]-> T2 = 112
>>[000-00:00:01,113]-> **** Loop 2 ****
>>[000-00:00:01,113]-> T1 = 1114
>>[000-00:00:01,113]-> T2 = 1215
>>[000-00:00:02,215]-> **** Loop 3 ****
>>[000-00:00:02,215]-> T1 = 2217
>>[000-00:00:02,215]-> T2 = 2318
>>[000-00:00:03,319]-> **** Loop 4 ****
>>[000-00:00:03,319]-> T1 = 3320
>>[000-00:00:03,319]-> T2 = 3421
>>[000-00:00:04,422]-> **** Loop 5 ****
>>[000-00:00:04,422]-> T1 = 4423
>>[000-00:00:04,422]-> T2 = 4525
```
