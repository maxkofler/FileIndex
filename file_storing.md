# File storage

Always relative to the previuos path.
Directories must end with '/'.

# Example

```
/root
/root/file1
/root/file2
/root/dir1/file1
/root/dir1/dir2/file2
/root/dir3/file3
```

will be stored as

```
/root/                #    The root directory '/root/'
file1                #
file2                #    Two files

dir1/                #    Directory 'dir1/': '/root/dir1/'
file1                #    File 'file1' in '/root/dir1/'

dir2/                #    Directory 'dir2': '/root/dir1/dir2/'
file2                #    File 'file2' in '/root/dir1/dir2/'

../../dir3/            #    Go up 2 direcories, new directory 'dir3/'
file3                #    File 'file3' in '/root/dir3/'
```

in the final file:

```
/root/
file1
file2
dir1/
file1
dir2/
file2
../../dir3/
file3
```