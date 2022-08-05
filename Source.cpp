#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class product
{
public:
	int ID;
	string name;
	int year;
	int price;
	int stock;
	product* pnext;
};
class procust
{
public:
	int PID;
	int CID;
	int price;
	string date;
	procust* pnext;
};
class Customer
{
public:
	string name;
	int ID;
	Customer* pnext;
};
class clistprocust //procust
{
public:
	procust* phead;
	procust* ptail;
	clistprocust()
	{
		phead = NULL;
		ptail = NULL;
	}
	~clistprocust()
	{
		procust* ptrav;
		ptrav = phead;
		while (ptrav != NULL)
		{
			phead = phead->pnext;
			delete ptrav;
			ptrav = phead;
		}
	}
	void attach(procust* pnn)
	{
		if (phead == NULL)
		{
			phead = pnn;
			ptail = pnn;
		}
		else
		{
			ptail->pnext = pnn;
			ptail = pnn;
		}
	}

	void dispall()
	{
		procust* ptrav;
		ptrav = phead;
		while (ptrav != NULL)
		{
			cout << "productID: " << ptrav->PID << "," << "CustID: "
				<< ptrav->CID << " ,Date:" << ptrav->date << ", product price" << ptrav->price << endl;
			ptrav = ptrav->pnext;
		}
	}

};

class clist2 //customers
{
public:
	Customer* phead;
	Customer* ptail;
	clist2()
	{
		phead = NULL;
		ptail = NULL;
	}
	~clist2()
	{
		Customer* ptrav;
		ptrav = phead;
		while (ptrav != NULL)
		{
			phead = phead->pnext;
			delete ptrav;
			ptrav = phead;
		}
	}
	void attach(Customer* pnn)
	{
		if (phead == NULL)
		{
			phead = pnn;
			ptail = pnn;
		}
		else
		{
			ptail->pnext = pnn;
			ptail = pnn;
		}
	}

	void dispall()
	{
		Customer* ptrav;
		ptrav = phead;
		while (ptrav != NULL)
		{
			cout << "Name: " << ptrav->name << "," << "ID: " << ptrav->ID << endl;
			ptrav = ptrav->pnext;
		}
	}
};
class clist //product 
{
public:
	product* phead;
	product* ptail;
	clist()
	{
		phead = NULL;
		ptail = NULL;
	}
	~clist()
	{
		product* ptrav;
		ptrav = phead;
		while (ptrav != NULL)
		{
			phead = phead->pnext;
			delete ptrav;
			ptrav = phead;
		}
	}
	void attach(product* pnn)
	{
		if (phead == NULL)
		{
			phead = pnn;
			ptail = pnn;
		}
		else
		{
			ptail->pnext = pnn;
			ptail = pnn;
		}
	}

	void dispall()
	{
		product* ptrav;
		ptrav = phead;
		while (ptrav != NULL)
		{
			cout << "Name: " << ptrav->name << "," << "ID: " << ptrav->ID << ", Price:" << ptrav->price << " ,Stock:" << ptrav->stock << endl;
			ptrav = ptrav->pnext;
		}
	}
};

