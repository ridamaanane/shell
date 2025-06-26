#include "minishell.h"

int is_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return 0;

    if (ft_strcmp(cmd->argv[0], "cd") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "exit") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "env") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "export") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "unset") == 0)
        return 1;

    return 0;
}
void exec_builtin(t_cmd *cmd)
{
    if (ft_strcmp(cmd->argv[0], "cd") == 0)
        do_cd(cmd);
    else if (ft_strcmp(cmd->argv[0], "echo") == 0)
        do_echo(cmd);
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        do_exit(cmd);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        do_env(cmd);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        do_export(cmd);
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        do_unset(cmd);
}

void executor(t_cmd *cmd, char **envp)
{
    t_cmd *temp = cmd;

    while (temp)
    {
        if (is_builtin(temp))
        {
            find_redirection(temp->redir);
            exec_builtin(temp);
        }
        else
            pipe_executor(temp, envp);
        temp = temp->next;
    }
}
