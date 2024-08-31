#pragma once

#define IServiceProvider WindowsIServiceProvider // Rename Windows IServiceProvider
#include <curl/curl.h>
#undef IServiceProvider  // Undefine after including

#include <iostream>
#include <string>
#include <nlohmann\json.hpp>


#include "Invoice.h"
#include <msclr/marshal_cppstd.h> // For converting std::string to System::String

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
	CURL* curl;
	CURLcode res;
	std::string response;

	curl = curl_easy_init();
	if (curl) {
		// Convert JSON object to string
		std::string jsonString = invoiceJson.dump();

		// Set up cURL options with HTTPS URL
		std::string url = "https://ims.pral.com.pk/ims/sandbox/api/Live/PostData";
		std::string token = "24d8fab3-f2e9-398f-ae17-b387125ec4a2"; // Sandbox Token

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



namespace HotelManagementSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;


	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			LoadRoomData();
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
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  tbRoomNo;

	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::TextBox^  tbDiscount;

	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::RadioButton^  radioButton1;
private: System::Windows::Forms::RadioButton^  radioButton2;
private: System::Windows::Forms::RadioButton^  radioButton3;
private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::Label^  label30;








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
		void InitializeComponent(void)
		{
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
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->tbRoomNo = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->tbDiscount = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvRoomData))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::LightBlue;
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
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
			this->label2->TabIndex = 1;
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
			this->label4->TabIndex = 3;
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
			this->tbName->TabIndex = 1;
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
			this->label5->TabIndex = 3;
			this->label5->Text = L"CNIC";
			// 
			// tbCnic
			// 
			this->tbCnic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbCnic->Location = System::Drawing::Point(119, 178);
			this->tbCnic->Name = L"tbCnic";
			this->tbCnic->Size = System::Drawing::Size(313, 30);
			this->tbCnic->TabIndex = 3;
			this->tbCnic->Text = L"61101-8903163-3";
			this->tbCnic->Enter += gcnew System::EventHandler(this, &MainForm::tbCnic_Enter);
			this->tbCnic->Leave += gcnew System::EventHandler(this, &MainForm::tbCnic_Leave);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(628, 611);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(123, 25);
			this->label6->TabIndex = 3;
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
			this->label7->TabIndex = 3;
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
			this->label8->TabIndex = 3;
			this->label8->Text = L"Time-Out";
			// 
			// dtpTimeIn
			// 
			this->dtpTimeIn->CalendarFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->dtpTimeIn->CustomFormat = L"";
			this->dtpTimeIn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpTimeIn->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->dtpTimeIn->Location = System::Drawing::Point(119, 351);
			this->dtpTimeIn->Name = L"dtpTimeIn";
			this->dtpTimeIn->Size = System::Drawing::Size(313, 30);
			this->dtpTimeIn->TabIndex = 5;
			this->dtpTimeIn->Value = System::DateTime(2024, 8, 19, 21, 40, 0, 0);
			// 
			// dtpTimeOut
			// 
			this->dtpTimeOut->CalendarFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->dtpTimeOut->CustomFormat = L"HH:MM";
			this->dtpTimeOut->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpTimeOut->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->dtpTimeOut->Location = System::Drawing::Point(611, 351);
			this->dtpTimeOut->Name = L"dtpTimeOut";
			this->dtpTimeOut->Size = System::Drawing::Size(285, 30);
			this->dtpTimeOut->TabIndex = 6;
			this->dtpTimeOut->Value = System::DateTime(2024, 8, 19, 21, 40, 0, 0);
			// 
			// dgvRoomData
			// 
			this->dgvRoomData->AllowUserToAddRows = false;
			this->dgvRoomData->AllowUserToDeleteRows = false;
			this->dgvRoomData->AllowUserToResizeColumns = false;
			this->dgvRoomData->AllowUserToResizeRows = false;
			this->dgvRoomData->BackgroundColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->dgvRoomData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvRoomData->GridColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->dgvRoomData->Location = System::Drawing::Point(25, 422);
			this->dgvRoomData->Name = L"dgvRoomData";
			this->dgvRoomData->RowHeadersVisible = false;
			this->dgvRoomData->RowTemplate->Height = 24;
			this->dgvRoomData->Size = System::Drawing::Size(597, 256);
			this->dgvRoomData->TabIndex = 7;
			// 
			// label12
			// 
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(25, 394);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(597, 25);
			this->label12->TabIndex = 1;
			this->label12->Text = L"Select Rooms";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnRefresh
			// 
			this->btnRefresh->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRefresh->Location = System::Drawing::Point(628, 422);
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
			this->tbNoOfRooms->Location = System::Drawing::Point(628, 639);
			this->tbNoOfRooms->Name = L"tbNoOfRooms";
			this->tbNoOfRooms->Size = System::Drawing::Size(123, 38);
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
			this->label14->TabIndex = 3;
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
			this->label15->TabIndex = 3;
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
			this->label16->TabIndex = 3;
			this->label16->Text = L"Payable";
			// 
			// btnCancel
			// 
			this->btnCancel->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnCancel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCancel->Location = System::Drawing::Point(919, 458);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(124, 51);
			this->btnCancel->TabIndex = 9;
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
			this->btnSave->TabIndex = 10;
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
			this->btnPrint->TabIndex = 11;
			this->btnPrint->Text = L"Print";
			this->btnPrint->UseVisualStyleBackColor = false;
			// 
			// btnCalculateTotal
			// 
			this->btnCalculateTotal->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnCalculateTotal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnCalculateTotal->Location = System::Drawing::Point(628, 458);
			this->btnCalculateTotal->Name = L"btnCalculateTotal";
			this->btnCalculateTotal->Size = System::Drawing::Size(149, 58);
			this->btnCalculateTotal->TabIndex = 8;
			this->btnCalculateTotal->Text = L"Calculate Total";
			this->btnCalculateTotal->UseVisualStyleBackColor = false;
			this->btnCalculateTotal->Click += gcnew System::EventHandler(this, &MainForm::btnCalculateTotal_Click);
			// 
			// label18
			// 
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->Location = System::Drawing::Point(21, 97);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(118, 32);
			this->label18->TabIndex = 12;
			this->label18->Text = L"Invoice No";
			// 
			// tbInvoiceNo
			// 
			this->tbInvoiceNo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbInvoiceNo->Location = System::Drawing::Point(145, 97);
			this->tbInvoiceNo->Name = L"tbInvoiceNo";
			this->tbInvoiceNo->Size = System::Drawing::Size(88, 27);
			this->tbInvoiceNo->TabIndex = 13;
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
			this->label19->TabIndex = 3;
			this->label19->Text = L"Contact No";
			// 
			// tbContact
			// 
			this->tbContact->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbContact->Location = System::Drawing::Point(679, 135);
			this->tbContact->MaxLength = 50;
			this->tbContact->Name = L"tbContact";
			this->tbContact->Size = System::Drawing::Size(217, 30);
			this->tbContact->TabIndex = 1;
			this->tbContact->Text = L"0340-8898238";
			this->tbContact->Enter += gcnew System::EventHandler(this, &MainForm::tbContact_Enter);
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
			this->label20->TabIndex = 3;
			this->label20->Text = L"Emergency Contact";
			// 
			// tbEmergencyContact
			// 
			this->tbEmergencyContact->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbEmergencyContact->Location = System::Drawing::Point(679, 175);
			this->tbEmergencyContact->MaxLength = 50;
			this->tbEmergencyContact->Name = L"tbEmergencyContact";
			this->tbEmergencyContact->Size = System::Drawing::Size(217, 30);
			this->tbEmergencyContact->TabIndex = 1;
			this->tbEmergencyContact->Text = L"0339-4098238";
			this->tbEmergencyContact->Enter += gcnew System::EventHandler(this, &MainForm::tbEmergencyContact_Enter);
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
			this->label21->TabIndex = 3;
			this->label21->Text = L"Nationality";
			// 
			// cbNationality
			// 
			this->cbNationality->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbNationality->FormattingEnabled = true;
			this->cbNationality->Location = System::Drawing::Point(611, 219);
			this->cbNationality->Name = L"cbNationality";
			this->cbNationality->Size = System::Drawing::Size(285, 33);
			this->cbNationality->TabIndex = 14;
			this->cbNationality->Text = L"Pakistani";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->Location = System::Drawing::Point(21, 272);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(92, 25);
			this->label22->TabIndex = 3;
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
			this->tbAddress->TabIndex = 1;
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
			this->label23->TabIndex = 12;
			this->label23->Text = L"Date";
			// 
			// dtpDate
			// 
			this->dtpDate->CalendarFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpDate->CustomFormat = L"";
			this->dtpDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpDate->Location = System::Drawing::Point(543, 93);
			this->dtpDate->Name = L"dtpDate";
			this->dtpDate->Size = System::Drawing::Size(353, 30);
			this->dtpDate->TabIndex = 5;
			this->dtpDate->Value = System::DateTime(2024, 8, 30, 0, 0, 0, 0);
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
			this->dtpDateIn->TabIndex = 5;
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
			this->label24->TabIndex = 12;
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
			this->dtpDateOut->TabIndex = 5;
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
			this->label25->TabIndex = 12;
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
			this->label9->TabIndex = 3;
			this->label9->Text = L"Buyer PNTN";
			// 
			// tbBuyerPNTN
			// 
			this->tbBuyerPNTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbBuyerPNTN->Location = System::Drawing::Point(182, 222);
			this->tbBuyerPNTN->Name = L"tbBuyerPNTN";
			this->tbBuyerPNTN->Size = System::Drawing::Size(250, 30);
			this->tbBuyerPNTN->TabIndex = 3;
			this->tbBuyerPNTN->Text = L"0715030-0";
			this->tbBuyerPNTN->Enter += gcnew System::EventHandler(this, &MainForm::tbCnic_Enter);
			this->tbBuyerPNTN->Leave += gcnew System::EventHandler(this, &MainForm::tbCnic_Leave);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(914, 58);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(94, 25);
			this->label13->TabIndex = 1;
			this->label13->Text = L"Charges";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(988, 676);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(144, 20);
			this->label10->TabIndex = 12;
			this->label10->Text = L"Booking Manager:";
			// 
			// label11
			// 
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(1138, 676);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(184, 20);
			this->label11->TabIndex = 12;
			this->label11->Text = L"Awais Shafi";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
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
			this->tbRoomNo->Text = L"112, 123";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(914, 99);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(111, 25);
			this->label17->TabIndex = 3;
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
			this->label26->TabIndex = 3;
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
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label27->Location = System::Drawing::Point(914, 362);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(156, 25);
			this->label27->TabIndex = 3;
			this->label27->Text = L"Payment Mode";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkBox1->Location = System::Drawing::Point(1086, 363);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(70, 24);
			this->checkBox1->TabIndex = 15;
			this->checkBox1->Text = L"Cash";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkBox2->Location = System::Drawing::Point(1163, 363);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(67, 24);
			this->checkBox2->TabIndex = 15;
			this->checkBox2->Text = L"Card";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkBox3->Location = System::Drawing::Point(1237, 363);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(88, 24);
			this->checkBox3->TabIndex = 15;
			this->checkBox3->Text = L"Cheque";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label28->Location = System::Drawing::Point(913, 403);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(136, 25);
			this->label28->TabIndex = 3;
			this->label28->Text = L"Invoice Type";
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton1->Location = System::Drawing::Point(1089, 404);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(63, 24);
			this->radioButton1->TabIndex = 16;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"New";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton2->Location = System::Drawing::Point(1162, 404);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(70, 24);
			this->radioButton2->TabIndex = 16;
			this->radioButton2->Text = L"Debit";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton3->Location = System::Drawing::Point(1242, 404);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(75, 24);
			this->radioButton3->TabIndex = 16;
			this->radioButton3->Text = L"Credit";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// label29
			// 
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label29->Location = System::Drawing::Point(996, 615);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(322, 20);
			this->label29->TabIndex = 12;
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
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightSteelBlue;
			this->ClientSize = System::Drawing::Size(1338, 705);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->cbNationality);
			this->Controls->Add(this->tbInvoiceNo);
			this->Controls->Add(this->label25);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label30);
			this->Controls->Add(this->label29);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->btnPrint);
			this->Controls->Add(this->btnSave);
			this->Controls->Add(this->btnCalculateTotal);
			this->Controls->Add(this->btnCancel);
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
	LoadRoomData();
}

