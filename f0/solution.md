# F1

----------------------

## 1.
- After running `$ cd ~` you end up in your own User directory (/home/your_user_name).

----------------------

## 2.
The following commands are able to create the requested folder tree format:
- `$ mkdir dir1`
- `$ mkdir dir1/dir2`
- `$ mkdir dir1/dir3`
- `$ mkdir dir1/dir2/dir4`
- `$ mkdir dir1/dir2/dir5`
- `$ mkdir dir1/dir2/dir4/dir6`

----------------------

## 3.
Let's split it in 2:

- The first piece, `$  cd dir1/dir2/dir4/dir6`, will take you to **dir6**, following the tree hierarchy you created in the previous exercise (to access **dir6** you need to be in **dir4** but to get to **dir4** you need to be in **dir2** and so on...);

- The second chunk contains two instances of `/..`. It's used to go back once in a directory. Since you're currently located in **dir6**, executing `/../..` will take you back to **dir2**.

Executing the command as a whole just does the exact same, but all at once, landing on **dir2**.

----------------------

## 4.
The commands you should run:
- `$ touch dir1/dir2/dir4/g22.doc`
- `$ touch dir1/dir2/f1.txt`
- `$ touch dir1/dir2/h22.txt`
- `$ touch dir1/dir2/g368.pdf`
- `$ touch dir1/dir3/f3a.txt`
- `$ touch dir1/dir3/g56.doc`
- `$ touch dir1/dir3/g3x.pdf`

----------------------

## 5.
The `find` command is used to search for files in a directory hierarchy, by matching conditions you specify when entering the command. Let's break it down:

- The parameter **dir1/dir2** argument specifies it should search for the files inside **dir2**, which is nested in **dir1**;

- The **-name** argument states the search should be focused on the name of the files;

- The third chunk is the REGEX (**"[fg][35][4-7a-z].txt"**). This one means it should find any files named with an 'f' or 'g', followed by either '3' or '5', which are followed by any number from 4 to 7 or a letter in the alphabet. Finally, the it must be a text file. 
Notice that in every "[...]" chunk of the REGEX we only allow one instance of it (e.g. the files have either 'f' or 'g' but not both);

- **-print** is only used to display the paths of the matching files.

Following the explanation, the first command won't return any results, since none of the files exacly match the regular expression. The second one though should return the path of the **f3a.txt** file.

----------------------

## 6.

The `rm` is used to remove a specific file from the File System. In this case we want to remove the **dir2** directory and all contents inside it, since we invoke it with the `-rf` flags (the 'r' stands for remove recursively any contents inside the directory and 'f' ignores any non-existent files). The new tree should look something like this:

==dir1==
&nbsp;&nbsp;&nbsp;└── ==dir3==
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── f3a.txt
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── g3x.pdf
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── g56.doc

----------------------

## 7.

|                  |      f3a.txt     |     g3x.pdf      |     j52.docx     |
|:----------------:|:----------------:|:----------------:|:----------------:|
| Octal permissions|       644        |       644        |       644        |
|   File owners    |      lblopes     |     lblopes      |     lblopes      |
|  Creation dates  |   Dec 29 15:43   |   Dec 29 15:44   |   Dec 29 15:47   |
|   Size (bytes)   |       1412       |     13923695     |       13793      |

----------------------

## 8.
Assuming the previous perms were "-rwxrwxrwx":
After `$ chmod 755 doit`: "-rwxr-xr-x";
After `$ chmod u-wx doit`: "--wxr-xr-x";
After `$ chmod go-rx doit`: "--wxr-xr-x";
After `$ chmod 644 doit`: "-rw-r--r--".

----------------------
