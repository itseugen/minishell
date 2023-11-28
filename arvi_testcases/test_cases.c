orignal

//category 1:

1. /bin/ls
1_test          environment     lexer           minishell       pipex.o
LICENSE         execution       libft           minishell.h     setup
Makefile        execution.c     libmock         operations      sig_hndlr
README.md       execution.o     main.c          out             utils
builtins        expander        main.o          parser

2. /bin/pwd
/Users/adhaka/minshell_base/minishell

3. /bin/date
Mon Nov 27 03:34:12 CET 2023

4. /bin/echo "Hello, World!"
/bin/echo "Hello, World"
Hello, World

5. empty command

does nothing gives bash again

6. spaces
does nothing

7. tab
shows everything in the folder

//category 2:

1. /bin/echo Hello, World!
Hello, World!

2. /bin/ls /usr/bin
list the files in the /usr/bin directory using the /bin/ls command

3. /bin/cat /etc/passwd

will display the content of the /etc/passwd file using the /bin/cat command.

4. /bin/expr 5 + 3

 will perform addition using the /bin/expr command and print the result, which is 8.

//category 3:

1. echo -n Hello
Hellobash-3.2$

2. echo "Hello\tWorld"
Hello\tWorld

3. echo
printsnewline

//category4:

1. exit
exit -> exits shell after printing exit.

2. exit 42
exit with exit code 42

3. exit "bye"
exit
bash: exit: bye: numeric argument required
exits shell

// category 5:

1. a. /bin/ls
	b. echo $?
This will list the contents of the root directory and print 0.

2. /bin/ls filethatdoesntexist
echo $?
This will attempt to list a non-existent file, and the exit status will be 1.

3. echo Hello, World!
echo $?
Hello, World! then prints-> 0

4. thiscommanddoesntexist
echo $?
bash: thiscommanddoesntexist: command not found -> 127

5. expr $? + 5
prints 132

expr $? + $?
Sums up the exit status of the last two commands
prints 0 or 254 or 127 depends on the last two commands.

//category signals is pretty self explanatory

// category 6:

1. echo "Hello, World"
Hello, World

2. "cat lol.c | cat > lol.c"
cat lol.c | cat > lol.c

3. name="John"
   echo "Hello, $name"
Hello, John

//category 7:

1. echo 'Command with' '' 'empty arguments'
Command with  empty arguments

2. echo 'Home directory: $HOME'
Home directory: $HOME

3. echo 'Command     with     Whitespaces'
Command     with     Whitespaces

4.  echo 'ls -l | grep file > out.txt'
ls -l | grep file > out.txt


// category 8
1. env
shows environment

//category 9

1. export MY_VARIABLE="Hello, World!"
export MY_VARIABLE="Hello, World"

   env | grep MY_VARIABLE
MY_VARIABLE=Hello, World

 export MY_VARIABLE="New Value"
 env | grep MY_VARIABLE
MY_VARIABLE=New Value

//cateogry 10
