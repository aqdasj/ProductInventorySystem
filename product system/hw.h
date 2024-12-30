//.h file
// Aqdas Juya , 11/12/2024 ,≈ ajuya@pdx.edu ,  program # 3, cs 163


#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
using namespace std;

struct Product {
	char * title;
	char * description;
	char * type;
	char * category;	
	float price;
	int quantity;
	char * seller_id;
	char * shop_name;
	int sold;
};
struct productnode {
	Product product_a;
	productnode * next;
};

class hashtable {
	public:
		hashtable(int size = 101);
		~hashtable();

		int add_product(const char *key, const Product & to_add);
		int load_file(const char * file_name);	
		int display_all() const;
		int display_category(const char *category) const;
		int retrieve_title(const char *title_find, const char * category_find, Product & result) const;
		int remove_seller(const char * seller);
		int march_product(const char *category_find, const char *title_find);
		int display_sold_items(const char *seller_id_find);
	private:
		productnode **hash_table;
		int hash_table_size;
		int hash(const char *key) const;
		int remove_all(productnode *&current);
		int remove_seller_recursive( productnode *& current, const char * seller);


};	
