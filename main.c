#include "text.h"
#include "raycaster.h"

int main()
{
	*(unsigned long*)0x4000000 = 0x403; // mode3, bg2 on 

	//tput(120,80,"J'irai jolie qualite prose!");
	render();

	return 0;
}
