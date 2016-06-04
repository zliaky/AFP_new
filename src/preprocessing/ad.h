#ifndef __AD__
#define __AD__

#include "defines.h"

class Ad {
public:
	int creative_id;
	string category_id;
	string series_id;
	string advertiser_id;
	int product_type;
	string product_id;

	string img_url;
	string dest_url;
	string literal;

	string dirname;
	string filename;

	int creative_id_map;
	int category_id_map;
	int series_id_map;
	int advertiser_id_map;
	int product_type_map;
	int product_id_map;
	int literal_map;
};

#endif
