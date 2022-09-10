#include"Header.h"
#include<iostream>
#include<string>
#include<stdexcept>
#include"Date.h"
#include<fstream>
#include<ctime>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

Product* Store::list_of_product = new Product[100];
int Store::size_of_products = 0;

Cart::Cart()
{
	size_cart = 0;
	list_of_items_cart = new pair<int, int>[100];
}
void Cart::add(int p_id, int Q)
{
	size_cart++;
	list_of_items_cart[size_cart - 1].first = p_id;
	list_of_items_cart[size_cart - 1].second = Q;
}
void Cart::remove_item(int p_id)
{
	find_id(p_id);
	int idx;
	for (int i = 0; i < size_cart; i++)
	{
		if (list_of_items_cart[i].first == p_id)
		{
			idx = i;
		}
	}
	for (int i = idx; i < size_cart; i++)
	{
		list_of_items_cart[i].first = list_of_items_cart[i + 1].first;
		list_of_items_cart[i].second = list_of_items_cart[i + 1].second;
	}
	size_cart--;

}
void Cart::find_id(int ID)
{
	for (int i = 0; i < size_cart; i++)
	{
		if (list_of_items_cart[i].first == ID)
		{
			return;
		}
	}
	throw runtime_error("Product not Found!");
}
void Cart::print()
{

 	for (int i = 0; i < size_cart; i++)
	{
	    for(int j = 0 ; j < Store::size_of_products; j++)
        {

            if(list_of_items_cart[i].first == Store::get_product(j).get_id())
            {
                	cout << "ID of the product: " << Store::get_product(j).get_id() << endl
				<< "Name of the product: " << Store::get_product(j).get_Name() << endl
				<< "Price of the product: " << Store::get_product(j).get_price() << endl
				<< "Brand of the product: " << Store::get_product(j).get_brand() << endl
				<< "Expire Date of the product : " << Store::get_product(j).get_Date() << endl;

            }
        }


	}
}
void Cart::reset()
{
	delete[] list_of_items_cart;
	list_of_items_cart = new pair<int, int>[100];
	size_cart = 0;
}
float Cart::get_total_price()
{
	float res = 0;
	for (int i = 0; i < size_cart; i++)
	{
		for (int j = 0; j < Store::size_of_products; j++)
			if (list_of_items_cart[i].first == Store::get_product(j).get_id())
			{
				res += Store::get_product(j).get_price() * list_of_items_cart[i].second;
			}
	}
	return res;
}

//void Cart::checkout()
//{
//
//}


Receipt::Receipt()
{
	list_of_items_pair_receipt = new pair<int, int>[100];
	size_receipt = 0;
}
float Receipt::get_total_price()
{
	float res = 0;
	for (int i = 0; i < size_receipt; i++)
	{

		for (int j = 0; j < Store::size_of_products; j++)
		{

			if (list_of_items_pair_receipt[i].first == Store::get_product(j).get_id())
			{

				res += Store::get_product(j).get_price() * list_of_items_pair_receipt[i].second;
			}
		}

	}

	return res;
}

Stock::Stock()
{
	list_of_pair_stock = new pair<int, int>[100];
	stock_size = 0;
}
int Stock::get_count(int ID)
{
	for (int i = 0; i < stock_size; i++)
	{
		if (list_of_pair_stock[i].first == ID)
		{
			return list_of_pair_stock[i].second;
		}
	}
	throw runtime_error("Product not Found!");
}
void Stock::change_count_by(int ID, int count)
{
	for (int i = 0; i < stock_size; i++)
	{
		if (list_of_pair_stock[i].first == ID)
		{
			list_of_pair_stock[i].second += count;
			return;
		}
	}
	throw runtime_error("Product not Found!");
}

Product::Product()
{
	id = 0;
	name = "";
	price = 0;
	brand = "";
	quantity = 0;
}
Product::Product(int ID, string Name, float Price, string Brand, Date ex, int Q)
{
	id = ID;
	name = Name;
	price = Price;
	brand = Brand;
	expire_date = ex;
	quantity = Q;
}


