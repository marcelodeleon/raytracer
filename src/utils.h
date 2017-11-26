/*
 * Se asegura que el valor siempre se encuentre dentro del intervalo [min, max] especificado.
 * En caso de que no sea así, el valor se trunca al extremo más cercano.
 */
int keep_in_range(int min, int max, int value);

/*
 * Se asegura que el valor siempre se encuentre en el intervalo [0, 1].
 * En caso de que no sea así, el valor se trunca al extremo más cercano.
 */
float keep_between_0_and_1(float value);
