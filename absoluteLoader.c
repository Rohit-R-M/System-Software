#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    FILE *file;
    int i, j; 
    int start_addr;
    char name[10];
    char line[50];
    char temp[10];
     int flag=0;
    file = fopen("abc.txt", "r");
    fscanf(file, "%s", line);
    printf("Enter program name: "); //program name is **
    scanf("%s", name);
    for(i=0;i<strlen(name);i++)
    {
		if(line[i+2]==name[i])
		{
			flag=0;
		}
	   else{
		   flag=1;
		   break;
	   }
   }
   if(flag==1)
   {
	   	printf("invalid name");
	   		   
	}
	else
	{
    printf("\nLocation\tObject code\n");
    do
    {
        fscanf(file, "%s", line);
          if (line[0] == 'T')
        {
            for (i = 2, j = 0; i < 8&& j < 6; i++, j++)
                temp[j] = line[i];
            temp[j] = '\0';
            start_addr = atoi(temp);
            i = 12;
            while (line[i] != '$')
            {
                if (line[i] != '^')
                {
                    printf("00%d\t\t%c%c\n", start_addr, line[i], line[i + 1]);
                    start_addr++;
                    i += 2;
                }
                else
                    i++;
            }
        }
        if (line[0] == 'E')
        {
            printf("\nExecution address: ");
            for (i = 2; i < 8; i++)
                printf("%c", line[i]);
            break;
        }
    } while (!feof(file));
}
    fclose(file);
}
