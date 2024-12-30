// Aqdas Juya , 11/12/2024 ,≈ ajuya@pdx.edu ,  program # 3, cs 163
//main.cpp file
#include "hw.h"


const int MAX {100};

int main () 
{
	hashtable table(100);
	char choice;

	do {
		cout <<  "    menue choice " << endl;
		cout << "1. add a new product" << endl;
		cout << "2. load from data file" << endl;
		cout << "3. display all" << endl;
		cout << "4. display by catagory" << endl;
                cout << "5. retrive by name" << endl;
		cout << "6. delete by seller number" << endl;
		cout << "7. sold the items by category or name" << endl;
		cout << "8. display the sold items" << endl;
		cout << "9. exit " << endl;



		cout << " Enter your choice: ";
		cin >> choice;
		cin.ignore(MAX, '\n');

		if (choice == '1') {
			Product new_product;


			new_product.title = new char[MAX];
			new_product.description = new char[MAX];
			new_product.type = new char[MAX];
			new_product.seller_id = new char[MAX];
			new_product.shop_name= new char[MAX];
			new_product.category = new char[MAX];

			cout <<" Enter product title: ";
			cin.get (new_product.title, MAX, '\n');
			cin.ignore(MAX,'\n');

			cout <<" Enter product description: ";
                        cin.get (new_product.description, MAX, '\n');
                        cin.ignore(MAX,'\n');

			cout <<" Enter product is category: ";
                        cin.get (new_product.category, MAX, '\n');
                        cin.ignore(MAX,'\n');

			cout <<" Enter product type: ";
                        cin.get (new_product.type, MAX, '\n');
                        cin.ignore(MAX,'\n');

			cout <<" Enter product seller id: ";
                        cin.get (new_product.seller_id, MAX, '\n');
                        cin.ignore(MAX,'\n');

			cout <<" Enter product shop name: ";
                        cin.get (new_product.shop_name, MAX, '\n');
                        cin.ignore(MAX,'\n');

			cout <<" Enter product price (please only enter number): ";
                        cin >> new_product.price;
                        cin.ignore(MAX,'\n');

			cout <<" Enter product quantity  (please only enter number): ";
                        cin >> new_product.quantity;
                        cin.ignore(MAX,'\n');

			cout <<" Enter if the product is sold(0 for sold, 1 for not sold): ";
                        cin >> new_product.sold;
                        cin.ignore(MAX,'\n');

			if(table.add_product(new_product.type, new_product)) {
				cout << "Everthing was added seccessfully." << endl;
			} else {
				cout <<"Failed to add everthing." << endl;
			}
		}else if (choice == '2') { 
			int count = table.load_file("products.txt");
			if (count > 0) {
				cout<< count << "products loaded!"<<  endl;
				
			} else {
				cout << "No products loaded from file. " << endl;
			}	
			
		} else if (choice == '3') {
			table.display_all();		
		} else if (choice == '4') {
			char category_input[100];
			cout << "enter category: ";
			cin.get(category_input, 100);
			cin.ignore();
			table.display_category(category_input);
		
		} else if( choice == '5') {
			char title_input[100];
			char category_input[100];

			Product result;

			cout << "Enter the title of the product you want to retrive: ";
			cin.get(title_input, 100);
			cin.ignore(1000, '\n');

			cout << "Enter the category of the product you want to retrieve: ";
			cin.get(category_input, 100);
			cin.ignore(1000, '\n');
			
			if(strlen(title_input) == 0|| strlen (category_input) ==0) {
				cout << "invalid input. " << endl;
				return 0;
			}


			if(table.retrieve_title(title_input,category_input, result)){
				cout << "Product found:" << endl;
				cout << "title: "<< result.title << endl
				     << "Description: " << result.description << endl
				     << " category: " << result.category << endl
				     << " type: " << result.type << endl
				     << " price: " << result.price<< endl
				     << " quantity: " << result.quantity << endl
				     << " seller id: " << result.seller_id << endl
				     << " shop name: " << result.shop_name << endl;
			} else {
				cout << " no prudect found in category: " << category_input << "with title: " <<title_input << endl;
			}
		}else if (choice == '6') {
				char seller_number[MAX];
				cout << "enter the seller if to delete all the sold items: ";
				cin.get(seller_number, MAX);
				cin.ignore(MAX, '\n');

				int sold_count = table.remove_seller(seller_number);
				if(sold_count > 0) {
					cout << " this is how many seller id's you have removed: " << sold_count<< endl;
				} else {
					cout << "You have not removed any seller id's" << endl;
				}

		} else if (choice == '7') {
			char category[MAX];
			char title[MAX];

			cout << "Enter the product category: ";
			cin.get(category, MAX, '\n');
		       	cin.ignore(MAX,'\n');

			cout << "Enter the product title: ";
                        cin.get(title, MAX, '\n');
                        cin.ignore(MAX,'\n');
			
			int sold_or_not = table.march_product(category, title);

			if(sold_or_not == 1) {
				cout <<" purchese succesfly." << endl;
			}else {
				cout << " purchase faild." << endl;
			}
		}else if (choice == '8'){
			char seller_id[MAX];

			cout <<" Enter the seller ID: ";
			cin.get(seller_id, 100, '\n');
			cin.ignore(100, '\n');

			if(table.display_sold_items(seller_id)== 0){
				cout << "no sold items fto display" << endl;
			}
		}else{ 
			cout << "Please pick the right choice!" << endl;
		}

	}while(choice != '9');




	return 0;
}

