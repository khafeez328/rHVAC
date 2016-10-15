#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <math.h>

//global variables

double k_values[4][10];
double p_kValues[10];
void init()
{
// 

}
void TempReadings()
{
	int clientSocket;
  char buffer[1024];
 // char buffer1[1024];
   struct sockaddr_in serverAddr;
  socklen_t addr_size;
  double count=100;
  int i=0;
  int t1=0;
  int t2=0;
  int min_after;
  int min_before;
  int diff=0;
  FILE *fpin;
  FILE *fpout;
  
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime(&rawtime);
 
  fpin = fopen("tempin.txt", "w+");
  fpout= fopen("tempout.txt", "w+");
  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(9002);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  /*---- Read the message from the server into the buffer ----*/
  recv(clientSocket, buffer, 1024, 0);
  send(clientSocket,buffer,13,0);
 

  /*---- Print the received message ----*/
  //recv(clientSocket, buffer, 1024, 0);
 // printf("Data received: %s",buffer); 
	fprintf(fpin,"#Time: %s \n", asctime(timeinfo) ); 
	fprintf(fpout,"#Time: %s \n", asctime(timeinfo) ); 
	//int hour=tm_hour;
	
	
	
	printf("Time: %s \n", asctime(timeinfo) ); 

  for (i = 0; i < count; i++)
   {
	   
	   recv(clientSocket, buffer, 1024, 0);
	
	   int node =buffer[4];
	
	  printf("NODE  Temp. Count\n");
	   printf("%d 	%d  %f  \n",buffer[4],buffer[13],count);
	   min_before=timeinfo->tm_min;
	  
	   if(node==1)
	   {

		   fprintf(fpin, "%d 	%d 	%d 	%d\n",timeinfo->tm_min,t1,buffer[11],buffer[13]);
		   printf(" in condition node 1 %d %d\n",buffer[4],buffer[13]);
		   if(timeinfo->tm_min != min_before)
		   t1++;
		 }
	   if(node==2)
	   {
		   fprintf(fpout, "%d	%d	%d\n",t2,buffer[11],buffer[13]);
		   printf("in condition node 2 %d %d\n",buffer[4],buffer[13]);
		   t2++;
		 }
		 printf("Data received 1: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n",
      	 buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7],buffer[8],buffer[9],buffer[10],
     	 buffer[11],buffer[12],buffer[13],buffer[14],buffer[15],buffer[16],buffer[17],buffer[18]);
      
   
      
      time (&rawtime);
      timeinfo = localtime(&rawtime);
      
      
      
     
   } 
   fprintf(fpin,"#Time: %s \n", asctime(timeinfo) ); 
   fprintf(fpout,"#Time: %s \n", asctime(timeinfo) ); 
   fclose(fpin);
   fclose(fpout);

}
double curr_Temp()
{
	int clientSocket;
  char buffer[1024];
 // char buffer1[1024];
   struct sockaddr_in serverAddr;
  socklen_t addr_size;
  
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime(&rawtime);
 
  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(9002);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  /*---- Read the message from the server into the buffer ----*/
  recv(clientSocket, buffer, 1024, 0);
  send(clientSocket,buffer,13,0);
 

  /*---- Print the received message ----*/
  //recv(clientSocket, buffer, 1024, 0);
 // printf("Data received: %s",buffer); 
	fprintf(fpin,"#Time: %s \n", asctime(timeinfo) ); 
	fprintf(fpout,"#Time: %s \n", asctime(timeinfo) ); 
	//int hour=tm_hour;
	
	
	
	printf("Time: %s \n", asctime(timeinfo) ); 

  
	   
	recv(clientSocket, buffer, 1024, 0);
	
	  
	  
	  
	  

		   
	printf(" node 	Humidity	 Temprature %d %d %d\n",buffer[4],buffer[13],buffer[11]);
	printf("%d 	%d 	 %d\n",buffer[4],buffer[13],buffer[11]);
	printf("Data received 1: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n",
      	 buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7],buffer[8],buffer[9],buffer[10],
     	 buffer[11],buffer[12],buffer[13],buffer[14],buffer[15],buffer[16],buffer[17],buffer[18]);
      
   
  double cur_temp=double(buffer[11]);   
  return cur_temp;
}

double calculate_kvalue(double t0 , double t1, double t_out, double time_t1)
{
	// t0 is init temperature 
	// t1 is tempratue at after time_t1 minutes
	// t2_out is outside temperature
	// time_t2 is minutes after which the tempratue 
	double k=0;
	//double t_inst = t_out + (t0 -t_out)e^kt;
	double temp_diff = t0 - t_out;
	printf("Temp diff = %f\n", temp_diff ); 
	double t3 = (t1 - t_out)/temp_diff;
	 printf("ooo  = %f\n", t3); 
	double t4 = log(t3);
	 printf("log of ooo = %f\n", t4 ); 
	k = t4/time_t1;
	return k;
}
double Predicted_Temp (double t0 , double t1, double t_out, double time_t1, double time_t2)
{
	// t0 is init temperature 
	// t1 is tempratue at after time_t1 minutes
	// t2_out is outside temperature
	// time_t2 is minutes after which the tempratue 
	double k=0;
	//double t_inst = t_out + (t0 -t_out)e^kt;
	double temp_diff = t0 - t_out;
	printf("Temp diff = %f\n", temp_diff ); 
	double t3 = (t1 - t_out)/temp_diff;
	 printf("ooo  = %f\n", t3); 
	double t4 = log(t3);
	 printf("log of ooo = %f\n", t4 ); 
	k = t4/time_t1;
	 printf("log / time  which is k = %f\n", k );

	double p_temp=t_out + (temp_diff * exp(k * time_t2));
	 
	return p_temp;
}
void Switching(int AC,int fan, int Ex_out,int Ex_in, int AC_state, int fan_state, int Ex_out_state,int Ex_in_state )
{

}
void rHVAC ()
{
//Check temp
// if it is in comfort zone
   // check predicted temp. 
	  //if the predicted temp is in of comfort zone
		

}
int main(){
	//TempReadings();

 double k = Predicted_Temp(27,34,37,15,30);
 printf("Predicted Temprature value = %f\n", k );  
 
  return 0;
}
