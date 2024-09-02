#pragma once

#define IServiceProvider WindowsIServiceProvider // Rename Windows IServiceProvider
#include <curl/curl.h>
#undef IServiceProvider  // Undefine after including

#include <iostream>
#include <string>
#include <nlohmann\json.hpp>

#include "Invoice.h"
#include <msclr/marshal_cppstd.h> // For converting std::string to System::String

#include <fstream>
#include "CustomerDataForm.h"
using namespace std;
using namespace System::Data::SqlClient;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;
// Token and URL (replace with actual values)
//std::string token = "24d8fab3-f2e9-398f-ae17-b387125ec4a2"; //sandbox token
//std::string url = "https://ims.pral.com.pk/ims/sandbox/api/Live/PostData";//sandbox url

// WriteCallback function to capture the response data
inline size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
	size_t totalSize = size * nmemb;
	response->append((char*)contents, totalSize);
	return totalSize;
}
/*
inline std::string SendInvoiceData(const nlohmann::json& invoiceJson) {
	CURL* curl;
	CURLcode res;
	std::string response;

	curl = curl_easy_init();
	if (curl) {
		// Convert JSON object to string
		std::string jsonString = invoiceJson.dump();

		// Set up cURL options
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8524/api/IMSFiscal/GetInvoiceNumberByModel");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonString.size());

		// Set up HTTP headers
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		// Set up the callback function to capture the response
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		// Perform the request
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
		}

		// Clean up
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
	}

	return response;
}
*/

inline std::string SendInvoiceData(const nlohmann::json& invoiceJson) {
	// Fetch data from the database
	String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
	SqlConnection^ conDataBase = gcnew SqlConnection(conString);
	SqlCommand^ cmdDataBase = gcnew SqlCommand("SELECT praAccessIDToken, praIDEnvironment FROM setting WHERE ID = 1;", conDataBase);

	std::string token;
	std::string env;

	try {
		conDataBase->Open();
		SqlDataReader^ reader = cmdDataBase->ExecuteReader();
		if (reader->Read()) {
			token = msclr::interop::marshal_as<std::string>(reader["praAccessIDToken"]->ToString());
			env = msclr::interop::marshal_as<std::string>(reader["praIDEnvironment"]->ToString());
		}
		reader->Close();
	}
	catch (Exception^ ex) {
		std::cerr << "Database error: " << msclr::interop::marshal_as<std::string>(ex->Message) << std::endl;
	}
	finally{
		conDataBase->Close();
	}

		// Replace "sandbox" with the environment from the database in the URL
	std::string url = "https://ims.pral.com.pk/ims/" + env + "/api/Live/PostData";


	//////////////////
	//////////////////
	CURL* curl;
	CURLcode res;
	std::string response;

	curl = curl_easy_init();
	if (curl) {
		// Convert JSON object to string
		std::string jsonString = invoiceJson.dump();

		// Set up cURL options with HTTPS URL
		//std::string url = "https://ims.pral.com.pk/ims/sandbox/api/Live/PostData";
		//std::string token = "24d8fab3-f2e9-398f-ae17-b387125ec4a2"; // Sandbox Token

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonString.size());

		// Set up HTTP headers including Authorization Bearer token
		struct curl_slist* headers = NULL;
		std::string bearer_token = "Authorization: Bearer " + token;
		headers = curl_slist_append(headers, bearer_token.c_str());
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		// Skip SSL certificate verification (similar to ServicePointManager.ServerCertificateValidationCallback)
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		// Set up the callback function to capture the response
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		// Perform the request
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
		}

		// Clean up
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
	}

	return response;
}

inline std::string FetchQRCode(const std::string& qrData) {
	CURL* curl;
	CURLcode res;
	std::string response;

	curl = curl_easy_init();
	if (curl) {
		// Prepare the URL with QR code data
		std::string url = "https://api.qrserver.com/v1/create-qr-code/?size=150x150&data=";
		// Escape the data to be URL-safe
		char* escapedData = curl_easy_escape(curl, qrData.c_str(), qrData.length());
		url += escapedData;
		curl_free(escapedData); // Free the escaped string

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// Set up the callback function to capture the response
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		// Skip SSL certificate verification
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		// Perform the request
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
		}

		// Clean up
		curl_easy_cleanup(curl);
	}

	return response;
}

