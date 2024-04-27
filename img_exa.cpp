#include <iostream>
#include "buddy/DIP/ImageContainer.h"
#include "buddy/Core/Container.h"
#include "buddy/DIP/imgcodecs/loadsave.h"
#include <opencv2/opencv.hpp>

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
	print<int>("channels ",myexa.channels());
	auto *data = myexa.getData();
	for(size_t i=0;i<ele;i++)
	{
		print<float>("at i= "+std::to_string(i),data[i]);
	}
	cv::Mat imo = cv::imread("./Img_dir/TestGrayImage.bmp",cv::IMREAD_GRAYSCALE);
	//intptr_t sizescv[2]={0};
	print("mat channels",imo.channels());
	Img<float,2> myex2(imo,nullptr,true);
	float *datacv = myex2.getData();
	for(size_t i=0;i<myex2.getSize();i++)
	{
		print<float>("myexa2 at i "+std::to_string(i),datacv[i]);
	}
	print<int>("channels",myex2.channels());
	return 0;
}
