# Parse a string to a float

The function `strtodouble` converts a string to a double similar to `atof`. It
is written in C99 and only depends on `libc`.


## Why?

`strtodouble` is a locale-independent version of `atof` and `strtodouble`.
`atof` and `strtod` respect the locale which means that the digit point is
locale-dependent. While in some applications this is exactly what you want, it
is a not suited for reading floats from data files or configurations files.


## Usage

The prototype of the function is:
```
double strtodouble(const char *str, int *success)
```
The string you want to parse is given as the pointer `str`. The parsing stops
at the first invalid character. The function returns the parsed value or NAN
(not a number) if an error occured. If success is not NULL, at exit success
will be 1 if the conversion was successfull or 0 if an error occured. Note that
checking success is the only way to tell the difference between an error and
parsing a NAN.


## Limitations

There is a number of limitations:
 - Hexadecimal floats are not supported.
 - Rounding-off errors may occur; this is most likely not an issue in most cases.
 - The function calls `pow` which might be slow.

## Testing

For tests see `test.c`.