inline void SaveQRCodeImage(const std::string& qrData, const std::string& filePath) {
	std::string qrCodeData = FetchQRCode(qrData);

	if (!qrCodeData.empty()) {
		std::ofstream outFile(filePath, std::ios::binary);
		outFile.write(qrCodeData.c_str(), qrCodeData.size());
		outFile.close();
	}
	else {
		std::cerr << "Failed to retrieve QR code data." << std::endl;
	}
}
namespace HotelManagementSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;
	using namespace System::IO;
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		String ^ praInvoiceNumberGlobalDeclare = "";

	public:
		String^ bookingManagerName;
		MainForm(String^ userName)
		{
			this->bookingManagerName = userName;
			InitializeComponent();
			//
			LoadRoomData("All Floor");
			LoadDataOnce();
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  tbName;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  tbCnic;

	private: System::Windows::Forms::Label^  label6;


	private: System::Windows::Forms::Label^  label7;


	private: System::Windows::Forms::Label^  label8;






	private: System::Windows::Forms::DateTimePicker^  dtpTimeIn;
	private: System::Windows::Forms::DateTimePicker^  dtpTimeOut;
	private: System::Windows::Forms::DataGridView^  dgvRoomData;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Button^  btnRefresh;


	private: System::Windows::Forms::TextBox^  tbNoOfRooms;
	private: System::Windows::Forms::TextBox^  tbRoomCharges;


	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TextBox^  tbGst;

	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  tbPayable;


	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::Windows::Forms::Button^  btnSave;
	private: System::Windows::Forms::Button^  btnPrint;
	private: System::Windows::Forms::Button^  btnCalculateTotal;

	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TextBox^  tbInvoiceNo;

	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TextBox^  tbContact;

	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::TextBox^  tbEmergencyContact;

	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::ComboBox^  cbNationality;

	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::TextBox^  tbAddress;

	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::DateTimePicker^  dtpDate;

	private: System::Windows::Forms::DateTimePicker^  dtpDateIn;

	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::DateTimePicker^  dtpDateOut;

	private: System::Windows::Forms::Label^  label25;


	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  tbBuyerPNTN;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  lblManagerName;

	private: System::Windows::Forms::TextBox^  tbRoomNo;

	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::TextBox^  tbDiscount;

	private: System::Windows::Forms::Label^  label27;
private: System::Windows::Forms::CheckBox^  cbPaymentModeCash;
private: System::Windows::Forms::CheckBox^  cbPaymentModeCard;
private: System::Windows::Forms::CheckBox^  cbPaymentModeCheque;



	private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::RadioButton^  rbInvoiceTypeNew;
private: System::Windows::Forms::RadioButton^  rbInvoiceTypeDebit;
private: System::Windows::Forms::RadioButton^  rbInvoiceTypeCredit;



private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::Label^  label30;
private: System::Windows::Forms::Label^  lblNote;
private: System::Drawing::Printing::PrintDocument^  printDocInvoice;
private: System::Windows::Forms::PrintPreviewDialog^  printPreviewInvoice;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::ComboBox^  cbFilterFloor;
private: System::Windows::Forms::Button^  btnViewOldData;









	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent()
		{
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tbName = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->tbCnic = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->dtpTimeIn = (gcnew System::Windows::Forms::DateTimePicker());
			this->dtpTimeOut = (gcnew System::Windows::Forms::DateTimePicker());
			this->dgvRoomData = (gcnew System::Windows::Forms::DataGridView());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->btnRefresh = (gcnew System::Windows::Forms::Button());
			this->tbNoOfRooms = (gcnew System::Windows::Forms::TextBox());
			this->tbRoomCharges = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->tbGst = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->tbPayable = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->btnPrint = (gcnew System::Windows::Forms::Button());
			this->btnCalculateTotal = (gcnew System::Windows::Forms::Button());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->tbInvoiceNo = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->tbContact = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->tbEmergencyContact = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->cbNationality = (gcnew System::Windows::Forms::ComboBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->tbAddress = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->dtpDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->dtpDateIn = (gcnew System::Windows::Forms::DateTimePicker());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->dtpDateOut = (gcnew System::Windows::Forms::DateTimePicker());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->tbBuyerPNTN = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->lblManagerName = (gcnew System::Windows::Forms::Label());
			this->tbRoomNo = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->tbDiscount = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->cbPaymentModeCash = (gcnew System::Windows::Forms::CheckBox());
			this->cbPaymentModeCard = (gcnew System::Windows::Forms::CheckBox());
			this->cbPaymentModeCheque = (gcnew System::Windows::Forms::CheckBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->rbInvoiceTypeNew = (gcnew System::Windows::Forms::RadioButton());
			this->rbInvoiceTypeDebit = (gcnew System::Windows::Forms::RadioButton());
			this->rbInvoiceTypeCredit = (gcnew System::Windows::Forms::RadioButton());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->lblNote = (gcnew System::Windows::Forms::Label());
			this->printDocInvoice = (gcnew System::Drawing::Printing::PrintDocument());
			this->printPreviewInvoice = (gcnew System::Windows::Forms::PrintPreviewDialog());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->cbFilterFloor = (gcnew System::Windows::Forms::ComboBox());
			this->btnViewOldData = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvRoomData))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::RoyalBlue;
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(1338, 45);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Hotel Blue Sky";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(20, 54);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(272, 36);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Customer Information";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(14, 323);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 17);
			this->label3->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(24, 140);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(68, 25);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Name";
			// 
			// tbName
			// 
			this->tbName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbName->Location = System::Drawing::Point(119, 135);
			this->tbName->MaxLength = 50;
			this->tbName->Name = L"tbName";
			this->tbName->Size = System::Drawing::Size(313, 30);
			this->tbName->TabIndex = 3;
			this->tbName->Text = L"Muhammad Awais Shafi";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(20, 183);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(65, 25);
			this->label5->TabIndex = 0;
			this->label5->Text = L"CNIC";
			// 
			// tbCnic
			// 
			this->tbCnic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbCnic->Location = System::Drawing::Point(119, 178);
			this->tbCnic->MaxLength = 15;
			this->tbCnic->Name = L"tbCnic";
			this->tbCnic->Size = System::Drawing::Size(313, 30);
			this->tbCnic->TabIndex = 5;
			this->tbCnic->Text = L"61101-8903163-3";
			this->tbCnic->Enter += gcnew System::EventHandler(this, &MainForm::tbCnic_Enter);
			this->tbCnic->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::tbCnic_KeyPress);
			this->tbCnic->Leave += gcnew System::EventHandler(this, &MainForm::tbCnic_Leave);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(761, 607);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(123, 25);
			this->label6->TabIndex = 0;
			this->label6->Text = L"No# Rooms";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(21, 356);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(86, 25);
			this->label7->TabIndex = 0;
			this->label7->Text = L"Time-In";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(455, 356);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(103, 25);
			this->label8->TabIndex = 0;
			this->label8->Text = L"Time-Out";
			// 
			// dtpTimeIn
			// 
			this->dtpTimeIn->CalendarFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->dtpTimeIn->CustomFormat = L"hh:mm tt";
			this->dtpTimeIn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpTimeIn->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dtpTimeIn->Location = System::Drawing::Point(119, 351);
			this->dtpTimeIn->Name = L"dtpTimeIn";
			this->dtpTimeIn->Size = System::Drawing::Size(313, 30);
			this->dtpTimeIn->TabIndex = 12;
			this->dtpTimeIn->Value = System::DateTime(2024, 8, 19, 21, 40, 0, 0);
			// 
			// dtpTimeOut
			// 
			this->dtpTimeOut->CalendarFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->dtpTimeOut->CustomFormat = L"hh:mm tt";
			this->dtpTimeOut->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpTimeOut->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dtpTimeOut->Location = System::Drawing::Point(611, 351);
			this->dtpTimeOut->Name = L"dtpTimeOut";
			this->dtpTimeOut->Size = System::Drawing::Size(285, 30);
			this->dtpTimeOut->TabIndex = 13;
			this->dtpTimeOut->Value = System::DateTime(2024, 8, 19, 21, 40, 0, 0);
			// 
			// dgvRoomData
			// 
			this->dgvRoomData->AllowUserToAddRows = false;
			this->dgvRoomData->AllowUserToDeleteRows = false;
			this->dgvRoomData->AllowUserToResizeColumns = false;
			this->dgvRoomData->AllowUserToResizeRows = false;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::Silver;
			this->dgvRoomData->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
			this->dgvRoomData->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dgvRoomData->BackgroundColor = System::Drawing::Color::LightSteelBlue;
			this->dgvRoomData->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dgvRoomData->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::DodgerBlue;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle2->Padding = System::Windows::Forms::Padding(5);
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvRoomData->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
			this->dgvRoomData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Menu;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvRoomData->DefaultCellStyle = dataGridViewCellStyle3;
			this->dgvRoomData->EnableHeadersVisualStyles = false;
			this->dgvRoomData->GridColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->dgvRoomData->Location = System::Drawing::Point(25, 422);
			this->dgvRoomData->Name = L"dgvRoomData";
			this->dgvRoomData->RowHeadersVisible = false;
			this->dgvRoomData->RowTemplate->Height = 24;
			this->dgvRoomData->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgvRoomData->Size = System::Drawing::Size(716, 256);
			this->dgvRoomData->TabIndex = 7;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(24, 394);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(145, 25);
			this->label12->TabIndex = 0;
			this->label12->Text = L"Select Rooms";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnRefresh
			// 
			this->btnRefresh->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRefresh->Location = System::Drawing::Point(747, 422);
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->Size = System::Drawing::Size(149, 30);
			this->btnRefresh->TabIndex = 7;
			this->btnRefresh->Text = L"Refresh";
			this->btnRefresh->UseVisualStyleBackColor = false;
			this->btnRefresh->Click += gcnew System::EventHandler(this, &MainForm::btnRefresh_Click);
			// 
			// tbNoOfRooms
			// 
			this->tbNoOfRooms->Enabled = false;
			this->tbNoOfRooms->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbNoOfRooms->Location = System::Drawing::Point(747, 635);
			this->tbNoOfRooms->Name = L"tbNoOfRooms";
			this->tbNoOfRooms->Size = System::Drawing::Size(149, 38);
			this->tbNoOfRooms->TabIndex = 1;
			this->tbNoOfRooms->Text = L"0";
			this->tbNoOfRooms->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// tbRoomCharges
			// 
			this->tbRoomCharges->Enabled = false;
			this->tbRoomCharges->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbRoomCharges->Location = System::Drawing::Point(1086, 141);
			this->tbRoomCharges->Name = L"tbRoomCharges";
			this->tbRoomCharges->Size = System::Drawing::Size(239, 38);
			this->tbRoomCharges->TabIndex = 1;
			this->tbRoomCharges->Text = L"0";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(914, 154);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(155, 25);
			this->label14->TabIndex = 0;
			this->label14->Text = L"Room Charges";
			// 
			// tbGst
			// 
			this->tbGst->Enabled = false;
			this->tbGst->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbGst->Location = System::Drawing::Point(1086, 199);
			this->tbGst->Name = L"tbGst";
			this->tbGst->Size = System::Drawing::Size(239, 38);
			this->tbGst->TabIndex = 1;
			this->tbGst->Text = L"0";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(914, 212);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(108, 25);
			this->label15->TabIndex = 0;
			this->label15->Text = L"GST-16%";
			// 
			// tbPayable
			// 
			this->tbPayable->Enabled = false;
			this->tbPayable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbPayable->Location = System::Drawing::Point(1086, 308);
			this->tbPayable->Name = L"tbPayable";
			this->tbPayable->Size = System::Drawing::Size(239, 38);
			this->tbPayable->TabIndex = 1;
			this->tbPayable->Text = L"0";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(918, 316);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(90, 25);
			this->label16->TabIndex = 0;
			this->label16->Text = L"Payable";
			// 
			// btnCancel
			// 
			this->btnCancel->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnCancel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCancel->Location = System::Drawing::Point(919, 458);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(124, 51);
			this->btnCancel->TabIndex = 16;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->UseVisualStyleBackColor = false;
			this->btnCancel->Click += gcnew System::EventHandler(this, &MainForm::btnCancel_Click);
			// 
			// btnSave
			// 
			this->btnSave->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnSave->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSave->Location = System::Drawing::Point(1060, 458);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(124, 51);
			this->btnSave->TabIndex = 17;
			this->btnSave->Text = L"Save";
			this->btnSave->UseVisualStyleBackColor = false;
			this->btnSave->Click += gcnew System::EventHandler(this, &MainForm::btnSave_Click);
			// 
			// btnPrint
			// 
			this->btnPrint->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnPrint->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnPrint->Location = System::Drawing::Point(1201, 458);
			this->btnPrint->Name = L"btnPrint";
			this->btnPrint->Size = System::Drawing::Size(124, 51);
			this->btnPrint->TabIndex = 18;
			this->btnPrint->Text = L"Print";
			this->btnPrint->UseVisualStyleBackColor = false;
			this->btnPrint->Click += gcnew System::EventHandler(this, &MainForm::btnPrint_Click);
			// 
			// btnCalculateTotal
			// 
			this->btnCalculateTotal->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnCalculateTotal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnCalculateTotal->Location = System::Drawing::Point(747, 458);
			this->btnCalculateTotal->Name = L"btnCalculateTotal";
			this->btnCalculateTotal->Size = System::Drawing::Size(149, 58);
			this->btnCalculateTotal->TabIndex = 15;
			this->btnCalculateTotal->Text = L"Calculate Total";
			this->btnCalculateTotal->UseVisualStyleBackColor = false;
			this->btnCalculateTotal->Click += gcnew System::EventHandler(this, &MainForm::btnCalculateTotal_Click);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->Location = System::Drawing::Point(21, 97);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(114, 25);
			this->label18->TabIndex = 0;
			this->label18->Text = L"Invoice No";
			// 
			// tbInvoiceNo
			// 
			this->tbInvoiceNo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbInvoiceNo->Location = System::Drawing::Point(150, 97);
			this->tbInvoiceNo->Name = L"tbInvoiceNo";
			this->tbInvoiceNo->Size = System::Drawing::Size(88, 27);
			this->tbInvoiceNo->TabIndex = 1;
			this->tbInvoiceNo->Text = L"001";
			this->tbInvoiceNo->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label19->Location = System::Drawing::Point(455, 140);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(120, 25);
			this->label19->TabIndex = 0;
			this->label19->Text = L"Contact No";
			// 
			// tbContact
			// 
			this->tbContact->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbContact->Location = System::Drawing::Point(679, 135);
			this->tbContact->MaxLength = 12;
			this->tbContact->Name = L"tbContact";
			this->tbContact->Size = System::Drawing::Size(217, 30);
			this->tbContact->TabIndex = 4;
			this->tbContact->Text = L"0340-8898238";
			this->tbContact->Enter += gcnew System::EventHandler(this, &MainForm::tbContact_Enter);
			this->tbContact->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::tbContact_KeyPress);
			this->tbContact->Leave += gcnew System::EventHandler(this, &MainForm::tbContact_Leave);
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->Location = System::Drawing::Point(455, 181);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(201, 25);
			this->label20->TabIndex = 0;
			this->label20->Text = L"Emergency Contact";
			// 
			// tbEmergencyContact
			// 
			this->tbEmergencyContact->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbEmergencyContact->Location = System::Drawing::Point(679, 175);
			this->tbEmergencyContact->MaxLength = 12;
			this->tbEmergencyContact->Name = L"tbEmergencyContact";
			this->tbEmergencyContact->Size = System::Drawing::Size(217, 30);
			this->tbEmergencyContact->TabIndex = 6;
			this->tbEmergencyContact->Text = L"0339-4098238";
			this->tbEmergencyContact->Enter += gcnew System::EventHandler(this, &MainForm::tbEmergencyContact_Enter);
			this->tbEmergencyContact->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::tbEmergencyContact_KeyPress);
			this->tbEmergencyContact->Leave += gcnew System::EventHandler(this, &MainForm::tbEmergencyContact_Leave);
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->Location = System::Drawing::Point(462, 227);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(113, 25);
			this->label21->TabIndex = 0;
			this->label21->Text = L"Nationality";
			// 
			// cbNationality
			// 
			this->cbNationality->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbNationality->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbNationality->FormattingEnabled = true;
			this->cbNationality->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Pakistani", L"Foreigners" });
			this->cbNationality->Location = System::Drawing::Point(611, 219);
			this->cbNationality->MaxDropDownItems = 2;
			this->cbNationality->Name = L"cbNationality";
			this->cbNationality->Size = System::Drawing::Size(285, 33);
			this->cbNationality->TabIndex = 8;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->Location = System::Drawing::Point(21, 272);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(92, 25);
			this->label22->TabIndex = 0;
			this->label22->Text = L"Address";
			// 
			// tbAddress
			// 
			this->tbAddress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbAddress->Location = System::Drawing::Point(119, 270);
			this->tbAddress->MaxLength = 50;
			this->tbAddress->Name = L"tbAddress";
			this->tbAddress->Size = System::Drawing::Size(777, 27);
			this->tbAddress->TabIndex = 9;
			this->tbAddress->Text = L"House 117, Dhoke Khaba, Rawalpindi, Pakistan";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label23->Location = System::Drawing::Point(455, 98);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(57, 25);
			this->label23->TabIndex = 0;
			this->label23->Text = L"Date";
			// 
			// dtpDate
			// 
			this->dtpDate->CalendarFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpDate->CustomFormat = L"yyyy-MM-dd HH:mm";
			this->dtpDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpDate->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dtpDate->Location = System::Drawing::Point(543, 93);
			this->dtpDate->Name = L"dtpDate";
			this->dtpDate->Size = System::Drawing::Size(353, 30);
			this->dtpDate->TabIndex = 2;
			this->dtpDate->Value = System::DateTime(2024, 8, 31, 14, 31, 50, 0);
			// 
			// dtpDateIn
			// 
			this->dtpDateIn->CalendarFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->dtpDateIn->CustomFormat = L"";
			this->dtpDateIn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpDateIn->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dtpDateIn->Location = System::Drawing::Point(119, 310);
			this->dtpDateIn->Name = L"dtpDateIn";
			this->dtpDateIn->Size = System::Drawing::Size(313, 30);
			this->dtpDateIn->TabIndex = 10;
			this->dtpDateIn->Value = System::DateTime(2024, 8, 29, 0, 0, 0, 0);
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label24->Location = System::Drawing::Point(21, 315);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(83, 25);
			this->label24->TabIndex = 0;
			this->label24->Text = L"Date-In";
			// 
			// dtpDateOut
			// 
			this->dtpDateOut->CalendarFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->dtpDateOut->CustomFormat = L"";
			this->dtpDateOut->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpDateOut->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dtpDateOut->Location = System::Drawing::Point(611, 310);
			this->dtpDateOut->Name = L"dtpDateOut";
			this->dtpDateOut->Size = System::Drawing::Size(285, 30);
			this->dtpDateOut->TabIndex = 11;
			this->dtpDateOut->Value = System::DateTime(2024, 8, 30, 0, 0, 0, 0);
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label25->Location = System::Drawing::Point(455, 315);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(100, 25);
			this->label25->TabIndex = 0;
			this->label25->Text = L"Date-Out";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(24, 227);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(132, 25);
			this->label9->TabIndex = 0;
			this->label9->Text = L"Buyer PNTN";
			// 
			// tbBuyerPNTN
			// 
			this->tbBuyerPNTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbBuyerPNTN->Location = System::Drawing::Point(182, 222);
			this->tbBuyerPNTN->MaxLength = 9;
			this->tbBuyerPNTN->Name = L"tbBuyerPNTN";
			this->tbBuyerPNTN->Size = System::Drawing::Size(250, 30);
			this->tbBuyerPNTN->TabIndex = 7;
			this->tbBuyerPNTN->Text = L"0715030-0";
			this->tbBuyerPNTN->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::tbBuyerPNTN_KeyPress);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(914, 58);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(94, 25);
			this->label13->TabIndex = 0;
			this->label13->Text = L"Charges";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(925, 676);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(144, 20);
			this->label10->TabIndex = 0;
			this->label10->Text = L"Booking Manager:";
			// 
			// lblManagerName
			// 
			this->lblManagerName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblManagerName->Location = System::Drawing::Point(1075, 676);
			this->lblManagerName->Name = L"lblManagerName";
			this->lblManagerName->Size = System::Drawing::Size(247, 20);
			this->lblManagerName->TabIndex = 0;
			this->lblManagerName->Text = L"Muhammad Awais Shafi";
			this->lblManagerName->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// tbRoomNo
			// 
			this->tbRoomNo->Enabled = false;
			this->tbRoomNo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbRoomNo->Location = System::Drawing::Point(1086, 94);
			this->tbRoomNo->Name = L"tbRoomNo";
			this->tbRoomNo->Size = System::Drawing::Size(239, 30);
			this->tbRoomNo->TabIndex = 1;
			this->tbRoomNo->Text = L"0";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(914, 99);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(111, 25);
			this->label17->TabIndex = 0;
			this->label17->Text = L"Rooms No";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label26->Location = System::Drawing::Point(914, 262);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(96, 25);
			this->label26->TabIndex = 0;
			this->label26->Text = L"Discount";
			// 
			// tbDiscount
			// 
			this->tbDiscount->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbDiscount->Location = System::Drawing::Point(1086, 249);
			this->tbDiscount->Name = L"tbDiscount";
			this->tbDiscount->Size = System::Drawing::Size(239, 38);
			this->tbDiscount->TabIndex = 1;
			this->tbDiscount->Text = L"0";
			this->tbDiscount->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::tbDiscount_KeyUp);
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label27->Location = System::Drawing::Point(914, 362);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(156, 25);
			this->label27->TabIndex = 0;
			this->label27->Text = L"Payment Mode";
			// 
			// cbPaymentModeCash
			// 
			this->cbPaymentModeCash->AutoSize = true;
			this->cbPaymentModeCash->Checked = true;
			this->cbPaymentModeCash->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbPaymentModeCash->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->cbPaymentModeCash->Location = System::Drawing::Point(1086, 363);
			this->cbPaymentModeCash->Name = L"cbPaymentModeCash";
			this->cbPaymentModeCash->Size = System::Drawing::Size(70, 24);
			this->cbPaymentModeCash->TabIndex = 15;
			this->cbPaymentModeCash->Text = L"Cash";
			this->cbPaymentModeCash->UseVisualStyleBackColor = true;
			// 
			// cbPaymentModeCard
			// 
			this->cbPaymentModeCard->AutoSize = true;
			this->cbPaymentModeCard->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->cbPaymentModeCard->Location = System::Drawing::Point(1163, 363);
			this->cbPaymentModeCard->Name = L"cbPaymentModeCard";
			this->cbPaymentModeCard->Size = System::Drawing::Size(67, 24);
			this->cbPaymentModeCard->TabIndex = 15;
			this->cbPaymentModeCard->Text = L"Card";
			this->cbPaymentModeCard->UseVisualStyleBackColor = true;
			// 
			// cbPaymentModeCheque
			// 
			this->cbPaymentModeCheque->AutoSize = true;
			this->cbPaymentModeCheque->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->cbPaymentModeCheque->Location = System::Drawing::Point(1237, 363);
			this->cbPaymentModeCheque->Name = L"cbPaymentModeCheque";
			this->cbPaymentModeCheque->Size = System::Drawing::Size(88, 24);
			this->cbPaymentModeCheque->TabIndex = 15;
			this->cbPaymentModeCheque->Text = L"Cheque";
			this->cbPaymentModeCheque->UseVisualStyleBackColor = true;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label28->Location = System::Drawing::Point(913, 403);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(136, 25);
			this->label28->TabIndex = 0;
			this->label28->Text = L"Invoice Type";
			// 
			// rbInvoiceTypeNew
			// 
			this->rbInvoiceTypeNew->AutoSize = true;
			this->rbInvoiceTypeNew->Checked = true;
			this->rbInvoiceTypeNew->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->rbInvoiceTypeNew->Location = System::Drawing::Point(1089, 404);
			this->rbInvoiceTypeNew->Name = L"rbInvoiceTypeNew";
			this->rbInvoiceTypeNew->Size = System::Drawing::Size(63, 24);
			this->rbInvoiceTypeNew->TabIndex = 16;
			this->rbInvoiceTypeNew->TabStop = true;
			this->rbInvoiceTypeNew->Text = L"New";
			this->rbInvoiceTypeNew->UseVisualStyleBackColor = true;
			// 
			// rbInvoiceTypeDebit
			// 
			this->rbInvoiceTypeDebit->AutoSize = true;
			this->rbInvoiceTypeDebit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->rbInvoiceTypeDebit->Location = System::Drawing::Point(1162, 404);
			this->rbInvoiceTypeDebit->Name = L"rbInvoiceTypeDebit";
			this->rbInvoiceTypeDebit->Size = System::Drawing::Size(70, 24);
			this->rbInvoiceTypeDebit->TabIndex = 16;
			this->rbInvoiceTypeDebit->Text = L"Debit";
			this->rbInvoiceTypeDebit->UseVisualStyleBackColor = true;
			// 
			// rbInvoiceTypeCredit
			// 
			this->rbInvoiceTypeCredit->AutoSize = true;
			this->rbInvoiceTypeCredit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->rbInvoiceTypeCredit->Location = System::Drawing::Point(1242, 404);
			this->rbInvoiceTypeCredit->Name = L"rbInvoiceTypeCredit";
			this->rbInvoiceTypeCredit->Size = System::Drawing::Size(75, 24);
			this->rbInvoiceTypeCredit->TabIndex = 16;
			this->rbInvoiceTypeCredit->Text = L"Credit";
			this->rbInvoiceTypeCredit->UseVisualStyleBackColor = true;
			// 
			// label29
			// 
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label29->Location = System::Drawing::Point(996, 615);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(322, 20);
			this->label29->TabIndex = 0;
			this->label29->Text = L"Hotel Blue Sky Management System";
			// 
			// label30
			// 
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label30->Location = System::Drawing::Point(992, 635);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(326, 20);
			this->label30->TabIndex = 12;
			this->label30->Text = L"Commettie Chock, Rawalpindi";
			// 
			// lblNote
			// 
			this->lblNote->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblNote->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->lblNote->Location = System::Drawing::Point(987, 512);
			this->lblNote->Name = L"lblNote";
			this->lblNote->Size = System::Drawing::Size(335, 91);
			this->lblNote->TabIndex = 12;
			// 
			// printDocInvoice
			// 
			this->printDocInvoice->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &MainForm::printDocInvoice_PrintPage);
			// 
			// printPreviewInvoice
			// 
			this->printPreviewInvoice->AutoScrollMargin = System::Drawing::Size(0, 0);
			this->printPreviewInvoice->AutoScrollMinSize = System::Drawing::Size(0, 0);
			this->printPreviewInvoice->ClientSize = System::Drawing::Size(400, 300);
			this->printPreviewInvoice->Enabled = true;
			this->printPreviewInvoice->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"printPreviewInvoice.Icon")));
			this->printPreviewInvoice->Name = L"printPreviewInvoice";
			this->printPreviewInvoice->Visible = false;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->label11->Location = System::Drawing::Point(919, 512);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(49, 20);
			this->label11->TabIndex = 12;
			this->label11->Text = L"Note:";
			// 
			// cbFilterFloor
			// 
			this->cbFilterFloor->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbFilterFloor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbFilterFloor->FormattingEnabled = true;
			this->cbFilterFloor->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Floor 1", L"Floor 2", L"Floor 3", L"All Floor" });
			this->cbFilterFloor->Location = System::Drawing::Point(607, 392);
			this->cbFilterFloor->MaxDropDownItems = 2;
			this->cbFilterFloor->Name = L"cbFilterFloor";
			this->cbFilterFloor->Size = System::Drawing::Size(134, 24);
			this->cbFilterFloor->TabIndex = 14;
			this->cbFilterFloor->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cbFilterFloor_SelectedIndexChanged);
			// 
			// btnViewOldData
			// 
			this->btnViewOldData->BackColor = System::Drawing::Color::DarkSlateGray;
			this->btnViewOldData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnViewOldData->ForeColor = System::Drawing::Color::Snow;
			this->btnViewOldData->Location = System::Drawing::Point(729, 48);
			this->btnViewOldData->Name = L"btnViewOldData";
			this->btnViewOldData->Size = System::Drawing::Size(167, 30);
			this->btnViewOldData->TabIndex = 19;
			this->btnViewOldData->Text = L"View Old Data";
			this->btnViewOldData->UseVisualStyleBackColor = false;
			this->btnViewOldData->Click += gcnew System::EventHandler(this, &MainForm::btnViewOldData_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightSteelBlue;
			this->ClientSize = System::Drawing::Size(1338, 705);
			this->Controls->Add(this->rbInvoiceTypeCredit);
			this->Controls->Add(this->rbInvoiceTypeDebit);
			this->Controls->Add(this->rbInvoiceTypeNew);
			this->Controls->Add(this->cbPaymentModeCheque);
			this->Controls->Add(this->cbPaymentModeCard);
			this->Controls->Add(this->cbPaymentModeCash);
			this->Controls->Add(this->cbFilterFloor);
			this->Controls->Add(this->cbNationality);
			this->Controls->Add(this->tbInvoiceNo);
			this->Controls->Add(this->label25);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->lblManagerName);
			this->Controls->Add(this->label30);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->lblNote);
			this->Controls->Add(this->label29);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->btnPrint);
			this->Controls->Add(this->btnSave);
			this->Controls->Add(this->btnCalculateTotal);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnViewOldData);
			this->Controls->Add(this->btnRefresh);
			this->Controls->Add(this->dtpDateOut);
			this->Controls->Add(this->dgvRoomData);
			this->Controls->Add(this->dtpDateIn);
			this->Controls->Add(this->dtpTimeOut);
			this->Controls->Add(this->dtpDate);
			this->Controls->Add(this->dtpTimeIn);
			this->Controls->Add(this->label28);
			this->Controls->Add(this->label27);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label26);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->tbPayable);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->tbDiscount);
			this->Controls->Add(this->tbGst);
			this->Controls->Add(this->tbBuyerPNTN);
			this->Controls->Add(this->tbCnic);
			this->Controls->Add(this->tbRoomCharges);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->tbRoomNo);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->tbNoOfRooms);
			this->Controls->Add(this->tbAddress);
			this->Controls->Add(this->tbEmergencyContact);
			this->Controls->Add(this->tbContact);
			this->Controls->Add(this->tbName);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(1356, 752);
			this->MinimumSize = System::Drawing::Size(1356, 752);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Hotel Blue Sky";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvRoomData))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void tbCnic_Enter(System::Object^  sender, System::EventArgs^  e) {
	if (tbCnic->Text == "xxxxx-xxxxxxx-x") {
		tbCnic->Text = "";
	}
}
private: System::Void tbCnic_Leave(System::Object^  sender, System::EventArgs^  e) {
	if (tbCnic->Text == ""){
		tbCnic->Text = "xxxxx-xxxxxxx-x";
	}
}
private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ filterFloor = cbFilterFloor->SelectedItem->ToString();
	LoadRoomData(filterFloor);
}

