/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:42:56 by jhh               #+#    #+#             */
/*   Updated: 2026/01/19 15:15:13 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(argc, argv, &data))
		return (1);
	if (init_data(&data))
		return (1);
	if (start_simulation(&data))
		return (1);
	cleanup(&data);
	return (0);
}
