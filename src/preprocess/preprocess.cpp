#include "defines.h"
#include "data.h"

// Train size = 112248
// Test size = 56355

vector<Data*> train;
vector<Data*> test;

map<string, int> qq;
map<string, int> image;
map<string, int> literal;
map<string, int> category_id;
map<string, int> series_id;
map<string, int> advertiser_id;
map<string, int> product_id;

int destroy(vector<Data*> &dataset) {
	for (int i = 0; i < dataset.size(); ++i) {
		delete dataset[i]->user;
		delete dataset[i]->ad;
		delete dataset[i]->feedback;
		delete dataset[i];
	}
	dataset.clear();
	return 0;
}

bool isnumber(string &s) {
	for (int i = 0; i < s.length(); ++i) {
		if ((s[i] < '0') || (s[i] > '9')) {
			return false;
		}
	}
	return true;
}

string int2str(int x) {
	stringstream ss;
	string s;
	ss << x;
	ss >> s;
	return s;
}

int str2int(string &s) {
	stringstream ss;
	int x;
	ss << s;
	ss >> x;
	return x;
}

int load(string filename, vector<Data*> &dataset, bool istrain) {
	ifstream fin;
	fin.open(filename.data());
	if (!fin) {
		cerr << "Loading '" << filename << "' failed!" << endl;
		return -1;
	}
	ifstream fpic;
	string str;
	dataset.clear();
	while (!fin.eof()) {
		str = "";
		fin >> str;
		if (str == "") {
			break;
		}
		Data *data = new Data();

		User *user = new User();
		user->qq = str;
		assert(qq.find(user->qq) != qq.end());
		user->qq_map = qq[user->qq];
		fin >> user->gender >> user->year >> user->surf_scene >> user->marriage_status >> user->education >> user->profession;
		data->user = user;

		Ad *ad = new Ad();
		fin >> ad->creative_id >> ad->category_id >> ad->series_id >> ad->advertiser_id >> ad->product_type;
		assert(category_id.find(ad->category_id) != category_id.end());
		ad->category_id_map = category_id[ad->category_id];
		assert(series_id.find(ad->series_id) != series_id.end());
		ad->series_id_map = series_id[ad->series_id];
		assert(advertiser_id.find(ad->advertiser_id) != advertiser_id.end());
		ad->advertiser_id_map = advertiser_id[ad->advertiser_id];
		if (ad->product_type < 25) {
			fin >> ad->product_id;
		}
		else {
			ad->product_id = "0";
		}
		assert(product_id.find(ad->product_id) != product_id.end());
		ad->product_id_map = product_id[ad->product_id];
		if (ad->product_type == 3) {
			ad->product_type_map = 0;
		}
		else if (ad->product_type == 12) {
			ad->product_type_map = 1;
		}
		else if (ad->product_type == 19) {
			ad->product_type_map = 2;
		}
		else if (ad->product_type == 22) {
			ad->product_type_map = 3;
		}
		else if (ad->product_type == 25) {
			ad->product_type_map = 4;
		}
		else if (ad->product_type == 26) {
			ad->product_type_map = 5;
		}
		else if (ad->product_type == 1000) {
			ad->product_type_map = 6;
		}
		else {
			cout << ad->product_type << endl;
			assert(false);
		}
		fin >> ad->img_url;
		fin >> str;
		if (str.substr(0, 4) != "http") {
			ad->literal = str;
		}
		else {
			ad->dest_url = str;
			fin >> ad->literal;
		}
		while (1) {
			fin >> str;
			if (isnumber(str)) {
				break;
			}
			ad->literal = ad->literal + " " + str;
		}
		assert(literal.find(ad->literal) != literal.end());
		ad->literal_map = literal[ad->literal];
		data->ad = ad;

		ad->dirname = "../../images/";
		ad->filename = int2str(ad->creative_id) + ".jpg";
		fpic.open((ad->dirname + ad->filename).data());
		if (!fpic) {
			cerr << "'" << ad->dirname + ad->filename << "'" << " does not exist!" << endl;
			return -1;
		}
		fpic.close();
		assert(image.find(ad->filename) != image.end());
		ad->creative_id_map = image[ad->filename];

		Feedback *feedback = new Feedback();
		feedback->imp_time = str2int(str);
		feedback->imp_time_map = feedback->imp_time - 1458110274;
		fin >> feedback->pos_id;

		if (feedback->pos_id / 100 == 720631310737625) {
			feedback->pos_id_map = 0;
		}
		else if (feedback->pos_id / 100 == 1441207251116904) {
			feedback->pos_id_map = 1;
		}
		else if (feedback->pos_id / 100 == 2161783191496183) {
			feedback->pos_id_map = 2;
		}
		else if (feedback->pos_id / 100 == 2882359131875463) {
			feedback->pos_id_map = 3;
		}
		else {
			assert(false);
		}

		if (istrain) {
			fin >> feedback->click_num;
		}
		data->feedback = feedback;

		dataset.push_back(data);
	}
	fin.close();
	cout << "Size = " << dataset.size() << endl;
	return 0;
}

int load_map(string filename, map<string, int> &m) {
	ifstream fin;
	fin.open(filename.data());
	if (!fin) {
		cerr << "Loading '" << filename << "' failed!" << endl;
		return -1;
	}
	int cnt = 0;
	while (!fin.eof()) {
		string s = "";
		getline(fin, s);
		if (s == "") {
			break;
		}
		m[s] = cnt;
		++cnt;
	}
	fin.close();
	cout << "Size = " << m.size() << endl;
	return 0;
}

int save(string filename, vector<Data*> &dataset, bool istrain) {
	ofstream fout;
	fout.open(filename.data());
	for (int i = 0; i < dataset.size(); ++i) {
		Data *data = dataset[i];
		User *user = data->user;
		Ad *ad = data->ad;
		Feedback *feedback = data->feedback;
		fout << user->qq_map << ", " << user->gender << ", " << user->year << ", " << user->surf_scene << ", " << user->marriage_status << ", " << user->education << ", " << user->profession << ", ";
		fout << ad->literal_map << ", " << ad->creative_id_map << ", " << ad->category_id_map << ", " << ad->series_id_map << ", " << ad->advertiser_id_map << ", " << ad->product_type_map << ", " << ad->product_id_map << ", ";
		fout << feedback->imp_time_map << ", " << feedback->pos_id_map;
		if (istrain) {
			fout << ", " << feedback->click_num;
		}
		fout << endl;
	}
	fout.close();
	return 0;
}

int save_map(string filename, vector<string> &v) {
	ofstream fout;
	fout.open(filename.data());
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); ++i) {
		fout << v[i] << endl;
	}
	fout.close();
	return 0;
}

int main() {
	load_map("../txt/qq.txt", qq);
	load_map("../txt/image.txt", image);
	load_map("../txt/literal.txt", literal);
	load_map("../txt/category_id.txt", category_id);
	load_map("../txt/series_id.txt", series_id);
	load_map("../txt/advertiser_id.txt", advertiser_id);
	load_map("../txt/product_id.txt", product_id);
	load("../../data/train11w.data", train, true);
	load("../../data/test5w.data", test, false);
	save("../txt/train.txt", train, true);
	save("../txt/test.txt", test, false);
	destroy(train);
	destroy(test);
	return 0;
}
