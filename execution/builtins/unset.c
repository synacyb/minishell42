#include "../../minishell.h"

void    free_alocation(char *key, char *value)
{
    free(key);
    free(value);
}
void    remove_element(t_list **env, char *arg)
{
    exporta data;
	t_list		*current;
	t_list		*previous;

    previous = 0;
	current = *env;
    while (current)
    {
        get_value_and_key(&data.key_list, &data.value_list, current->content);
        if(ft_strcmp(arg, data.key_list) == 0)
        {
            if(previous == 0)
                *env = current->next;
            else
                previous->next = current->next;

            free(current->content);
            free(current);
            return ;
            free_alocation(data.key_list, data.value_list);
        }
        free_alocation(data.key_list, data.value_list);
		previous = current;
		current = current->next;
    }
}
void    remove_variable(t_list **env, t_node *arg)
{
    int i = 1;

    while (arg->args[i])
	{
        remove_element(env, arg->args[i]);
		i++;
	}
}