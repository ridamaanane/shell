#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	sub_len = s_len - start;
	if (sub_len > len)
		sub_len = len;
	substr = malloc(sizeof(char) * (sub_len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < sub_len)
	{
		substr[i++] = s[start++];
	}
	substr[i] = '\0';
	return (substr);
}




// int is_builtin(char *cmd)
// {
//     if (!cmd)
//         return (0);
//     if (ft_strcmp(cmd, "cd") == 0)
//         return (1);
//     if (ft_strcmp(cmd, "echo") == 0)
//         return (1);
//     if (ft_strcmp(cmd, "pwd") == 0)
//         return (1);    
//     if (ft_strcmp(cmd, "env") == 0)
//         return (1);    
//     if (ft_strcmp(cmd, "export") == 0)
//         return (1);    
//     if (ft_strcmp(cmd, "unset") == 0)
//         return (1);    
//     if (ft_strcmp(cmd, "exit") == 0)
//         return (1);    
//     return (0);
// }


// int exec_builtin(char **args, t_env *env)
// {
//     if (ft_strcmp(args[0], "cd") == 0)
//         return (do_cd(args, env));
//     else if (ft_strcmp(args[0], "echo") == 0)
//         return (do_echo(args, env));
//     else if (ft_strcmp(args[0], "pwd") == 0)
//         return (do_pwd(args, env));
//     else if (ft_strcmp(args[0], "env") == 0)
//         return (do_env(args, env));
//     else if (ft_strcmp(args[0], "export") == 0)
//         return (do_export(args, env));
//     else if (ft_strcmp(args[0], "unset") == 0)
//         return (do_unset(args, env));
//     else if (ft_strcmp(args[0], "exit") == 0)
//         return (do_exit(args, env));
//     return (1);
// }












