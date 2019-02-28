#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main()
{

	  char size[64];
	  char param[1024];
	  if(getenv("CONTENT-LENGTH"))
	  {
		    strcpy(size,getenv("CONTENT-LENGTH"));
		    int cl=atoi(size);
		    int i=0;
		    for(;i<cl;i++)
		    {
			      read(0,param+i,1);
		    }

		    param[i]=0;
		    int a,b;
		    sscanf(param,"a=%d&b=%d",&a,&b);


		    printf("<html>\n");
		    printf("<h4>%d + %d = %d</h4>",a,b,a+b);
		    printf("<h4>%d - %d = %d</h4>",a,b,a-b);
		    printf("<h4>%d * %d = %d</h4>",a,b,a*b);
		    printf("<h4>%d / %d = %d</h4>",a,b,a/b);
		    printf("</html>\n");
	  }
}

