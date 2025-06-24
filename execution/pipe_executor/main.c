#include "minishell.h"

int count_cmds(t_cmd *cmd)
{
    int count = 0;
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return count;
}

int *create_pipes(t_cmd *cmd)
{
    int nb_cmd = count_cmds(cmd);
    int nb_pipes = nb_cmd - 1;
    int *pipes = malloc(sizeof(int) * nb_pipes * 2); //2 mean read and write
    if (!pipes)
        return (NULL);

    int i = 0;
    while (i < nb_pipes)
    {
        if (pipe(&pipes[i * 2]) < 0)
        {
            perror("pipe failed");
            free(pipes);
            return NULL;
        }
        i++;
    }
    return (pipes);
}
char *get_cmd_path(char *cmd)
{
    int i;
    char *chunk;
    char *full_path;
    char **paths;
    
    paths = ft_split(getenv("PATH"), ':');
    full_path = NULL;
    i = 0;
    while (paths && paths[i])
    {
        chunk = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(chunk, cmd);
        free(chunk);
        if (access(full_path, X_OK) == 0)
            break;
        free(full_path);
        full_path = NULL;
        i++;
    }
    free_split_content(paths);
    return (full_path);
}
void close_pipe_and_wait(int nb_cmds, int nb_pipes, char *pipes)
{
    // parent: close pipes
    int i = 0;
    while (i < nb_pipes * 2)
    {
        close(pipes[i]);
        i++;
    }

    // wait all children
    int j = 0;
    while (j < nb_cmds)
    {
        wait(NULL);
        j++;
    }
    free(pipes); //7it deja allocinahom fcreate pipes
}
void pipe_executor(t_cmd *cmd, char **envp)
{
    int nb_cmds = count_cmds(cmd);
    int nb_pipes = nb_cmds - 1;
    int *pipes = create_pipes(cmd);
    if (!pipes)
    {
        perror("failed to create pipes");
        return;
    }
    t_cmd *temp;
    int i = 0;
    int j = 0;

    temp = cmd;
    while (temp)
    {
        pid_t pid = fork();
        char *path = get_cmd_path(temp->argv[0]);
        if (pid == 0)
        {
            if (i != 0)
                dup2(pipes[(i - 1) * 2], STDIN_FILENO); //(STDIN Mean read end dial prev pipe)
            if (temp->next)
                dup2(pipes[i * 2 + 1], STDOUT_FILENO);
            while (j < nb_pipes * 2)
            {
                close(pipes[j]);
                j++;
            }
            if (!path)
            {
                printf("%s: command not found\n", temp->argv[0]);
                exit(127);
            }
            execve(path, temp->argv, envp); //temp->argv = { "ls", "-l", NULL }
            perror("execve failed");
            exit(127); //command not found
            
        }
        else if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }
        temp = temp->next;
        i++;
    }
    close_pipe_and_wait(nb_cmds, nb_pipes, pipes);
}


int main()
{
    // Setup dummy cmd list: ls | wc | cat  => 3 cmds -> 2 pipes
    t_cmd c1 = { NULL };
    t_cmd c2 = { NULL };
    t_cmd c3 = { NULL };
    c1.next = &c2;
    c2.next = &c3;

    int *pipes = create_pipes(&c1);
    if (!pipes)
    {
        printf("Pipe creation failed!\n");
        return 1;
    }

    // Print fds
    int nb_cmd = count_cmds(&c1);
    int nb_pipes = nb_cmd - 1;
    int i = 0;
    while (i < nb_pipes)
    {
        printf("Pipe %d -> read fd: %d, write fd: %d\n", i, pipes[i*2], pipes[i*2+1]);
        i++;
    }

    // Clean up
    // for (int i = 0; i < nb_pipes * 2; i++)
    //     close(pipes[i]);
    // free(pipes);

    return 0;
}