#include <stdio.h>
#include<string.h>
int* decToBin(int decNumber);
void main(void) {
	FILE *finp,*fout,*fopcode,*freg,*fhex,*fh, *flout, *flin;
	char inp[17], op[17], ch, a[10],lbl[17],b[10];
	int o,r,h,i,l, count=0,lineno=0,count1=0,label=0;
	finp = fopen("Input.txt", "r");
	fout = fopen("Output.txt", "w");
	flout = fopen("Label.txt", "w");
	fopcode = fopen("opcodes.txt", "r");
	freg = fopen("register.txt", "r");
	fhex = fopen("hex2bin.txt", "r");
	if((!finp)||(!fout)||(!fopcode)||(!freg)||(!fhex)) return;
    int *p;
	fscanf(finp,"%s",a);
    while(!feof(finp))
    {
        if(strchr(a,':')!=NULL)
        {
            count1++;
            label=strlen(a);


            p=decToBin(count1);

            int counter = 0;
            fprintf(flout,"%s ",a);

            while(counter<7)
            {
                fprintf(flout,"%d",*(p+counter));
                counter++;
            }
            fprintf(flout,"\n");

            a[label-1]='\0';
            fprintf(flout,"%s ",a);
            p=decToBin(count1);
            counter = 0;
            while(counter<7)
            {
                fprintf(flout,"%d",*(p+counter));
                counter++;
            }
            fprintf(flout,"\n");
        }
        fscanf(finp,"%s",a);
    }
    fprintf(flout,"XX");
    fclose(flout);
    fclose(finp);
    finp = fopen("Input.txt", "r");
    flin = fopen("Label.txt", "r");
	while(!feof(finp))
    {
		rewind(fopcode);
		rewind(freg);
		rewind(fhex);
		rewind(flin);
		fscanf(finp,"%s",inp);

		if(strcasecmp(inp,"HLT")==0)
		{
		    fprintf(fout,"\n1111111111110001");
			break;
		}

		printf("%s\n",inp);

        //label
        while(1)
        {
			fscanf(flin,"%s",lbl);
			//printf("lablel scanned = %s ", lbl);
			if(strcasecmp(lbl,"XX")==0)
			{
				break;
			}
			//printf("here");
			if(strcasecmp(inp,lbl)==0) {
                //printf("match");
				fscanf(flin,"%s",lbl);
				fprintf(fout,"\n%s",lbl);
				l=1; break;
			} else {
				fscanf(flin,"%s",lbl);
				l=0;
			}
		}

        //opcode
		while(1) {
			fscanf(fopcode,"%s",op);
			if(strcasecmp(op,"XX")==0)
			{
				break;
			}
			if(strcasecmp(inp,op)==0) {
				fscanf(fopcode,"%s",op);
				fprintf(fout,"\n%s",op);
				o=1; break;
			} else {
				fscanf(fopcode,"%s",op);
				o=0;
			}
		}
		if(o==1)
			lineno++;

        /*
		int len=strlen(inp);
		if( inp[len-1] == ':' )
		{
			o=1;
			fprintf(fout,"\n1111111111111001");
		}

		*/

        //register
		while(1) {
			fscanf(freg,"%s",op);
			if(strcasecmp(op,"XX")==0)
			{
				break;
			}
			if(strcasecmp(inp,op)==0) {
				fscanf(freg,"%s",op);
				fprintf(fout," %s",op);
				r=1; break;
			} else {
				fscanf(freg,"%s",op);
				r=0;
			}
		}

        //hextobinary
		while(1)
        {
			fscanf(fhex,"%s",op);
			if(strcasecmp(op,"XX")==0)
			{
				break;
			}
			if(strcasecmp(inp,op)==0) {
				fscanf(fhex,"%s",op);
				fprintf(fout," %s",op);
				h=1; break;
			} else {
				fscanf(fhex,"%s",op);
				h=0;
			}
		}

		if(!o && !r && !h && !l) {
			lineno++;
			printf("\n'%s' is an Invalid Instruction/Register/Value at line %d",inp,lineno);
			fprintf(fout," '%s",inp);
			count++;
			printf("\n\nPress\n1 for help\n2 for continue\n3 for exit");
			scanf("%d",&i);
			if(i==1)
			{

				fh=fopen("help.txt", "r");
				while(1)
   				{
     					ch = fgetc(fh);
      					if( feof(fh) )
      					{
          					break ;
      					}
      					printf("%c", ch);
   				}
				fclose(fh);
			}
			else if(i==2)
				continue;
			else
				break;
		}
}
	fclose(finp);
	fclose(fout);
	fclose(fopcode);
	fclose(flin);
	fclose(freg);
	fclose(fhex);
	printf("\nTask Successfully done! and Total Number of errors = %d\n\n",count);
    return;
}

int* decToBin(int decNumber)
{
    int quo;
    int i, j;
    int* binNumber;
    binNumber=(int*)malloc(7*sizeof(int));
    for(i=0; i<7; i++)
    {
        binNumber[i]=0;
    }
    i=6;
    quo = decNumber;
    while(quo!=0)
    {
         binNumber[i--]= quo % 2;
         quo = quo / 2;
    }
    printf("Equivalent binary value of decimal number %d: ",decNumber);
    for(j=0;j<7;j++)
    {
        printf("%d", binNumber[j]);
    }
    printf("\n");
    return binNumber;
}
