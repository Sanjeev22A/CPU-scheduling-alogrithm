#include <stdlib.h>

int main() {
    // Compile and execute writer.c
    system("gcc writer.c -o writer");
    system("./writer");

    // Compile and execute rr.c
    system("gcc RR.c -o rr");
    system("./rr");

    // Compile and execute irr.c
    system("gcc irr.c -o irr");
    system("./irr");

    // Execute graph.py using Python
    system("python3 graph.py");

    return 0;
}
