#ifndef INCLUDE_HELPER_H
#define INCLUDE_HELPER_H

char general_help[] = "\n\
Usege: [COMMAND] [OPTION]... [FILE]\n\
See for individual command: help [COMMAND]\n\
\
 commands:\n\
 recovery	full recovery from your backup database\n\
 backup		create the backup for your files and dirs\n\
 ls		show files and dir in current dir\n\
 cd		change the current dir\n\
 rm		remove dir or file\n\
 info           show information about this program\n\
";

/*
char show_info[] = "\n\
 Copyright Anon\n\
 source
";
*/

char recovery_help[] = "\n\
Usege: recovery [OPTION]... [FILE]\n\
Examples: recovery --full\n\
	  recovery -p /books/book.pdf\n\
 options:\n\
 -f, --full		recovery a full database\n\
 -p, --path [PATH]	recovery to choice path\n\
";

char backup_help[] = "\n\
Usege: backup [OPTION]... [FILEPATH]\n\
Example: backup -p /mydirondb/music/ ~/home/user/Music/BohemianRhapsody.mp3\n\
 options:\n\
 -p, --path [PATH]	choice path(dir) for locate of backup\n\
";

char cd_help[] = "\
Usege: cd [DIR]\n\
Example: cd /music/pop/\n\
";

char rm_help[] = "\
Usege: rm [PATH]\n\
Example: rm /music/pop/BohemianRhapsody.mp3\n\
";

#endif
