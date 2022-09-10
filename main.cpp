// onlineShop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Header.h"
using namespace std;

int main()
{

    try
    {
        Store& s1 = Store::get_distance();


        cout << ".....................................Home Page............................................." << endl;
        cout << "1.Add Customer" << endl;
        cout << "2.Add Product" << endl;
        cout << "3.view Products" << endl;
        cout << "4.Sales Report" << endl;
        cout << "5.Customer Page" << endl;
        cout << "6.Stock Page" << endl;
        cout << "7.checkOut" << endl;
        cout << "8.Save to File" << endl;
        cout << "9.Exit" << endl;
        cout << "10.if you want to clear screen" << endl;
        while (1)
        {
            try
            {
                int n;
                cin >> n;
                if (n == 1)
                {
                    s1.add_customer();
                    cout << "Done!" << endl;

                }
                if (n == 2)
                {
                    s1.add_product();
                    cout << "Done!"<< endl;

                }
                if (n == 3)
                {
                    s1.view_products();

                }
                if (n == 4)
                {
                    Date start;
                    Date end;
                    cout << "Enter Start Date: ";
                    cin >> start;
                    cout << "Enter End Date: ";
                    cin >> end;
                    s1.sales_report(start, end);



                }
                if (n == 5)
                {
                 cout << "............................customer Page...................................." << endl;
                 cout << "Please Enter Customer's ID: ";
                 int ID;
                 cin >> ID;
                 cout << "1.Add to Cart" << endl;
                 cout << "2.Remove items from Cart" << endl;
                 cout << "3.Reset Cart" << endl;
                 cout << "4.Print Cart" << endl;
                 cout << "5.Get total Price of Cart" << endl;
                 cout << "6.Get Total Purchase Amount" << endl;
                 cout << "7.checkOut" << endl;
                 cout << "8.Return to HomePage" << endl;
                 cout << "9.if you want to clear screen" << endl;
                    while (1)
                    {
                       // cout << "............................customer Page...................................." << endl;
                        try
                        {

                            int m;
                            cin >> m;
                            if (m == 1)
                            {
                                cout << "Please Enter ID of The Product: ";
                                int ID_Pro;
                                cin >> ID_Pro;
                                cout << "Please Enter Quantity of the Product: ";
                                int Q;
                                cin >> Q;
                                s1.get_customer_list(ID).get_cart().add(ID_Pro, Q);
                                 cout << "Done!"<< endl;


                            }
                            if (m == 2)
                            {
                                cout << "Please Enter ID of The Product: ";
                                int ID_Pro;
                                cin >> ID_Pro;
                                s1.get_customer_list(ID).get_cart().remove_item(ID_Pro);
                                cout << "Done!"<< endl;

                            }
                            if (m == 3)
                            {
                                s1.get_customer_list(ID).get_cart().reset();
                                 cout << "Done!"<< endl;

                            }
                            if (m == 4)
                            {
                                s1.get_customer_list(ID).get_cart().print();


                            }
                            if (m == 5)
                            {
                               cout <<"total price of cart: "  << s1.get_customer_list(ID).get_cart().get_total_price() << endl;
                            }
                            if (m == 6)
                            {
                                cout <<"Total Purchase amount of this Customer: " <<s1.get_customer_list(ID).get_total_purchase_amount() << endl;
                            }
                            if (m == 7)
                            {
                                s1.checkout(ID);
                                 cout << "Done!"<< endl;

                            }
                            if (m == 8)
                                break;
                            if(m == 9)
                            {

                                system("CLS");
                                        cout << ".....................................Home Page............................................." << endl;
                                        cout << "1.Add Customer" << endl;
                                        cout << "2.Add Product" << endl;
                                        cout << "3.view Products" << endl;
                                        cout << "4.Sales Report" << endl;
                                        cout << "5.Customer Page" << endl;
                                        cout << "6.Stock Page" << endl;
                                        cout << "7.checkOut" << endl;
                                        cout << "8.Save to File" << endl;
                                        cout << "9.Exit" << endl;
                                        cout << "10.if you want to clear screen" << endl;
                                        cout << "............................customer Page...................................." << endl;
                                        cout << "1.Add to Cart" << endl;
                                        cout << "2.Remove items from Cart" << endl;
                                         cout << "3.Reset Cart" << endl;
                                         cout << "4.Print Cart" << endl;
                                         cout << "5.Get total Price of Cart" << endl;
                                         cout << "6.Get Total Purchase Amount" << endl;
                                         cout << "7.checkOut" << endl;
                                         cout << "8.Return to HomePage" << endl;
                                         cout << "9.if you want to clear screen" << endl;
                            }
                        }
                        catch (const runtime_error& err)
                        {
                            cout << err.what() << endl;
                        }
                    }
                }
                if (n == 6)
                {
                    cout << "...................................Stock Page..........................................." << endl;
                    cout << "1.Change Count By" << endl;
                    cout << "2.get Count" << endl;
                    cout << "3.view stock" << endl;
                    cout << "4.Return to homePage" << endl;
                    cout << "5.if you want to clear screen"<< endl;
                    while (1)
                    {
                        try
                        {
                            int k;
                            cin >> k;
                            if (k == 1)
                            {
                                cout << "Enter ID of the product: ";
                                int ID_stock;
                                int Q;
                                cin >> ID_stock;
                                cout << "Enter Quantity of the product: ";
                                cin >> Q;
                                s1.get_stock().change_count_by(ID_stock, Q);
                                cout << "Done!" << endl;
                            }
                            if (k == 2)
                            {
                             cout << "Enter ID of the product: ";
                             int ID_stock;
                             cin >> ID_stock;
                             cout << "Quantity of this product in Stock: ";
                             cout << s1.get_stock().get_count(ID_stock) << endl;
                            }
                            if (k == 3)
                            {
                                s1.get_stock().view_stock();
                            }
                            if (k == 4)
                                break;

                            if(k == 5)
                            {

                                system("CLS");
                                        cout << ".....................................Home Page............................................." << endl;
        cout << "1.Add Customer" << endl;
        cout << "2.Add Product" << endl;
        cout << "3.view Products" << endl;
        cout << "4.Sales Report" << endl;
        cout << "5.Customer Page" << endl;
        cout << "6.Stock Page" << endl;
        cout << "7.checkOut" << endl;
        cout << "8.Save to File" << endl;
        cout << "9.Exit" << endl;
        cout << "10.if you want to clear screen" << endl;
                                  cout << "...................................Stock Page..........................................." << endl;
                    cout << "1.Change Count By" << endl;
                    cout << "2.get Count" << endl;
                    cout << "3.view stock" << endl;
                    cout << "4.Return to homePage" << endl;
                    cout << "5.if you want to clear screen"<< endl;
                            }

                        }
                        catch (const runtime_error& err)
                        {
                            cout << err.what() << endl;
                        }
                    }
                }
                if (n == 7)
                {
                    cout << "Enter Customer's ID: ";
                    int ID;
                    cin >> ID;
                    s1.checkout(ID);
                }
                if (n == 8)
                {
                    s1.save_to_file();
                }
                if (n == 9)
                {
                    cout << "Hope to meet you again!" << endl;
                    break;
                }
                if(n == 10)
                {

                    system("CLS");
                       cout << ".....................................Home Page............................................." << endl;
        cout << "1.Add Customer" << endl;
        cout << "2.Add Product" << endl;
        cout << "3.view Products" << endl;
        cout << "4.Sales Report" << endl;
        cout << "5.Customer Page" << endl;
        cout << "6.Stock Page" << endl;
        cout << "7.checkOut" << endl;
        cout << "8.Save to File" << endl;
        cout << "9.Exit" << endl;
        cout << "10.if you want to clear screen" << endl;
                }
            }

            catch (const runtime_error& err)
            {
                cout << err.what() << endl;
            }

        }


        s1.save_to_file();



    }
    catch (runtime_error& err)
    {
        cout << err.what() << endl;
    }

    return 0;
}
