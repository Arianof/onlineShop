#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include"Date.h"
#include<string>
#include <utility>
#include<vector>
#include<fstream>
#include<stdexcept>


class Product
{
public:
	Product();
	Product(int, std::string, float, std::string, Date, int);
	int get_id()
	{
		return id;
	}
	float get_price()
	{
		return price;
	}
	std::string get_Name()
	{
		return name;
	}
	std::string get_brand()
	{
		return brand;
	}
	Date get_Date()
	{
		return expire_date;
	}
	int get_quantity()
	{
		return quantity;
	}
private:
	int id;
	std::string name;
	float price;
	std::string brand;
	Date expire_date;
	int quantity;
};

class Stock
{
	friend class Store;
public:
	Stock();
	int get_count(int);
	void change_count_by(int, int);
	void view_stock()
	{
		for (int i = 0; i < stock_size; i++)
		{
			std::cout << "Item " << i + 1 << std::endl;
			std::cout << list_of_pair_stock[i].first << std::endl;
			std::cout << list_of_pair_stock[i].second << std::endl;
		}
	}

private:
	std::pair<int, int>* list_of_pair_stock;
	int stock_size;
};

class Cart
{
	friend class Customer;
	friend class Store;
public:
	Cart();
	float get_total_price();
	void add(int, int);
	void remove_item(int);
	void print();
	//void checkout();
	void reset();
	int get_size()
	{
		return size_cart;
	}
	//void check_id(int);
	void find_id(int);
private:
	std::pair<int, int>* list_of_items_cart;
	int size_cart;
};

class Receipt
{
	friend class Customer;
	friend class Store;
public:
	Receipt();
	float get_total_price();

private:
	std::pair<int, int>* list_of_items_pair_receipt;
	int size_receipt;
	Date date;
};

class Customer
{
	friend class Receipt;
	friend class Cart;
	friend class Store;
public:
	Customer();
	Customer(int, std::string, std::string, std::string, float);
	void convert_cart_to_receipt();
	float get_total_purchase_amount();
	int get_id()
	{
		return id;
	}
	std::string get_name()
	{
		return Name;
	}
	std::string get_phone_number()
	{
		return phone_number;
	}
	std::string get_address()
	{
		return address;
	}
	float get_balance()
	{
		return balance;
	}
	Cart& get_cart()
	{
		return cart;
	}
	void set_id(int ID)
	{

		id = ID;
	}

private:
	int id;
	std::string Name;
	std::string phone_number;
	Receipt* history;
	int size_of_history;
	std::string address;
	Cart cart;
	float balance;
};

class Store
{
	friend class Receipt;
	friend class Cart;
public:
	static Store& get_distance()
	{
		static Store instance;
		return instance;
	}
	void checkout(int);
	void add_customer();
	void add_product();
	void view_products();
	void save_to_file();
	void sales_report(Date, Date);
	static Product& get_product(int i)
	{
		return list_of_product[i];
	}
	Customer& get_customer_list(int input_id)
	{
		for (int i = 0; i < size_of_customers; i++)
		{
			if (list_of_customers[i].get_id() == input_id)
			{
				return list_of_customers[i];
			}
		}
		throw std::runtime_error("Customer's ID Not Found!");
	}
	Stock& get_stock()
	{
		return stock;
	}
private:
	Store()
	{
		list_of_customers = new Customer[100];
		size_of_customers = 0;
		//......................................product file........................................
		std::ifstream products_file("Products");
		if (!products_file)
		{
			throw std::runtime_error("Error in file openning!");
		}
		int id;
		std::string name;
		float price;
		std::string brand;
		Date ex;
		int Q;
		int i = 0;
		while (products_file >> id >> name >> price >> brand >> ex >> Q)
		{
			//cout << "1" << endl;
			Product P(id, name, price, brand, ex, Q);
			Store::list_of_product[i] = P;
			i++;
			Store::size_of_products++;
		}
		products_file.close();

		//........................................customer file.............................
		std::ifstream customer_file("Customers");
		if (!customer_file)
		{
			throw std::runtime_error("Error in file openning!");
		}
		std::string phone;
		std::string address;

		i = 0;
		while (customer_file >> id >> name >> phone >> address >> price)
		{
			Customer C(id, name, phone, address, price);
			list_of_customers[i] = C;
			i++;
			size_of_customers++;
		}
		customer_file.close();

		//............................stock file........................................
		std::ifstream stock_file("Stock");
		if (!stock_file)
		{
			throw std::runtime_error("Error in openning file!");
		}
		int Quantity;
		i = 0;
		while (stock_file >> id >> Quantity)
		{
			stock.list_of_pair_stock[i].first = id;
			stock.list_of_pair_stock[i].second = Quantity;
			i++;
			stock.stock_size++;
		}
		stock_file.close();
		//........................................cart file....................................
		std::ifstream cart_file("Cart");
		if (!cart_file)
		{
			throw std::runtime_error("Error in openning file!");
		}
		int sizeCart;
		i = 0;
		int id_cart;
		while (cart_file >> id >> sizeCart)
		{
			// list_of_customers[i].set_id(id);
			for (int j = 0; j < sizeCart; j++)
			{
				cart_file >> id_cart >> Q;
				list_of_customers[i].cart.list_of_items_cart[j].first = id_cart;
				list_of_customers[i].cart.list_of_items_cart[j].second = Q;

			}
			list_of_customers[i].cart.size_cart = sizeCart;
			i++;
		}
		cart_file.close();
		//......................................history file..................................
		std::ifstream history_file("history");
		if (!history_file)
			throw std::runtime_error("Error in opening file!");
		int size_his = 0;
		int size_res = 0;
		int id_res;
		i = 0;
		Date d;
		while (history_file >> id >> size_his)
		{
			//list_of_customers[i].set_id(id);
			for (int j = 0; j < size_his; j++)
			{
				history_file >> size_res;
				for (int k = 0; k < size_res; k++)
				{
					history_file >> id_res >> Q;
					list_of_customers[i].history[j].list_of_items_pair_receipt[k].first = id_res;
					list_of_customers[i].history[j].list_of_items_pair_receipt[k].second = Q;
				}
				history_file >> d;
				list_of_customers[i].history[j].date = d;
				list_of_customers[i].history[j].size_receipt = size_res;
			}
			list_of_customers[i].size_of_history = size_his;
			i++;
		}
		history_file.close();
	}
	Store(const Store&) = delete;
	void operator=(const Store&) = delete;
	static Product* list_of_product;
	static int size_of_products;
	Stock stock;
	Customer* list_of_customers;
	int size_of_customers;
};

#endif // HEADER_H_INCLUDED
