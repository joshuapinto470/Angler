#include "AnglerED.h"



int main(int argc, char *argv[]) {
    spdlog::info("CPU Arch : {} bit", sizeof(void *) * 8);

    AnglerED angler(800, 400);
    angler.Loop();

    return 0;
}


