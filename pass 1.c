#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main() 
{
    char opcode[10], operand[10], label[10], code[10], mnemonic[10];
    int locctr, start, length;

    FILE *fp1, *fp2, *fp3, *fp4,*fp5;

    fp1 = fopen("input11.txt", "r");
    fp2 = fopen("optab11.txt", "r");
    fp3 = fopen("symtble11.txt", "w");
    fp4 = fopen("out11.txt", "w");
    fp5=fopen("len11.txt","w");
    fscanf(fp1, "%s\t%s\t%x", label, opcode, &start);

    if(strcmp(opcode, "START")==0) 
	{
        //start = atoi(operand);
        locctr = start;
        fprintf(fp4, "%X\t%s\t%s\t%x\n",start, label, opcode, start);
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }
    else 
	{
        locctr = 0;
    }
    
    while(strcmp(opcode, "END")!=0) 
	{
        fprintf(fp4, "%X\t", locctr);

        if(strcmp(label, "**")!=0) 
		{
            fprintf(fp3, "%s\t%x\n", label, locctr);
        }

        fscanf(fp2, "%s\t%s", code, mnemonic);

        while(strcmp(code, "END")!=0) 
		{
            if(strcmp(opcode, code)==0) 
			{
                locctr+=3;
                break;
            }
            fscanf(fp2, "%s\t%s", code, mnemonic);
        }

        if(strcmp(opcode, "WORD")==0)
		{
            locctr+=3;
        }
        else if(strcmp(opcode, "RESW")==0) 
		{
            locctr+=(3*(atoi(operand)));
        }
        else if(strcmp(opcode, "RESB")==0) 
		{
            locctr+=(atoi(operand));
        }
        else if(strcmp(opcode, "BYTE")==0) 
		{
            if(operand[0] == 'X' || operand[0] == 'x') 
			{
        		locctr += (strlen(operand) - 3) / 2;
    		} 
			else if(operand[0] == 'C' || operand[0] == 'c') 
			{
        		locctr += strlen(operand) - 3; 
    		}
        }

        fprintf(fp4, "%s\t%s\t%s\t\n", label, opcode, operand);
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
        rewind(fp2);
    }

    fprintf(fp4, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    
    length = locctr-start;
    fprintf(fp5,"%d",length);
    printf("The length of the code : %d\n", length);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    return 0;
}
