#include <Application.h>

int main(int argc, char *argv[]) {
    spdlog::info("CPU Arch : {} bit", sizeof(void *) * 8);

    // AnglerED angler(800, 400);
    // angler.Loop();
    BENCH_SESSION_START
    App app;
    app.Init();
    app.Loop();
    BENCH_SESSION_END
    spdlog::info("Exit");
    return 0;
}


