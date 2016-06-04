#include "defines.h"

vector<string> literals;
vector<string> dictionary;

int load(string filename, vector<string> &literals) {
	ifstream fin;
	fin.open(filename.data());
	if (!fin) {
		cerr << "Loading '" << filename << "' failed!" << endl;
		return -1;
	}
	literals.clear();
	string literal;
	while (!fin.eof()) {
		getline(fin, literal);
		if (literal == "") {
			break;
		}
		literals.push_back(literal);
	}
	cout << "Size = " << literals.size() << endl;
	fin.close();
	return 0;
}

int load_dictionary(string filename, vector<string> &dictionary) {
	ifstream fin;
	fin.open(filename.data());
	if (!fin) {
		cerr << "Loading '" << filename << "' failed!" << endl;
		return -1;
	}
	dictionary.clear();
	string word;
	while (!fin.eof()) {
		word = "";
		fin >> word;
		if (word == "") {
			break;
		}
		dictionary.push_back(word);
	}
	cout << "Size = " << dictionary.size() << endl;
	fin.close();
	return 0;
}

int save_vector(string filename, vector<string> &literals, vector<string> &dictionary) {
	ofstream fout;
	fout.open(filename.data());
	for (int i = 0; i < literals.size(); ++i) {
		if (i % 1000 == 0) {
			cout << "Now " << i << endl;
		}
		for (int j = 0; j < dictionary.size(); ++j) {
			string s = literals[i];
			int flag = 0;
			while (1) {
				int pos = s.find(dictionary[j]);
				if (pos >= s.length()) {
					break;
				}
				fout << j << " ";
				s = s.substr(pos + 1, s.length());
			}
		}
		fout << -1 << endl;
	}
	fout.close();
	return 0;
}

int main() {
	load("../txt/literal.txt", literals);
	load_dictionary("../txt/dictionary.txt", dictionary);
	save_vector("../txt/vector_literal.txt", literals, dictionary);
	return 0;
}
