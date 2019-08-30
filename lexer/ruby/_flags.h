#ifndef FLAGS_RUBY_H
#define FLAGS_RUBY_H

//$ ruby [ options ] [.] [ programfile ] [ arguments ... ]

//-a
//Used with -n or -p to split each line. Check -n and -p options.

//-c
//Checks syntax only, without executing program.

//-C dir
//Changes directory before executing (equivalent to -X).

//-d
//Enables debug mode (equivalent to -debug).

//-F pat
//Specifies pat as the default separator pattern ($;) used by split.

//-e prog
//Specifies prog as the program from the command line. Specify multiple -e options for multiline programs.

//-h
//Displays an overview of command-line options.

//-i [ ext]
//Overwrites the file contents with program output. The original file is saved with the extension ext. If ext isn't specified, the original file is deleted.

//-I dir
//Adds dir as the directory for loading libraries.

//-K [ kcode]
//Specifies the multibyte character set code (e or E for EUC (extended Unix code); s or S for SJIS (Shift-JIS); u or U for UTF8; and a, A, n, or N for ASCII).

//-l
//Enables automatic line-end processing. Chops a newline from input lines and appends a newline to output lines.

//-n
//Places code within an input loop (as in while gets; ... end).

//-0[ octal]
//Sets default record separator ($/) as an octal. Defaults to \0 if octal not specified.

//-p
//Places code within an input loop. Writes $_ for each iteration.

//-r lib
//Uses require to load lib as a library before executing.

//-s
//Interprets any arguments between the program name and filename arguments fitting the pattern -xxx as a switch and defines the corresponding variable.

//-T [level]
//Sets the level for tainting checks (1 if level not specified).

//-v
//Displays version and enables verbose mode.

//-w
//Enables verbose mode. If program file not specified, reads from STDIN.

//-x [dir]
//Strips text before #!ruby line. Changes directory to dir before executing if dir is specified.

//-X dir
//Changes directory before executing (equivalent to -C).

//-y
//Enables parser debug mode.

//--copyright
//Displays copyright notice.

//--debug
//Enables debug mode (equivalent to -d).

//--help
//Displays an overview of command-line options (equivalent to h).

//--version
//Displays version.

//--verbose
//Enables verbose mode (equivalent to -v). Sets $VERBOSE to true.

//--yydebug
//Enables parser debug mode (equivalent to -y).

#endif // FLAGS_RUBY_H
