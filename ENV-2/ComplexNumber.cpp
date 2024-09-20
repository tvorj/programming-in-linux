#include "ComplexNumber.hpp"

ComplexNumber::ComplexNumber(double real_part, double imaginary_part ): rpart(real_part), impart(imaginary_part){}

void ComplexNumber::set_num(double real_part, double imaginary_part){
	rpart = real_part;
	impart = imaginary_part;
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& obj){
	os<< obj.rpart << " + " << obj.impart<<"* i"<<std::endl;
	return os;
}

double ComplexNumber::abs_val()const{
	return sqrt(pow(rpart,2) + pow(impart,2));
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& other)const{
	ComplexNumber temp(rpart + other.rpart, impart + other.impart);
	return temp;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& other)const{
	ComplexNumber temp(rpart - other.rpart, impart - other.impart);
	return temp;
}

ComplexNumber ComplexNumber::operator*(double cvalue)const{
	ComplexNumber temp(rpart * cvalue, impart * cvalue);
	return temp;
}