private:
	void LoadRoomData()
	{
		String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
		SqlConnection^ conDataBase = gcnew SqlConnection(conString);
		SqlCommand^ cmdDataBase = gcnew SqlCommand("SELECT Room, Type, Category, Rent FROM room;", conDataBase);

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
				chkColumn->Width = 50;             // Optional: set the width of the checkbox column

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
}
private: System::Void btnCancel_Click(System::Object^  sender, System::EventArgs^  e) {
	LoadRoomData();
	tbNoOfRooms->Text = "0";
	tbRoomCharges->Text = "0";
	tbGst->Text = "0";
	tbPayable->Text = "0";
}
private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {


	if (tbName->Text == "") 
	{
		MessageBox::Show("Kindly Enter Name");
		return;
	}

	if (tbNoOfRooms->Text != "0" || tbRoomCharges->Text != "0" || tbGst->Text != "0" || tbPayable->Text != "0")
	{
		String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
		// Create the SQL query string
		String^ query = "INSERT INTO customer (Invoice, Name, Cell, NoOfRooms, Rent, Gst, Total) VALUES (@Invoice, @Name, @Cell, @NoOfRooms, @Rent, @Gst, @Total);";

		// Assuming you have a connection string
		SqlConnection^ connection = gcnew SqlConnection(conString);

		try {
			connection->Open();

			// Create a SqlCommand object
			SqlCommand^ command = gcnew SqlCommand(query, connection);

			// Bind the parameters with data from text boxes
			command->Parameters->AddWithValue("@Invoice", 8);//Unique Key Constraint
			command->Parameters->AddWithValue("@Name", tbName->Text);
			if (tbContact->Text == "03xx-xxxxxxx")
			{
				command->Parameters->AddWithValue("@Cell", "");
			}
			else {
				command->Parameters->AddWithValue("@Cell", tbContact->Text);
			}
			command->Parameters->AddWithValue("@NoOfRooms", Convert::ToInt32(tbNoOfRooms->Text));
			command->Parameters->AddWithValue("@Rent", Convert::ToDouble(tbRoomCharges->Text));
			command->Parameters->AddWithValue("@Gst", Convert::ToDouble(tbGst->Text));
			command->Parameters->AddWithValue("@Total", Convert::ToDouble(tbPayable->Text));

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
	}
	else {
		MessageBox::Show("Please make sure all fields are filled out correctly.", "Validation Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}
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
	String^ invoiceNumberStr = gcnew String(invoiceNumber.c_str());
	String^ apiResponseMessageStr = gcnew String(apiResponseMessage.c_str());
	String^ apiCodeMessageStr = gcnew String(apiCodeMessage.c_str());
	String^ apiErrorsMessageStr = gcnew String(apiErrorsMessage.c_str());
	MessageBox::Show("Generated Invoice Number: " + invoiceNumberStr 
		+ "\nCode: " + apiCodeMessageStr
		+ "\nAPI Response: " + apiResponseMessageStr
		+ "\nErrors: " + apiErrorsMessageStr
		, "API Response" , MessageBoxButtons::OK, MessageBoxIcon::Information);

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
};
}


