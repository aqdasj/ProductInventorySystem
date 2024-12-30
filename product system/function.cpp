// Aqdas Juya , 11/13/2024 ,≈ ajuya@pdx.edu ,  program # 3, cs 13 
//function.cpp file:
#include "hw.h"

hashtable::hashtable(int size ){

	hash_table = new productnode *[size];

	for(int i = 0; i< size; ++i) {
		hash_table[i] = nullptr;
	}
	hash_table_size = size;
}

int hashtable::hash(const char *key) const{
	if(!key) return 0;

	int count = 0;
	int length = strlen(key);
	const int prime = 31;
	for(int i = 0; i < length; ++ i){
		count = (count * prime+ tolower(key[i])) % hash_table_size;
		if (count < 0) count += hash_table_size;
	}
	return count;

}
int hashtable::add_product(const char *key, const Product & to_add){
	
	if(!key) return 0;  

	int index = hash(key);
	
	productnode *temp = new productnode;
	if(!temp) return 0;

	temp -> product_a.title = new char[strlen(to_add.title) +1];
	strcpy(temp -> product_a.title, to_add.title);

        temp -> product_a.description = new char[strlen(to_add.description) +1];
        strcpy(temp -> product_a.description, to_add.description);

	temp -> product_a.category = new char[strlen(to_add.category) +1];
        strcpy(temp -> product_a.category, to_add.category);

	temp -> product_a.type = new char[strlen(to_add.type) +1];
        strcpy(temp -> product_a.type, to_add.type);

	temp -> product_a.seller_id = new char[strlen(to_add.seller_id) +1];
        strcpy(temp -> product_a.seller_id, to_add.seller_id);

	temp -> product_a.shop_name = new char[strlen(to_add.shop_name) +1];
        strcpy(temp -> product_a.shop_name, to_add.shop_name);
	
	temp -> product_a.price = to_add.price;
	temp -> product_a.quantity = to_add.quantity;
	temp -> product_a.sold = to_add.sold;

	temp -> next = hash_table[index];
	hash_table[index] = temp;
	return 1;


}

int hashtable::load_file(const char * file_name){

	ifstream file(file_name);
	const int MAX = 100;
	int count = 0;

	if(!file) {
		cout << " cannot open the file: " << file_name << endl;
		return 0;
	}


	Product to_add;

	to_add.title = new char[MAX];
	to_add.description = new char [MAX];
	to_add.category = new char [MAX];
	to_add.type = new char [MAX];
	to_add.seller_id = new char[MAX];
	to_add.shop_name = new char[MAX];


	while( file.get(to_add.title, MAX, '|')) {
		 file.ignore(MAX,'|');

		 file.get(to_add.description, MAX, '|');
		 file.ignore(MAX,'|');

		 file.get(to_add.category, MAX, '|');
		 file.ignore(MAX,'|');

		 file.get(to_add.type, MAX, '|');
		 file.ignore(MAX,'|');

		 file >> to_add.price;
                 file.ignore(MAX, '|');

		 file >> to_add.quantity;
                 file.ignore(MAX, '|');	 
		 
		 file.get(to_add.seller_id, MAX, '|');
		 file.ignore(MAX,'|');
		 
		 file.get(to_add.shop_name, MAX, '\n');
                 file.ignore(MAX,'\n');
		 
		 to_add.sold =1;


		 add_product(to_add.category, to_add); 
		 ++count;
	 }
	file.close();

	return count;
}


