#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

//Para compilar
//g++ -o histograma2 histograma2.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
void plotHist(Mat &hist, const char* title)
{
  //Grafica los histogramas
  //Crea una matriz para guardar la grafica del histograma
  Mat graf(800, 1024 , CV_8UC3, Scalar(50, 50, 50));
  namedWindow(title, WINDOW_AUTOSIZE);

  int scalax = cvRound(graf.cols/255); //Obtiene un escala en x
  //Obtiene los valores escalados en y para el alto del histograma (800)
  normalize(hist, hist, 0, graf.rows, NORM_MINMAX);

  //Dibuja las lineas del histograma
  for (size_t i = 1; i < hist.rows; i++)
  {
    line(graf, Point((i-1)*scalax,
        cvRound(graf.rows-hist.at<float>(i-1))), //Punto inicial de la linea
        Point((i)*scalax,
        cvRound(graf.rows-hist.at<float>(i))), //Punto final de la linea
        Scalar(50, 50, 255), 2); //Color BGR 50,50,255 con grosor del linea 2
  }

  imshow(title, graf);
}


int main()
{
  Mat a = imread("ciudad.jpg", CV_8UC1);
  Mat hist;
  Mat histAcum(256, 1, CV_32F, Scalar(0));
  namedWindow("imagen", WINDOW_AUTOSIZE);
  int intensidad;

  //Histograma con la funcion de opencv
  int histSize[] = {256};
  float range[] = {0, 256};
  const float *ranges[] = {range};
  calcHist(&a, 1, 0, Mat(), hist, 1, histSize, ranges); //Calcula el histograma

  //hitograma acumulativo
  histAcum.at<float>(0) += hist.at<float>(0);
  for (size_t i = 1; i < hist.rows; i++)
  {
    histAcum.at<float>(i) = histAcum.at<float>(i - 1) + hist.at<float>(i);
  }


  plotHist(hist, "Histo");
  plotHist(histAcum, "Acum");

  imshow("imagen", a);
  waitKey(0); //Espera una tecla despues de 0 milisegundos
  destroyAllWindows();
  return 0;
}
