# longlogger - logger with size

A slimmed down version of `util-linux`'s `logger`, `longlogger` supports entries longer than 1024 bytes. Longlogger only supports receiving log entries from `stdin`.

## Reasoning

Applications shouldn't be concerned with how or where log files are transmitted/stored. Instead, simply log to `stdout` and let the execution environment determine what to do with the log stream. Longlogger enables this by lifting the `logger` limitation on entry length.

## Compiling

To build `longlogger`, simply execute `make`.

## Installation

Simply build and install using make (sudo may be required for install):

    make && make install

## License

This software is based on the source code from `logger` utility in the `util-linux` package. The license found in longlogger.c has been reproduced from the original logger.c license.

  + Source Repository: git://git.kernel.org/pub/scm/utils/util-linux/util-linux.git
  + Source Commit: e6d0c4c1acfafed3fac1907b90d6f1077b581736
