rpi-air-conditioner
===================

It is a Raspberry Pi IR controller for air conditioner.
It sends IR commands using raspberry to air conditioner.

Currently only basic functions are supported for Mitsubishi MSZ-SF35VE.
Type of remote is: SG11D 1523.

#### Installation:
```
make
sudo make install
```

#### Usage:
```
sudo mitsu <temp> <on> <operation>
        <temp> = 16, ... 31
        <on> = 1=ON | 0=OFF
        <operation> = 0=HEATING | 1=DEHUMIDIFY | 2=COOLING
```

LED diode of IR transmitter is connected to GPIO 5 according to wiringPi library.
```
+----------+-Rev2-+------+--------+------+-------+
| wiringPi | GPIO | Phys | Name   | Mode | Value |
+----------+------+------+--------+------+-------+
|      5   |  24  |  18  | GPIO 5 | OUT  | Low   |
+----------+------+------+--------+------+-------+
```


#### Note:

If it doesn' work, in file *mitsu.h* experiment with timings regarding of CPU speed to achieve correct frequency of IR pulses. Variable is called ```EMPIRICAL_DELAY```. Also, try to set variables ```DEBUG``` and ```DUMP_RAW``` and recompile for additional info.


