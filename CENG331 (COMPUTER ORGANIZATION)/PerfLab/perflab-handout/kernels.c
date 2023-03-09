/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/*
 * Please fill in the following team_t struct
 */
team_t team = {
        "egelipa",    /* Team Name */

        "e244978",      /* First student ID */
        "Hasan Ege Meyvecioğlu",       /* First student name */

        "",             /* Second student ID */
        "",           /* Second student name */

        "",             /* Third student ID */
        ""            /* Third student Name */
};


/********************
 * CONVOLUTION KERNEL
 ********************/

/***************************************************************
 * Your different versions of the convolution functions  go here
 ***************************************************************/

/*
 * naive_conv - The naive baseline version of convolution
 */
char naive_conv_descr[] = "naive_conv: Naive baseline implementation";
void naive_conv(int dim, pixel *src, pixel *ker, unsigned *dst) {
    int i,j,k,l;

    for(i = 0; i < dim-8+1; i++)
        for(j = 0; j < dim-8+1; j++) {
            dst[RIDX(i, j, dim)] = 0;
            for(k = 0; k < 8; k++)
                for(l = 0; l < 8; l++) {
                    dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].red * ker[RIDX(k, l, 8)].red;
                    dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].green * ker[RIDX(k, l, 8)].green;
                    dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].blue * ker[RIDX(k, l, 8)].blue;
                }

        }
}

/*
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */
char convolution_descr[] = "Convolution: Current working version";
void convolution(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    pixel *temp_src,*temp_ker;
    int i, j,s;
    for (i = 0; i < dim - 7; i++) {
        for (j = 0; j < dim - 7; j++) {
            temp_ker=ker;
            {
                temp_src = src + j;

                s = temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src->blue * temp_ker++->blue;
                
                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src->blue * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src->blue * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src->blue * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src->blue * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src->blue * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src->blue * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src++->blue * temp_ker++->blue;
                
                s += temp_src->red  * temp_ker->red;
                s += temp_src->green * temp_ker->green;
                s += temp_src->blue * temp_ker->blue;

                ///////////////////////////////////////////////

            }
            *(dst + j) = s;
        }
        src+=dim;
        dst+=dim;
    }

}
/*********************************************************************
 * register_conv_functions - Register all of your different versions
 *     of the convolution functions  with the driver by calling the
 *     add_conv_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_conv_functions() {
    add_conv_function(&naive_conv, naive_conv_descr);
    add_conv_function(&convolution, convolution_descr);
    /* ... Register additional test functions here */
}




/************************
 * AVERAGE POOLING KERNEL
 ************************/

/*********************************************************
 * Your different versions of the average pooling  go here
 *********************************************************/

/*
 * naive_average_pooling - The naive baseline version of average pooling
 */
char naive_average_pooling_descr[] = "Naive Average Pooling: Naive baseline implementation";
void naive_average_pooling(int dim, pixel *src, pixel *dst) {
    int i,j,k,l;

    for(i = 0; i < dim/2; i++)
        for(j = 0; j < dim/2; j++) {
            dst[RIDX(i, j, dim/2)].red = 0;
            dst[RIDX(i, j, dim/2)].green = 0;
            dst[RIDX(i, j, dim/2)].blue = 0;
            for(k = 0; k < 2; k++) {
                for (l = 0; l < 2; l++) {
                    dst[RIDX(i, j, dim/2)].red += src[RIDX(i*2 + k, j*2 + l, dim)].red;
                    dst[RIDX(i, j, dim/2)].green += src[RIDX(i*2 + k, j*2 + l, dim)].green;
                    dst[RIDX(i, j, dim/2)].blue += src[RIDX(i*2 + k, j*2 + l, dim)].blue;
                }
            }
            dst[RIDX(i, j, dim/2)].red /= 4;
            dst[RIDX(i, j, dim/2)].green /= 4;
            dst[RIDX(i, j, dim/2)].blue /= 4;
        }
}


/*
 * average_pooling - Your current working version of average_pooling
 * IMPORTANT: This is the version you will be graded on
 */
