ArdLog serves as simle logger for Arduino which creates formatted messages over Serial:
* Each message has timestamp.
* Each message within single loop has the same timestamp, so that you can logically connect activities together.
* Messages can be formatted using *sprint* syntax.
* Text for the messages is being held in PROGMEM.

# Configuration
* Logger is disabled by default, in order to enable it set *LOG* in *ArdLog.h* to true.
* Messages are created over default Serial port. You can choose alternative serial ports by setting: *USE_SERIAL_1*, *USE_SERIAL_2* or *USE_SERIAL_3* to true in  *ArdLog.h*.
* In order to print current time for each message set *USE_CURRENT_TIME* in *ArdLog.h* to true. By default logger will sample time only once at the beginning of each loop.

# Getting up an running
1. Choose suitable configuration in *ArdLog.h*. In most cases you have to only set *LOG* in *ArdLog.h* to true.
2. Call *log_setup()* in *setup()* method - this will initialize logger variables and serial port.
3. Call  *log_cycle()* at the beginning of each *loop()* - this will sample current time.
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
