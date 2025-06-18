#include "minishell.h"

void check_fd(int fd)
{
    if (fd < 0)
    {
        perror("open failed");
        exit(1);
    }
}
void dup_fd_out_app(int fd)
{
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2 failed");
        close(fd);
        exit(1);
    }
}
void dup_fd_inp(int fd)
{
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2 failed");
        close(fd);
        exit(1);
    }
}

// void handle_heardoc(char *filename)
// {
//     int pipefd[2];
//     pipe(pipefd);

//     while (1)
//     {
//         char *line = readline(">");
//         if (ft_strcmp(line, filename) == 0)
//         {
//             free(line);
//             break;
//         }
//         write(pipefd[1], line, ft_strlen(line));
//         write(pipefd[1], "\n", 1);
//         free(line);
//     }
//     close(pipefd[1]);

//     dup2(pipefd[0], STDIN_FILENO);
//     close(pipefd[0]);
//     execve("/bin/cat", )

// }


void find_redirection(t_redir *redir)
{
    int fd;
    
    while(redir)
    {
        if (redir->type == R_INPUT)
        {   
            fd = open(redir->filename, O_RDONLY);
            check_fd(fd);
            dup_fd_out_app(fd);
            close(fd);
        }
        else if (redir->type == R_OUTPUT)
        {
            fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            check_fd(fd);
            dup_fd_inp(fd);
            close(fd);
        }
        else if (redir->type == R_APPAND)
        {
            fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
            check_fd(fd);
            dup_fd_out_app(fd);
            close(fd);
        }
        // else if (redir->type == R_HERDOC)
        // {
        //     handle_heardoc(redir->filename);
        // }
        redir = redir->next;
    }    
}


