# OS3-Executables
A C program to find executable files in a unix file system.

Takes any number of directories and colon separated directories (such as $PATH) as arguments.

## Usage
Build with:
```sh
❯ make
gcc -o OS3-Executables.out src/main.c
```
Example@
```sh
❯ ./OS3-Executables.out /home/anthonydecruz/.cargo/bin .
DIRECTORY: /home/anthonydecruz/.cargo/bin
     1226849 -               rustup
     1226849 -        rust-analyzer
     1226849 -              rustfmt
     1226849 -            cargo-fmt
     1226849 -                rustc
     1226849 -              rustdoc
     1226849 -                cargo
     1226849 -            rust-lldb
     1226849 -             rust-gdb
     1226849 -          rust-gdbgui
     1226849 -                  rls
     1226849 -         cargo-clippy
     1226849 -        clippy-driver
     1226849 -           cargo-miri
     1304089 -            rustlings
     1377968 -                cross
     1377969 -           cross-util
     2248620 -               stylua
DIRECTORY: .
     3103737 -  OS3-Executables.out
```

Todo:
- [x] Parse argument directories both in the form of {dir1:dir2} in the style of PATH and {dir1 dir2}
- [x] Find all of the files within those directories
- [x] Identify whether or n:w
ot they are executables via the inode using `stat`
- [x] Print it all out.
