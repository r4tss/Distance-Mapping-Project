#include <stdio.h>
#include <math.h>

int main()
{
    int points_n = 0;
    FILE *f;
    f = fopen("./measurements.dmap", "r");
    char measurement[64];

    fgets(measurement, 64, f);
    int ch = getc(f) - 48, n = 0, i = 0;
    for(n = 0;n < 2;n++)
    {
        if(ch <= 9 && ch >= 0)
            points_n += (ch * (int)pow(10, 1-n));
        ch = getc(f) - 48;
    }

    double angles[points_n], distances[points_n];
    int read_angle = 1;

    n = 0;
    while(ch != EOF)
    {
        if(ch == '\n')
        {
            read_angle = 0;
            i = 0;
        }
        else if(ch == ' ')
        {
            i++;
            n = 0;
            printf("\n");
        }
        else
            ch -= 48;

        if(ch <= 9 && ch >= 0)
        {
            if(read_angle == 1)
            {
                angles[i] += ch * pow(10, 2-n);
                n++;
            }
            else
            {
                distances[i] += ch * pow(10, 1-n);
                n++;
            }
        }
        ch = getc(f);
    }
    fclose(f);
    return 0;
}
