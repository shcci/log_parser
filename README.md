# log_parser
utmp, wtmp of linux parser

windows version

## Build
* Visual Studio 2015 Community

## Usage
log_parser.exe [file_name]
### Example
```
C:\Users\xinfolab> log_parser.exe utmp
reboot           4.4.0-31-generic        Tue Nov 29 18:39:28 2016
runlevel         4.4.0-31-generic        Tue Nov 29 18:40:20 2016
INIT_PROCESS     tty1    tty1    Tue Nov 29 18:40:20 2016
LOGIN_PROCESS    10426   tty1    LOGIN          Tue Nov 29 18:40:20 2016
USER_PROCESS     10763   tty7    xinfolab        :0
DEAD_PROCESS     tty1    tty1    Tue Nov 29 23:04:51 2016
reboot           4.4.0-31-generic        Tue Nov 29 23:05:00 2016
INIT_PROCESS     tty1    tty1    Tue Nov 29 23:05:11 2016
LOGIN_PROCESS    5310    tty1    LOGIN          Tue Nov 29 23:05:11 2016
runlevel         4.4.0-31-generic        Tue Nov 29 23:05:14 2016
USER_PROCESS     5886    tty7    xinfolab        :0
```
