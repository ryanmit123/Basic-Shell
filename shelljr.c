/* Ryan Mitchell
   UID: rymit9
   ID: 118522210 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sysexits.h>
#include <string.h> 

int main(){
  
  char input[1024] = "", line[1024] = "", arg[1024] = "", *argv[3];
  char stack[16][1024];
  int stack_cnt = 0, count = 0;
  pid_t pid;
  


  printf("shell_jr: ");
  fflush(stdout);
  fgets(line, 1024, stdin);
  sscanf(line, "%s", input);


  /* UNTIL EXIT COMMANDS ARE ENTERED */
  while(strcmp(input, "exit") && strcmp(input, "goodbye")){

    /* changes directory */
    if(!strcmp(input, "cd")){

      sscanf(line, "%s %s", input, arg);

      /* might need to strcat() to form entire location*/
      chdir(arg);


    /* changes to given directory and pushes onto stack */
    } else if(!strcmp(input, "pushd")){

      if(stack_cnt >= 16){

	      printf("Directory stack is full\n");

      } else {

	      /* gets argument, adds to stack, changes to directory */
	      sscanf(line, "%s %s", input, arg);

	      getcwd(stack[stack_cnt], 1024);

	      stack_cnt++;
	      chdir(arg);
	
      }
      

    /* Displays all directories in stack */
    } else if(!strcmp(input, "dirs")){

      for(count = 0; count < stack_cnt; count++){

        printf("%s\n", stack[count]);

      }


    /* pop directory */
    } else if(!strcmp(input, "popd")){

      if(stack_cnt <= 0){

	      printf("Directory stack is empty\n");

      } else {

	      chdir(stack[stack_cnt - 1]);

	      stack_cnt--;

      }


    /* if another command is given*/
    } else {

      pid = fork();

      if(pid == -1){

	      perror("Fork Error");

      } else if(pid == 0){      /* CHILD */

	      sscanf(line, "%s %s", input, arg);
	
	      argv[0] = input;
	      argv[1] = arg;
	      argv[2] = NULL;
	
	      execvp(argv[0], argv); 

	      /* if fails */
	      if(sscanf(line, "%s %s", input, arg) == 2){

	      printf("Failed to execute %s %s\n", input, arg);

	      } else {

	      printf("Failed to execute %s\n", input);

	      }

	      exit(71);
	

      } else {         /* PARENT */

	      wait(NULL);

      }

    }

    printf("shell_jr: ");
    fflush(stdout);

    if(fgets(line, 1024, stdin) == NULL){

      break;

    }

    sscanf(line, "%s", input);

  }

  /* if goodbye or exit are entered */
  if(!strcmp(input, "exit") || !strcmp(input, "goodbye")){

    printf("See you\n");
    exit(0);

  }

  return 0;

}