void Store::checkout(int customer_id)
{

	for (int i = 0; i < size_of_customers; i++)
	{

		if (list_of_customers[i].get_id() == customer_id)
		{

			for (int j = 0; j < list_of_customers[i].cart.size_cart; j++)
			{

				for (int k = 0; k < stock.stock_size; k++)
				{
					if (stock.list_of_pair_stock[k].first == list_of_customers[i].cart.list_of_items_cart[j].first)
					{

						stock.change_count_by(list_of_customers[i].cart.list_of_items_cart[j].first, -1 * list_of_customers[i].cart.list_of_items_cart[j].second);
						if(stock.get_count(list_of_customers[i].cart.list_of_items_cart[j].first) < 0)
                            throw runtime_error("Out OF Stock!");

					}
				}

			}

			list_of_customers[i].convert_cart_to_receipt();
		}

	}
}
void Store::add_customer()
{
	int ID;
	string name;
	string phone;
	string Address;
	float Balance;
	//getLine
	cout << "ID: ";
	cin >> ID;
	for(int i = 0; i < Store::size_of_customers; i++)
    {
        if(Store::list_of_customers[i].get_id() == ID)
            throw runtime_error("Customer with this ID exists!");
    }
	cout << "Name: ";
	cin >> name;
	cout << "Phone Number: ";
	cin >> phone;
	cout << "Address: ";
	cin >> Address;
	cout << "Balance: ";
	cin >> Balance;
	Customer C(ID, name, phone, Address, Balance);
	int tmp = size_of_customers++;
	list_of_customers[tmp] = C;
}
void Store::add_product()
{
	int ID;
	string Name;
	float Price;
	string Brand;
	Date ex;
	int Q;
	cout << "ID: ";
	cin >> ID;
	for(int i = 0; i < size_of_products; i++)
    {
        if(list_of_product[i].get_id() == ID)
            throw runtime_error("Product with this ID exists!");
    }
	cout << "Name: ";
	cin >> Name;
	cout << "Price: ";
	cin >> Price;
	cout << "Brand: ";
	cin >> Brand;
	cout << "Expire Date: ";
	cin >> ex;
	cout << "In Stock: ";
	cin >> Q;

	Product P(ID, Name, Price, Brand, ex, Q);
	Store::size_of_products++;
	Store::list_of_product[Store::size_of_products - 1] = P;
	int tmp = stock.stock_size++;
	stock.list_of_pair_stock[tmp].second += Q;
	stock.list_of_pair_stock[tmp].first = ID;
}
void Store::view_products()
{
	for (int i = 0; i < Store::size_of_products; i++)
	{
		cout << "ID: " << Store::list_of_product[i].get_id() << endl;
		cout << "Name: " << Store::list_of_product[i].get_Name() << endl;
		cout << "Brand: " << Store::list_of_product[i].get_brand() << endl;
		cout << "Price: " << Store::list_of_product[i].get_price() << endl;
		cout << "Ex Date: " << Store::list_of_product[i].get_Date() << endl;
	}
}
void Store::sales_report(Date start, Date end)
{
	float tmp = 0;
	float max = 0;
	float sum = 0;
	Date max_date;
	string res = "";
	Date i(start);
	end++;
	for (i ; i != end; ++i)
	{
		tmp = 0;
		res = "";

		for (int j = 0; j < size_of_customers; j++)
		{
			for (int k = 0; k < list_of_customers[j].size_of_history; k++)
			{
				if (list_of_customers[j].history[k].date == i)
				{


 					tmp += list_of_customers[j].history[k].get_total_price();
				}
			}
		}
		if (max < tmp)
		{
			max = tmp;
			max_date = i;
		}
		sum += tmp;
		tmp /= 100;
		while (tmp)
		{
			res += "++";
			res += " ";
			tmp--;
		}
		cout << i << ": " << res << endl;
	}
	cout << "Highest Sales Rate Date: " << max_date << endl;
	cout << "Total Sales: " << sum << endl;
}
void Store::save_to_file()
{
    //......................................product file........................................
	ofstream Product_file("Products");
	for (int i = 0; i < size_of_products; i++)
	{
		//Product_file << "Product "<< i << endl;
		Product_file << list_of_product[i].get_id() << endl;
		Product_file << list_of_product[i].get_Name() << endl;
		Product_file << list_of_product[i].get_price() << endl;
		Product_file << list_of_product[i].get_brand() << endl;
		Product_file << list_of_product[i].get_Date() << endl;
		Product_file << list_of_product[i].get_quantity() << endl;
	}
	Product_file.close();
//........................................customer file.............................
	ofstream customer_file("Customers");
	for (int i = 0; i < size_of_customers; i++)
	{
		//customer_file << "Customer "<< i << endl;
		customer_file << list_of_customers[i].get_id() << endl;
		customer_file << list_of_customers[i].get_name() << endl;
		customer_file << list_of_customers[i].get_phone_number() << endl;
		customer_file << list_of_customers[i].get_address() << endl;
		customer_file << list_of_customers[i].get_balance() << endl;
	}
	customer_file.close();


//......................................history file..................................
	ofstream history_file("history");
	for (int i = 0; i < size_of_customers; i++)
	{
        history_file << list_of_customers[i].get_id() << endl;
        history_file << list_of_customers[i].size_of_history << endl;
		for (int j = 0; j < list_of_customers[i].size_of_history; j++)
		{
            history_file << list_of_customers[i].history[j].size_receipt << endl;
			for (int k = 0; k < list_of_customers[i].history[j].size_receipt; k++)
			{
				//history_file << "Customer " << i << endl;
				//history_file << list_of_customers[i].history[j].get_total_price() << endl;
				history_file << list_of_customers[i].history[j].list_of_items_pair_receipt[k].first << endl;
				history_file << list_of_customers[i].history[j].list_of_items_pair_receipt[k].second << endl;
			}
            history_file << list_of_customers[i].history[j].date << endl;
		}
	}
	history_file.close();
//............................stock file........................................
	ofstream stock_file("Stock");
	for (int i = 0; i < stock.stock_size; i++)
	{
		//stock_file << "Pair " << i << endl;
		//stock_file << stock.stock_size << endl;
		stock_file << stock.list_of_pair_stock[i].first << endl;
		stock_file << stock.list_of_pair_stock[i].second << endl;
	}
	stock_file.close();
//........................................cart file....................................
	ofstream cart_file("Cart");
	for (int i = 0; i < size_of_customers; i++)
	{
        cart_file << list_of_customers[i].get_id() << endl;
        cart_file << list_of_customers[i].cart.size_cart << endl;
		for (int j = 0; j < list_of_customers[i].cart.size_cart; j++)
		{
			//cart_file << "Customer " << i << endl;
			cart_file << list_of_customers[i].cart.list_of_items_cart[j].first << endl;
			cart_file << list_of_customers[i].cart.list_of_items_cart[j].second << endl;
		}
	}
	cart_file.close();
}

