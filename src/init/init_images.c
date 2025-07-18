/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:07:01 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 10:56:19 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"
/* creamos una imagen vacia que podemos dibujar despues pixel a pixel*/
void    init_img(t_general *gen, t_image *img, int width, int heigth)
{
    //iniciamos valores
    init_s_images(&gen->img);
    //se crea una imagen en negro o vacio
    img->image = mlx_new_image(gen->mlx, width, heigth); 
    if (img->image == NULL)
        clean_exit(gen, error("mlx", ERR_MLX_IMG, 1));
    //accedemos a los datos de los pixeles para poder modificar
    img->addr = (int *)mlx_get_data_addr(img->image, &img->pixel_bits, 
        &img->size_line, &img->endian);     
}

/* cogemos una imagen desde PATH y la pasamos de XMP a imagen*/
void    init_textures_img(t_general *gen, t_image *img, char *path)
{
    //iniciamos valores
    init_s_images(&gen->img);
    //cargamos la imagen XMP desde PATH
    img->image = mlx_xpm_file_to_image(gen->mlx, path, &gen->text.h_size, &gen->text.w_size); 
    if (img->image == NULL)
        clean_exit(gen, error("mlx", ERR_MLX_IMG, 1));
    //accedemos a los datos de los pixeles de esta imagen
    img->addr = (int *)mlx_get_data_addr(img->image, &img->pixel_bits,
        &img->size_line, &img->endian);
    
}

/* cogemos la imagen XPM y la guardamos en un array en la RAM, para que sea mas rapido a la hora de leer*/
int *save_xmp_to_mem(t_general *gen, char *path)
{
    t_image tmp;
    int *ram;
    int x;
    int y;

    //iniciamos las texturas de la imagen
    init_textures_img(gen, &tmp, path);
    //reservamos memoria para un array de 1, donde el elmento sera del tamaño del size de la textura
    ram = ft_calloc(1, sizeof * ram * gen->text.w_size * gen->text.h_size);
    if (!ram)
        clean_exit(gen, -1);
    y = 0;
    while (y < gen->text.h_size)
    {
        x = 0;
        while (x < gen->text.w_size)
        {
            /*esta formula, indica que pixel 2D (en las coordenadas X y Y), sera el pixel en el array 1D
            entonces para saber, cogemos la fila columna Y * ANCHURA DE PIXEL + fila X
            EJEMPLO = imagen 10 pixel, si queremos saber qual es el pixel x=3, y=2 en 1D
            seria, indice (pixel en 1d) = 2 * 10 + 3 = 23, entonces el pixel[3][2] sera igual al pixel 23, en 1D*/
            ram[y * gen->text.w_size + x] = tmp.addr[y * gen->text.w_size + x];
            x++;
        }
        y++;
    }
    //destruimos la imagen de tmp
    mlx_destroy_image(gen->mlx, tmp.image);
    //retornamos la nueva imagen en 1S
    return (ram);
}

/* iniciamos las texturas de las paredes*/
void init_textures(t_general *gen)
{
    int i;

    i = 0;
    //reservamos espacio para un array de 5, tamaño de gen->textures    
    gen->textures = ft_calloc(5, sizeof * gen->textures);
    /* a cada array se le guardara la imagen XPM, passada a memoria */
    gen->textures[0] = save_xmp_to_mem(gen, gen->text.N);
    gen->textures[1] = save_xmp_to_mem(gen, gen->text.S);
    gen->textures[2] = save_xmp_to_mem(gen, gen->text.W);
    gen->textures[3] = save_xmp_to_mem(gen, gen->text.E);
}