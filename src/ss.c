/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ss.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 20:17:12 by mshagga           #+#    #+#             */
/*   Updated: 2019/08/13 20:17:12 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

typedef struct s_type
{
	int		a;
}				t_type;

t_type	foo(t_type x)
{
	x.a++;
	return(x);
}

int main()
{
	t_type *x;
	t_type b;

	x = (t_type*)malloc(sizeof(x));
	x->a = 0;
	b = foo(*x);
	// free(x);
	printf("b = %d alloc = %d\n", b.a, x->a);
	return (0);
}