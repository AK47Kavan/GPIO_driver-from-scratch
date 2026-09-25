#include <stdint.h>
//uint32_t k;
#define GPIO_INPUT     0U
#define GPIO_OUTPUT    1U
#define GPIO_ALTERNATE 2U
#define GPIO_ANALOG    3U

struct GPIO{
    uint32_t MODE;
    uint32_t OUTPUT;
    uint32_t INPUT;

};

struct GPIO *GPIO;
uint32_t pin;
void gpio_set_mode(uint32_t pin, uint32_t mode)
{
    uint32_t MASK;
    uint32_t VALUE;
    uint32_t SHIFT = pin * 2U;// so pin 0 means 0 then pin 1 means 2 shift and so on
    MASK  = 3U << SHIFT;// this will shift that
    VALUE = mode << SHIFT;//thiswill shift mode to that position for the value

    GPIO->MODE &= ~MASK;// we make it zero for that particular position
    GPIO->MODE |= VALUE;// then we write the mode
}

void gpio_write(uint32_t pin, uint32_t level){
if (level == GPIO_HIGH)
    GPIO->OUTPUT |= (1U << pin);
else
    GPIO->OUTPUT &= ~(1U << pin);
}
