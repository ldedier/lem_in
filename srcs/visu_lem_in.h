/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_lem-in.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 22:04:38 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/11 18:12:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISU_LEM_IN_H
# define FT_VISU_LEM_IN_H

# include "lem_in.h"
# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_mixer/SDL_mixer.h>
# include "../libft/srcs/libft.h"

# define WIN_WIDTH		1200
# define WIN_HEIGHT		950

typedef struct			s_image
{
	void				*ptr;
	int					*data;
	int					width;
	int					height;
	int					bpp;
	int					line_size;
	int					endian;
}						t_image;

#endif
