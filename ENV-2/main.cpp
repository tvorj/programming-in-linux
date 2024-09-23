#include <iostream>
#include <stdlib.h>
#include "ComplexNumber.hpp"
#include "sortByAbsValue.hpp"
int main(){
	ComplexNumber* arr = new ComplexNumber[5];
	arr[0].set_num(1,2);
	arr[1].set_num(1, 0);
	arr[3].set_num(5,1);
	arr[4].set_num(2,2);
	for(std::size_t i = 0; i < 5; i++){
		std::cout<<arr[i];
	}
	std::cout<<"After sort"<<std::endl;
	sortByAbsValue(arr, 5);
	for(std::size_t i = 0; i < 5; i++){
		std::cout<<arr[i];
		std::cout<<std::endl;
	}
	delete[] arr;	
	std::cout<<"Worked well"<<std::endl;
	return 0;
}
