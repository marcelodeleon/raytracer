int keep_in_range(int min, int max, int value)
{
    if(value > max)
    {
        value = max;
    }
    else
    {
        if(value < min)
        {
            value = min;
        }
    }

    return value;
}