int hashtable::display_all()const{
	if (!hash_table) {
		return 0;
	}
	bool has_data = false;
	for(int i=0; i <hash_table_size; ++i) {
		productnode * current = hash_table[i];
		
		if(current){ 
			has_data = true;
		
			while(current) {
				cout << "Title: " << current ->product_a.title <<endl
				     << "Discription: " << current ->product_a.description << endl
			             << "category: " << current ->product_a.category <<endl
			     	     << "type: " << current ->product_a.type <<endl
			     	     << "Price: " << current ->product_a.price <<endl
				     << "quantity: " << current ->product_a.quantity <<endl
				     << "seller id: " << current ->product_a.seller_id <<endl
				     << "shop name: " << current ->product_a.shop_name <<endl;
			        cout << " -----------------------------------" << endl; 
				current = current -> next;
		
			}
			cout << endl;
		}
	
	}
	if(!has_data) {
		cout << "no data to display in any bucket." << endl;
	}
	return 1;	
}
int hashtable::display_category(const char *category) const{

	if(!category ) { 
		cout << "Invalid category input." << endl;
		return 0;
	}
	bool found = false; 
	for(int i = 0; i < hash_table_size; ++i) {
		productnode * current = hash_table[i];

		while (current) {
			if(strcmp(current -> product_a.category, category) == 0) {
				if(!found) {
					cout << "products in category: " << category << endl;
					found = true;
				}
				cout << "Title: " << current ->product_a.title <<endl
                                     << "Discription: " << current ->product_a.description << endl
                                     << "category: " << current ->product_a.category <<endl
                                     << "type: " << current ->product_a.type <<endl
                                     << "Price: " << current ->product_a.price <<endl
                                     << "quantity: " << current ->product_a.quantity <<endl
                                     << "seller id: " << current ->product_a.seller_id <<endl
                                     << "shop name: " << current ->product_a.shop_name <<endl;
                                cout << " -----------------------------------" << endl;
			}
			current = current -> next;
		}
	}
	if(!found) {
		cout << "No products found in the category: " << category << endl;
		return 0;
	}
	return 1;

}  
int hashtable::retrieve_title(const char *title_find, const char * category_find, Product & result) const{
	if(!title_find || title_find[0] == '\0' || !category_find || category_find[0] == '\0'){
		return 0;
	}

	int index = hash(category_find);
	if(index < 0 || index >= hash_table_size|| !hash_table[index]) {
		return 0;
	}

	productnode * current = hash_table[index];

	while(current) {
		if(strcmp(current -> product_a.title, title_find) == 0 && strcmp(current -> product_a.category, category_find) == 0){
			


			result.title = new  char[strlen(current -> product_a.title) +1];
			strcpy(result.title, current -> product_a.title);

			result.description = new char[strlen(current -> product_a.description) +1];
                        strcpy(result.description, current -> product_a.description);


			result.category = new char[strlen(current -> product_a.category) +1];
                        strcpy(result.category, current -> product_a.category);

			result.type = new char[strlen(current -> product_a.type) +1];
                        strcpy(result.type, current -> product_a.type);

			result.seller_id = new char[strlen(current -> product_a.seller_id) +1];
			strcpy(result.seller_id, current -> product_a.seller_id);

       
		       	result.shop_name = new char[strlen(current -> product_a.shop_name) +1];
			strcpy(result.shop_name, current -> product_a.shop_name);

			result.price = current -> product_a.price;
		       	result.quantity = current ->product_a.quantity;
			result.sold = current ->product_a.sold;
			return 1;
		}
		current = current -> next;
	}
	return 0;
}
int hashtable::remove_seller(const char * seller){
	if( seller == nullptr || *seller == '\0') {
		return 0;
	}
	int total_removed = 0;
	for(int i = 0; i < hash_table_size; ++i) {
		total_removed += remove_seller_recursive(hash_table[i], seller);
	}
	return total_removed;
}

int hashtable::remove_seller_recursive( productnode *& current, const char * seller) {
	if(!current) return 0;

	if (strcmp(current -> product_a.seller_id, seller) == 0) {
		productnode* remove = current;
		current = current -> next;
		delete[] remove -> product_a.title;
       		delete[] remove -> product_a.description;
        	delete[] remove -> product_a.category;
        	delete[] remove -> product_a.type;
        	delete[] remove -> product_a.seller_id;
        	delete[] remove -> product_a.shop_name;
		
		delete remove;
		return 1 + remove_seller_recursive(current, seller);
	}
	return remove_seller_recursive(current-> next, seller);
}

int hashtable::march_product(const char *category_find, const char *title_find){
	
	if(!hash_table || hash_table_size == 0 || !title_find || !category_find)  {
		return 0;
	}

	int index = hash(category_find);

	productnode * current = hash_table[index];

	while(current) {
		if(strcmp(current -> product_a.title, title_find) == 0 && strcmp(current -> product_a.category, category_find) ==0) {
			if(current -> product_a.quantity > 0) {
				current -> product_a.quantity --; //we are reducing the number by 1
				current -> product_a.sold = 1;
				return 1;
			} else {
				return 0;
			}
		}
		current = current -> next;
	}
	return 0;

}
int hashtable::display_sold_items(const char *seller_id_find) {

	if(!hash_table || !seller_id_find) {
		return 0;
	}

	bool found = false;

	for(int i = 0; i< hash_table_size; ++i) {
		productnode *current =hash_table[i];

		while(current) {
				if(current -> product_a.sold == 1 && strcmp(current-> product_a.seller_id, seller_id_find) == 0) {
					cout << "Title: " << current ->product_a.title <<endl
                                     << "Discription: " << current ->product_a.description << endl
                                     << "category: " << current ->product_a.category <<endl
                                     << "type: " << current ->product_a.type <<endl
                                     << "Price: " << current ->product_a.price <<endl
                                     << "quantity: " << current ->product_a.quantity <<endl
                                     << "seller id: " << current ->product_a.seller_id <<endl
                                     << "shop name: " << current ->product_a.shop_name <<endl;
                                     cout << " -----------------------------------" << endl;

				     found = true;
			
				}
		current = current -> next;
		}
	}
	if(!found) {
		return 0;
	}
	return 1;


}
hashtable::~hashtable() { 

	for(int i = 0; i < hash_table_size; ++i) {
		remove_all(hash_table[i]);
		hash_table[i] = nullptr;
	}
	delete[] hash_table;
	hash_table = nullptr;

}

int hashtable::remove_all(productnode *&current) {
	if( !current) return 0;
	delete[] current -> product_a.title;
	delete[] current -> product_a.description;
	delete[] current -> product_a.category;
	delete[] current -> product_a.type;
	delete[] current -> product_a.seller_id;
	delete[] current -> product_a.shop_name;

	productnode * temp = current -> next;
	delete current;
	current = nullptr;

	return 1 + remove_all(temp);


}
