#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

//Para compilar
//g++ -o histograma histograma.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
void plotHist(Mat &hist, const char* title)
{
  //Grafica los histogramas
  Mat graf(800, 1024 , CV_8UC3, Scalar(50, 50, 50));
  namedWindow(title, WINDOW_AUTOSIZE);

  int scalax = cvRound(graf.cols/255);
  normalize(hist, hist, 0, graf.rows, NORM_MINMAX);
  for (size_t i = 1; i < hist.rows; i++)
  {
    line(graf, Point((i-1)*scalax,
        cvRound(graf.rows-hist.at<double>(i-1))),
        Point((i)*scalax,
        cvRound(graf.rows-hist.at<double>(i))),
        Scalar(50, 50, 255), 2);
  }

  imshow(title, graf);
}


int main()
{
  Mat a = imread("ciudad.jpg", CV_8UC1);
  Mat hist(256, 1, CV_64F);
  Mat histAcum(256, 1, CV_64F, Scalar(0));
  hist = 0;
  namedWindow("imagen", WINDOW_AUTOSIZE);
  int intensidad;

  //Histograma normal
  for (size_t i = 0; i < a.rows; i++)
  {
    for (size_t j = 0; j < a.cols; j++)
    {
        intensidad = a.at<unsigned char>(i, j);
        hist.at<double>(intensidad) += 1;
    }
  }

  //hitograma acumulativo
  histAcum.at<double>(0) += hist.at<double>(0);
  for (size_t i = 1; i < hist.rows; i++)
  {
    histAcum.at<double>(i) = histAcum.at<double>(i - 1) + hist.at<double>(i);
  }


  plotHist(hist, "Histo");
  plotHist(histAcum, "Acum");

  imshow("imagen", a);
  waitKey(0);
  destroyAllWindows();
  return 0;
}
