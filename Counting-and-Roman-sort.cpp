#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

vector<int> *countingSort(vector<int> *A) {
	int max = A->at(0);
	int min = A->at(0);
	for (int i = 0; i < A->size(); i++) {
		if (A->at(i) > max)
			max = A->at(i);
		if (A->at(i) < min)
			min = A->at(i);
	}
	vector<int> *C = new vector<int>(max - min + 1);
	for (int i = 0; i < C->size(); i++) {
		C->at(i) = 0;
	}
	for (int i = 0; i < A->size(); i++) {
		C->at(A->at(i) - min)++;
	}
	for (int i = 1; i < C->size(); i++) {
		C->at(i) = C->at(i) + C->at(i - 1);
	}
	vector<int> *B = new vector<int>(A->size());
	for (int i = A->size() - 1; i >= 0; i--) {
		B->at(C->at(A->at(i) - min) - 1) = A->at(i);
		C->at(A->at(i) - min)--;
	}
	return B;
}
vector<int> *romanSort(vector<int> *A) {
	int max = 0;
	int min = 0;
	for (int i = 0; i < A->size(); i++) {
		if (A->at(i) > max)
			max = A->at(i);
		if (A->at(i) < min)
			min = A->at(i);
	}
	vector<int> *C = new vector<int>(max - min + 1);
	for (int i = 0; i < C->size(); i++) {
		C->at(i) = 0;
	}
	for (int i = 0; i < A->size(); i++) {
		C->at(A->at(i) - min)++;
	}
	vector<int> *B = new vector<int>(A->size());
	int counter = B->size() - 1;;
	for (int i = C->size() - 1; i >= 0; i--) {
		for (int j = C->at(i); j>0; j--) {
			B->at(counter) = i + min;
			counter--;
		}
	}
	return B;
}
vector<int> *readFile(string filename) {
		vector<int> *allInts = new vector<int>();
		ifstream myfile(filename);
		if (myfile) {
			int value;
			while (myfile >> value) {
				allInts->push_back(value);
			}
			myfile.close();
			return allInts;
		}
		else {
			cout << "File can't be opened";
			exit(0);
		}
}
void outputFile(vector<int> *B) {
		ofstream myfile("out.txt");
		if (myfile) {
			for (int i = 0; i < B->size(); i++) {
				myfile << B->at(i) << " ";
			}
			myfile.close();
		}
		else {
			cout << "File can't be typed into!" << endl;
		}
}

int main(int argc, char** argv) {
	if (argc == 3) {
		if (strcmp(argv[1], "0") == 0) {
			try {
				outputFile(countingSort(readFile(argv[2])));
			}
			catch (exception ex) {
				cout << "erroe" << endl;
			}
		}
		else if (strcmp(argv[1], "1") == 0) {
			outputFile(romanSort(readFile(argv[2])));
		}
		else {
			cout << "2. argument mora biti 0 ali 1" << endl;
		}
	}
	else
		cout << "Neveljavni argumenti: uvrg-vaja1 x y, kjer je x 0 ali 1(0-Counting sort, 1-Roman sort) in y pot do datoteke." << endl;
	system("PAUSE");
	return 0;
}