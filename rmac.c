
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<limits.h>

int main(){

    int i,j,k, p_success=0, no_pack,count=0;
    float g_avgload, value[1000000];
    float time, temp, prev=0.0;
    float p_aloha[20],pa_thrput[20];
	
	printf("How many packets you want to transmit\n");
	scanf("%d",&no_pack);


	for(j=0; j<20; j++){

		g_avgload= (j+1)*.10;

		for(i=0;i<no_pack*g_avgload;i++)
		{
	
	 	    temp=randchk()/(float) INT_MAX; // call the randchk(), that will give us the non-zero random value
	
	 	    time=-(1/g_avgload)*logf(temp); 

	 	    value[i]= prev+time;

		    prev=value[i];
		}
		
		
		for(i=1;i<no_pack*g_avgload-1;i++)
		{

	   		 if((value[i] - value[i-1]) >= 1 && (value[i+1] - value[i]) >= 1){

	       			 p_success++;

	    		 }

	   	}

		p_aloha[j]=p_success/(float) no_pack;
 		pa_thrput[j]= (g_avgload)* expf(-2 * g_avgload); //pure aloha throughput calculation
	     
		p_success=0;

	
	}

	//call the function to print the throughputs for different loads.
	pfile(&p_aloha, &pa_thrput);

	
  return 0;
}

//randchk function will return the non-zero random value
int randchk(){

	int temp;

	temp=rand();// call the random function

	if( temp == 0){
	
		randchk();

	}else{
		
		return temp;

	}
}

/************************************************************************************************
 * Printing the throughputs of the pure-aloha for different loads in pure_aloha.m file
 ************************************************************************************************/

int pfile(float *p_aloha, float *pa_thrput){

    int i;
    FILE *fout;


    fout= fopen("pure_aloha.m", "w"); //open the throughput.m file in write mode

    fprintf(fout, "      \n\n");

    fprintf(fout, "xload = [ ");

    for(i=0; i<20; i++){
	
	fprintf(fout, "%f\t", .10*(i+1));
	
    }

    fprintf(fout, "];\n\n");

   //printing the data in matrix format

    fprintf(fout, "ypure = [ ");

    for(i=0; i<20; i++){
	
	fprintf(fout, "%f\t", p_aloha[i]);
	
    }
    fprintf(fout, "];\n\n");


    
    fprintf(fout, "      \n");

    fprintf(fout, "zpure = [ ");

    for(i=0; i<20; i++){
	
	fprintf(fout, "%f\t", pa_thrput[i]);
	
    }

    fprintf(fout, "];\n\n");

    //specifying plot function in output file, so that matlab can generate the graph

    fprintf(fout, "plot(xload, zpure, 'r',xload, ypure, 'b'); \n\n");

    fprintf(fout, "grid on;\ntitle('pure-Aloha simulated and calculated throughput comparison');\n");

    fprintf(fout, "xlabel('G = Offered load');\nylabel('S = Throughput');\n");

    close(fout);// close the file

return 0;
}


