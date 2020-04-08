#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
//Para compilar
//g++ -o histograma_video histograma_video.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
void plotHist(Mat &hist, const char* title)
{
  //Grafica los histogramas
  Mat graf(800, 1024, CV_8UC3, Scalar(50, 50, 50));

  int scalax = cvRound(graf.cols/255);
  normalize(hist, hist, 0, graf.rows, NORM_MINMAX);
  for (size_t i = 1; i < hist.rows; i++)
  {
    line(graf, Point((i-1)*scalax,
        cvRound(graf.rows-hist.at<float>(i-1))),
        Point((i)*scalax,
        cvRound(graf.rows-hist.at<float>(i))),
        Scalar(50, 50, 255), 2);
  }

  imshow(title, graf);
}


int main()
{
  //Entrada de video por webcam 0
  VideoCapture cap(0);
  namedWindow("hist", WINDOW_AUTOSIZE);
  namedWindow("video", WINDOW_NORMAL);


  if(!cap.isOpened()) return 0;

  //Obtiene los fps y el retardo
  double fps = cap.get(CAP_PROP_FPS);
  int retardo = cvRound(1000/fps);

  //Matrices del frame y el histo
  Mat hist;
  Mat frame;

  //Variables para la función calcHist
  int histSize[] = {256};
  float range[] = {0, 256};
  const float *ranges[] = {range};

  while(1) //Para recorrer todos los frames del video
  {
    //Llena de ceros el histograma, para limpiarlo y tener fondo negro
    hist = 0;
    //Obtiene la imagen del video
    cap.read(frame);
    //cap >> frame; //Otra forma de obtener la imagen del video

    if (frame.empty()) break; //Sale en caso de que no se lean los frames
    cvtColor(frame, frame, COLOR_BGR2GRAY); //Convierte el frame a escala de grises

    calcHist(&frame, 1, 0, Mat(), hist, 1, histSize, ranges); //Calcula el histograma

    plotHist(hist, "hist"); //Grafica el histograma
    imshow("video", frame); //Muestra el frame del video
    if(waitKey(retardo) > 0) break; //Hace el retardo en milisegundos y pregunta por una tecla


  }
  cap.release(); //Libera la entrada de audio
  destroyAllWindows();
  return 0;
}
