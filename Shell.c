#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


using namespace std;





//removes white space characters and stores \0
void tokenization(char command[] , char** argv)
{


   	int row= 0;
 
   	int col= 0;
    
  	    	
		
	for( int i = 0 ; command[i]!='\n'; i++)
    	{
		if(!isspace(command[i]))
		{
		    argv[row][col] = command[i]; 
		    
		    col++;
		    
		}
		else
		{
		    
		    argv[row][col] = '\0';
		    col = 0;
		    row++;   

		}
	

       }
       argv[row][col] = '\0';
    

    
}
void execute(char** argv)
{
    int  status;
    pid_t pid = fork();

    if(pid <0)
    {
        cout<<"Error creating child\n";
        exit(1);
    
    }
    else if(pid == 0)
    {
        
        if(execvp(argv[0] , argv) < 0)
        {
                cout<<"Cannot Execute Command\n";
                exit(1);
        }
        

    }
    else if(pid> 0)
    {
    	while (wait(&status) != pid);
    }

}

//counts words in command line
int countWords(char command[])
{
    int totalWords=0;
    
    for( int i = 0 ; i<strlen(command); i++)
    {
	if(isspace(command[i]))
	{
	    totalWords++;
	}
			
		
    }
    return totalWords;
}



int main()
{

    char commandLine[100];
    int totalWords;
    cout<<" WELCOME to Maheen's Shell Program\nTo exit the shell, type exit \n";
	
    char CURR_DIR[40];
    char **argv;
    
    
    
    
    while(1)
    {

        cout<<"Prompt> ";
        if (getcwd(CURR_DIR, sizeof(CURR_DIR)) != NULL)  //getsthe current directory and path of file
        {
            cout<<CURR_DIR<<" ";
        }

   	
        fgets(commandLine,100,stdin);
  
  	totalWords = countWords(commandLine);  //counts total word in command line
        
       
        
	argv = new char*[totalWords+1];    //intialization of argv array
	for (int i = 0 ; i < totalWords; i++)
	{
		argv[i] = new char[50];
	}	
			 
	    
	tokenization(commandLine, argv); //removes whitespaces
	

	    

        if (strcmp(argv[0], "exit") == 0)
        {
                exit(0);   
        }
                
        execute(argv); 
        
   }
   return 0;

}