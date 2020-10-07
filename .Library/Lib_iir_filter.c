#include "Lib_iir_filter.h"

#define f_size 256
#define num_sections 3
float X[num_sections][f_size];
float Y[num_sections][f_size];
uint16_t  index[num_sections];

float ts[num_sections][3] = {{1 , 2 ,  1 },
	                     {1 , 2 ,  1 },               //bo loc thong thap 10k = do rong 0.2 ms
			     {1 , 2 ,  1 }  };            //F: 800-10-40-1-61

float ms[num_sections][3] = {{1 , -1.724708,  0.836611 },
                             {1 , -1.510916,  0.608947 },
			     {1 , -1.410005,  0.501489 }  };


float gain[num_sections] = {  0.027975,    0.024508,       0.022871 };                                                                                                         


void initialization(){
	for(uint16_t i = 0; i<num_sections;i++)
        {
		for(uint16_t j=0; j< f_size; j++)
                {
			X[i][j]=0;
			Y[i][j]=0;
		}
		index[i] = 0;
	}
}

float   section_filter(float x,uint8_t sections)
{
	    uint8_t k = index[sections];
    	X[sections][k] = gain[sections]*x;
		float conv = 0;
		for (uint8_t i = 0; i < num_sections; i++) 
                {
			if((k-i)<0)
                        {
			     conv += ts[sections][i] * X[sections][k - i+f_size];
	    	        }
                        else
                        {
	    		 conv += ts[sections][i] * X[sections][k - i];
			}
		}
		for (uint8_t j = 1; j < num_sections; j++)
                {
			if((k-j)<0)
                        {
			     conv -= ms[sections][j] * Y[sections][k - j+f_size];
	    	        }
                        else
                        {
	    		    conv -= ms[sections][j] * Y[sections][k - j];
			}
		}
		Y[sections][k] = conv;
		k++;
		k %= f_size;
		index[sections]=k;
    	return conv;
}

uint16_t iir_filter(uint16_t in)
{
        float out[num_sections];
        out[0] =  section_filter(in , 0);
        for(uint8_t i = 1 ;i < num_sections; i++)
        {
            out[i] = section_filter(out[i-1] , i);
	}
	 return (uint16_t)out[num_sections-1];
}
