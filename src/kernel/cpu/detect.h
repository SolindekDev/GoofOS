#ifndef DETECT_H
    #define DETECT_H 0x1

    #define AMD     0x1
    #define INTEL   0x2
    #define OTHER   0x3

    int detect_cpu_type();
#endif