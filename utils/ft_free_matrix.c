/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luevange <luevange@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:49:27 by luevange          #+#    #+#             */
/*   Updated: 2025/05/20 17:52:08 by luevange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_free_matrix(char **matrix)
{
    int	i;

    i = 0;
    if (matrix == NULL)
        return ;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}