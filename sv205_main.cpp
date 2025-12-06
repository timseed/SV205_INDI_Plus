#include "indi_sv205.h"
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <indidevapi.h>

SV205* driver = nullptr;

// Handle Ctrl+C / termination signals
void signal_handler(int sig)
{
    if (driver)
    {
        driver->Disconnect();
        delete driver;
        driver = nullptr;
    }
    IDMessage("SV205", "Exiting due to signal %d", sig);
    exit(0);
}

int main(int argc, char* argv[])
{
    (void)argc; (void)argv;

    // Set up signal handlers
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    driver = new SV205();

    IDMessage("SV205", "Driver process started");

    if (!driver->Connect())
    {
        IDMessage("SV205", "Failed to connect");
        delete driver;
        return 1;
    }

    IDMessage("SV205", "Connected successfully");

    // Simple loop to mimic INDI server driver cycle
    while (true)
    {
        driver->TimerHit();
        usleep(100000); // 100 ms
    }

    // Cleanup (never reached in this simple loop)
    driver->Disconnect();
    delete driver;

    return 0;
}




