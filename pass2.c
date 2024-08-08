#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main() 
{
    char label[10], opcode[10], operand[10], symbol[10], code[10], mnemonic[10];
    int locctr, start, length, address;
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;
    fp1 = fopen("intermediate.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtbl.txt", "r");
    fp4 = fopen("output1.txt", "w");
    fp5 = fopen("length.txt", "r");
    fscanf(fp5, "%d", &length);
    fclose(fp5);
    fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    if(strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fp4, "H^%s^%06d^%06d\n", label, start, length);
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }
    fprintf(fp4, "T^%06d^", locctr);
    while(strcmp(opcode, "END") != 0) {
        if(strcmp(opcode, "BYTE") == 0 || strcmp(opcode, "WORD") == 0) {
            if(strcmp(opcode, "BYTE") == 0) {
                fprintf(fp4, "^%s", operand);
            } else {
                fprintf(fp4, "^%06d", atoi(operand));
            }
        } else {
            rewind(fp2);
            fscanf(fp2, "%s\t%s", code, mnemonic);
            while(strcmp(code, "END") != 0) {
                if(strcmp(opcode, code) == 0) {
                    rewind(fp3);
                    fscanf(fp3, "%s\t%d", symbol, &address);
                    while(strcmp(symbol, operand) != 0) {
                        fscanf(fp3, "%s\t%d", symbol, &address);
                    }
                    fprintf(fp4, "^%s%06d", mnemonic, address);
                    break;
                }
                fscanf(fp2, "%s\t%s", code, mnemonic);
            }
        }
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }

    fprintf(fp4, "\nE^%06d\n", start);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    return 0;
}
