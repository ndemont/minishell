# minishellrose ☎️

## gpetit 
- [ ] pwd
- [ ] env
- [ ] cd

## ndemont 
- [ ] export
- [ ] echo
- [ ] unset
- [ ] exit
- [x] error -> edit to not quit the program

## How-To save our datas

- [ ] struct global avec tout 
- [ ] char ** env
- [ ] liste chainees de commandes (termcap)
- [ ] struct par commande 
- [ ] arbre binaire: 1.operation 2.command 3.command arg 4.command return 5.leftchild 6.rightchild
- [ ] le current path (cd)
- [ ] le retour de la derniere commande ($?)

## allowed functions:

- printf
- malloc
- free
- write
- open
- read
- close
- fork 
- wait / waitpid / wait3 / wait4
- signal 
- kill
- exit
- getcwd
- chdir
- stat / lstat / fstat
- execve
- dup / dup2
- pipe
- opendir / readdir / closedir
- strerror
- errno
- isatty / ttyname / ttyslot
- ioctl
- getenv
- tcsetattr / tcgetattr
- tgetent
- tgetflag / tgetnum / tgetstr
- tgoto
- tputs

## Commands builtins:

1) **export** (sans arg) -> "declare -x var" affichage var alpha

  KO : |
  ne fonctionne pas lorsquil est suivi d'un '|'
  ex: export BANANE=1 | cat -e --> la variable n'est pas crée
  
  OK : >
  
  OK : >>
  
  OK : <
  fonctionne lorsqu'il est suivi d'un '<'
  ex: export B00=3 < file --> creer la variable BOO=3

2) **echo** avec variables. ex BOO=2
si la variable n'existe pas, n'effiche rien

echo BOO -> BOO

echo "BOO" -> BOO

echo $BOO -> 2

echo $"BOO" -> BOO

echo "$BOO" -> 2

3) **pwd** 
prend des arguments mais ne les traite jamais. Les redirections et l'appending fonctionnent, sauf '<'. En effet, pwd ne prend pas d'argument.

## Small MAN for minishell functions 📚

fork -- create a new process

wait -- wait for process termination

waitpid -- wait for process termination

wait3 -- wait for process termination

wait4 -- wait for process termination

signal -- simplified software signal facilities

kill -- terminate or signal a process

exit

getcwd -- get working directory pathname

chdir

stat -- display file status

lstat -- get file status

fstat -- get file status

execve -- execute a file

dup -- duplicate an existing file descriptor

dup2 -- duplicate an existing file descriptor

pipe - Postfix delivery to external command

opendir -- directory operations

readdir -- directory operations

closedir -- directory operations

strerror -- system error messages

errno -- introduction to system calls and error numbers

isatty -- get name of associated terminal (tty) from file descriptor

ttyname -- get name of associated terminal (tty) from file descriptor

ttyslot -- get name of associated terminal (tty) from file descriptor

ioctl -- control device

getenv -- environment variable functions

tcsetattr -- manipulating the termios structure

tcgetattr -- manipulating the termios structure

tgetent - direct curses interface to the terminfo capability database

tgetflag - direct curses interface to the terminfo capability database

tgetnum - direct curses interface to the terminfo capability database

tgetstr - direct curses interface to the terminfo capability database

tgoto - direct curses interface to the terminfo capability database

tputs - direct curses interface to the terminfo capability database


