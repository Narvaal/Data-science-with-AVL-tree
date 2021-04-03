#include "Tree.h"

int main(){
	Data data[10];
	data[0].setCast("João cleber");
	data[0].setId(0);

	data[1].setCast( "cleber");
	data[1].setId(1);

	data[2].setCast("João ");
	data[2].setId(2);

	Tree rv;

	rv.insert(data[0]);
	rv.insert(data[1]);
	rv.insert(data[2]);

	rv.inOrder();
	std::cout << "\nRaiz: " << rv.getRoot()->getData().getId() << std::endl;

}