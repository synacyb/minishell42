#include "libft.h"

void    memory_released(t_list **head)
{
    ft_lstclear(head, free);
}

void    *garbage_collector(size_t size, short option)
{
    static t_list    *head;
    t_list            *new;
    void            *ptr;

    if (option == 1)
    {
        ptr = malloc(size);
        if (!ptr)
            return (memory_released(&head), exit(EXIT_FAILURE), NULL);
        new = ft_lstnew(ptr);
        if (!new)
            return (memory_released(&head), exit(EXIT_FAILURE), NULL);
        ft_lstadd_back(&head, new);
        return (ptr);
    }
    if (option == 0)
        memory_released(&head);
    return (NULL);
}