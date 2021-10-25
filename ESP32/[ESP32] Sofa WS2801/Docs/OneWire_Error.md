# OneWire error

---

Library is broken, if not compile change following in file <span style="color:#AA0000">``OneWire_direct_gpio.h``</span>

```c
rtc_gpio_desc
```
to
```c
rtc_io_desc
```

---