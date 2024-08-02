#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() 
{
    char label[10], opcode[10], operand[10], code[10], mnemonic[10];
    char symbol[10], address[10];
    int locctr, start, length;
    int textLength = 0;
    char textRecord[70] = "";

    FILE *intermediate, *optab, *symtbl, *output, *len;

    intermediate = fopen("out.txt", "r");
    optab = fopen("optab.txt", "r");
    symtbl = fopen("symtab.txt", "r");
    output = fopen("output.txt", "w");
    len = fopen("length.txt", "r");

    if (intermediate == NULL || optab == NULL || symtbl == NULL || output == NULL || len == NULL)
	{
        perror("Error opening files");
        return 1;
    }

    fscanf(len, "%d", &length);
    fscanf(intermediate, "%X\t%s\t%s\t%s", &locctr, label, opcode, operand);

    if (strcmp(opcode, "START") == 0) 
	{
        start = locctr;
        fprintf(output, "H^%s^%06X^%06X\n", label, start, length);
        fscanf(intermediate, "%X\t%s\t%s\t%s", &locctr, label, opcode, operand);
    }

    int textStart = locctr;

    while (strcmp(opcode, "END") != 0) 
	{
        if (strcmp(opcode, "BYTE") == 0) 
		{
            if (operand[0] == 'C') 
			{
                for (int i = 2; operand[i] != '\''; i++) 
				{
                    char hex[3];
                    sprintf(hex, "%02X", operand[i]);
                    strcat(textRecord, hex);
                    textLength++;
                }
            } 
			else if (operand[0] == 'X') 
			{
                for (int i = 2; operand[i] != '\''; i++) 
				{
                    char hex[2];
                    sprintf(hex, "%c", operand[i]);
                    strcat(textRecord, hex);
                }
                textLength += (strlen(operand) - 3) / 2;
            }
        }
		else if (strcmp(opcode, "WORD") == 0) 
		{
            char temp[7];
            sprintf(temp, "%06X", atoi(operand));
            strcat(textRecord, temp);
            textLength += 3;
        } 
		else if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0) 
		{
            if (textLength > 0) 
			{
                fprintf(output, "T^%06X^%02X^%s\n", textStart, textLength, textRecord);
                textLength = 0;
                textRecord[0] = '\0';
            }
            textStart = locctr + (strcmp(opcode, "RESW") == 0 ? 3 * atoi(operand) : atoi(operand));
        } 
		else 
		{
            rewind(optab);
            fscanf(optab, "%s\t%s", code, mnemonic);
            while (strcmp(code, "END") != 0) 
			{
                if (strcmp(opcode, code) == 0) 
				{
                    strcat(textRecord, mnemonic);
                    textLength += 3;

                    rewind(symtbl);
                    fscanf(symtbl, "%s\t%s", symbol, address);
                    while (strcmp(symbol, operand) != 0 && !feof(symtbl)) 
					{
                        fscanf(symtbl, "%s\t%s", symbol, address);
                    }
                    if (strcmp(symbol, operand) == 0) 
					{
                        strcat(textRecord, address);
                    } else 
					{
                        strcat(textRecord, "0000");
                    }
                    break;
                }
                fscanf(optab, "%s\t%s", code, mnemonic);
            }
        }

        fscanf(intermediate, "%X\t%s\t%s\t%s", &locctr, label, opcode, operand);

        if (textLength >= 30) 
		{
            fprintf(output, "T^%06X^%02X^%s\n", textStart, textLength, textRecord);
            textLength = 0;
            textRecord[0] = '\0';
            textStart = locctr;
        }
    } 
    if (textLength > 0) 
	{
        fprintf(output, "T^%06X^%02X^%s\n", textStart, textLength, textRecord);
    }
    fprintf(output, "E^%06X\n", start);

    fclose(intermediate);
    fclose(optab);
    fclose(symtbl);
    fclose(output);
    fclose(len);

    printf("Pass 2 Assembler: Object code generated in output.txt\n");
    return 0;
}

