# myshell

<h1>Shell Operator's Manual</h1>

<h2>Operation and Commands</h2>
The shell is command-line interface that is used to interact with the operating system. Users can enter internal or external commands and arguments. This shell supports I/O redirection, external process creation, as well as foreground/background process execution, all described below. Listed next are internal commands built into the shell.


<ul>
  <li>cd: Changes the current directory to given argument. Also changes the PWD environment varible to match the current working directory. If no argument is given, command will print the current directory. </li>
  <li>clr: Clears the screen.</li>
  <li>dir: List the contents of given directory. If no directory is given will list the contents of the current directory.</li>
  <li>environ: List all the environment strings.</li>
  <li>echo: Print given text to output</li>
  <li>help: Displays User Manual with the more filter.</li>
  <li>pause: Pauses shell execution untill "Enter" key is pressed.</li>
  <li>quit: Terminates shell execution.</li>
</ul>


<h2>Environment Concepts and Accessing Environment</h2>
Shell runs within an environment that contains variables, paths, and configurations.
To access these variables, users can use the command "environ".



<h2>I/O redirection</h2>
I/O Redirection allows the user to change the input and output sources of commands.
Redirection Operators inlude:
<ul>
  <li><: redirects standard output to a file.</li>
  <li>>: redirects standard input to a file, overwriting if content exists in file.</li>
  <li>>>: redirects standard input to a file, appending if content exists in file.</li>
</ul>
For example
echo Hello, World! > output_file.txt

Will output "Hello, World" into output_file.txt 
<h2>Proccesses and Process Creation</h2>

Put simply, a process is an executing program. A process in memory can be divided into a text section, a data section, a heap section, and a stack section. Activity is tracked by a Program Counter and process registers. A process is identified and managed with a process identifier, a PID.

<h3>Process Creation </h3>

Parent Prcoess(es) create children processes, which, in turn create other processes, forming a tree of processes. When the shell is given an external program command, a new process is created with the fork() system call. The new process is an exact copy of the calling (parent) process, except the child process ID and parent process ID. After a successful fork(), two processes are running in parrallel: the parent process and the newly created child process. Using the exec() family of function calls, the shell will replace the program, data, and stack of the child process will the new program specified in the shell input. This allows for the shell to run an external program.

<h3>Foreground and Background Execution</h3>
Processes can run in the foreground or background.

<ul>
  <li>Foreground Execution: A process that runs in the foreground takes control of the shell until it terminates. </li>
  <li>Background Execution: A process that runs in the background allows the user to continue using the shell while it executes.</li>
</ul>

To execute an external command in the background, add an ampersand (&) to the end of the command:

./externalCommand arg1 &


<h2>References</h2>
<ol>
  <li>Silberschatz, A., Gagne, G., & Galvin, P. B. (2018). Operating System Concepts (10th ed.). Laurie Rosatone.</li>
  <li>Nemeth, E., Snyder, G., Hein, T., Whaley, B., and Mackin, D., 2011. UNIX and Linux System Administration Handbook (4th Edition). Addison-Wesley Professional.</li>
  <li>Newham, C. and Rosenblatt, B., 2005. Learning the bash Shell: Unix Shell Programming. O'Reilly Media.
</li>
  <li>Tanenbaum, A. S., & Woodhull, A. S. (2015). Operating Systems: Design and Implementation (3rd ed.). Pearson.</li>
</ol>








