#include <iostream>
#include <string>
#include <sstream>
#include <exception>
//#include <regex>
#include <locale>	

struct FourOctets {
	bool isValid;
	int octets[ 4 ];
};
		
FourOctets getOctets( const std::string & textLine ) {
	std::string testLine( textLine );

	// заводим структуру октетов 
	FourOctets answer;
	answer.isValid = false;
	for(int i=0; i<4; i++) {
		answer.octets[i] = -1;
	}
	// --------------------------

	// если встретили символ - выходим
	/*for (int i=0; i < testLine.length(); i++) {
			if (isalpha((unsigned int)testLine[i])) {
				return answer;
			}
	}*/
	// --------------------------

	size_t foundOffset = 0;
	size_t numberOfDots = 0;

	// разбиваем по точкам
	while ( ( foundOffset = testLine.find( '.' ) ) != std::string::npos ) { 
		testLine.replace( foundOffset, 1, 1, ' ' );
		numberOfDots++;
	}
	// --------------------------
	
	if( numberOfDots == 3 ) {
		std::stringstream ss( testLine );
		ss.exceptions( std::ios::failbit | std::ios::badbit );
		int *octets = answer.octets;
		try {
			ss >> octets[ 0 ] >> octets[ 1 ] >> octets[ 2 ] >> octets[ 3 ];
			if(octets[0] > 255 || octets[1] > 255 || octets[2] > 255 || octets[3] > 255 || octets[0] < 0 || octets[1] < 0 || octets[2] < 0 || octets[3] < 0) {
				answer.isValid = false;
			} else {
				answer.isValid = true;
			}
		} catch (...) {
			answer.isValid = false;
		}
	}
	return answer;
}
		
int main(void) {
	setlocale(LC_ALL, "Russian");
	std::string inputString;
	while( getline (std::cin, inputString) ) {
		FourOctets ipAddress = getOctets( inputString );
		if( ipAddress.isValid ) {
			if( ipAddress.octets[ 0 ] <= 127 ) std::cout << "A" << std::endl;
			if( ipAddress.octets[ 0 ] >= 128 && ipAddress.octets[ 0 ] <= 191 ) std::cout << "B" << std::endl;
			if( ipAddress.octets[ 0 ] >= 192 && ipAddress.octets[ 0 ] <= 223 ) std::cout << "C" << std::endl;
			if( ipAddress.octets[ 0 ] >= 224 && ipAddress.octets[ 0 ] <= 239 ) std::cout << "D" << std::endl;
			if( ipAddress.octets[ 0 ] >= 240 && ipAddress.octets[ 0 ] <= 255 ) std::cout << "E" << std::endl;
		} else {
			std::cout << "X" << std::endl;		
		}
	}
	return 0;
}