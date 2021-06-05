/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** defines ***/
#define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/

struct editorConfig {
    struct termios orig_termios;
};

struct editorConfig E;

/*** terminal ***/

void die(const char *s) {
    perror(s); // most C library functiosn that fail will set the global errno variable to indicate what the error was. 
    exit(1);
}

// When the program quits this is called ot return the program to its original settings. 
void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1) {
        die("tcsetattr");
    }
}

void enableRawMode() {

    if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) 
        die("tcgetattr"); // reads terminal attributes into 'terminos struct'
    atexit(disableRawMode);

    struct termios raw = E.orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); 
    raw.c_iflag &= ~(ICRNL | IXON); // FLag from termios
    raw.c_iflag &= ~(OPOST); // Post processing of output
    raw.c_iflag &= ~(CS8); 
    raw.c_lflag &= ~(ECHO | ICANON |IEXTEN | ISIG); // modifies a flag of terminal attributes
    // ECHO is a bitflag defined as 0000000000000000000000001000 in binary.The tilde is the NOT operatior to get it all 1s.
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VMIN] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) 
         die("tcsetattr"); //modifies terminal attributes. TCSAFLUSH tells it when to apply the change.  
}

char editorReadKey() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die ("read");
    }
    return c;
}

/*** output ***/

void editorDraw() {
    int y;
    for (y = 0; y < 24; y++) {
        write(STDOUT_FILENO, "~\r\n", 3);
    }
}

void editorRefreshScren() {
    write(STDOUT_FILENO, "\x1b[2J", 4); // \x1b is the escap sequence.
    write(STDOUT_FILENO, "\x1b[H", 3); 

    editorDrawRows();

    write(STDOUT_FILENO, "\x1b[H", 3);
}

/*** input ***/

void editorProcessorKeypresses() {
    char c = editorReadKey();

    switch (c) {
        case CTRL_KEY('q'):
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            exit(0);
            break;
    }
}

/*** init ***/

int main() {
    enableRawMode();

    while (1) {
        editorRefreshScreen();
        editorProcessKeypres(); 
    }
    return 0;
}
