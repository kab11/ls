/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 17:52:39 by kblack            #+#    #+#             */
/*   Updated: 2018/12/17 17:52:42 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_abs(int i)
{
	if (i < 0)
		i *= -1;
	return (i);
}