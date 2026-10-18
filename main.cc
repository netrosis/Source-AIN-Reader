#include "NodeGraph/AIN.h"

int main(){
	printf("Valve AIN reader!\n");
	NodeGraph nodes;
	if(nodes.loadAIN("gm_construct.ain")){
		nodes.printNodes();
		nodes.printLinks();
	}
}