char average_pooling_descr[] = "Average Pooling: Current working version";
void average_pooling(int dim, pixel *src, pixel *dst)
{

    
    int i,j,id;
    int red_sum,green_sum,blue_sum;
    for(i = 0; i < dim/2; i++)
    {
        for(j = 0; j < dim/2-7; j+=8) 
        {
            id = RIDX(i, j, dim/2);
            red_sum = src[RIDX(i*2, j*2, dim)].red + src[RIDX(i*2, j*2+1, dim)].red + src[RIDX(i*2+1, j*2, dim)].red + src[RIDX(i*2+1, j*2+1, dim)].red;
            green_sum = src[RIDX(i*2, j*2, dim)].green + src[RIDX(i*2, j*2+1, dim)].green + src[RIDX(i*2+1, j*2, dim)].green + src[RIDX(i*2+1, j*2+1, dim)].green;
            blue_sum = src[RIDX(i*2, j*2, dim)].blue + src[RIDX(i*2, j*2+1, dim)].blue + src[RIDX(i*2+1, j*2, dim)].blue + src[RIDX(i*2+1, j*2+1, dim)].blue;
            
            dst[id].red = red_sum >> 2;
            dst[id].green = green_sum >> 2;
            dst[id++].blue = blue_sum >> 2;

            red_sum = src[RIDX(i*2, (1+j)*2, dim)].red + src[RIDX(i*2, (1+j)*2+1, dim)].red + src[RIDX(i*2+1, (1+j)*2, dim)].red + src[RIDX(i*2+1, (1+j)*2+1, dim)].red;
            green_sum = src[RIDX(i*2, (1+j)*2, dim)].green + src[RIDX(i*2, (1+j)*2+1, dim)].green + src[RIDX(i*2+1, (1+j)*2, dim)].green + src[RIDX(i*2+1, (1+j)*2+1, dim)].green;
            blue_sum = src[RIDX(i*2, (1+j)*2, dim)].blue + src[RIDX(i*2, (1+j)*2+1, dim)].blue + src[RIDX(i*2+1, (1+j)*2, dim)].blue + src[RIDX(i*2+1, (1+j)*2+1, dim)].blue;
            
            dst[id].red = red_sum >> 2;
            dst[id].green = green_sum >> 2;
            dst[id++].blue = blue_sum >> 2;

            red_sum = src[RIDX(i*2, (2+j)*2, dim)].red + src[RIDX(i*2, (2+j)*2+1, dim)].red + src[RIDX(i*2+1, (2+j)*2, dim)].red + src[RIDX(i*2+1, (2+j)*2+1, dim)].red;
            green_sum = src[RIDX(i*2, (2+j)*2, dim)].green + src[RIDX(i*2, (2+j)*2+1, dim)].green + src[RIDX(i*2+1, (2+j)*2, dim)].green + src[RIDX(i*2+1, (2+j)*2+1, dim)].green;
            blue_sum = src[RIDX(i*2, (2+j)*2, dim)].blue + src[RIDX(i*2, (2+j)*2+1, dim)].blue + src[RIDX(i*2+1, (2+j)*2, dim)].blue + src[RIDX(i*2+1, (2+j)*2+1, dim)].blue;
            
            dst[id].red = red_sum >> 2;
            dst[id].green = green_sum >> 2;
            dst[id++].blue = blue_sum >> 2;

            red_sum = src[RIDX(i*2, (3+j)*2, dim)].red + src[RIDX(i*2, (3+j)*2+1, dim)].red + src[RIDX(i*2+1, (3+j)*2, dim)].red + src[RIDX(i*2+1, (3+j)*2+1, dim)].red;
            green_sum = src[RIDX(i*2, (3+j)*2, dim)].green + src[RIDX(i*2, (3+j)*2+1, dim)].green + src[RIDX(i*2+1, (3+j)*2, dim)].green + src[RIDX(i*2+1, (3+j)*2+1, dim)].green;
            blue_sum = src[RIDX(i*2, (3+j)*2, dim)].blue + src[RIDX(i*2, (3+j)*2+1, dim)].blue + src[RIDX(i*2+1, (3+j)*2, dim)].blue + src[RIDX(i*2+1, (3+j)*2+1, dim)].blue;
            
            dst[id].red = red_sum >> 2;
            dst[id].green = green_sum >> 2;
            dst[id++].blue = blue_sum >> 2;
    
            red_sum = src[RIDX(i*2, (4+j)*2, dim)].red + src[RIDX(i*2, (4+j)*2+1, dim)].red + src[RIDX(i*2+1, (4+j)*2, dim)].red + src[RIDX(i*2+1, (4+j)*2+1, dim)].red;
            green_sum = src[RIDX(i*2, (4+j)*2, dim)].green + src[RIDX(i*2, (4+j)*2+1, dim)].green + src[RIDX(i*2+1, (4+j)*2, dim)].green + src[RIDX(i*2+1, (4+j)*2+1, dim)].green;
            blue_sum = src[RIDX(i*2, (4+j)*2, dim)].blue + src[RIDX(i*2, (4+j)*2+1, dim)].blue + src[RIDX(i*2+1, (4+j)*2, dim)].blue + src[RIDX(i*2+1, (4+j)*2+1, dim)].blue;
            
            dst[id].red = red_sum >> 2;
            dst[id].green = green_sum >> 2;
            dst[id++].blue = blue_sum >> 2;

            red_sum = src[RIDX(i*2, (5+j)*2, dim)].red + src[RIDX(i*2, (5+j)*2+1, dim)].red + src[RIDX(i*2+1, (5+j)*2, dim)].red + src[RIDX(i*2+1, (5+j)*2+1, dim)].red;
            green_sum = src[RIDX(i*2, (5+j)*2, dim)].green + src[RIDX(i*2, (5+j)*2+1, dim)].green + src[RIDX(i*2+1, (5+j)*2, dim)].green + src[RIDX(i*2+1, (5+j)*2+1, dim)].green;
            blue_sum = src[RIDX(i*2, (5+j)*2, dim)].blue + src[RIDX(i*2, (5+j)*2+1, dim)].blue + src[RIDX(i*2+1, (5+j)*2, dim)].blue + src[RIDX(i*2+1, (5+j)*2+1, dim)].blue;
            
            dst[id].red = red_sum >> 2;
            dst[id].green = green_sum >> 2;
            dst[id++].blue = blue_sum >> 2;

            red_sum = src[RIDX(i*2, (6+j)*2, dim)].red + src[RIDX(i*2, (6+j)*2+1, dim)].red + src[RIDX(i*2+1, (6+j)*2, dim)].red + src[RIDX(i*2+1, (6+j)*2+1, dim)].red;
            green_sum = src[RIDX(i*2, (6+j)*2, dim)].green + src[RIDX(i*2, (6+j)*2+1, dim)].green + src[RIDX(i*2+1, (6+j)*2, dim)].green + src[RIDX(i*2+1, (6+j)*2+1, dim)].green;
            blue_sum = src[RIDX(i*2, (6+j)*2, dim)].blue + src[RIDX(i*2, (6+j)*2+1, dim)].blue + src[RIDX(i*2+1, (6+j)*2, dim)].blue + src[RIDX(i*2+1, (6+j)*2+1, dim)].blue;
            
            dst[id].red = red_sum >> 2;
            dst[id].green = green_sum >> 2;
            dst[id++].blue = blue_sum >> 2;

            red_sum = src[RIDX(i*2, (7+j)*2, dim)].red + src[RIDX(i*2, (7+j)*2+1, dim)].red + src[RIDX(i*2+1, (7+j)*2, dim)].red + src[RIDX(i*2+1, (7+j)*2+1, dim)].red;
            green_sum = src[RIDX(i*2, (7+j)*2, dim)].green + src[RIDX(i*2, (7+j)*2+1, dim)].green + src[RIDX(i*2+1, (7+j)*2, dim)].green + src[RIDX(i*2+1, (7+j)*2+1, dim)].green;
            blue_sum = src[RIDX(i*2, (7+j)*2, dim)].blue + src[RIDX(i*2, (7+j)*2+1, dim)].blue + src[RIDX(i*2+1, (7+j)*2, dim)].blue + src[RIDX(i*2+1, (7+j)*2+1, dim)].blue;
            
            dst[id].red = red_sum >> 2;
            dst[id].green = green_sum >> 2;
            dst[id].blue = blue_sum >> 2;
        }

        for(;j<dim/2;j++)
        { 
            red_sum = src[RIDX(i*2, j*2, dim)].red + src[RIDX(i*2, j*2+1, dim)].red + src[RIDX(i*2+1, j*2, dim)].red + src[RIDX(i*2+1, j*2+1, dim)].red;
            green_sum = src[RIDX(i*2, j*2, dim)].green + src[RIDX(i*2, j*2+1, dim)].green + src[RIDX(i*2+1, j*2, dim)].green + src[RIDX(i*2+1, j*2+1, dim)].green;
            blue_sum = src[RIDX(i*2, j*2, dim)].blue + src[RIDX(i*2, j*2+1, dim)].blue + src[RIDX(i*2+1, j*2, dim)].blue + src[RIDX(i*2+1, j*2+1, dim)].blue;
            
            dst[RIDX(i, j, dim/2)].red = red_sum >> 2;
            dst[RIDX(i, j, dim/2)].green = green_sum >> 2;
            dst[RIDX(i, j, dim/2)].blue = blue_sum >> 2;
        }

    }

}

/******************************************************************************
 * register_average_pooling_functions - Register all of your different versions
 *     of the average pooling  with the driver by calling the
 *     add_average_pooling_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 ******************************************************************************/

void register_average_pooling_functions() {
    add_average_pooling_function(&naive_average_pooling, naive_average_pooling_descr);
    add_average_pooling_function(&average_pooling, average_pooling_descr);

    /* ... Register additional test functions here */
}




