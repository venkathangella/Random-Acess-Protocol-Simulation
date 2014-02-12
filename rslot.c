/* Author: venkat thangella
*  Date  : 28/01/2014
*  Modified :  29/01/2014
*  Funcionality : To calculate the throughput for the slotted aloha protocol
*		  through simulation technique.
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<limits.h>

int main(){

    int i,j,slo_success=0, no_pack,count=0;
    float g_avgload, value[1000000];
    float time, temp, prev=0.0;
    float slo_aloha[20],sa_thrput[20];
	

	printf("How many packets you want to transmit\n");
	scanf("%d",&no_pack);

	for(j=0; j<20; j++){

		g_avgload= (j+1)*.10;

		for(i=0;i<no_pack*g_avgload;i++)
		{
	
	 	    temp=randchk()/(float) INT_MAX; // call the randchk(), that will give us the non-zero random value
	
	 	    time=-(1/g_avgload)*logf(temp); 

	 	    value[i]= ceil(prev+time);

		    prev=prev+time;
		}

		for(i=1;i<no_pack*g_avgload;i++){

			if((value[i] - value[i-1]) >= 1 ){

			   if(value[i] != value[i+1]){

			 	slo_success++;
					
			}
		      }
	   	}

		slo_aloha[j]= slo_success/(float) no_pack; // through simulation

		sa_thrput[j]= (g_avgload)* expf(-g_avgload);  ///slotted aloha throughput calculation

		slo_success=0;
	
	}

	//call the function to print the throughputs for different loads.
	pfile(&sa_thrput, &slo_aloha);
	

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
 * Printing the throughputs of the slotted aloha to slotted_aloha.m file
 ************************************************************************************************/

int pfile(float *sa_thrput, float *slo_aloha){

    int i;
    FILE *fout;

    fout= fopen("slotted_aloha.m", "w"); //open the slotted_aloha.m file in write mode

    fprintf(fout, "      \n\n");

    fprintf(fout, "xload = [ ");

    for(i=0; i<20; i++){
	
	fprintf(fout, "%f\t", .10*(i+1));
	
    }

    fprintf(fout, "];\n\n");

   //printing the data in matrix format

    fprintf(fout, "yslotted = [ ");

    for(i=0; i<20; i++){
	
	fprintf(fout, "%f\t", sa_thrput[i]);
	
    }
    fprintf(fout, "];\n\n");


    
    fprintf(fout, "      \n");

    fprintf(fout, "zslotted = [ ");

    for(i=0; i<20; i++){
	
	fprintf(fout, "%f\t", slo_aloha[i]);
	
    }

    fprintf(fout, "];\n\n");

    //specifying plot function in output file, so that matlab can generate the graph

    fprintf(fout, "plot(xload, zslotted, 'r',xload, yslotted, 'b'); \n\n");

    fprintf(fout, "grid on;\ntitle('Slotted-Aloha simulated and calculated Throughput comparison');\n");

    fprintf(fout, "xlabel('G = Offered load');\nylabel('S = Throughput');\n");

    close(fout);// close the file

return 0;
}


