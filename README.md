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
1. Choose suitable configuration in *ArdLog.h*.
2. Call *log_setup()* in *setup()* method - this will initialize logger variables and Serial.
3. Call  *log_cycle()* at the beginning of each *loop()* - this will sample current time.
4. Put log messages into *#if LOG log(F("....") #endif* - once logger is disabled, it will not waste RAM and CUP.

```cpp
#include <ArdUtil.h>
#include <ArdLog.h>

uint16_t loopIdex = 0;

void setup() {
  log_setup();
}

void loop() {
  log_cycle();
  
  loopIdex++;

  log(F("**** Loop %d ****"), loopIdex);
  
  uint32_t t1 = ms();
  
#if LOG
  log(F("T1 = %ld"), t1);
#endif

  delay(100);
  uint32_t t2 = ms();
#if LOG
  log(F("T2 = %ld"), t2);
#endif

  if(t1 == t2){
     log(F("T1 == T2"));
  }
  delay(1000);
}

```

This is output created by example above:
```
>>[000-00:00:00,000]-> Status -> Free RAM: 7660
>>[000-00:00:00,000]-> Logger initialized, free RAM: 7667
>>[000-00:00:00,004]-> Status -> Free RAM: 7654
>>[000-00:00:00,004]-> **** Loop 1 ****
>>[000-00:00:00,004]-> T1 = 4
>>[000-00:00:00,004]-> T2 = 4
>>[000-00:00:00,004]-> T1 == T2
>>[000-00:00:01,116]-> **** Loop 2 ****
>>[000-00:00:01,116]-> T1 = 1116
>>[000-00:00:01,116]-> T2 = 1116
>>[000-00:00:01,116]-> T1 == T2
>>[000-00:00:02,220]-> **** Loop 3 ****
>>[000-00:00:02,220]-> T1 = 2220
>>[000-00:00:02,220]-> T2 = 2220
>>[000-00:00:02,220]-> T1 == T2
>>[000-00:00:03,323]-> **** Loop 4 ****
>>[000-00:00:03,323]-> T1 = 3323
>>[000-00:00:03,323]-> T2 = 3323
>>[000-00:00:03,323]-> T1 == T2
```

