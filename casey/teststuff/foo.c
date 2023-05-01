static void bar() {
    char *ptr = 0;
    *ptr = 1;
}

void setup_debug_handlers(void);

int main(int argc, char **argv) {
    setup_debug_handlers();
    bar();
    return 0;
}