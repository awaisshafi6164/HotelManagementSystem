#pragma once

#include <string>
#include <vector>
#include <ctime> // For DateTime

struct InvoiceItems {
	std::string ItemCode;
	std::string ItemName;
	std::string RefUSIN;
	double Quantity;
	double TotalAmount;
	double SaleValue;
	double TaxCharged;
	int TaxRate;
	std::string PCTCode;
	double FurtherTax;
	int InvoiceType;
	double Discount;
};

struct Invoice {
	std::string InvoiceNumber;
	int POSID;
	std::string USIN;
	std::string DateTime;
	std::string BuyerPNTN;
	std::string BuyerCNIC;
	std::string BuyerName;
	std::string BuyerPhoneNumber;
	std::string RefUSIN;
	int PaymentMode;
	double TotalSaleValue;
	double TotalQuantity;
	double TotalBillAmount;
	double TotalTaxCharged;
	double Discount;
	double FurtherTax;
	int InvoiceType;
	std::vector<InvoiceItems> Items; // Use vector for list of items
};

// Function to populate Items list
inline std::vector<InvoiceItems> CreateItems() {
	std::vector<InvoiceItems> lst;
	InvoiceItems objItem;
	// in future send items to CreateItems constructor and then use it in below

	/*
	objItem.ItemCode = "";
	objItem.ItemName = "";
	objItem.Quantity = 0;
	objItem.TotalAmount = 0.0;
	objItem.SaleValue = 0.0;
	objItem.TaxCharged = 0.0;
	objItem.TaxRate = 0;
	objItem.PCTCode = "0";
	objItem.FurtherTax = 0.0;
	objItem.InvoiceType = 1;
	objItem.Discount = 0.0;
	objItem.RefUSIN = "";
	*/

	objItem.ItemCode = "0000";
	objItem.ItemName = "Item Name";
	objItem.Quantity = 3.0;
	objItem.TotalAmount = 3000.00;
	objItem.SaleValue = 3180.00;
	objItem.TaxCharged = 180.00;
	objItem.TaxRate = 6;
	objItem.PCTCode = "00000000";
	objItem.FurtherTax = 20.00;
	objItem.InvoiceType = 1;
	objItem.Discount = 500.00;
	//objItem.RefUSIN = "";
	lst.push_back(objItem);
	return lst;
}
