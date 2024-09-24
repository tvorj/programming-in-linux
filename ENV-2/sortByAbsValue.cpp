#include "sortByAbsValue.hpp"
#include <iostream>

//bubble sort for ComplexNumber arrays
void sortByAbsValue(ComplexNumber* arr, std::size_t size){
	bool swapped;
	for(std::size_t i = 0; i < size - 1; i++){
		swapped = false;
		for(std::size_t j = 0; j < size - i - 1; j++){
			if(arr[j].abs_val() > arr[j+1].abs_val()){
				std::swap(arr[j], arr[j+1]);
				swapped = true;
			}
		}
		if(swapped == false){
			break;
		}
	}
}
