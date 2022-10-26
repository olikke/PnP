#pragma once

#include <chrono>

static void getTime(std::chrono::high_resolution_clock::time_point &time) {
    time=std::chrono::high_resolution_clock::now();
}
static long getMilliSecSince(std::chrono::high_resolution_clock::time_point time) {
    std::chrono::system_clock::time_point now;
    getTime(now);
    return std::chrono::duration_cast<std::chrono::milliseconds>(now-time).count();
}
static long getMicroSecSince(std::chrono::high_resolution_clock::time_point time) {
    std::chrono::system_clock::time_point now;
    getTime(now);
    return std::chrono::duration_cast<std::chrono::microseconds>(now-time).count();
}
