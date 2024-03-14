#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
    constexpr float doorOpenTiming = 10.0f; //seconds
    constexpr float maxResponseTime = 5.0f; //seconds
    constexpr int refreshInterval = 100; //milliseconds, baseline is 1000
    constexpr int doorBlockMax = 3;
    constexpr int maxWeight = 450; //kg
    constexpr int safeFloor = 0;
}

#endif // CONSTANTS_H
