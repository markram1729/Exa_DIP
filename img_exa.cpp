#include <iostream>
#include <cfloat>
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

bool compare(float a,float b)
{
	//if(a==b) return true;
	//float eps = std::abs(a-b);
	//std::cout<<"abds "<<abs(a-b)<<"true "<<eps<<std::endl;
//	if(eps<0)eps=-eps;
	return ( std::abs(a-b)<FLT_EPSILON);
}
template <typename T,size_t N>
//bool testcvdp(cv::Mat imgcv,intptr_t sizes[N],Img<float,2> myexa,bool norm)
bool testcvdp(cv::Mat imgcv,Img<float,N> myexa,bool norm)
{
	if(myexa.getSizes()[0]!=imgcv.rows|| myexa.getSizes()[1]!=imgcv.cols)
	{
		return false;
	}
	float *data=myexa.getData();
	int k=0;
	size_t batch=0,channel=0;
	/*if(N==2)
	{
		batch=1;
		channel=1;
		rows = myexa.getSizes()[]
	}
	else
	{
		batch=sizes[0];
		channel=sizes[1];
	}
	for(size_t i=0;i<batch;i++)
	{
		fOr(size_t j=0;j<channel;j++)
		*/
	//std::cout<<" "<<std::typeid(imgcv)<<std::endl;
/*	for(int i=0;i<myexa.getSizes()[0];i++)
	{
		for(int j=0;j<myexa.getSizes()[1];j++)
		{
			if(!norm)
			{
                          float tmp =
                              cv::saturate_cast<float>(imgcv.at<uchar>(i, j));
                          float tmp1 = data[k];
                          std::cout << "hh " << tmp << " " << tmp1 << " "
                                    << (tmp - tmp1) << std::endl;
                          if (!compare(tmp, tmp1)) {
                            print<float>("my ss ", data[k]);
                            std::cout << "crdue " << data[k] << std::endl;
                            std::cout << "hh " << tmp << " " << tmp1
                                      << std::endl;
                            printf("UUNN %f %f", tmp, tmp1);
                            std::cout << "Not equal at  " << i << "-" << j
                                      << std::endl;
                            std::cout << "ff " << (float)imgcv.at<float>(i, j)
                                      << std::endl;
                            std::cout << "imgcv "
                                      << (float)imgcv.at<uchar>(i, j)
                                      << std::endl;
                            print<float>("", imgcv.at<uchar>(i, j));
                            return false;
                          }
                          k++;
                        }
			else{
				float tmp = cv::saturate_cast<float>(imgcv.at<float>(i,j));
				float tmp1=data[k];
				//tmp=tmp*100000.f;
				//tmp1=tmp1*100000.f;
				//std::cout<<"hh "<<tmp<<" "<<tmp1<<" "<<(tmp1-tmp)<<std::endl;
				float eps = (tmp1-tmp);
				//if(eps<0)eps=-eps;
				//std::cout<<"flot diff "<<eps<<" d "<<FLT_EPSILON<<std::endl;
				if(!compare(tmp,tmp1))
				{
					print<float>("my ss ",data[k]);
					std::cout<<"crdue "<<data[k]<<std::endl;
					std::cout<<"hh "<<tmp<<" "<<tmp1<<std::endl;
					printf("UUNN %f %f",tmp,tmp1);
					std::cout<<"Not equal at  "<<i<<"-"<<j<<std::endl;
					std::cout<<"ff "<<(float)imgcv.at<float>(i,j)<<std::endl;
					std::cout<<"imgcv "<<(float)imgcv.at<uchar>(i,j)<<std::endl;
					print<float>("",imgcv.at<uchar>(i,j));
					return false;
				}
				k++;
			}

		}
	}
*/
		
	return true;
}
int main()
{
	Img<float,3> myexa =imread<float,3>("./Img_dir/TestGrayImage.jpg",dip::IMGRD_COLOR);

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
	cv::Mat imo = cv::imread("/home/regaltos/dev/llvm_dev/buddy_exa/Img_dir/YuTu.jpg",cv::IMREAD_COLOR);
	//intptr_t sizescv[2]={0};
	//testcvdp(imo,);
	print("mat channels",imo.channels());
	std::cout<<"test Mat"<<imo<<std::endl;
	//bool k=testcvdp<float,3>(imo,myexa,false);
	//print<bool>("bool k",k);
	intptr_t sizesexai[4]={1,imo.channels(),imo.rows,imo.cols};
	Img<float,4> myex2(imo,sizesexai,false);
	float *datacv = myex2.getData();
	for(size_t i=0;i<myex2.getSize();i++)
	{
		print<float>("myexa2 at i "+std::to_string(i),datacv[i]);
	}
	print<int>("channels",myex2.channels());
	print("mat channels",imo.channels());
	cv::Mat img2cv=cv::imread("./Img_dir/TestGrayImage.jpg",cv::IMREAD_GRAYSCALE);
	std::cout<<"Print Mat \n"<<img2cv<<std::endl;
	cv::Mat check_img(img2cv.rows,img2cv.cols,CV_32FC1);
	img2cv.convertTo(check_img,CV_32FC1,1.f/255);
	std::cout<<"dd \n"<<check_img<<std::endl;
	//bool s =testcvdp<float,2>(check_img,myex2,true);
	//std::cout<<"out --> "<<s<<std::endl;
	return 0;
}
