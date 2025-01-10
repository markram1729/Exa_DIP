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
	if(a==b) return true;
	float eps = a-b;
	if(eps<0)eps=-eps;
	// if(eps<FLT_EPSILON) return true;

	return (std::abs(a - b)< FLT_EPSILON);
}

template <typename T,size_t N>
bool testcvdp(cv::Mat imgcv,Img<T,N> myexa,bool norm,intptr_t sizes[N]=nullptr)
{
	if(N==4)
	{
		if(imgcv.dims!=N || sizes==nullptr)
		{
			std::cout<<"Given dims "<<imgcv.dims<<"nullptr"<<std::endl;
			return false ;
		}
		float *data = myexa.getData();
		size_t samples = imgcv.size[0];
		size_t channels = imgcv.size[1];
		size_t rows = imgcv.size[2];
		size_t cols = imgcv.size[3];
		int k=0;
		for(size_t i=0;i<samples;i++)
		{
			for(size_t chn =0;chn<channels;chn++)
			{
				T* chndata = imgcv.ptr<T>(i,chn);
				for(size_t m=0;k<rows;m++)
				{
					for(size_t l=0;l<cols;l++)
					{
						if(!compare(data[k],chndata[m*cols+l]))
						{
							return false ;
						}
						k++;
					}
				}
			}
		}
		return true;
	}
	else if(N==2)
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
	
	
}
int main()
{
	Img<float,2> myexa =imread<float,2>("./Img_dir/TestGrayImage.jpg",dip::IMGRD_COLOR);

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
	bool k=testcvdp<float,2>(imo,myexa,false);
	print<bool>("bool k",k);
	Img<float,2> myex2(imo,nullptr,true);

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

  bool s =testcvdp<float,2>(check_img,myex2,true);
	std::cout<<"out --> "<<s<<std::endl;

	std::vector<cv::Mat> vec_img = {img2cv,imo};
	double norm=1.0;
	cv::Mat blob = cv::dnn::blobFromImages(vec_img,norm,cv::Size(img2cv.cols,img2cv.rows));

	std::cout<<"Sizes "<<blob.size()<<" "<<blob.size[0]<<" "<<blob.size[1]<<" "<<blob.size[2]<<" "<<blob.size[3]<<std::endl;
	intptr_t sizes[4]={blob.size[0],blob.size[1],blob.size[2],blob.size[3]};
	Img<float,4>myexacv4(blob,sizes,false);	
	float *cv4data = myexacv4.getData();
	int cv4ele = myexacv4.getSize();
	std::cout<<" dims "<<blob.dims<<std::endl;
	for(size_t i =0;i<cv4ele;i++)
	{
		print<float>(" ",cv4data[i]);
	}
	bool cv4k = testcvdp<float,4>(blob,myexacv4,false,sizes);
	std::cout<<"just checkin "<<cv4k<<std::endl;

	cv::Mat blob2 = cv::dnn::blobFromImages(vec_img,1.0f/255.0,cv::Size(img2cv.cols,img2cv.rows));
	
	Img<float,4>myexacv4n(blob2,sizes,false);	
	float *cv4ndata = myexacv4n.getData();
	int cv4nele = myexacv4n.getSize();
	std::cout<<" dims "<<blob2.dims<<std::endl;
	for(size_t i =0;i<cv4ele;i++)
	{
		print<float>(" ",cv4ndata[i]);
	}
	bool cv4k2 = testcvdp<float,4>(blob2,myexacv4n,false);
	std::cout<<"just checkin "<<cv4k2<<std::endl;

	return 0;
}
