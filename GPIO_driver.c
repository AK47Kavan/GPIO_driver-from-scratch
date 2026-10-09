#include <stdint.h>
//uint32_t k;
#define GPIO_INPUT     0U
#define GPIO_OUTPUT    1U
#define GPIO_ALTERNATE 2U
#define GPIO_ANALOG    3U
#define GPIO_PIN_COUNT 16U
#define GPIO_HIGH     1U
#define GPIO_LOW      0U
#define GPIO_INVALID  4U

struct GPIO{
    uint32_t MODE;
    uint32_t OUTPUT;
    uint32_t INPUT;

};

volatile struct GPIO *GPIO =
    (volatile struct GPIO *)0x50000000U;

uint32_t pin;

void gpio_init(void){
    GPIO->MODE = 0x00000000;
    GPIO->OUTPUT = 0x00000000;
}

int  gpio_set_mode(uint32_t pin, uint32_t mode)
{
    if(pin<GPIO_PIN_COUNT && mode<=GPIO_ANALOG){
    uint32_t MASK;
    uint32_t VALUE;
    uint32_t SHIFT = pin * 2U;// so pin 0 means 0 then pin 1 means 2 shift and so on
    MASK  = 3U << SHIFT;// this will shift that
    VALUE = mode << SHIFT;//this will shift mode to that position for the value

    GPIO->MODE &= ~MASK;// we make it zero for that particular position
    GPIO->MODE |= VALUE;// then we write the mode
    return 1;
    }
    return 0;
}

int  gpio_write(uint32_t pin, uint32_t level){
    uint32_t MASK = 3U<<(pin*2U);
    uint32_t mode = (GPIO->MODE & MASK) >> (pin * 2U);// get the mode for that pin
    if(pin<GPIO_PIN_COUNT){
        if(mode==GPIO_OUTPUT){
        if (level == GPIO_HIGH){
            GPIO->OUTPUT |= (1U << pin);
        return 1;
        }
        else if(level == GPIO_LOW){
            GPIO->OUTPUT &= ~(1U << pin);
            return 1;
        }
        else{
            return 0;
        }
        }
    }
    return 0;
}


int gpio_read(uint32_t pin){
    if(pin<GPIO_PIN_COUNT){
        //uint32_t value = GPIO->INPUT;
        uint32_t SHIFT = pin * 2U;
        uint32_t MASK = 3U << SHIFT;
        uint32_t value = (GPIO->MODE & MASK) >> SHIFT;
        if(value==GPIO_INPUT){
        if(GPIO->INPUT&(1U << pin)){
            return GPIO_HIGH;
        }
            else{
                return GPIO_LOW;
            }
        }
        else{
            return GPIO_INVALID;
        }
        return GPIO_INVALID
    }

int gpio_toggle(uint32_t pin){
        if(pin<GPIO_PIN_COUNT){
            uint32_t SHIFT = pin * 2U;
            uint32_t MASK = 3U << SHIFT;
            uint32_t value = (GPIO->MODE & MASK) >> SHIFT;
    if(value==GPIO_OUTPUT){
        if(GPIO->OUTPUT & (1U << pin)){
            GPIO->OUTPUT &=~(1U<<pin);
        }
        else{
            GPIO->OUTPUT |= (1U<<pin);
        }
        return 1;
    }
    }
    return 0;
}

int gpio_enable_interrupt(uint32_t pin){
    if(pin<GPIO_PIN_COUNT){
        GPIO->INT_ENABLE |= (1U << pin);
        GPIO->INT_RISING |= (1U << pin);
        return 1;
    }
    return 0;
}
volatile uint32_t button_events = 0;

void gpio_isr(void){
    uint16_t pending;
    pending = GPIO->INT_STATUS;
    for(int i = 0; i < GPIO_PIN_COUNT; i++)
    {
        if(pending & (1U << i))
        {
            // handle pending pin
            GPIO->INT_STATUS = (1U << i);
            button_events++;
        }
    }
}
