# sh.c

A simple shell written in C!  
Build exclusively for educative purposes and it demonstrates just the basics of how a shell works

## Installation

You would need gyp/ninja to build and run this project  

Following commands assume installation outside sh.c

So first install gyp like this:

```sh
$ git clone https://chromium.googlesource.com/external/gyp.git && cd gyp  
$ sudo python setup.py install
```
Ninja is a small build system that is designed to be ultra fast  

Get ninja installed like this:

```sh
$ git clone https://github.com/ninja-build/ninja.git && cd ninja  
$ cd ninja  
$ ./configure.py --bootstrap  
$ cp ninja /usr/local/bin/
```

Now build the shell

```sh
$ gyp sh.gyp --depth=. -f ninja  
$ ninja -v -C out/Default -f build.ninja  
```

It's all set to be run. Run it like:

```sh
$ ./out/Default/shell
```

## Features

* Built-ins: history, history bg
* Supports system commands

## To do

- [X] Basic shell architecture (REPL through unix style fork/exec)
- [X] Directory prompt
- [X] Shell built-in : history (queue with a buffer limit)
- [X] Execute background processes through &
- [ ] Built-ins: cd, exit, help
- [ ] Status of background processes through monitoring child continuously
- [ ] Ability to pass process to foreground/background through fg/bg
- [ ] Remove output of background processes from terminal completely