private:
	void LoadRoomData(String^ filterFloor)
	{
		lblManagerName->Text = bookingManagerName;
		cbNationality->SelectedItem = "Pakistani";
		cbFilterFloor->SelectedItem = filterFloor;

		String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
		SqlConnection^ conDataBase = gcnew SqlConnection(conString);

		String^ query;
		if (filterFloor == "Floor 1") {
			query = "SELECT Room, Type, Category, Rent FROM room WHERE Room >= 100 AND Room < 200;";
		}
		else if (filterFloor == "Floor 2") {
			query = "SELECT Room, Type, Category, Rent FROM room WHERE Room >= 200 AND Room < 300;";
		}
		else if (filterFloor == "Floor 3") {
			query = "SELECT Room, Type, Category, Rent FROM room WHERE Room >= 300 AND Room < 400;";
		}
		else { // All Floor
			query = "SELECT Room, Type, Category, Rent FROM room;";
		}
		SqlCommand^ cmdDataBase = gcnew SqlCommand(query, conDataBase);

		try {
			SqlDataAdapter^ sda = gcnew SqlDataAdapter();
			sda->SelectCommand = cmdDataBase;
			DataTable^ dbdataset = gcnew DataTable();
			sda->Fill(dbdataset);
			BindingSource^ bSource = gcnew BindingSource();

			// Check if the checkbox column already exists
			if (!dgvRoomData->Columns->Contains("chkSelect")) {
				// Create a new DataGridViewCheckBoxColumn
				DataGridViewCheckBoxColumn^ chkColumn = gcnew DataGridViewCheckBoxColumn();
				chkColumn->HeaderText = "Select";  // Set the header text for the column
				chkColumn->Name = "chkSelect";     // Set the name of the column
				//chkColumn->Width = 50;             // Optional: set the width of the checkbox column

												   // Add the checkbox column to the DataGridView
				dgvRoomData->Columns->Add(chkColumn);

				// Adjust the column order so that the checkbox appears first
				dgvRoomData->Columns["chkSelect"]->DisplayIndex = 0;
			}
			//this is comment
			bSource->DataSource = dbdataset;
			dgvRoomData->DataSource = bSource;

			// Optional: Remove the Update command if not needed
			// sda->Update(dbdataset);
		}
		catch (Exception^ ex) {
			MessageBox::Show(ex->Message);
		}
		finally
		{
			conDataBase->Close();
		}
	}
	void LoadDataOnce()
	{
		String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
		SqlConnection^ conDataBase = gcnew SqlConnection(conString);
		SqlCommand^ cmdDataBase = gcnew SqlCommand("SELECT TOP 1 InvoiceNo FROM customer ORDER BY InvoiceNo DESC;", conDataBase);

		try
		{
			conDataBase->Open();
			SqlDataReader^ reader = cmdDataBase->ExecuteReader();
			String^ latestInvoiceNo = "0";

			if (reader->Read())
			{
				latestInvoiceNo = reader["InvoiceNo"]->ToString();
			}

			reader->Close();
			conDataBase->Close();

			// Increment the invoice number
			int invoiceNo;
			if (Int32::TryParse(latestInvoiceNo, invoiceNo))
			{
				invoiceNo++;
				tbInvoiceNo->Text = invoiceNo.ToString();
			}
			else
			{
				tbInvoiceNo->Text = "001"; // Start from 1 if conversion fails
			}
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->Message);
		}
		finally
		{
			if (conDataBase->State == ConnectionState::Open)
			{
				conDataBase->Close();
			}
		}
	}


