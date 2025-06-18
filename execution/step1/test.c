// #include "minishell.h"
// #include <unistd.h>

// int handle_heardoc()
// {
//     int pipefd[2];
//     pipe(pipefd);

//     while (1)
//     {
//         char *line = readline("> ");
//         if (ft_strcmp(line, "file") == 0)
//         {
//             free(line);
//             break;
//         }
//         write(pipefd[1], line, ft_strlen(line));
//         write(pipefd[1], "\n", 1);
//         free(line);
//     }
//     close(pipefd[1]);
//     return (pipefd[0]); 
// }

// int main()
// {
//     int f = handle_heardoc();

//     char *args[] = {"/bin/cat", NULL};

//     dup2(f, STDIN_FILENO); 
//     char *test = malloc(1234);
//     pid_t pid = fork();
//     if (pid == 0)
//     {
//         execve("/bin/cat", args, NULL);
//         perror("execve failed");
//         close(f);
//     }
//     else 
//         waitpid(pid, NULL, 0);
//     close (f);
//     (void) test;
// }
#include "minishell.h"

int main(void)
{
    int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, 1);  // replace stdout b fd
    close(fd);

    printf("rida\n");

    return 0;
}