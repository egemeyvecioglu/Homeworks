char ege_descr[] = "Convolution: EGE";
void ege(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    pixel *temp_src,*temp_ker;
    unsigned short *temp_src;
    int i, j,s;
    for (i = 0; i < dim - 7; i++) {
        for (j = 0; j < dim - 7; j++) {
            temp_ker=ker;
            {
                temp_src = src + j;

                s = *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *temp_src * temp_ker++->blue;
                
                ///////////////////////////////////////////////
                temp_src += dim-23;
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *temp_src * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-23;
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *temp_src * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-23;
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *temp_src * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-23;
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *temp_src * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-23;
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *temp_src * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-23;
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *temp_src * temp_ker++->blue;

                ///////////////////////////////////////////////
                temp_src += dim-23;
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *(temp_src++) * temp_ker++->blue;
                
                s += *(temp_src++)  * temp_ker->red;
                s += *(temp_src++) * temp_ker->green;
                s += *temp_src * temp_ker->blue;

                ///////////////////////////////////////////////

            }
            *(dst + j) = s;
        }
        src+=dim;
        dst+=dim;
    }

}