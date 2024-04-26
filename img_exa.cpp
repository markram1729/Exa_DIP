#include <iostream>
#include "buddy/DIP/ImageContainer.h"
#include "buddy/Core/Container.h"
#include "buddy/DIP/imgcodecs/loadsave.h"

template<typename T>
void print(const std::string &s ="Out",T x=0)
{
	std::cout<<s<<" "<<x<<std::endl;
}
int main()
{
	Img<float,2> myexa =imread<float,2>("./Img_dir/TestGrayImage.jpg",dip::IMGRD_GRAYSCALE);

	size_t n=myexa.getRank();
	print<size_t>("My Rank",n);
	for(size_t i=0;i<n;i++)
	{
		std::cout<<" sizes "<<myexa.getSizes()[i]<<std::endl;

	}
	size_t ele = myexa.getSize();
	print<size_t>("array size",ele);
		
	return 0;
}
