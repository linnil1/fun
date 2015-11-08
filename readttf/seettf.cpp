#include<bits/stdc++.h>


int main(){
	std::fstream f;
	f.open("Minecraft.ttf",std::ios::binary | std::ios::in);
	if( !f.is_open() )
		puts("no");
	unsigned char c;
	int t=1;
	f.seekg(0);
	while( f.read((char *)&c , 1 )){
		printf("%02x ",(int)c);
		if(t++%32==0)
			puts("");
	}
	return 0;
};
