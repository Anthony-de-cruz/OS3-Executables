# OS3-Executables
A C program to find executable files in a unix file system.


Todo:
- [x] Parse argument directories both in the form of {dir1:dir2} in the style of PATH and {dir1 dir2}
- [x] Find all of the files within those directories
- [x] Identify whether or not they are executables via the inode using `stat`
- [x] Print it all out.
