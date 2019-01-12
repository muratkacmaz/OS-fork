// Murat Kaçmaz
// 150140052

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
// parenta 1 dedim. cocuklarının numaralandırmaları da 1.1, 1.2, 1.1.1 vs seklinde.

int main (int argc, char ** argv )
{
	pid_t  f1,f2,f1_1,f2_1,f2_2,f2_1_1;
	
	f1 = fork();
	if (f1 == 0) // in first child 1.1
	{	 f1_1 = fork();  
		if(f1_1 == 0)// first grand child   1.1.1
		{
			
			printf("First Grand Child PID (1.1.1): %d \n", getpid());
			printf("Hierarchy : 3 \n\n\n\n");
		}
		else if (f1_1>0)    //1.1
		{	
			printf("\tFirst Child PID (1.1): %d \n", getpid());
			printf("\tFirst Child's first child (1.1.1): %d \n", f1_1 );
			printf("\tHierarchy : 2 \n\n\n\n");
		}
		else { perror ("Fork not working \n");}
		
	}
	
	else  // in parent 1
	{	
		f2 = fork();
		if(f2==0) //in second child 1.2
		{	f2_1 = fork();  
			if(f2_1 == 0 ) //in  grand child 1.2.1
			{		
				f2_1_1 = fork();
				if(f2_1_1 == 0 ) { // grand grand child  1.2.1.1
				
					printf("\tS_G_G_C PID (1.2.1.1): %d \n", getpid());
					printf("\tHierarchy : 4 \n\n\n\n");
				}
				else if (f2_1_1>0){ // second childs first child  1.2.1

					printf("\t\tS_G_C PID (1.2.1): %d \n", getpid());
					printf("\t\tG_G_C (1.2.1.1): %d \n",f2_1_1);
					printf("\t\tHierarchy : 3 \n\n\n\n");
				}
				else { perror ("Fork not working \n");}
								
			}	
			else if (f2_1>0)
			{	
				f2_2 = fork();
				if(f2_2 == 0 ){ // 2.2 child     1.2.2
					printf("\t\t\t\tS_G_C_2 PID (1.2.2): %d \n", getpid());	
					printf("\t\t\t\tHierarchy : 3 \n\n\n\n");
				}
				else if (f2_2 > 0 ) { // second child   1.2
					printf("\t\t\tSecond Child PID (1.2): %d \n", getpid());
					printf("\t\t\t2nd Child's 1st child (1.2.1): %d \n",f2_1);
					printf("\t\t\t2nd Child's 2nd child (1.2.2): %d \n",f2_2);
					printf("\t\t\tHierarchy : 2 \n\n\n\n");
						
				}
				else { perror ("Fork not working \n");}

						
			}
			else { perror ("Fork not working \n");}

			
		}
		else if (f2 < 0 )
		{ perror ("Fork not working \n");}

		else    // root 1
		{	
			
			printf("\t\tRoot's PID (1): %d \n", getpid());
			printf ("\t\tFirst child  of Root (1.1): %d \n",f1 );
			printf ("\t\tSecond child of Root (1.2): %d \n",f2);
			printf("\t\tHierarchy : 1 \n\n\n\n");
			wait(NULL);
		}
	}
	return 0 ;
}
