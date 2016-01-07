This project contains few utility classes for Arduino projects. 

# Cached access to *millis()*
Function *millis()* needs few CPU cycles and sometimes we have to access it multiple times within single main-loop. The idea is to read value returned by *millis()* at the beginning of each iteration, store returned value in global variable and access this stored value instead of calling original function.

*ms()* provides access to cached value.

This also means, that *ms()* returns always the same vale within single iteration.

```cpp
#include <ArdUtil.h>

void setup() {
  util_setup();
}

void loop() {
  util_cycle();
  
  uint32_t t1 = ms();
  delay(100);
  uint32_t t2 = ms();
  
  if(t1 == t2){
  // this is always true
  }
}

```


# Logger over Serial port
The logger allows you to log formatted messages over Serial:
* Logger is disabled by default, in order to enable it set *LOG_DISABLED* in *ArdLog.h* to true.
* Each message has timestamp.
* Each message within single loop has the same timestamp, so that you can logically connect activities together.
* Messages can be formatted using *sprint* syntax
* Text for the messages is being held in PROGMEM

```cpp
#include <ArdUtil.h>
#include <ArdLog.h>

uint16_t loopIdex = 0;

void setup() {
  util_setup();
  log_setup();
}

void loop() {
  util_cycle();
  log_cycle();
  
  loopIdex++;

  log(F("**** Loop %d ****"), loopIdex);
  
  uint32_t t1 = ms();
  log(F("T1 = %ld"), t1);
  
  delay(100);
  uint32_t t2 = ms();

  log(F("T2 = %ld"), t2);
  
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

