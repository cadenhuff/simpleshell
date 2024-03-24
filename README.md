# simpleshell

Description of operation and commands (10 marks)
Description of environment concepts (10 marks)
Description of i/o redirection (10 marks)
Description of the process concept, and the differences between background and foreground execution (5 marks)
Overall layout and display of understanding (10 marks)
Inclusion of four references from peer-reviewed sources such as books, articles etc. (5 marks). Note that the inclusion of Wikipedia, or a random website which just happened to come up in a Google search will result in a grade of 0 for this aspect.

<h1>Shell Operator's Manual</h1>

<h2>Operation and Commands</h2>



<ul>
  <li>cd</li>
  <li>clr</li>
  <li>dir</li>
  <li>environ</li>
  <li>echo</li>
  <li>help</li>
  <li>pause</li>
  <li>quit</li>
</ul>


<h2>Environment Concepts and Accessing Environment</h2>

<h2>I/O redirection</h2>

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




