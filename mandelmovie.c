#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <math.h>

int main(int argc, char **argv)
{
    int numOfProcesses;
    numOfProcesses = atoi(argv[1]);

    // Create a list of commands that mandelmovie will run
    char *argument_list[] = {"./mandel", "-x 0.286932", "-y 0.014287", "-s 2", "-m 1000", "-W 2000", "-H 2000", "", "-n 3", NULL};
    pid_t pid;
    int status;

    int j = 1;
    int i = 0;
    double b = 0.0001;
    double a = 2;
    double scale;
    scale = a;

    char filename[100];
    char targetSize[100];
    while (i < 50)
    {
        for (j = 1; j <= numOfProcesses; j++)
        {
            i++;

            // Decrease the scale for each image until we reach the target size
            scale = scale * exp(log(b / a) / 49);
            // Add the num for the scale into a string
            snprintf(targetSize, sizeof targetSize, "-s %f", scale);
            // Add the scale string to the list of commands
            argument_list[3] = targetSize;
            // Add the -o command for each number of mandel.bmp file
            snprintf(filename, sizeof filename, "-o mandel%d.bmp", i);
            // Add the filename to the list of commands
            argument_list[7] = filename;
            printf("%s\n", argument_list[7]);

            // Create forks for the numOfProcesses
            pid = fork();
            // Break out of the for loop when a child is created so that we can execute the command.
            if (pid == 0)
            {
                break;
            }
        }
        if (pid > 0)
        {
            while (j > 0)
            {

                wait(&status);
                j--;
            }
        }
        else if (pid == 0) // child process
        {
            // printf("%d\n", getpid());
            execvp(argument_list[0], argument_list); // execute a command
        }
        else if (pid < 0)
        {
            perror("fork failed\n");
        }
    }
    return 0;
}