Customer::Customer()
{
	id = 0;
	Name = "";
	phone_number = "";
	address = "";
	balance = 0;
	history = new Receipt[100];
	size_of_history = 0;
}
Customer::Customer(int ID, string name, string phone, string Address, float Balance)
{
	id = ID;
	Name = name;
	phone_number = phone;
	address = Address;
	balance = Balance;
	history = new Receipt[100];
	size_of_history = 0;
}
void Customer::convert_cart_to_receipt()
{
	Receipt R;
	Date date;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	date.setYear(1900 + ltm->tm_year);
	date.setMonth(1 + ltm->tm_mon);
	date.setDay(ltm->tm_mday);


	for (int i = 0; i < cart.get_size(); i++)
	{
		R.list_of_items_pair_receipt[i].first = cart.list_of_items_cart[i].first;
		R.list_of_items_pair_receipt[i].second = cart.list_of_items_cart[i].second;
		R.size_receipt++;
	}


	float remove_price = 0;
	remove_price = R.get_total_price();

	if (balance < remove_price)
		throw runtime_error("Balance is Not Enough!");


	R.date = date;

	balance -= remove_price;
	cart.reset();

	int tmp = size_of_history++;
	history[tmp] = R;

}
float Customer::get_total_purchase_amount()
{
	float res = 0;
	for (int i = 0; i < size_of_history; i++)
	{
		res += history[i].get_total_price();
	}
	return res;
}
