int duty_cycle_to_bits(int duty_cycle)
{
    if (duty_cycle < 0 || duty_cycle > 100) {
        return -1; // Invalid duty cycle
    }
    return (duty_cycle * 8192) / 100;
}