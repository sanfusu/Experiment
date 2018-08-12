/**
 * @author sanfusu@foxmail.com 
 */
#include "crc.h"
#include <stdint.h>
#include <stdio.h>

void crc_tab_gen(uint32_t *table, uint32_t poly)
{
    uint32_t reg = 0;
    for (int i = 0; i <= 255; i++)
    {
        reg = i << 24;
        for (int j = 0; j <= 7; j++)
        {
            if (reg >> 31)
            {
                reg = (reg << 1) ^ poly;
            }
            else
            {
                reg <<= 1;
            }
        }
        table[i] = reg;
    }
}

uint32_t crc_cal(uint8_t *data, uint32_t len, uint32_t poly)
{
    uint32_t table[256];
    uint32_t reg;
    crc_tab_gen(table, poly);
    for (int i = 0; i < len; i++)
    {
        reg = (reg << 8) ^ table[(reg >> 24) ^ *data++];
    }
    return reg;
}

int main()
{
    uint32_t poly = 0x4C11DB7;
    uint32_t table[256] = {0};
    crc_tab_gen(table, poly);
    FILE *file = fopen("./crc_table.c", "w+");
    fputs("#include <stdint.h>\n", file);
    fputs("const uint32_t crc_table[256] = {\n", file);
    for (int i = 0; i < 256; i++)
    {
        fprintf(file, "\t%#.8x,", table[i]);
        fprintf(file, "\t%#.8x,", table[++i]);
        fprintf(file, "\t%#.8x,", table[++i]);
        fprintf(file, "\t%#.8x,\n", table[++i]);
    }
    fputs("};\n\n", file);
    fputs("uint32_t crc_cal(uint8_t *data, uint32_t len, uint32_t poly)\n"
        "{\n"
        "\tuint32_t table[256];\n"
        "\tuint32_t reg;\n"
        "\tcrc_tab_gen(table, poly);\n"
        "\tfor (int i = 0; i < len; i++)\n"
        "\t{\n"
        "\t\treg = (reg << 8) ^ table[(reg >> 24) ^ *data++];\n"
        "\t}\n"
        "\treturn reg;\n"
        "}\n", file);
    fclose(file);
}