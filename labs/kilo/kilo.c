#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void die(const char *s) {
    perror(s); // most C library functiosn that fail will set the global errno variable to indicate what the error was. 
    exit(1);
}

// When the program quits this is called ot return the program to its original settings. 
void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
        die("tcsetattr");
    }
}

void enableRawMode() {

    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) 
        die("tcgetattr"); // reads terminal attributes into 'terminos struct'
    atexit(disableRawMode);

    struct termios raw = orig_termios;
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

int main() {
    enableRawMode();

    while (1) {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) 
            die("read"); // read will wait 100 ms for input before returning. 
        // iscntrol checks if character is a control character. ASCII 0-31, 127, 32-126. 
        if (iscntrl(c)) {
            printf("%d\r\n", c); // This prints out the ASCII inde of the character.
        } 
        else {
            printf("%d ('%c')\r\n", c, c);
        }
        if (c == 'q') break;
    }
    return 0;
}
