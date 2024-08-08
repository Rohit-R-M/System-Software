#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
 {
    FILE *intermediate_fp, *symtab_fp, *output_fp, *objcode_fp;
    char label[10], opcode[10], operand[10], mnemonic[20][20] = {"LDA", "STA", "LDCH", "STCH", "MUL"};
    char code[20][20] = {"33", "44", "53", "57", "20"};
    int address, start, finaddr, prevaddr, diff;

    intermediate_fp = fopen("out.txt", "r");
    symtab_fp = fopen("symtbl.txt", "r");
    output_fp = fopen("output.txt", "w");
    objcode_fp = fopen("objcode.txt", "w");

    fscanf(intermediate_fp, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) 
	{
        fprintf(output_fp, "\t%s\t%s\t%s\n", label, opcode, operand);
        fprintf(objcode_fp, "H^%s^00%s^00%d\n", label, operand, finaddr);
        fscanf(intermediate_fp, "%d %s %s %s", &address, label, opcode, operand);
        start = address;
        diff = prevaddr - start;
        fprintf(objcode_fp, "T^00%d^%d", address, diff);
    }

    while (strcmp(opcode, "END") != 0) 
	{
        if (strcmp(opcode, "BYTE") == 0) 
		{
            fprintf(output_fp, "%d\t%s\t%s\t%s\t", address, label, opcode, operand);
            int len = strlen(operand);
            int actual_len = len - 3;
            fprintf(objcode_fp, "^");
            for (int i = 2; i < (actual_len + 2); i++) 
			{
                fprintf(output_fp, "%c", operand[i]);
                fprintf(objcode_fp, "%c", operand[i]);
            }
            fprintf(output_fp, "\n");
        } 
		else if (strcmp(opcode, "WORD") == 0) 
		{
            int value = atoi(operand);
            fprintf(output_fp, "%d\t%s\t%s\t%s\t00000%d\n", address, label, opcode, operand, value);
            fprintf(objcode_fp, "^00000%d", value);
        } 
		else if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, "RESW") == 0)
		{
            fprintf(output_fp, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);
        } else 
		{
            int j = 0;
            while (strcmp(opcode, mnemonic[j]) != 0 && j < 5) 
			{
                j++;
            }
            if (j < 5) 
			{
                if (strcmp(operand, "COPY") == 0) 
				{
                    fprintf(output_fp, "%d\t%s\t%s\t%s\t%s0000\n", address, label, opcode, operand, code[j]);
                } 
				else 
				{
                    char symbol[10];
                    int add;
                    rewind(symtab_fp);
                    while (fscanf(symtab_fp, "%s %d", symbol, &add) != EOF && strcmp(operand, symbol) != 0);
                    fprintf(output_fp, "%d\t%s\t%s\t%s\t%s%d\n", address, label, opcode, operand, code[j], add);
                    fprintf(objcode_fp, "^%s%d", code[j], add);
                }
            }
        }
        prevaddr = address;
        fscanf(intermediate_fp, "%d %s %s %s", &address, label, opcode, operand);
    }

    fprintf(output_fp, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);
    fprintf(objcode_fp, "\nE^00%d", start);

    fclose(objcode_fp);
    fclose(output_fp);
    fclose(symtab_fp);
    fclose(intermediate_fp);

    return 0;
}