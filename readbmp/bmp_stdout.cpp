#include<bits/stdc++.h>
using std::fstream;

// unsigned char	1
// unsigned short	2
// unsigned long	4
// unsigned int		4

/*
also see
http://blog.xuite.net/edxid/note/18088900-%E4%BD%BF%E7%94%A8C%2B%2B%E5%AD%98%E5%8F%96BMP%E6%AA%94%E6%A1%88
https://en.wikipedia.org/wiki/BMP_file_format
*/
void copy_file(fstream &FileIn, fstream &FileOut){
	FileIn.seekp(2);
	int size;
	FileIn.read((char *)&size, 4);
	char *tmp = new char[size];
	FileIn.seekp(0);
	FileIn.read(tmp, 54);
	FileOut.seekp(0);
	FileOut.write(tmp, 54);

	printf("%d\n", size);
	delete tmp;

}
char  pic[2000][2000][3]; // to avoid stack overflow

void read_data(int &w, int &h, fstream &FileIn){
	// read w h
	FileIn.seekp(18);
	FileIn.read((char *)&w, 4);
	FileIn.read((char *)&h, 4);
	//printf("%d %d\n", w, h);
	if (w >= 2000 || h >= 2000){
		puts("it is too big ");
		exit(0);
	}
	/*FileIn.seekp(10);
	FileIn.read((char *)&offset, 4);
	printf("%d\n", offset);*/	
	
	int com;
	short bpp;
	FileIn.seekp(28);
	FileIn.read((char *)&bpp, 2);
	//printf("%d\n",(int) bpp);
	if (bpp != 24){
		puts("noway is not 24 bit per pixel");
		exit(0);
	}
	FileIn.read((char *)&com, 4);
	//printf("%d\n", com);
	if (com){
		puts("noway it is compressed");
		exit(0);
	}
	// read raw data

	FileIn.seekp(54);

	for (int i = 0; i < h; ++i){
		for (int j = 0; j < w; ++j)
			FileIn.read((char *)pic[i][j], 3);
		//The size of each row is rounded up to a multiple of 4 bytes (a 32-bit DWORD) by padding.
		char more[5];
		FileIn.read(more, (4 - (3 * w) % 4) % 4);
	}
}

void testforbasic(){	
	fstream FileIn , FileOut;
	FileIn .open("YEE.bmp", std::ios::in  | std::ios::binary);
	FileOut.open("YEEouter.bmp" , std::ios::out | std::ios::binary);

	if (!FileIn.is_open()){
		puts("Oh no ...");
		scanf("%*d");
		return ;
	}
	copy_file(FileIn,FileOut);
	int w, h;
	read_data(w, h, FileIn);

	//output to test it
	char zero[5];
	memset(zero, 0, sizeof(0));

	FileOut.seekp(54);
	for (int i = 0; i < h; ++i){
		//for (int i = h - 1; i >= 0;--i){
		for (int j = w - 1; j >= 0; --j)
			//for (int j = 0; j < w;++j)
			FileOut.write((char *)pic[i][j], 3);
		//The size of each row is rounded up to a multiple of 4 bytes (a 32-bit DWORD) by padding.
		FileOut.write(zero, (4 - ( 3 * w) % 4)%4);
	}
			
	FileIn.close();
	FileOut.close();
	//system("YEEouter.bmp");
	scanf("%*d");
}

char wordcolor[13] = {" .^*I7OXH#NM"};//12 levels



int main(int argc,char **argv){
	
	//testforbasic(); return 0;
	fstream FileIn;
	//drag your bmp file to the exe and you will find the picture i converted
	if (argc==1)
		FileIn.open("YEE.bmp", std::ios_base::in | std::ios_base::binary);
	else{
		puts("Warning it is for BMP format with 24bits per pixel and not compressed one");

		FileIn.open(argv[1], std::ios_base::in | std::ios_base::binary);
		printf("%s\n", argv[1]);
		if (strlen(argv[1])>=4 &&((std::string)argv[1]).compare(strlen(argv[1]) - 4,4, ".bmp") != 0){
			puts("this is not bmp");
			scanf("%*d");
			return 0;
		}
	}	
	if (!FileIn.is_open()){
		puts("Oh no ...");
		scanf("%*d");
		return 0;
	}
	
	
	// main covert picure to stdoutput
	int w, h;
	read_data(w, h, FileIn);

	int scw=70, sch=40; // for std output
	int wgap = w / scw, hgap = h / sch;
	// it is upsidedown  .... why ?
	for (int i = std::min(hgap*sch,h-1); i >=0; i-=hgap,puts(""))
		for (int j = 0; j < w; j += wgap){
			long long int ti=0,color[3];
			color[0] = color[1] = color[2] = 0;
			for (int a = 0; a < hgap && i+a < h;++a)
				for (int b = 0; b < wgap && j + b < w; ++b){
					for (int k = 0; k < 3; ++k)
						color[k] += pic[i + a][j + b][k];
					ti++;
				}
			std::sort(color, color + 3);
			// use the definition of V of HSV
			// the max is 255 and convert to 12 levels
			putchar(wordcolor[std::max((long long int)0,std::min(( color[2] )/ti/25  ,(long long int)11))]);
		}


	scanf("%*d");

	return 0;
}
