//
//
// Codé par William ISABELLE
//
// Codé par William ISABELLE
//
// Codé par William ISABELLE
//

#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<string>
#include<fstream>
using namespace cv;

char LinearDistributionGraytoChar(int grayValue)
{
	char AsciiList[] = { "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft|1?-_+~i!lI;:^`'." };
	int ValueNumber = strlen(AsciiList);
	for (int i = 1; i < ValueNumber; i++)
	{
		if (grayValue < i*(255/ValueNumber))
		{
			return AsciiList[i - 1];
		}
	}
	return '.';
}

std::string toASCII(Mat frm, int cols = 200, int rows = 60) //Respecter les proportions 4/3 si possible
{
	int IntervalWidth = frm.cols / cols;
	int IntervalHeigth = frm.rows / rows;

	int GrayValue;

	std::string AsciiImage = "";

	for (int i = 0; i < frm.rows; i+= IntervalHeigth)
	{
		for (int j = 0; j < frm.cols; j+= IntervalWidth)
		{
			GrayValue = frm.at<uint8_t>(i, j);
			AsciiImage += LinearDistributionGraytoChar(GrayValue);
		}
		AsciiImage += "\n";
	}

	return AsciiImage;
}

void WebcamToAscii(int Rows, int Cols)
{
	std::ofstream ofs("AsciiImage.txt", std::ios::out);

	VideoCapture capture(0);
	Mat frame, grayscale_Frame;
	for (;;)
	{

		capture >> frame;
		cvtColor(frame, grayscale_Frame, COLOR_BGR2GRAY);

		std::system("cls");
		std::cout << toASCII(grayscale_Frame, Rows, Cols);
		imshow("Gray image", grayscale_Frame);
		
		if (waitKey(30) >= 0) break;
	}

	ofs << toASCII(grayscale_Frame);
	ofs.close();
}

void ImageToAscii(int Rows, int Cols)
{
	std::ofstream ofs("AsciiImage.txt", std::ios::out);

	std::string filepath = "";
	std::cout << "Chemin d'acces relatif a l'image : "; std::cin >> filepath;
	Mat grayscale_Frame = imread(filepath, IMREAD_GRAYSCALE);

	for (;;)
	{
		std::system("cls");
		std::cout << toASCII(grayscale_Frame);

		imshow("Gray image", grayscale_Frame);
		if (waitKey(30) >= 0) break;
	}
	ofs << toASCII(grayscale_Frame);
	ofs.close();
}

void Run()
{
	bool ChoiceIsDone = false;
	while (!ChoiceIsDone)
	{
		std::cout << "Press 1 to : WebCam to Ascii" << std::endl;
		std::cout << "Press 2 to : Image to Ascii" << std::endl;
		int Choice; std::cin >> Choice;
		std::cout << std::endl;

		int Rows; int Cols;
		std::cout << "Dimensions de l'ascii Art ;" << std::endl;
		std::cout << "Hauteut : "; std::cin >> Rows;
		std::cout << "Largeur : "; std::cin >> Cols;

		switch (Choice)
		{
		case 1:ChoiceIsDone = true;
			WebcamToAscii(Rows, Cols);
			break;
		case 2:ChoiceIsDone = true;
			ImageToAscii(Rows, Cols);
			break;
		default:
			break;
		}
	}
}


int main()
{
	Run();
	return 0;
}
