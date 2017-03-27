Building FuzzyCLIPS systems using Visual C++
--------------------------------------------

There is a workspace called fzclips (fzclips.dsw) that has 3 projects:

1. fzclipslib - used to create a static library called fzclipslib.lib

2. fzclipswin - used to create a windows version of FuzzyCLIPS with a simple interface
                for loading and executing FuzzyCLIPS programs (fzclipswin.exe)

2. fzclipscmd - used to create a command line version of FuzzyCLIPS 
                for loading and executing FuzzyCLIPS programs (fzclipscmd.exe)

When compiling and linking these systems one must be sure that the file
setup.h is correctly set to identify that the correct compiler/environment is
set. In this case there should be the following line:

#define IBM_MSC 1   /* IBM PC, with Microsoft C 6.0           */

and all other environment lines must be set to a 0 (zero) value.

Also the correct value for the WINDOW_INTERFACE definition must be configured.
When creating the fzclipswin.exe version the value must be set to 1.

#define WINDOW_INTERFACE 1

and when creating fzclipscmd.exe or fzclipslib.lib the value must be 0.

#define WINDOW_INTERFACE 0


The projects are set to have no debugging information included in the
output files. 

The work was done using version 6.0 of VC++.




