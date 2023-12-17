
#ifndef __HEADER_GPIO__
#define __HEADER_GPIO__

#define GPIO0   0
#define GPIO1   1
#define GPIO2   2
#define GPIO3   3
#define GPIO4   4
#define GPIO5   5
#define GPIO6   6
#define GPIO7   7
#define GPIO8   8
#define GPIO9   9
#define GPIO10  10
#define GPIO11  11
#define GPIO12  12
#define GPIO13  13
#define GPIO14  14
#define GPIO15  15
#define GPIO16  16
#define GPIO17  17
#define GPIO18  18  // <--
#define GPIO19  19  // <--
#define GPIO21  21  // <--
#define GPIO22  22  // <--
#define GPIO23  23  // <--
#define GPIO25  25
#define GPIO26  26
#define GPIO27  27
#define GPIO32  32
#define GPIO33  33
#define GPIO34  34
#define GPIO35  35
#define GPIO36  36
#define GPIO37  37
#define GPIO39  39

#define OUTPUT  0
#define INPUT   1

#define LOW     0
#define HIGH    1

void gpio_set_mode(int gpio_pin, int mode);     // (GPIO<N>, [INPUT|OUTPUT])
// void gpio_set_state(int gpio_pin, int state);   // (GPIO<N>, [HIGH|LOW])

#endif // __HEADER_GPIO__

