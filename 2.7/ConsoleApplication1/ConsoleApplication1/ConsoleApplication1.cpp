// CPP program for iterative implementation of QuickSelect

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <regex>
#include <map>

void menu();

using namespace std;

class IPv6 {
private:
	int subnetBits;			//128-for regular IPs, otherwise from 0 to 127
	 bitset<128> address;
	 string repr;
public:
	IPv6( string newAddress, int newSubnetBits);	//stored in HEX notation
	bool checkSubnet(IPv6 subnet);
	 bitset<128> getAddress();
	int getSubnetBits();
	 string getRepr();
};

 map<char,  string> mapForIPv6{ {'0', "0000"}, {'1', "0001"},{'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"}, {'8', "1000"},
	{'9', "1001"}, {'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}, {'a', "1010"}, {'b', "1011"}, {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"} };

IPv6::IPv6( string newAddress, int newSubnetBits = 128) {
	this->repr = newAddress;
	newAddress.push_back(':');
	 regex word("\\w+\\:");
	this->subnetBits = newSubnetBits;

	 sregex_iterator currentMatch(newAddress.begin(), newAddress.end(), word);
	 sregex_iterator lastMatch;
	int iter = 0;

	while (currentMatch != lastMatch) {
		 string currStr = (*currentMatch).str();
		currStr.pop_back();
		// cout << currStr <<  endl;
		for (int i = 0; i < 4 - currStr.size(); i++) {
			for (int j = 0; j < 4; j++) {
				this->address[iter] = 0;
				iter++;
			}
		}
		for (int i = 0; i < currStr.size(); i++) {
			 string temp = mapForIPv6[currStr[i]];
			for (int j = 0; j < 4; j++) {
				this->address[iter] = int(temp[j]) - 48;
				iter++;
			}
		}
		currentMatch++;
	}
}

bool IPv6::checkSubnet(IPv6 subnet) {
	if (this->subnetBits != 128) {
		 cout << "The first address represents a subnet \n";
		return false;
	}
	 bitset<128> netAddress = this->getAddress();
	 bitset<128> subAddress = subnet.getAddress();
	for (int i = 0; i < subnet.getSubnetBits(); i++) {
		if (netAddress[i] != subAddress[i]) return false;
	}
	return true;
}

 bitset<128> IPv6::getAddress() {
	return this->address;
}

int IPv6::getSubnetBits() {
	return this->subnetBits;
}

 string IPv6::getRepr() {
	return this->repr;
}

class IPv4 {
private:
	int subnetBits;			//32-for regular IPs, otherwise from 0 to 31
	 bitset<32> address;
	 string repr;
public:
	IPv4( string newAddress, int newSubnetBits);	//stored in DEC notation
	bool checkSubnet(IPv4 subnet);
	 bitset<32> getAddress();
	int getSubnetBits();
	 string getRepr();
};

IPv4::IPv4( string newAddress, int newSubnetBits = 32) {
	this->repr = newAddress;
	newAddress.push_back('.');
	 regex word("\\d+\\.");
	this->subnetBits = newSubnetBits;

	 sregex_iterator currentMatch(newAddress.begin(), newAddress.end(), word);
	 sregex_iterator lastMatch;
	int bitBlock = 0;
	while (currentMatch != lastMatch) {
		 string currStr = (*currentMatch).str();
		currStr.pop_back();
		int currNum =  stoi(currStr);
		currStr = "";
		int iter = 256;
		do {
			iter /= 2;
			currStr.push_back(char(currNum / iter + 48));
			currNum %= iter;
		} while (iter != 1);

		for (int i = 0; i < 8; i++) {
			this->address[bitBlock * 8 + i] = int(currStr[i]) - 48;
		}
		bitBlock++;
		currentMatch++;
	}
}

bool IPv4::checkSubnet(IPv4 subnet) {
	if (this->subnetBits != 32) {
		 cout << "The first address represents a subnet \n";
		return false;
	}
	 bitset<32> netAddress = this->getAddress();
	 bitset<32> subAddress = subnet.getAddress();
	for (int i = 0; i < subnet.getSubnetBits(); i++) {
		if (netAddress[i] != subAddress[i]) return false;
	}
	return true;
}

 bitset<32> IPv4::getAddress() {
	return this->address;
}

int IPv4::getSubnetBits() {
	return this->subnetBits;
}

 string IPv4::getRepr() {
	return this->repr;
}

 vector<IPv4> IPv4s;
 vector<IPv6> IPv6s;

void menu() {
	if (IPv4s.size() == 0) {
		 cout << "No available IPv4 adresses \n";
	}
	else {
		 cout << "Available IPv4 adresses: \n";
		for (auto addr : IPv4s) {
			 cout << addr.getRepr();
			if (addr.getSubnetBits() != 32)  cout << " \\ " << addr.getSubnetBits();
			 cout <<  endl;
			/* bitset<32> tempBitset = addr.getAddress();
			for (int bit = 0; bit < 32; bit++)  cout << tempBitset[bit];
			 cout <<  endl;*/
		}


	}
	 cout <<  endl;
	if (IPv6s.size() == 0) {
		 cout << "No available IPv6 adresses \n";
	}
	else {
		 cout << "Available IPv6 adresses: \n";
		for (auto addr : IPv6s) {
			 cout << addr.getRepr();
			if (addr.getSubnetBits() != 128)  cout << " \\ " << addr.getSubnetBits();
			 cout <<  endl;
			/* bitset<128> tempBitset = addr.getAddress();
			for (int bit = 0; bit < 128; bit++)  cout << tempBitset[bit];
			 cout <<  endl;*/
		}
	}
	 cout <<  endl;
	 cout << "Press 0 to exit \n";
	 cout << "Press 1 to insert an IPv4 address \n";
	 cout << "Press 2 to check if an IPv4 address belongs to a subnet \n";
	 cout << "Press 3 to insert an IPv6 address \n";
	 cout << "Press 4 to check if an IPv6 address belongs to a subnet \n";
	int choice;
	 cin >> choice;
	switch (choice) {
	case 0: {
		break;
	}
	case 1: {
		 string tempStr;
		int tempNum;
		 cout << "Enter the address in format a.b.c.d, where a,b,c,d are decimal numbers \n";
		 cin >> tempStr;
		 cout << "Enter the subnet mask or 32 to enter a regular address: \n";
		 cin >> tempNum;
		IPv4 newIPv4(tempStr, tempNum);
		IPv4s.push_back(newIPv4);
		menu();
		break;
	}
	case 2: {
		 cout << "Choose a regular address: \n";
		for (int i = 0; i < IPv4s.size(); i++) {
			auto addr = IPv4s[i];
			 cout << i << " " << addr.getRepr();
			if (addr.getSubnetBits() != 32)  cout << " \\ " << addr.getSubnetBits();
			 cout <<  endl;
		}
		int choice1;
		 cin >> choice1;
		 cout << "Choose a subnet: \n";
		for (int i = 0; i < IPv4s.size(); i++) {
			auto addr = IPv4s[i];
			 cout << i << " " << addr.getRepr();
			if (addr.getSubnetBits() != 32)  cout << " \\ " << addr.getSubnetBits();
			 cout <<  endl;
		}
		int choice2;
		 cin >> choice2;
		 cout << "Address " << IPv4s[choice1].getRepr() << ((IPv4s[choice1].getSubnetBits() == 32) ? "" : (" /" +  to_string(IPv4s[choice1].getSubnetBits()))) << " " << ((IPv4s[choice1].checkSubnet(IPv4s[choice2])) ? "does " : "does not ");
		 cout << "belong to the subnet " << IPv4s[choice2].getRepr() << ((IPv4s[choice2].getSubnetBits() == 32) ? " " : (" / " +  to_string(IPv4s[choice2].getSubnetBits()))) <<  endl;
		menu();
		break;
	}
	case 3: {
		 string tempStr;
		int tempNum;
		 cout << "Enter the address in format a:b:c:d:e:f:g:h, where a-h are hexadecimal numbers \n";
		 cin >> tempStr;
		 cout << "Enter the subnet mask or 128 to enter a regular address: \n";
		 cin >> tempNum;
		IPv6 newIPv6(tempStr, tempNum);
		IPv6s.push_back(newIPv6);
		menu();
		break;
	}
	case 4: {
		 cout << "Choose a regular address: \n";
		for (int i = 0; i < IPv6s.size(); i++) {
			auto addr = IPv6s[i];
			 cout << i << " " << addr.getRepr();
			if (addr.getSubnetBits() != 128)  cout << " \\ " << addr.getSubnetBits();
			 cout <<  endl;
		}
		int choice1;
		 cin >> choice1;
		 cout << "Choose a subnet: \n";
		for (int i = 0; i < IPv6s.size(); i++) {
			auto addr = IPv6s[i];
			 cout << i << " " << addr.getRepr();
			if (addr.getSubnetBits() != 128)  cout << " \\ " << addr.getSubnetBits();
			 cout <<  endl;
		}
		int choice2;
		 cin >> choice2;
		 cout << "Address " << IPv6s[choice1].getRepr() << ((IPv6s[choice1].getSubnetBits() == 128) ? "" : (" /" +  to_string(IPv6s[choice1].getSubnetBits()))) << " " << ((IPv6s[choice1].checkSubnet(IPv6s[choice2])) ? "does " : "does not ");
		 cout << "belong to the subnet " << IPv6s[choice2].getRepr() << ((IPv6s[choice2].getSubnetBits() == 128) ? "" : (" / " +  to_string(IPv6s[choice2].getSubnetBits()))) <<  endl;
		menu();
		break;
	}
	default: {
		 cout << "Cannot recognize the command \n";
		menu();
		break;
	}
	}

}

int main() {

	IPv4 textIPv4("255.123.12.5");
	IPv4 subnet1v4("255.123.0.0", 16);
	IPv4 subnet2v4("123.255.0.0", 16);
	IPv4s.push_back(textIPv4);
	IPv4s.push_back(subnet1v4);
	IPv4s.push_back(subnet2v4);

	IPv6 textIPv6("ABCD:1234:EF15:91B4:DCBA:4321:51FE:4B19");
	IPv6 subnet1v6("ABCD:1234:EF15:91B4:DCBA:4321:51FE:0", 112);
	IPv6 subnet2v6("ABCD:1234:EF15:91B4:DCBA:4321:FE:0", 112);
	IPv6s.push_back(textIPv6);
	IPv6s.push_back(subnet1v6);
	IPv6s.push_back(subnet2v6);
	menu();
}