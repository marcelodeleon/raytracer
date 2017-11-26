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

float keep_between_0_and_1(float value)
{
    if(value > 1)
    {
        value = 0.1f;
    }
    else
    {
        if(value < 0)
        {
            value = 0.0f;
        }
    }

    return value;
}