int main()
{
	fstream File;
	clist L_product;
	File.open("//Users//product.txt");
	if (File.is_open())
	{
		string line;
		while (getline(File, line))
		{
			int it = 0;
			string tmp[6];
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == ',')
				{
					it++;
				}
				else
				{
					tmp[it] += line[i];
				}
			}
			product* pnn = new product;
			pnn->ID = stoi(tmp[0]);
			pnn->name = (tmp[1]);
			pnn->stock = stoi(tmp[2]);
			pnn->price = stoi(tmp[3]);

			pnn->pnext = NULL;
			L_product.attach(pnn);
		}


		File.close();
	}
	else
	{
		cout << "NOt " << endl;
	}
	L_product.dispall();
	/////////////////////////////////////////////////////
	fstream FileC;
	clist2 L_cust;
	clistprocust L_procust;
	FileC.open("//Users//Customer.txt");
	if (FileC.is_open())
	{
		string line;
		while (getline(FileC, line))
		{
			int it = 0;
			string tmp[3];
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == ',')
				{
					it++;
				}
				else
				{
					tmp[it] += line[i];
				}
			}
			Customer* pnn = new Customer;
			pnn->ID = stoi(tmp[0]);
			pnn->name = (tmp[1]);
			pnn->pnext = NULL;
			L_cust.attach(pnn);

		}


		FileC.close();
	}
	else
	{
		cout << "NOt " << endl;
	}
	cout << "======================================" << endl;
	L_cust.dispall();
	///////////////////////////////////////////////////
	cout << "please enter what do you want 1-buy , 2-return , 3-display the income of a date , 4-display order from a spacific ID ";
	int choose;
	cin >> choose;
	if (choose == 1)
	{
		cout << "Enter your ID " << endl;
		int CustId;
		cin >> CustId;
		fstream FileCB;
		FileCB.open("//Users//PC.txt", ios::app);
		Customer* ptrav = L_cust.phead;
		int f = 0;
		while (ptrav != NULL)
		{
			if (ptrav->ID == CustId)
			{
				f = 1;

				break;
			}
			ptrav = ptrav->pnext;
		}
		string date;
		product* ptrav2 = L_product.phead;
		//////////////////////////////////////////////
		if (f != 1) //is not a cust
		{
			FileC.open("//Users//custemer.txt", ios::app);
			cout << "please enter your name" << endl;
			int namec;
			cin >> namec;
			cin.ignore();
			Customer* pnnc = new Customer();
			pnnc->ID = CustId;
			pnnc->name = namec;
			pnnc->pnext = NULL;
			if (FileC.is_open())
			{
				FileC << pnnc->ID << "," << pnnc->name << "," << endl;
				FileC.close();
			}//if file
			L_cust.attach(pnnc);

			cout << "Enter Product ID " << endl;
			int productId;
			cin >> productId;
			while (ptrav2 != NULL)
			{
				if (productId == ptrav2->ID)
				{
					if (ptrav2->stock > 0)
					{
						cout << "Enter Today's Date" << endl;
						cin.ignore();
						getline(cin, date);
						procust* pnn = new procust();
						pnn->PID = productId;
						pnn->CID = CustId;
						pnn->price = ptrav2->price;
						pnn->date = date;
						pnn->pnext = NULL;
						ptrav2->stock--;
						if (FileCB.is_open())
						{
							FileCB << pnn->PID << "," << pnn->CID << "," << pnn->date << "," << pnn->price << endl;
							FileCB.close();
						}
						L_procust.attach(pnn);
					}
				}
				ptrav2 = ptrav2->pnext;
			}

		} //is not a custmer 
		L_procust.dispall();
		cout << endl << "========================" << endl;
		L_product.dispall();
		L_cust.dispall();

		FileC.open("//Users//Customer.txt");
		FileCB.open("//Users//PC.txt");
		File.open("//Users//product.txt");
		Customer* pt = L_cust.phead;
		if (FileC.is_open())
		{
			while (pt != NULL)
			{
				FileC << pt->ID << "," << pt->name << endl;
				pt = pt->pnext;
			}
			FileC.close();
		}
		product* pt2 = L_product.phead;
		if (File.is_open())
		{
			while (pt2 != NULL)
			{
				File << pt2->ID << "," << pt2->name << "," << pt2->stock << "," << pt2->price << endl;
				pt2 = pt2->pnext;
			}


			File.close();
		}

		procust* pt3 = L_procust.phead;
		if (FileCB.is_open())
		{
			while (pt3 != NULL)
			{
				FileCB << pt3->PID << "," << pt3->CID << "," << pt3->price << "," << pt3->date << endl;
				pt3 = pt3->pnext;
			}
			FileC.close();
		}
		///////////////////////////////////////////////		
		string date1;
		product* ptrav22 = L_product.phead;
		if (f == 1)
		{
			cout << "Enter Product ID " << endl;
			int productId;
			cin >> productId;
			while (ptrav22 != NULL)
			{
				if (productId == ptrav22->ID)
				{
					if (ptrav22->stock > 0)
					{
						cout << "Enter Today's Date" << endl;
						cin.ignore();
						getline(cin, date);
						procust* pnn = new procust();
						pnn->PID = productId;
						pnn->CID = CustId;
						pnn->price = ptrav22->price;
						pnn->date = date;
						pnn->pnext = NULL;
						ptrav22->stock--;
						if (FileCB.is_open())
						{
							FileCB << pnn->PID << "," << pnn->CID << "," << pnn->date << "," << pnn->price << endl;
							FileCB.close();
						}
						L_procust.attach(pnn);
					}
				}
				ptrav22 = ptrav22->pnext;
			}

		}//if cust is here 
		L_procust.dispall();
		cout << endl << "========================" << endl;
		L_product.dispall();
		L_cust.dispall();

		FileC.open("//Users//Customer.txt");
		FileCB.open("//Users//PC.txt");
		File.open("//Users//product.txt");
		Customer* ptc = L_cust.phead;
		if (FileC.is_open())
		{
			while (ptc != NULL)
			{
				FileC << ptc->ID << "," << ptc->name << endl;
				ptc = ptc->pnext;
			}
			FileC.close();
		}
		product* ptp = L_product.phead;
		if (File.is_open())
		{
			while (ptp != NULL)
			{
				File << ptp->ID << "," << ptp->name << "," << ptp->stock << "," << ptp->price << endl;
				ptp = ptp->pnext;
			}


			File.close();
		}

		procust* ptf = L_procust.phead;
		if (FileCB.is_open())
		{
			while (ptf != NULL)
			{
				FileCB << ptf->PID << "," << ptf->CID << "," << ptf->price << "," << ptf->date << endl;
				ptf = ptf->pnext;
			}
			FileC.close();
		}
	}//choose 1

	if (choose == 2)
	{
		cout << "Enter your ID " << endl;
		int CustId2;
		cin >> CustId2;
		cout << "Enter product ID " << endl;
		int productId2;
		cin >> productId2;
		cout << "Enter Today's Date" << endl;
		string date1;
		cin >> date1;
		procust* ptemp = L_procust.phead;
		procust* PB = NULL;
		while (ptemp != NULL)
		{
			if (ptemp->PID == productId2 && ptemp->CID == CustId2 && ptemp->date == date1)
			{
				cout << "Returned successfully";
				break;
			}
			PB = ptemp;
			ptemp = ptemp->pnext;
		}
		if (PB != NULL)
		{
			if (ptemp == L_procust.ptail)
			{
				PB->pnext = NULL;
				L_procust.ptail = PB;
			}
			else
			{
				PB->pnext = ptemp->pnext;
			}
		}
		if (PB == NULL)
		{
			L_procust.phead = ptemp->pnext;
		}
		delete ptemp;

		product* ptrav21 = L_product.phead;
		while (ptrav21 != NULL)
		{
			if (productId2 == ptrav21->ID)
			{
				ptrav21->stock++;

			}
			ptrav21 = ptrav21->pnext;
		}

		L_procust.dispall();
		cout << endl << "========================" << endl;
		L_product.dispall();
		L_cust.dispall();
		fstream FileCB;
		FileC.open("//Users//Customer.txt");
		FileCB.open("//Users/PC.txt");
		File.open("//Users//product.txt");

		Customer* pt1 = L_cust.phead;
		if (FileC.is_open())
		{
			while (pt1 != NULL)
			{
				FileC << pt1->ID << "," << pt1->name << endl;
				pt1 = pt1->pnext;
			}
			FileC.close();
		}
		product* pt21 = L_product.phead;
		if (File.is_open())
		{
			while (pt21 != NULL)
			{
				File << pt21->ID << "," << pt21->name << "," << pt21->stock << "," << pt21->price << endl;
				pt21 = pt21->pnext;
			}
			File.close();
		}
		procust* pt31 = L_procust.phead;
		if (FileCB.is_open())
		{
			while (pt31 != NULL)
			{
				FileCB << pt31->PID << "," << pt31->CID << "," << pt31->price << "," << pt31->date << endl;
				pt31 = pt31->pnext;
			}
			FileC.close();
		}

	}//choose 2 

	if (choose == 3)
	{
		cout << "Please enter your date :" << endl;
		string datep;
		cin >> datep;
		int tot = 0;
		procust* ptem = L_procust.phead;
		while (ptem != NULL)
		{
			if (ptem->date == datep)
			{
				tot += ptem->price;
			}
			ptem = ptem->pnext;
		}
		cout << "The date is : " << datep << endl;
		cout << "The income is :" << tot << endl;

	}//choose 3

	if (choose == 4)
	{
		cout << "Please enter Custmer ID :" << endl;
		int CIDL;
		cin >> CIDL;
		procust* ptemc = L_procust.phead;
		int count = 0;
		while (ptemc != NULL)
		{
			if (ptemc->CID == CIDL)
			{
				count++;
				int num = count;
			}
			ptemc = ptemc->pnext;
		}
		cout << "Customer ID is : " << CIDL << endl << "She/He made" << count << endl;
	}//choose 4		
}//main

