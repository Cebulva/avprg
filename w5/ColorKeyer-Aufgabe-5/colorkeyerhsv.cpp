#include "colorkeyerhsv.h"
#include <QDebug>
using namespace cv;


ColorKeyerHSV::ColorKeyerHSV()
    : hueUpperThreshold(340/2)
    , hueLowerThreshold(360/2)
    , saturationThreshold(120)
    , alpha(0)
    , useMedian(false)
    , useOpening(false)
{
}

Mat ColorKeyerHSV::process(const Mat &input){
    // convert BGR -> HSV
    Mat hsvFrame;
    cvtColor(input, hsvFrame, CV_BGR2HSV);

    // perform color keying
    Mat binaryMask = colorKeying(hsvFrame);

    if (useMedian){
        medianBlur(binaryMask, binaryMask, 5);
    }

    if (useOpening){
        erode(binaryMask, binaryMask, Mat());
        dilate(binaryMask, binaryMask, Mat());
    }

    // calculate center of mass
    centerOfMass(binaryMask);

    // convert binary Image to 3 channel image
    Mat output;
    cvtColor(binaryMask, output, CV_GRAY2BGR);
    drawCross(output, center, 5, Scalar(0, 255, 0));

    return output;
}
Mat ColorKeyerHSV::colorKeying(Mat& hsvFrame){
    // initialize Mat object for output
    Mat output(hsvFrame.rows, hsvFrame.cols, CV_8UC1);

    for(int x = 0; x < hsvFrame.cols; x++){
        for(int y = 0; y < hsvFrame.rows; y++){
            Vec3b hsvPixel = hsvFrame.at<Vec3b>(y,x);
            int hue = hsvPixel[0];
            int saturation = hsvPixel[1];

            // Maskierung und Schwerpunktsberechnung
            bool isWhite = false;
            if (saturation > saturationThreshold){
                if (hueLowerThreshold < hueUpperThreshold){
                    if (hue >= hueLowerThreshold && hue <= hueUpperThreshold){
                        isWhite = true;
                    }
                }
                else {
                    if (hue >= hueLowerThreshold || hue <= hueUpperThreshold){
                        isWhite = true;
                    }
                }
            }
            if (isWhite){
                output.at<uchar>(y,x) = 255;
            }
            else{
                output.at<uchar>(y,x) = 0;
            }
        }
    }
    return output;
}

void ColorKeyerHSV::centerOfMass(Mat& image){
    int sumx = 0;
    int sumy = 0;
    int count = 0;
    for(int x = 0; x < image.cols; x++){
        for (int y = 0; y < image.rows; y++){
            if (image.at<uchar>(y,x) == 255){
                sumx += x;
                sumy += y;
                count++;
            }
        }
    }
    if (count > 0){
        center = (1 - alpha) * center + alpha * Point(sumx/count, sumy/count);
    }
}

void ColorKeyerHSV::drawCross(Mat& image, Point center, int length, Scalar color){
    if(center.x > 0 && center.y > 0){
        line(image, center-Point(0, length), center+Point(0,length), color, 1);
        line(image, center-Point(length, 0), center+Point(length, 0), color, 1);
    }
}

void ColorKeyerHSV::setHueLowerThreshold(int value){
    hueLowerThreshold = value/2;
    qDebug() << "hueLowerThreshold: " << value;
}
void ColorKeyerHSV::setHueUpperThreshold(int value){
    hueUpperThreshold = value/2;
    qDebug() << "hueUpperThreshold: " << value;
}
void ColorKeyerHSV::setSaturationThreshold(int value){
    saturationThreshold = value/2;
    qDebug() << "saturationThreshold: " << value;
}
void ColorKeyerHSV::setAlpha(float alpha){
    this->alpha = alpha;
}

void ColorKeyerHSV::setMedianEnable(bool enable){
    this->useMedian = enable;
}

void ColorKeyerHSV::setOpeningEnable(bool enable){
    this->useOpening = enable;
}
