#include <stdint.h>
//uint32_t k;
uint32_t MASK;
uint32_t VALUE;

struct GPIO{
    uint32_t MODE;
    uint32_t OUTPUT;
    uint32_t INPUT;

};

struct GPIO *GPIO;
uint32_t pin;
void gpio_set_mode(uint32_t pin, uint32_t mode)
{
    int SHIFT = pin * 2;
    MASK  = 3U << SHIFT;
    VALUE = mode << SHIFT;

    GPIO->MODE &= ~MASK;
    GPIO->MODE |= VALUE;
}

void gpio_write(uint32_t pin, uint32_t level){
    MASK = 1U << pin;
    VALUE = level << pin;

    GPIO->OUTPUT &= ~MASK;
    GPIO->OUTPUT |= VALUE;
}
