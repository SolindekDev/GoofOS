#ifndef TIMER_H
    #define TIMER_H 0x1
    void init_timer(unsigned int freq);
    static void timer_callback(registers_t regs);
#endif