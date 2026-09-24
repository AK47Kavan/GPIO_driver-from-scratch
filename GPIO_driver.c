void gpio_set_mode(uint32_t pin, uint32_t mode)
{
    SHIFT = pin * 2;
    MASK  = 3U << SHIFT;
    VALUE = mode << SHIFT;

    GPIO->MODE &= ~MASK;
    GPIO->MODE |= VALUE;
}
