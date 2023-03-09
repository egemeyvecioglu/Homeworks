char convolution_descr[] = "Convolution: Current working version";
void convolution(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    pixel *temp_src = src,*temp_ker;
    int i, j,id,id1,s,k;
    for (i = 0; i < dim - 7; i++) {
        for (j = 0; j < dim - 7; j++) {
            temp_ker=ker;
            {
                temp_src = src + RIDX((i + k), (j), dim);
                id1 = 0;
                s = (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += (*temp_src).blue * (*(temp_ker++)).blue;
                
                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += (*temp_src).blue * (*(temp_ker++)).blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += (*temp_src).blue * (*(temp_ker++)).blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += (*temp_src).blue * (*(temp_ker++)).blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += (*temp_src).blue * (*(temp_ker++)).blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += (*temp_src).blue * (*(temp_ker++)).blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += (*temp_src).blue * (*(temp_ker++)).blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += ((*temp_src)++).blue * (*(temp_ker++)).blue;
                
                s += (*temp_src).red  * (*temp_ker).red;
                s += (*temp_src).green * (*temp_ker).green;
                s += (*temp_src).blue * (*temp_ker).blue;

                ///////////////////////////////////////////////

            }
            dst[RIDX(i, j, dim)] = s;
        }
    }

}



char convolution_descr[] = "Convolution: Current working version";
void convolution(int dim, pixel *src, pixel *ker, unsigned *dst)
{
pixel *temp_src;
    int i, j,s;
    for (i = 0; i < dim - 7; i++) {
        for (j = 0; j < dim - 7; j++) {
            {
                temp_src = src + RIDX((i), (j), dim);
               
                s = temp_src->red  * (ker)->red;
                s += temp_src->green * (ker)->green;
                s += temp_src++->blue * (ker)->blue;
                
                s += temp_src->red  * (ker+1)->red;
                s += temp_src->green * (ker+1)->green;
                s += temp_src++->blue * (ker+1)->blue;
                
                s += temp_src->red  * (ker+2)->red;
                s += temp_src->green * (ker+2)->green;
                s += temp_src++->blue * (ker+2)->blue;
                
                s += temp_src->red  * (ker+3)->red;
                s += temp_src->green * (ker+3)->green;
                s += temp_src++->blue * (ker+3)->blue;

                s += temp_src->red  * (ker+4)->red;
                s += temp_src->green * (ker+4)->green;
                s += temp_src++->blue * (ker+4)->blue;
                
                s += temp_src->red  * (ker+5)->red;
                s += temp_src->green * (ker+5)->green;
                s += temp_src++->blue * (ker+5)->blue;
                
                s += temp_src->red  * (ker+6)->red;
                s += temp_src->green * (ker+6)->green;
                s += temp_src++->blue * (ker+6)->blue;
                
                s += temp_src->red  * (ker+7)->red;
                s += temp_src->green * (ker+7)->green;
                s += temp_src++->blue * (ker+7)->blue;
                
                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * (ker+8)->red;
                s += temp_src->green * (ker+8)->green;
                s += temp_src->blue * (ker+8)->blue;
                
                s += temp_src->red  * (ker+9)->red;
                s += temp_src->green * (ker+9)->green;
                s += temp_src++->blue * (ker+9)->blue;
                
                s += temp_src->red  * (ker+10)->red;
                s += temp_src->green * (ker+10)->green;
                s += temp_src++->blue * (ker+10)->blue;
                
                s += temp_src->red  * (ker+11)->red;
                s += temp_src->green * (ker+11)->green;
                s += temp_src++->blue * (ker+11)->blue;
                
                s += temp_src->red  * (ker+12)->red;
                s += temp_src->green * (ker+12)->green;
                s += temp_src++->blue * (ker+12)->blue;
                
                s += temp_src->red  * (ker+13)->red;
                s += temp_src->green * (ker+13)->green;
                s += temp_src++->blue * (ker+13)->blue;
                
                s += temp_src->red  * (ker+14)->red;
                s += temp_src->green * (ker+14)->green;
                s += temp_src++->blue * (ker+14)->blue;
                
                s += temp_src->red  * (ker+15)->red;
                s += temp_src->green * (ker+15)->green;
                s += temp_src->blue * (ker+15)->blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * (ker+16)->red;
                s += temp_src->green * (ker+16)->green;
                s += temp_src++->blue * (ker+16)->blue;
                
                s += temp_src->red  * (ker+17)->red;
                s += temp_src->green * (ker+17)->green;
                s += temp_src++->blue * (ker+17)->blue;
                
                s += temp_src->red  * (ker+18)->red;
                s += temp_src->green * (ker+18)->green;
                s += temp_src++->blue * (ker+18)->blue;
                
                s += temp_src->red  * (ker+19)->red;
                s += temp_src->green * (ker+19)->green;
                s += temp_src++->blue * (ker+19)->blue;
                
                s += temp_src->red  * (ker+20)->red;
                s += temp_src->green * (ker+20)->green;
                s += temp_src++->blue * (ker+20)->blue;
                
                s += temp_src->red  * (ker+21)->red;
                s += temp_src->green * (ker+21)->green;
                s += temp_src++->blue * (ker+21)->blue;
                
                s += temp_src->red  * (ker+22)->red;
                s += temp_src->green * (ker+22)->green;
                s += temp_src++->blue * (ker+22)->blue;
                
                s += temp_src->red  * (ker+23)->red;
                s += temp_src->green * (ker+23)->green;
                s += temp_src->blue * (ker+23)->blue;

                ///////////////////////////////////25///////////
                temp_src += dim-7;
                s += temp_src->red  * (ker+24)->red;
                s += temp_src->green * (ker+24)->green;
                s += temp_src++->blue * (ker+24)->blue;
                
                s += temp_src->red  * (ker+25)->red;
                s += temp_src->green * (ker+25)->green;
                s += temp_src++->blue * (ker+25)->blue;
                
                s += temp_src->red  * (ker+26)->red;
                s += temp_src->green * (ker+26)->green;
                s += temp_src++->blue * (ker+26)->blue;
                
                s += temp_src->red  * (ker+27)->red;
                s += temp_src->green * (ker+27)->green;
                s += temp_src++->blue * (ker+27)->blue;
                
                s += temp_src->red  * (ker+28)->red;
                s += temp_src->green * (ker+28)->green;
                s += temp_src++->blue * (ker+28)->blue;
                
                s += temp_src->red  * (ker+29)->red;
                s += temp_src->green * (ker+29)->green;
                s += temp_src++->blue * (ker+29)->blue;
                
                s += temp_src->red  * (ker+30)->red;
                s += temp_src->green * (ker+30)->green;
                s += temp_src++->blue * (ker+30)->blue;
                
                s += temp_src->red  * (ker+31)->red;
                s += temp_src->green * (ker+31)->green;
                s += temp_src->blue * (ker+31)->blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * (ker+32)->red;
                s += temp_src->green * (ker+32)->green;
                s += temp_src++->blue * (ker+32)->blue;
                
                s += temp_src->red  * (ker+33)->red;
                s += temp_src->green * (ker+33)->green;
                s += temp_src++->blue * (ker+33)->blue;
                
                s += temp_src->red  * (ker+34)->red;
                s += temp_src->green * (ker+34)->green;
                s += temp_src++->blue * (ker+34)->blue;
                
                s += temp_src->red  * (ker+35)->red;
                s += temp_src->green * (ker+35)->green;
                s += temp_src++->blue * (ker+35)->blue;
                
                s += temp_src->red  * (ker+36)->red;
                s += temp_src->green * (ker+36)->green;
                s += temp_src++->blue * (ker+36)->blue;
                
                s += temp_src->red  * (ker+37)->red;
                s += temp_src->green * (ker+37)->green;
                s += temp_src++->blue * (ker+37)->blue;
                
                s += temp_src->red  * (ker+38)->red;
                s += temp_src->green * (ker+38)->green;
                s += temp_src++->blue * (ker+38)->blue;
                
                s += temp_src->red  * (ker+39)->red;
                s += temp_src->green * (ker+39)->green;
                s += temp_src->blue * (ker+39)->blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * (ker+40)->red;
                s += temp_src->green * (ker+40)->green;
                s += temp_src++->blue * (ker+40)->blue;
                
                s += temp_src->red  * (ker+41)->red;
                s += temp_src->green * (ker+41)->green;
                s += temp_src++->blue * (ker+41)->blue;
                
                s += temp_src->red  * (ker+42)->red;
                s += temp_src->green * (ker+42)->green;
                s += temp_src++->blue * (ker+42)->blue;
                
                s += temp_src->red  * (ker+43)->red;
                s += temp_src->green * (ker+43)->green;
                s += temp_src++->blue * (ker+43)->blue;
                
                s += temp_src->red  * (ker+44)->red;
                s += temp_src->green * (ker+44)->green;
                s += temp_src++->blue * (ker+44)->blue;
                
                s += temp_src->red  * (ker+45)->red;
                s += temp_src->green * (ker+45)->green;
                s += temp_src++->blue * (ker+45)->blue;
                
                s += temp_src->red  * (ker+46)->red;
                s += temp_src->green * (ker+46)->green;
                s += temp_src++->blue * (ker+46)->blue;
                
                s += temp_src->red  * (ker+47)->red;
                s += temp_src->green * (ker+47)->green;
                s += temp_src->blue * (ker+47)->blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * (ker+48)->red;
                s += temp_src->green * (ker+48)->green;
                s += temp_src++->blue * (ker+48)->blue;
                
                s += temp_src->red  * (ker+49)->red;
                s += temp_src->green * (ker+49)->green;
                s += temp_src++->blue * (ker+49)->blue;
                
                s += temp_src->red  * (ker+50)->red;
                s += temp_src->green * (ker+50)->green;
                s += temp_src++->blue * (ker+50)->blue;
                
                s += temp_src->red  * (ker+51)->red;
                s += temp_src->green * (ker+51)->green;
                s += temp_src++->blue * (ker+51)->blue;
                
                s += temp_src->red  * (ker+52)->red;
                s += temp_src->green * (ker+52)->green;
                s += temp_src++->blue * (ker+52)->blue;
                
                s += temp_src->red  * (ker+53)->red;
                s += temp_src->green * (ker+53)->green;
                s += temp_src++->blue * (ker+53)->blue;
                
                s += temp_src->red  * (ker+54)->red;
                s += temp_src->green * (ker+54)->green;
                s += temp_src++->blue * (ker+54)->blue;
                
                s += temp_src->red  * (ker+55)->red;
                s += temp_src->green * (ker+55)->green;
                s += temp_src->blue * (ker+55)->blue;

                ///////////////////////////////////////////////
                temp_src += dim-7;
                s += temp_src->red  * (ker+56)->red;
                s += temp_src->green * (ker+56)->green;
                s += temp_src++->blue * (ker+56)->blue;
                
                s += temp_src->red  * (ker+57)->red;
                s += temp_src->green * (ker+57)->green;
                s += temp_src++->blue * (ker+57)->blue;
                
                s += temp_src->red  * (ker+58)->red;
                s += temp_src->green * (ker+58)->green;
                s += temp_src++->blue * (ker+58)->blue;
                
                s += temp_src->red  * (ker+59)->red;
                s += temp_src->green * (ker+59)->green;
                s += temp_src++->blue * (ker+59)->blue;
                
                s += temp_src->red  * (ker+60)->red;
                s += temp_src->green * (ker+60)->green;
                s += temp_src++->blue * (ker+60)->blue;
                
                s += temp_src->red  * (ker+61)->red;
                s += temp_src->green * (ker+61)->green;
                s += temp_src++->blue * (ker+61)->blue;
                
                s += temp_src->red  * (ker+6)->red;
                s += temp_src->green * (ker+6)->green;
                s += temp_src++->blue * (ker+6)->blue;
                
                s += temp_src->red  * (ker+63)->red;
                s += temp_src->green * (ker+63)->green;
                s += temp_src->blue * (ker+63)->blue;

                ///////////////////////////////////////////////

            }
            dst[RIDX(i, j, dim)] = s;
        }
    }
}