#include <iostream>
#include "buddy/DIP/ImageContainer.h"
#include "buddy/Core/Container.h"
#include "buddy/DIP/imgcodecs/loadsave.h"
#include <opencv2/opencv.hpp>
//#include <typeinfo>
template<typename T>
void print(const std::string &s ="Out",T x=0)
{
	std::cout<<s<<" "<<x<<std::endl;
}

bool testcvdp(cv::Mat imgcv,Img<float,2> myexa)
{
	if(myexa.getSizes()[0]!=imgcv.rows|| myexa.getSizes()[1]!=imgcv.cols)
	{
		return false;
	}
	float *data=myexa.getData();
	int k=0;
	//std::cout<<" "<<std::typeid(imgcv)<<std::endl;
	for(size_t i=0;i<myexa.getSizes()[0];i++)
	{
		for(size_t j=0;j<myexa.getSizes()[1];j++)
		{
			float tmp = cv::saturate_cast<float>(imgcv.at<float>(i,j));
			float tmp1=data[k];
			if(tmp1!=tmp)
			{
				print<float>("my ss ",data[k]);
				std::cout<<"crdue "<<data[k]<<std::endl;
				std::cout<<"hh "<<tmp<<" "<<tmp1<<std::endl;
				printf("UUNN %f %f",tmp,tmp1);
				std::cout<<"Not equal at  "<<i<<"-"<<j<<std::endl;
				std::cout<<"ff "<<(float)imgcv.at<float>(i,j)<<std::endl;
				std::cout<<"imgcv "<<imgcv.at<float>(i,j)<<std::endl;
				print<float>("",imgcv.at<uchar>(i,j));
				return false;
			}
			k++;
		}
	}
	return true;
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
	cv::Mat imo = cv::imread("./Img_dir/TestGrayImage.jpg",cv::IMREAD_GRAYSCALE);
	//intptr_t sizescv[2]={0};
	//testcvdp(imo,);
	print("mat channels",imo.channels());
	std::cout<<"test Mat"<<imo<<std::endl;
	bool k=testcvdp(imo,myexa);
	print<bool>("bool k",k);
	Img<float,2> myex2(imo,nullptr,true);
	float *datacv = myex2.getData();
	for(size_t i=0;i<myex2.getSize();i++)
	{
		print<float>("myexa2 at i "+std::to_string(i),datacv[i]);
	}
	print<int>("channels",myex2.channels());
	cv::Mat img2cv=cv::imread("./Img_dir/TestGrayImage.jpg",cv::IMREAD_GRAYSCALE);
	std::cout<<"Print Mat \n"<<img2cv<<std::endl;
	cv::Mat check_img(img2cv.rows,img2cv.cols,CV_32FC1);
	img2cv.convertTo(check_img,CV_32FC1,1.f/255);
	std::cout<<"dd \n"<<check_img<<std::endl;
	bool s =testcvdp(check_img,myex2);
	std::cout<<"out --> "<<s<<std::endl;
	return 0;
}
