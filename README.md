A lightweight C program that measures command execution time exactly like PowerShell’s ´Measure-Command´, with structured output showing both human-readable units and high-precision decimal totals.

## Features

* **Exact Powershell-compatible output**:
  * Interger breakdowns (Days, Hours, Minutes, Seconds, Milliseconds)
  * Decimal Totals (TotalDays, TotalHours, TotalMinutes, TotalSeconds, TotalMilliseconds)
  * .NET-style Ticks (100-nanosecond intervals)
* Uses **monotonic clock** (`CLOCK_MONOTONIC`) - immune to system clock adjustments
* Measures **real/wall-clock time** (not CPU time)

## Quick start

### Get the object-file
`gcc -o measure-command main.c`

### Move it to your usr/local/bin to use it easily 
`sudo mv measure-command /usr/local/bin`

### Run your exec file with measure-command
`measure-command ./a.out`

### Output

`Days: 0
Hours: 0
Minutes: 0
Seconds: 0
Milliseconds: 710
Ticks: 7101340
TotalDays: 0.0000082177...
TotalHours: 0.000197222...
TotalMinutes: 0.0118333...
TotalSeconds: 0.710134...
TotalMilliseconds: 710.134...`