private: System::Void btnCalculateTotal_Click(System::Object^  sender, System::EventArgs^  e) {
	//on click btnCalculateTotal function code here
	
	int noOfRooms = 0;
	String^ roomNo = "";
	double roomCharges = 0;
	double gst = 0;
	double payable = 0;

	for (int i = 0; i < dgvRoomData->Rows->Count; i++)
	{
		DataGridViewRow^ row = dgvRoomData->Rows[i];

		//check if checkboxes in the row is selected
		bool isSelected = Convert::ToBoolean(row->Cells["chkSelect"]->Value);
		
		if (isSelected)
		{
			// Fetch number of rooms and rent from the respective cells
			String^ rooms = Convert::ToString(row->Cells["Room"]->Value);
			double rent = Convert::ToDouble(row->Cells["Rent"]->Value);
			roomNo = roomNo + rooms + ", ";
			//noOfRooms += rooms;
			noOfRooms++;
			//roomCharges += (rooms * rent);
			roomCharges += rent;
		}
	}

	// Apply GST
	gst = roomCharges * 0.16;

	// Calculate Grand Total
	payable = roomCharges + gst;

	// Display the results in the respective text fields
	tbNoOfRooms->Text = noOfRooms.ToString();
	tbRoomNo->Text = roomNo;
	//tbRoomCharges->Text = roomCharges.ToString("F2");  // F2 formats to 2 decimal places
	tbRoomCharges->Text = roomCharges.ToString(); 
	tbGst->Text = gst.ToString();
	tbPayable->Text = payable.ToString();

	if (noOfRooms == 0)
	{
		tbRoomNo->Text = "0";
	}
}
private: System::Void btnCancel_Click(System::Object^  sender, System::EventArgs^  e) {
	LoadRoomData("All Floor");
	tbRoomNo->Text = "0";
	tbNoOfRooms->Text = "0";
	tbRoomCharges->Text = "0";
	tbGst->Text = "0";
	tbPayable->Text = "0";
	tbDiscount->Text = "0";
}
private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {

	// checking of there is any empty fields
	if (tbInvoiceNo->Text == ""
		|| dtpDate->Text == ""
		|| tbName->Text == ""
		|| tbContact->Text == ""
		|| tbCnic->Text == ""
		|| tbCnic->Text == "xxxxx-xxxxxxx-x"
		|| tbEmergencyContact->Text == ""
		|| cbNationality->Text == ""
		|| tbAddress->Text == ""
		|| dtpDateIn->Text == ""
		|| dtpDateOut->Text == ""
		|| dtpTimeIn->Text == ""
		|| dtpTimeOut->Text == ""
		|| tbNoOfRooms->Text == ""
		|| tbRoomNo->Text == ""
		|| tbRoomCharges->Text == ""
		|| tbGst->Text == ""
		|| tbPayable->Text == "")
	{
		MessageBox::Show("Kindly fill all the fields.", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Error);
		//return;
	}

	if (tbRoomCharges->Text == "" || tbRoomCharges->Text == "0") {
		MessageBox::Show("Select Room and then click on Calculate Total", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return;
	}

	//////
	// save UI data into variables for easy access
	//////

	//Make variables to store fetched data from fields from UI's
	String^ invoiceNo = tbInvoiceNo->Text->ToString(); // varchar(50) == String
	String^ name = tbName->Text->ToString(); // varchar(150) == String
	String^ cnic = tbCnic->Text->ToString(); // varchar(15) == String
	String^ buyerPNTN = tbBuyerPNTN->Text->ToString(); // varchar(9) == String
	String^ address = tbAddress->Text->ToString(); // varchar(MAX) == String
	String^ contact = tbContact->Text->ToString(); // varchar(20) == String
	String^ emergencyContact = tbEmergencyContact->Text->ToString(); // varchar(20) == String
	//String^ date = dtpDate->Text->ToString(); //tbEmergencyContact->Text->ToString(); // date
	DateTime date = dtpDate->Value;
	String^ praFormatDateTime = date.ToString("yyyy-MM-dd HH:mm:ss.fff");
	DateTime dateIn = dtpDateIn->Value;
	String^ praFormatDateIn = dateIn.ToString("yyyy-MM-dd");
	DateTime dateOut = dtpDateOut->Value;
	String^ praFormatDateOut = dateOut.ToString("yyyy-MM-dd");
	DateTime timeIn = dtpTimeIn->Value;
	String^ praFormatTimeIn = timeIn.ToString("hh:mm tt");
	DateTime timeOut = dtpTimeOut->Value;
	String^ praFormatTimeOut = timeOut.ToString("hh:mm tt");
	String^ nationality = cbNationality->Text->ToString();
	double noOfRooms = Convert::ToDouble(tbNoOfRooms->Text);
	double roomCharges = Convert::ToDouble(tbRoomCharges->Text);
	double gst = Convert::ToDouble(tbGst->Text);
	double discount = Convert::ToDouble(tbDiscount->Text);
	double payable = Convert::ToDouble(tbPayable->Text);

	// Initialize the value to 0
	int paymentMode = 0;

	// Check if cbPaymentModeCash is checked
	if (cbPaymentModeCash->Checked) {
		paymentMode = 1;
	}
	if (cbPaymentModeCard->Checked) {
		paymentMode = 2;
	}
	if (cbPaymentModeCheque->Checked) {
		paymentMode = 3;
	}
	// If more than one CheckBox is checked, set the value to 5 which is mixed according to PRA Doc
	if ((cbPaymentModeCash->Checked && cbPaymentModeCard->Checked) ||
		(cbPaymentModeCash->Checked && cbPaymentModeCheque->Checked) ||
		(cbPaymentModeCard->Checked && cbPaymentModeCheque->Checked)) {
		paymentMode = 5;
	}

	switch (paymentMode) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		break;
	default:
		MessageBox::Show("Kindly Select Any Payment Mode.");
		return;
		break;
	}

	int invoiceType = 0;
	if (rbInvoiceTypeNew->Checked)
	{
		invoiceType = 1;
	} 
	else if (rbInvoiceTypeDebit->Checked)
	{
		invoiceType = 2;
	} 
	else if (rbInvoiceTypeCredit->Checked)
	{
		invoiceType = 3;
	}


	/*
	MessageBox::Show("InvoiceNo: "+invoiceNo
		+ "\nName: "+name
		+ "\nCNIC: " + cnic
		+ "\nBuyerPNTN: " + buyerPNTN
		+ "\nAddress: " + address
		+ "\nContact: " + contact
		+ "\nEmergency Contact: " + emergencyContact
		+ "\nDate: " + praFormatDateTime
		+ "\nDate-In: " + praFormatDateIn
		+ "\nDate-Out: " + praFormatDateOut
		+ "\nTime-In: " + praFormatTimeIn
		+ "\nTime-Out: " + praFormatTimeOut
		+ "\nNationality: " + nationality
		+ "\nPayment Mode: " + paymentMode
		+ "\nInvoice Type: " + invoiceType
		+ "\nBooking Manager Name: " + bookingManagerName
	);
	*/

	///////////
	//send above data to PRA API for PRA invoice number 
	//////////
	Invoice custInv;
	custInv.InvoiceNumber = "";  // or provide a valid default
	custInv.POSID = 814741;  // Change to appropriate value if required
	custInv.USIN = msclr::interop::marshal_as<std::string>(invoiceNo->ToString());
	custInv.DateTime = msclr::interop::marshal_as<std::string>(praFormatDateTime->ToString());
	custInv.BuyerPNTN = msclr::interop::marshal_as<std::string>(buyerPNTN->ToString());
	custInv.BuyerCNIC = msclr::interop::marshal_as<std::string>(cnic->ToString());
	custInv.BuyerName = msclr::interop::marshal_as<std::string>(name->ToString());
	custInv.BuyerPhoneNumber = msclr::interop::marshal_as<std::string>(contact->ToString());
	custInv.TotalSaleValue = roomCharges;
	custInv.TotalQuantity = noOfRooms;
	custInv.TotalBillAmount = payable;
	custInv.TotalTaxCharged = gst;
	custInv.Discount = discount;
	custInv.FurtherTax = payable;
	custInv.PaymentMode = paymentMode;
	custInv.RefUSIN = "";  // Ensure this matches expected format
	custInv.InvoiceType = invoiceType;
	custInv.Items = CreateItems(); // send items to CreateItems list constructor
	// make a loop to send items to createitems one by one till the number of items complete

	//convert above invoice to JSON Formate 
	nlohmann::json jsonObj = {
		{ "InvoiceNumber", custInv.InvoiceNumber },
		{ "POSID", custInv.POSID },
		{ "USIN", custInv.USIN },
		{ "DateTime", custInv.DateTime },
		{ "BuyerPNTN", custInv.BuyerPNTN },
		{ "BuyerCNIC", custInv.BuyerCNIC },
		{ "BuyerName", custInv.BuyerName },
		{ "BuyerPhoneNumber", custInv.BuyerPhoneNumber },
		{ "TotalSaleValue", custInv.TotalSaleValue },
		{ "TotalQuantity", custInv.TotalQuantity },
		{ "TotalBillAmount", custInv.TotalBillAmount },
		{ "TotalTaxCharged", custInv.TotalTaxCharged },
		{ "Discount", custInv.Discount },
		{ "FurtherTax", custInv.FurtherTax },
		{ "PaymentMode", custInv.PaymentMode },
		{ "RefUSIN", custInv.RefUSIN },
		{ "InvoiceType", custInv.InvoiceType },
		{ "Items", nlohmann::json::array() }
	};

	// Add Items to JSON (createitems)
	for (const auto& item : custInv.Items) {
		jsonObj["Items"].push_back({
			{ "ItemCode", item.ItemCode },
			{ "ItemName", item.ItemName },
			{ "Quantity", item.Quantity },
			{ "PCTCode", item.PCTCode },
			{ "TaxRate", item.TaxRate },
			{ "SaleValue", item.SaleValue },
			{ "TotalAmount", item.TotalAmount },
			{ "TaxCharged", item.TaxCharged },
			{ "Discount", item.Discount },
			{ "FurtherTax", item.FurtherTax },
			{ "InvoiceType", item.InvoiceType },
			{ "RefUSIN", item.RefUSIN }
			});
	}

	// Send data to the API and get the response
	std::string response = SendInvoiceData(jsonObj);

	// Parse the response to extract the InvoiceNumber
	nlohmann::json responseJson = nlohmann::json::parse(response);
	std::string invoiceNumber = responseJson.contains("InvoiceNumber") ? responseJson["InvoiceNumber"] : "Not Available";
	std::string apiResponseMessage = responseJson.contains("Response") ? responseJson["Response"] : "No Response";
	std::string apiCodeMessage = responseJson.contains("Code") ? responseJson["Code"] : "No Response";
	std::string apiErrorsMessage = responseJson.contains("Errors") ? responseJson["Errors"] : "No Response";

	String^ praInvoiceNo = gcnew String(invoiceNumber.c_str());
	praInvoiceNumberGlobalDeclare = praInvoiceNo;
	String^ apiResponseMessageStr = gcnew String(apiResponseMessage.c_str());
	if (apiCodeMessage == "100")
	{
		lblNote->Text = praInvoiceNo;
		MessageBox::Show("PRA Invoice Number: " + praInvoiceNo, "Success", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}
	else {
		// Display the InvoiceNumber and response message in a message box
		String^ apiCodeMessageStr = gcnew String(apiCodeMessage.c_str());
		String^ apiErrorsMessageStr = gcnew String(apiErrorsMessage.c_str());
		MessageBox::Show("Generated Invoice Number: " + praInvoiceNo
			+ "\nCode: " + apiCodeMessageStr
			+ "\nAPI Response: " + apiResponseMessageStr
			+ "\nErrors: " + apiErrorsMessageStr
			, "API Response", MessageBoxButtons::OK, MessageBoxIcon::Information);

		lblNote->Text = apiResponseMessageStr;
		return;
	}

	///////////
	//saving data to database customer table
	//////////

	String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
	// Create the SQL query string
	String^ query = "INSERT INTO customer (InvoiceNo, PRAInvoiceNo, Date, Name, CNIC, BuyerPNTN, ContactNo, EmergencyContact, Address, Nationality, DateIn, DateOut, TimeIn, TimeOut, RoomNo, NoOfRooms, RoomCharges, GST, Discount, Payable, PaymentMode, InvoiceType, ManagerName) VALUES (@InvoiceNo, @PRAInvoiceNo, @Date, @Name, @CNIC, @BuyerPNTN, @ContactNo, @EmergencyContact, @Address, @Nationality, @DateIn, @DateOut, @TimeIn, @TimeOut, @RoomNo, @NoOfRooms, @RoomCharges, @GST, @Discount, @Payable, @PaymentMode, @InvoiceType, @ManagerName);";

	// Assuming you have a connection string
	SqlConnection^ connection = gcnew SqlConnection(conString);

	try {
		connection->Open();

		// Create a SqlCommand object
		SqlCommand^ command = gcnew SqlCommand(query, connection);

		/*
		
		MessageBox::Show("InvoiceNo: "+invoiceNo
		+ "\nName: "+name
		+ "\nCNIC: " + cnic
		+ "\nBuyerPNTN: " + buyerPNTN
		+ "\nAddress: " + address
		+ "\nContact: " + contact
		+ "\nEmergency Contact: " + emergencyContact
		+ "\nDate: " + praFormatDateTime
		+ "\nDate-In: " + praFormatDateIn
		+ "\nDate-Out: " + praFormatDateOut
		+ "\nTime-In: " + praFormatTimeIn
		+ "\nTime-Out: " + praFormatTimeOut
		+ "\nNationality: " + nationality
		+ "\nPayment Mode: " + paymentMode
		+ "\nInvoice Type: " + invoiceType
		);
		
		*/

		String^ roomNo = tbRoomNo->Text->ToString();

		// Bind the parameters with data from text boxes
		command->Parameters->AddWithValue("@InvoiceNo", invoiceNo);//Unique Key Constraint
		command->Parameters->AddWithValue("@PRAInvoiceNo", praInvoiceNo);
		command->Parameters->AddWithValue("@Date", praFormatDateTime);
		command->Parameters->AddWithValue("@Name", name);
		command->Parameters->AddWithValue("@CNIC", cnic);
		command->Parameters->AddWithValue("@BuyerPNTN", buyerPNTN);
		command->Parameters->AddWithValue("@ContactNo", contact);
		command->Parameters->AddWithValue("@EmergencyContact", emergencyContact);
		command->Parameters->AddWithValue("@Address", address);
		command->Parameters->AddWithValue("@Nationality", nationality);
		command->Parameters->AddWithValue("@DateIn", praFormatDateIn);
		command->Parameters->AddWithValue("@DateOut", praFormatDateOut);
		command->Parameters->AddWithValue("@TimeIn", praFormatTimeIn);
		command->Parameters->AddWithValue("@TimeOut", praFormatTimeOut);
		command->Parameters->AddWithValue("@RoomNo", roomNo);
		command->Parameters->AddWithValue("@NoOfRooms", noOfRooms);
		command->Parameters->AddWithValue("@RoomCharges", roomCharges);
		command->Parameters->AddWithValue("@GST", gst);
		command->Parameters->AddWithValue("@Discount", discount);
		command->Parameters->AddWithValue("@Payable", payable);
		command->Parameters->AddWithValue("@PaymentMode", paymentMode);
		command->Parameters->AddWithValue("@InvoiceType", invoiceType);
		command->Parameters->AddWithValue("@ManagerName", bookingManagerName);

		// Execute the query
		command->ExecuteNonQuery();

		MessageBox::Show("Data saved successfully!", "Save", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	catch (Exception^ ex) {
		MessageBox::Show("An error occurred: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	finally{
		connection->Close();
	}

	/*

	//////
	// API Code below
	//////

	Invoice objInv;
	objInv.InvoiceNumber = "";  // or provide a valid default
	objInv.POSID = 814741;  // Change to appropriate value if required
	objInv.USIN = "001";
	objInv.DateTime = "2024-08-27 12:00:00.000";  // Ensure this matches expected format
	objInv.BuyerPNTN = "0715030-0";
	objInv.BuyerCNIC = "12345-1234567-8";
	objInv.BuyerName = "Muhammad Awais";
	objInv.BuyerPhoneNumber = "0340-8898238";
	objInv.TotalSaleValue = 0.0;
	objInv.TotalQuantity = 0.0;
	objInv.TotalBillAmount = 0.0;
	objInv.TotalTaxCharged = 0.0;
	objInv.Discount = 0.0;
	objInv.FurtherTax = 0.0;
	objInv.PaymentMode = 1;
	objInv.RefUSIN = "";  // Ensure this matches expected format
	objInv.InvoiceType = 1;
	objInv.Items = CreateItems(); // Populate Items list with correct data

								  // Convert Invoice to JSON
	nlohmann::json jsonObj = {
		{ "InvoiceNumber", objInv.InvoiceNumber },
	{ "POSID", objInv.POSID },
	{ "USIN", objInv.USIN },
	{ "DateTime", objInv.DateTime },
	{ "BuyerPNTN", objInv.BuyerPNTN },
	{ "BuyerCNIC", objInv.BuyerCNIC },
	{ "BuyerName", objInv.BuyerName },
	{ "BuyerPhoneNumber", objInv.BuyerPhoneNumber },
	{ "TotalSaleValue", objInv.TotalSaleValue },
	{ "TotalQuantity", objInv.TotalQuantity },
	{ "TotalBillAmount", objInv.TotalBillAmount },
	{ "TotalTaxCharged", objInv.TotalTaxCharged },
	{ "Discount", objInv.Discount },
	{ "FurtherTax", objInv.FurtherTax },
	{ "PaymentMode", objInv.PaymentMode },
	{ "RefUSIN", objInv.RefUSIN },
	{ "InvoiceType", objInv.InvoiceType },
	{ "Items", nlohmann::json::array() }
	};


	// Add Items to JSON
	for (const auto& item : objInv.Items) {
		jsonObj["Items"].push_back({
			{ "ItemCode", item.ItemCode },
			{ "ItemName", item.ItemName },
			{ "Quantity", item.Quantity },
			{ "PCTCode", item.PCTCode },
			{ "TaxRate", item.TaxRate },
			{ "SaleValue", item.SaleValue },
			{ "TotalAmount", item.TotalAmount },
			{ "TaxCharged", item.TaxCharged },
			{ "Discount", item.Discount },
			{ "FurtherTax", item.FurtherTax },
			{ "InvoiceType", item.InvoiceType },
			{ "RefUSIN", item.RefUSIN }
			});
	}

	// Send data to the API and get the response
	std::string response = SendInvoiceData(jsonObj);

	// Parse the response to extract the InvoiceNumber
	nlohmann::json responseJson = nlohmann::json::parse(response);
	std::string invoiceNumber = responseJson.contains("InvoiceNumber") ? responseJson["InvoiceNumber"] : "Not Available";
	std::string apiResponseMessage = responseJson.contains("Response") ? responseJson["Response"] : "No Response";
	std::string apiCodeMessage = responseJson.contains("Code") ? responseJson["Code"] : "No Response";
	std::string apiErrorsMessage = responseJson.contains("Errors") ? responseJson["Errors"] : "No Response";

	// Display the InvoiceNumber and response message in a message box
	String^ praInvoiceNo = gcnew String(invoiceNumber.c_str());
	String^ apiResponseMessageStr = gcnew String(apiResponseMessage.c_str());
	String^ apiCodeMessageStr = gcnew String(apiCodeMessage.c_str());
	String^ apiErrorsMessageStr = gcnew String(apiErrorsMessage.c_str());
	MessageBox::Show("Generated Invoice Number: " + praInvoiceNo 
		+ "\nCode: " + apiCodeMessageStr
		+ "\nAPI Response: " + apiResponseMessageStr
		+ "\nErrors: " + apiErrorsMessageStr
		, "API Response" , MessageBoxButtons::OK, MessageBoxIcon::Information);

	*/

}
private: System::Void tbContact_Enter(System::Object^  sender, System::EventArgs^  e) {
	if (tbContact->Text == "03xx-xxxxxxx") {
		tbContact->Text = "";
	}
}
private: System::Void tbContact_Leave(System::Object^  sender, System::EventArgs^  e) {
	if (tbContact->Text == "") {
		tbContact->Text = "03xx-xxxxxxx";
	}
}
private: System::Void tbEmergencyContact_Enter(System::Object^  sender, System::EventArgs^  e) {
	if (tbEmergencyContact->Text == "03xx-xxxxxxx") {
		tbEmergencyContact->Text = "";
	}
}
private: System::Void tbEmergencyContact_Leave(System::Object^  sender, System::EventArgs^  e) {
	if (tbEmergencyContact->Text == "") {
		tbEmergencyContact->Text = "03xx-xxxxxxx";
	}
}
private: System::Void tbCnic_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	// Check if the pressed key is a digit or backspace
	if (Char::IsDigit(e->KeyChar) || e->KeyChar == (char)Keys::Back) {
		TextBox^ tb = dynamic_cast<TextBox^>(sender);

		// Prevent entry if the maximum length is reached
		if (tb->Text->Length >= 15 && e->KeyChar != (char)Keys::Back) {
			e->Handled = true;
			return;
		}

		// Handle deletion to correctly format the CNIC when the backspace key is pressed
		if (e->KeyChar == (char)Keys::Back) {
			// Handle the case where the backspace deletes a hyphen
			if (tb->Text->Length > 0 && (tb->Text->Length == 6 || tb->Text->Length == 14)) {
				tb->Text = tb->Text->Substring(0, tb->Text->Length - 1);
				tb->SelectionStart = tb->Text->Length; // Set the cursor to the correct position
			}
			return;
		}

		// Insert hyphens automatically at the correct positions
		if (tb->Text->Length == 5 || tb->Text->Length == 13) {
			tb->Text += "-";
			tb->SelectionStart = tb->Text->Length; // Set the cursor to the correct position
		}
	}
	else {
		// Prevent entry of any non-digit characters (except backspace)
		e->Handled = true;
	}
}
private: System::Void tbBuyerPNTN_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	// Check if the pressed key is a digit or backspace
	if (Char::IsDigit(e->KeyChar) || e->KeyChar == (char)Keys::Back) {
		TextBox^ tb = dynamic_cast<TextBox^>(sender);

		// Prevent entry if the maximum length is reached
		if (tb->Text->Length >= 9 && e->KeyChar != (char)Keys::Back) {
			e->Handled = true;
			return;
		}

		// Handle deletion to correctly format the CNIC when the backspace key is pressed
		if (e->KeyChar == (char)Keys::Back) {
			// Handle the case where the backspace deletes a hyphen
			if (tb->Text->Length > 0 && (tb->Text->Length == 8)) {
				tb->Text = tb->Text->Substring(0, tb->Text->Length - 1);
				tb->SelectionStart = tb->Text->Length; // Set the cursor to the correct position
			}
			return;
		}

		// Insert hyphens automatically at the correct positions
		if (tb->Text->Length == 7) {
			tb->Text += "-";
			tb->SelectionStart = tb->Text->Length; // Set the cursor to the correct position
		}
	}
	else {
		// Prevent entry of any non-digit characters (except backspace)
		e->Handled = true;
	}
}
private: System::Void tbContact_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	// Check if the pressed key is a digit or backspace
	if (Char::IsDigit(e->KeyChar) || e->KeyChar == (char)Keys::Back) {
		TextBox^ tb = dynamic_cast<TextBox^>(sender);

		// Prevent entry if the maximum length is reached
		if (tb->Text->Length >= 12 && e->KeyChar != (char)Keys::Back) {
			e->Handled = true;
			return;
		}

		// Handle deletion to correctly format the CNIC when the backspace key is pressed
		if (e->KeyChar == (char)Keys::Back) {
			// Handle the case where the backspace deletes a hyphen
			if (tb->Text->Length > 0 && (tb->Text->Length == 5)) {
				tb->Text = tb->Text->Substring(0, tb->Text->Length - 1);
				tb->SelectionStart = tb->Text->Length; // Set the cursor to the correct position
			}
			return;
		}

		// Insert hyphens automatically at the correct positions
		if (tb->Text->Length == 4) {
			tb->Text += "-";
			tb->SelectionStart = tb->Text->Length; // Set the cursor to the correct position
		}
	}
	else {
		// Prevent entry of any non-digit characters (except backspace)
		e->Handled = true;
	}
}
private: System::Void tbEmergencyContact_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	// Check if the pressed key is a digit or backspace
	if (Char::IsDigit(e->KeyChar) || e->KeyChar == (char)Keys::Back) {
		TextBox^ tb = dynamic_cast<TextBox^>(sender);

		// Prevent entry if the maximum length is reached
		if (tb->Text->Length >= 12 && e->KeyChar != (char)Keys::Back) {
			e->Handled = true;
			return;
		}

		// Handle deletion to correctly format the CNIC when the backspace key is pressed
		if (e->KeyChar == (char)Keys::Back) {
			// Handle the case where the backspace deletes a hyphen
			if (tb->Text->Length > 0 && (tb->Text->Length == 5)) {
				tb->Text = tb->Text->Substring(0, tb->Text->Length - 1);
				tb->SelectionStart = tb->Text->Length; // Set the cursor to the correct position
			}
			return;
		}

		// Insert hyphens automatically at the correct positions
		if (tb->Text->Length == 4) {
			tb->Text += "-";
			tb->SelectionStart = tb->Text->Length; // Set the cursor to the correct position
		}
	}
	else {
		// Prevent entry of any non-digit characters (except backspace)
		e->Handled = true;
	}
}
private: System::Void tbDiscount_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	double roomCharges = Convert::ToDouble(tbRoomCharges->Text);
	double gst;
	double payable = Convert::ToDouble(tbPayable->Text);

	if (tbDiscount->Text == "0" || tbDiscount->Text == "")
	{
		gst = roomCharges * 0.16;
		payable = roomCharges + gst;
		tbPayable->Text = payable.ToString();
		return;
	}
	double discount = Convert::ToDouble(tbDiscount->Text);

	gst = roomCharges * 0.16;
	payable = roomCharges + gst;
	payable = payable - discount;

	tbPayable->Text = payable.ToString();

}
private: System::Void printDocInvoice_PrintPage(System::Object^ sender, System::Drawing::Printing::PrintPageEventArgs^ e) {
	///////////
	//variables
	///////////

	//Make variables to store fetched data from fields from UI's
	String^ invoiceNo = tbInvoiceNo->Text->ToString(); // varchar(50) == String
	String^ name = tbName->Text->ToString(); // varchar(150) == String
	String^ cnic = tbCnic->Text->ToString(); // varchar(15) == String
	String^ buyerPNTN = tbBuyerPNTN->Text->ToString(); // varchar(9) == String
	String^ address = tbAddress->Text->ToString(); // varchar(MAX) == String
	String^ contact = tbContact->Text->ToString(); // varchar(20) == String
	String^ emergencyContact = tbEmergencyContact->Text->ToString(); // varchar(20) == String
																	 //String^ date = dtpDate->Text->ToString(); //tbEmergencyContact->Text->ToString(); // date
	DateTime date = dtpDate->Value;
	String^ praFormatDateTime = date.ToString("yyyy-MM-dd HH:mm:ss.fff");
	DateTime dateIn = dtpDateIn->Value;
	String^ praFormatDateIn = dateIn.ToString("yyyy-MM-dd");
	DateTime dateOut = dtpDateOut->Value;
	String^ praFormatDateOut = dateOut.ToString("yyyy-MM-dd");
	DateTime timeIn = dtpTimeIn->Value;
	String^ praFormatTimeIn = timeIn.ToString("hh:mm tt");
	DateTime timeOut = dtpTimeOut->Value;
	String^ praFormatTimeOut = timeOut.ToString("hh:mm tt");
	String^ nationality = cbNationality->Text->ToString();
	String^ roomNo = tbRoomNo->Text->ToString();
	double noOfRooms = Convert::ToDouble(tbNoOfRooms->Text);
	double roomCharges = Convert::ToDouble(tbRoomCharges->Text);
	double gst = Convert::ToDouble(tbGst->Text);
	double discount = Convert::ToDouble(tbDiscount->Text);
	double payable = Convert::ToDouble(tbPayable->Text);

	// Define layout bounds
	float x = 20.0;
	float y = 20.0;
	// Calculate the page width
	float pageWidth = e->PageBounds.Width;

	// Header
	float textWidth = e->Graphics->MeasureString("Hotel Blue Sky", gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold)).Width;
	float xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("Hotel Blue Sky", gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold), Brushes::Black, xCentered, y);
	y += 20; // Space between sections

	textWidth = e->Graphics->MeasureString("Commettie Chock, Rawalpindi", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("Commettie Chock, Rawalpindi", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
	y += 15; 

	textWidth = e->Graphics->MeasureString("051-12345678", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("051-12345678", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
	y += 15;

	textWidth = e->Graphics->MeasureString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
	y += 10;

	/////
	// Subheader - Invoice Information
	/////
	x = 10;

	e->Graphics->DrawString("Invoice No: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	e->Graphics->DrawString(invoiceNo, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x+80, y);
	y += 20;

	e->Graphics->DrawString("Date: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	e->Graphics->DrawString(praFormatDateTime, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x+35, y);
	y += 15;

	textWidth = e->Graphics->MeasureString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
	y += 10;

	//////////////
	// Customer Information
	///////////////

	textWidth = e->Graphics->MeasureString("Customer Details", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("Customer Details", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, xCentered, y);
	y += 15;

	textWidth = e->Graphics->MeasureString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
	y += 15;

	e->Graphics->DrawString("Name: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	e->Graphics->DrawString(name, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x + 45, y);
	y += 20;

	e->Graphics->DrawString("CNIC: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	e->Graphics->DrawString(cnic, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x + 45, y);
	y += 20;

	e->Graphics->DrawString("Contact: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	e->Graphics->DrawString(contact, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x + 55, y);
	y += 20;
	
	e->Graphics->DrawString("Emergency No: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	e->Graphics->DrawString(emergencyContact, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x + 100, y);
	y += 20;
	
	e->Graphics->DrawString("Nationality: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	e->Graphics->DrawString(nationality, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x + 80, y);
	y += 15;
	
	textWidth = e->Graphics->MeasureString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
	y += 10;
	//////////////
	// Stay Information
	//////////////

	textWidth = e->Graphics->MeasureString("Staying Information", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("Staying Information", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, xCentered, y);
	y += 15;

	textWidth = e->Graphics->MeasureString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
	y += 15;

	e->Graphics->DrawString("Check-In: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	textWidth = e->Graphics->MeasureString(praFormatDateIn + "  " + praFormatTimeIn, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
	float xEnd = (pageWidth - textWidth - 10); // Ending calculation
	e->Graphics->DrawString(praFormatDateIn + "  " + praFormatTimeIn, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
	y += 20;

	e->Graphics->DrawString("Check-Out: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	textWidth = e->Graphics->MeasureString(praFormatDateOut + "  " + praFormatTimeOut, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
	xEnd = (pageWidth - textWidth - 10); // Ending calculation
	e->Graphics->DrawString(praFormatDateOut + "  " + praFormatTimeOut, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
	y += 20;

	e->Graphics->DrawString("No Of Rooms: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	textWidth = e->Graphics->MeasureString(""+noOfRooms, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
	xEnd = (pageWidth - textWidth - 20); // Ending calculation
	e->Graphics->DrawString(""+noOfRooms, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
	y += 20;

	e->Graphics->DrawString("Rooms: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	textWidth = e->Graphics->MeasureString(roomNo, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
	xEnd = (pageWidth - textWidth - 20); // Ending calculation
	e->Graphics->DrawString(roomNo, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
	y += 15;

	textWidth = e->Graphics->MeasureString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
	y += 10;

	/////////////
	// Billing Information
	/////////////

	textWidth = e->Graphics->MeasureString("Billing Information", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("Billing Information", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, xCentered, y);
	y += 15;

	textWidth = e->Graphics->MeasureString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
	y += 15;

	e->Graphics->DrawString("Room Charges: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	textWidth = e->Graphics->MeasureString(roomCharges.ToString("C2"), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
	xEnd = (pageWidth - textWidth - 20); // Ending calculation
	e->Graphics->DrawString(roomCharges.ToString("C2"), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
	y += 20;

	e->Graphics->DrawString("GST-16%: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	textWidth = e->Graphics->MeasureString(gst.ToString("C2"), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
	xEnd = (pageWidth - textWidth - 20); // Ending calculation
	e->Graphics->DrawString(gst.ToString("C2"), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
	y += 20;
	
	e->Graphics->DrawString("Discount: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	textWidth = e->Graphics->MeasureString(discount.ToString("C2"), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
	xEnd = (pageWidth - textWidth - 20); // Ending calculation
	e->Graphics->DrawString(discount.ToString("C2"), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
	y += 20;

	e->Graphics->DrawString("Total Payable: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
	textWidth = e->Graphics->MeasureString(payable.ToString("C2"), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
	xEnd = (pageWidth - textWidth - 20); // Ending calculation
	e->Graphics->DrawString(payable.ToString("C2"), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
	y += 20;
	
	textWidth = e->Graphics->MeasureString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
	y += 15;

	////////////
	// Footer
	float pageHeight = e->PageBounds.Height;

	//String^ praInvoiceNumberGlobalDeclare
	// Example QR code data
	//String^ praInvoiceNo = "81474124090113415541*Test*";
	String^ praInvoiceNo = praInvoiceNumberGlobalDeclare;
	//MessageBox::Show(praInvoiceNumberGlobalDeclare);
	//MessageBox::Show(praInvoiceNo);
	std::string qrData = "https://e.pra.punjab.gov.pk/IMSFiscalReport/SearchPOSInvoice_Report.aspx?PRAInvNo=" + msclr::interop::marshal_as<std::string>(praInvoiceNo->ToString());
	std::string filePath = "qr_code.png";
	// Save QR code image
	SaveQRCodeImage(qrData, filePath);
	// Load and display QR code image (for C++/CLI, convert the file to Bitmap)
	Bitmap^ qrImage = gcnew Bitmap(gcnew String(filePath.c_str()));
	// Example QR code image
	qrImage = gcnew Bitmap(gcnew String("qr_code.png"));
	// Desired size for the QR code image
	int qrWidth = 120; // Width in pixels
	int qrHeight = 120; // Height in pixels
	// Calculate position to center the QR code
	int qrX = (pageWidth - qrWidth) / 2;
	int qrY = e->PageBounds.Height - qrHeight - 70; // Adjust 60 to set space between QR and "Thank you"
	// Draw the QR code image
	e->Graphics->DrawImage(qrImage, qrX, qrY, qrWidth, qrHeight);

	textWidth = e->Graphics->MeasureString(praInvoiceNo, gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString(praInvoiceNo, gcnew System::Drawing::Font("Arial", 8, FontStyle::Italic), Brushes::Black, xCentered, pageHeight - 50);

	
	textWidth = e->Graphics->MeasureString("Thank you for staying with us!", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
	xCentered = (pageWidth - textWidth) / 2; // Centering calculation
	e->Graphics->DrawString("Thank you for staying with us!", gcnew System::Drawing::Font("Arial", 8, FontStyle::Italic), Brushes::Black, xCentered, pageHeight - 20);

}
private: System::Void btnPrint_Click(System::Object^  sender, System::EventArgs^  e) {
	printPreviewInvoice->Document = printDocInvoice;
	printDocInvoice->DefaultPageSettings->PaperSize = gcnew System::Drawing::Printing::PaperSize("Custom", 285, 700);
	printPreviewInvoice->ShowDialog();
}
private: System::Void cbFilterFloor_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	String^ filterFloor = cbFilterFloor->SelectedItem->ToString();
	LoadRoomData(filterFloor);
}
private: System::Void btnViewOldData_Click(System::Object^  sender, System::EventArgs^  e) {
	HotelManagementSystem::CustomerDataForm customerDataForm;
	customerDataForm.ShowDialog();
}
};
}

