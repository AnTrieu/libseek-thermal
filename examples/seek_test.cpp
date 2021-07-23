/*
 *  Test program SEEK Thermal Compact/CompactXR
 *  Author: Maarten Vandersteegen
 */
#include <opencv2/highgui/highgui.hpp>
#include "seek.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{

    LibSeek::SeekThermal seek(argc == 2 ? argv[1] : "");
    cv::Mat frame, grey_frame;

    int cntDelay = 0;
    int flagIgnore = 0;
	
    if (!seek.open()) {
        std::cout << "\nfailed to open seek cam" << std::endl;
        return -1;
    }

    std::cout << "-------------\n BEGIN SHOW FRAME \n------------- " << std::endl;

    while(1) {
        if (!seek.read(frame)) {
            std::cout << "no more LWIR img" << std::endl;
            return -1;
        }

        cv::normalize(frame, grey_frame, 0, 65535, cv::NORM_MINMAX);
	cv::imshow("LWIR", grey_frame);

	if((flagIgnore == 0) && (cntDelay++ >= 10))
	{
	    // type = 2 => format CV_16UC1 
	    std::cout << "-------------" << std::endl;
	    std::cout << "Type grey frame: " << grey_frame.type() << std::endl;
            std::cout << "Type frame: " << frame.type() << std::endl;
	    std::cout << "-------------" << std::endl;

	    std::cout << "-------------" << std::endl;
	    std::cout << "Row grey frame: " << grey_frame.rows << std::endl;
            std::cout << "Col grey frame: " << grey_frame.cols<< std::endl;
	    std::cout << "-------------" << std::endl;
	        
            std::ofstream fout("GreyFrameData.txt");
		
            fout<<grey_frame;	
	    fout.close();
	
	    flagIgnore = 1;
	    cntDelay = 0;	
	}
	else if((flagIgnore == 1) && (cntDelay++ >= 10))
	{
	    std::cout << "\nDone !!!" << std::endl;

	    flagIgnore = 2;
	    cntDelay = 0;  
	}
	

        char c = cv::waitKey(10);
        if (c == 's') {
            cv::waitKey(0);
        } 
    }
}
