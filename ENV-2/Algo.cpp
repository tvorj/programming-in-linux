#include "Algo.hpp"
#include <iostream>

void Algo(ComplexNumber* arr, std::size_t size){
	bool key;
	for(std::size_t i = 0; i < size - 1; i++){
		key = false;
		for(std::size_t j = 0; j < size - i - 1; j++){
			if(arr[j].abs_val() > arr[j+1].abs_val()){
				std::swap(arr[j], arr[j+1]);
				key = true;
			}
		}
		if(key == false){
			break;
		}
	}
}
