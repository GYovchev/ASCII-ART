#include "bitmap_image.hpp"
#include <iostream>
#include <fstream>

const char CHARS[128]="$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1}]?-_+~<>i!lI;:,\"^`'. ";
const char CHARS2[32]=" .:-=+*#%@";

int get_pixel_value(int red, int green, int blue)
{
    return 0.2126*red + 0.7152*green + 0.0722*blue;
}

int main()
{
    char input_name[100];
    char output_name[100];

    int font_size;

    std::cout<<"Enter name/path of the file we will convert:\n";
    std::cin>>input_name;

    std::cout<<"Enter name/path of the file where we will save the result:\n";
    std::cin>>output_name;

    std::cout<<"Enter font-size:\n";
    std::cin>>font_size;


    bitmap_image IN(input_name);

    std::ofstream OUT;
    OUT.open(output_name);



    unsigned int width;
    unsigned int height;

    height = IN.height();
    width  = IN.width();

    const int display_width = 740;
	int N = height*font_size/display_width;

    for ( std::size_t y = 0; y < height-N; y+=N )
    {
        for ( std::size_t x = 0; x < width-N; x+=N )
        {
            int sum_of_values = 0;
            int num_of_pixels = (N + 1)*(N + 1);

            unsigned char red;
            unsigned char green;
            unsigned char blue;

            for ( std::size_t y1 = y; y1 < y+N; y1++ )
            {
                for ( std::size_t x1 = x; x1 < x+N; x1++ )
                {
                    IN.get_pixel( x1, y1, red, green, blue );
					sum_of_values += get_pixel_value(red, green, blue);
                }
            }

		OUT<<CHARS[66-sum_of_values/num_of_pixels*67/255];
		OUT<<CHARS[66-sum_of_values/num_of_pixels*67/255];

		sum_of_values = 0;
		num_of_pixels = 0;
        }
        OUT<<"\n";
    }

    return 0;
}
