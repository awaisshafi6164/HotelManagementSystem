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
#include <sys\stat.h>
using namespace std;
using namespace System::Data::SqlClient;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

inline size_t WriteCallbackCustomerData(void* contents, size_t size, size_t nmemb, std::string* response) {
	size_t totalSize = size * nmemb;
	response->append((char*)contents, totalSize);
	return totalSize;
}

inline std::string FetchQRCodeCustomerData(const std::string& qrData) {
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
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbackCustomerData);
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

inline void SaveQRCodeImageCustomerData(const std::string& qrData, const std::string& filePath) {
	std::string qrCodeData = FetchQRCodeCustomerData(qrData);

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

	/// <summary>
	/// Summary for CustomerDataForm
	/// </summary>
	public ref class CustomerDataForm : public System::Windows::Forms::Form
	{
	public:
		CustomerDataForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			LoadData();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CustomerDataForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Drawing::Printing::PrintDocument^  printDocInvoice;
	private: System::Windows::Forms::PrintPreviewDialog^  printPreviewInvoice;
	protected:


	private: System::Windows::Forms::DataGridView^  dgvCustomerData;
	private: System::Windows::Forms::Button^  btnPrint;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CustomerDataForm::typeid));
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->printDocInvoice = (gcnew System::Drawing::Printing::PrintDocument());
			this->printPreviewInvoice = (gcnew System::Windows::Forms::PrintPreviewDialog());
			this->dgvCustomerData = (gcnew System::Windows::Forms::DataGridView());
			this->btnPrint = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvCustomerData))->BeginInit();
			this->SuspendLayout();
			// 
			// printDocInvoice
			// 
			this->printDocInvoice->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &CustomerDataForm::printDocInvoice_PrintPage);
			// 
			// printPreviewInvoice
			// 
			this->printPreviewInvoice->AutoScrollMargin = System::Drawing::Size(0, 0);
			this->printPreviewInvoice->AutoScrollMinSize = System::Drawing::Size(0, 0);
			this->printPreviewInvoice->ClientSize = System::Drawing::Size(400, 300);
			this->printPreviewInvoice->Enabled = true;
			this->printPreviewInvoice->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"printPreviewInvoice.Icon")));
			this->printPreviewInvoice->Name = L"printPreviewDialog1";
			this->printPreviewInvoice->Visible = false;
			// 
			// dgvCustomerData
			// 
			this->dgvCustomerData->AllowUserToAddRows = false;
			this->dgvCustomerData->AllowUserToDeleteRows = false;
			this->dgvCustomerData->AllowUserToOrderColumns = true;
			this->dgvCustomerData->AllowUserToResizeRows = false;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::Silver;
			this->dgvCustomerData->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
			this->dgvCustomerData->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dgvCustomerData->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
			this->dgvCustomerData->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;
			this->dgvCustomerData->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dgvCustomerData->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::DodgerBlue;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.5F));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle2->Padding = System::Windows::Forms::Padding(5);
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvCustomerData->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
			this->dgvCustomerData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Menu;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvCustomerData->DefaultCellStyle = dataGridViewCellStyle3;
			this->dgvCustomerData->EnableHeadersVisualStyles = false;
			this->dgvCustomerData->GridColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->dgvCustomerData->Location = System::Drawing::Point(12, 74);
			this->dgvCustomerData->Name = L"dgvCustomerData";
			this->dgvCustomerData->RowTemplate->Height = 24;
			this->dgvCustomerData->Size = System::Drawing::Size(1006, 401);
			this->dgvCustomerData->TabIndex = 1;
			// 
			// btnPrint
			// 
			this->btnPrint->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnPrint->Location = System::Drawing::Point(12, 12);
			this->btnPrint->Name = L"btnPrint";
			this->btnPrint->Size = System::Drawing::Size(134, 56);
			this->btnPrint->TabIndex = 2;
			this->btnPrint->Text = L"Print";
			this->btnPrint->UseVisualStyleBackColor = true;
			this->btnPrint->Click += gcnew System::EventHandler(this, &CustomerDataForm::btnPrint_Click);
			// 
			// CustomerDataForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1030, 487);
			this->Controls->Add(this->btnPrint);
			this->Controls->Add(this->dgvCustomerData);
			this->Name = L"CustomerDataForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CustomerDataForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvCustomerData))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		void LoadData()
		{
			String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
			SqlConnection^ conDataBase = gcnew SqlConnection(conString);
			SqlCommand^ cmdDataBase = gcnew SqlCommand("SELECT Id, InvoiceNo, PRAInvoiceNo, Date, Name, CNIC, BuyerPNTN, ContactNo, EmergencyContact, Address, Nationality, DateIn, DateOut, TimeIn, TimeOut, RoomNo, NoOfRooms, RoomCharges, GST, Discount, Payable, PaymentMode, InvoiceType, ManagerName FROM customer;", conDataBase);

			try {
				SqlDataAdapter^ sda = gcnew SqlDataAdapter();
				sda->SelectCommand = cmdDataBase;
				DataTable^ dbdataset = gcnew DataTable();
				sda->Fill(dbdataset);
				BindingSource^ bSource = gcnew BindingSource();

				bSource->DataSource = dbdataset;
				dgvCustomerData->DataSource = bSource;

				// Enable editing in DataGridView
				dgvCustomerData->ReadOnly = false;
				dgvCustomerData->AllowUserToResizeRows = false;
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message);
			}
			finally
			{
				conDataBase->Close();
			}
		}
		void GenerateAndPrintInvoice(String^ invoiceNo, String^ praInvoiceNo, DateTime date, String^ name, String^ cnic, String^ buyerPNTN, String^ contactNo, String^ emergencyContact, String^ address, String^ nationality, DateTime dateIn, DateTime dateOut, String^ timeIn, String^ timeOut, String^ roomNo, String^ noOfRoomsStr, String^ roomChargesStr, String^ gstStr, String^ discountStr, String^ payableStr, String^ paymentMode, String^ invoiceType, String^ managerName, System::Drawing::Printing::PrintPageEventArgs^  e)
		{

			String^ praFormatDateTime = date.ToString("yyyy-MM-dd hh:mm tt");
			String^ praFormatDateIn = dateIn.ToString("yyyy-MM-dd");
			String^ praFormatDateOut = dateOut.ToString("yyyy-MM-dd");

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

			textWidth = e->Graphics->MeasureString("051-5501436-7", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
			xCentered = (pageWidth - textWidth) / 2; // Centering calculation
			e->Graphics->DrawString("051-5501436-7", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
			y += 15;

			textWidth = e->Graphics->MeasureString("PNTN: 0715030-0", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
			xCentered = (pageWidth - textWidth) / 2; // Centering calculation
			e->Graphics->DrawString("PNTN: 0715030-0", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
			y += 15;

			textWidth = e->Graphics->MeasureString("FOM: "+managerName, gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
			xCentered = (pageWidth - textWidth) / 2; // Centering calculation
			e->Graphics->DrawString("FOM: " + managerName, gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
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
			e->Graphics->DrawString(invoiceNo, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x + 80, y);
			y += 20;

			e->Graphics->DrawString("Date: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			e->Graphics->DrawString(praFormatDateTime, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x + 45, y);
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


			e->Graphics->DrawString("Name: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			e->Graphics->DrawString(name, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x + 45, y);
			y += 20;

			e->Graphics->DrawString("CNIC: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			e->Graphics->DrawString(cnic, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x + 45, y);
			y += 20;

			e->Graphics->DrawString("Contact: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			e->Graphics->DrawString(contactNo, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x + 55, y);
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


			e->Graphics->DrawString("Check-In: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			textWidth = e->Graphics->MeasureString(praFormatDateIn + "  " + timeIn, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
			float xEnd = (pageWidth - textWidth - 10); // Ending calculation
			e->Graphics->DrawString(praFormatDateIn + "  " + timeIn, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
			y += 20;

			e->Graphics->DrawString("Check-Out: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			textWidth = e->Graphics->MeasureString(praFormatDateOut + "  " + timeOut, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
			xEnd = (pageWidth - textWidth - 10); // Ending calculation
			e->Graphics->DrawString(praFormatDateOut + "  " + timeOut, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
			y += 20;

			e->Graphics->DrawString("No Of Rooms: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			textWidth = e->Graphics->MeasureString("" + noOfRoomsStr, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
			xEnd = (pageWidth - textWidth - 20); // Ending calculation
			e->Graphics->DrawString("" + noOfRoomsStr, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
			y += 20;

			/*
			e->Graphics->DrawString("Rooms: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			textWidth = e->Graphics->MeasureString(roomNo, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
			xEnd = (pageWidth - textWidth - 20); // Ending calculation
			e->Graphics->DrawString(roomNo, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
			y += 15;
			*/

			// Draw the "Rooms:" label
			e->Graphics->DrawString("Rooms: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);

			// Measure the width of the "Rooms: " label
			float labelWidth = e->Graphics->MeasureString("Rooms: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold)).Width;

			// Calculate the available space for the roomNo text on the same line
			float availableWidth = pageWidth - x - labelWidth - 20; // 20 is for padding

																	// Set the starting x position for the roomNo text (after the "Rooms:" label)
			float roomTextStartX = x + labelWidth;

			// Measure the width of the roomNo text
			textWidth = e->Graphics->MeasureString(roomNo, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;

			if (textWidth <= availableWidth) {
				// If the text fits on the same line, print it after the "Rooms:" label
				e->Graphics->DrawString(roomNo, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, roomTextStartX, y);
				y += 15; // Move down to the next line if necessary
			}
			else {
				// If the text doesn't fit on the same line, wrap it to the next line(s)
				int currentIndex = 0;
				String^ remainingText = roomNo;

				// Loop to print each part of the text that fits within the available width
				while (remainingText->Length > 0) {
					// Find how many characters fit within the available width
					int fittingChars = remainingText->Length * (availableWidth / textWidth);

					// Get the substring that fits on this line
					String^ lineText = remainingText->Substring(0, Math::Min(fittingChars, remainingText->Length));

					// Measure the width of the line text
					textWidth = e->Graphics->MeasureString(lineText, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;

					// Print the text on the same or new line
					e->Graphics->DrawString(lineText, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, roomTextStartX, y);

					// Move y down for the next line
					y += 15;

					// Remove the printed part from remainingText
					remainingText = remainingText->Substring(Math::Min(fittingChars, remainingText->Length));

					// Reset roomTextStartX for subsequent lines (to align with the left margin)
					roomTextStartX = x;
					availableWidth = pageWidth - x - 20; // New width for wrapped lines
				}
			}

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


			e->Graphics->DrawString("Room Charges: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			textWidth = e->Graphics->MeasureString(roomChargesStr, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
			xEnd = (pageWidth - textWidth - 20); // Ending calculation
			e->Graphics->DrawString(roomChargesStr, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
			y += 20;

			e->Graphics->DrawString("GST-16%: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			textWidth = e->Graphics->MeasureString(gstStr, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
			xEnd = (pageWidth - textWidth - 20); // Ending calculation
			e->Graphics->DrawString(gstStr, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
			y += 20;

			e->Graphics->DrawString("Discount: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			textWidth = e->Graphics->MeasureString(discountStr, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
			xEnd = (pageWidth - textWidth - 20); // Ending calculation
			e->Graphics->DrawString(discountStr, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
			y += 20;

			e->Graphics->DrawString("Total Payable: ", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Black, x, y);
			textWidth = e->Graphics->MeasureString(payableStr, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular)).Width;
			xEnd = (pageWidth - textWidth - 20); // Ending calculation
			e->Graphics->DrawString(payableStr, gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, xEnd, y);
			y += 20;

			textWidth = e->Graphics->MeasureString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
			xCentered = (pageWidth - textWidth) / 2; // Centering calculation
			e->Graphics->DrawString("=======================================", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, y);
			y += 15;

			////////////
			// Footer
			float pageHeight = e->PageBounds.Height;

			// Example QR code data
			String^ praNo = praInvoiceNo;
			std::string qrData = "https://e.pra.punjab.gov.pk/IMSFiscalReport/SearchPOSInvoice_Report.aspx?PRAInvNo=" +
				msclr::interop::marshal_as<std::string>(praNo->ToString());
			std::string filePath = "qr_code.png";

			// Save QR code image
			SaveQRCodeImageCustomerData(qrData, filePath);

			// Load and display QR code image (for C++/CLI, convert the file to Bitmap)
			Bitmap^ qrImage = nullptr;
			try
			{
				qrImage = gcnew Bitmap(gcnew String(filePath.c_str()));

				// Desired size for the QR code image
				int qrWidth = 120; // Width in pixels
				int qrHeight = 120; // Height in pixels

									// Calculate position to center the QR code
				int qrX = (pageWidth - qrWidth) / 2;
				int qrY = e->PageBounds.Height - qrHeight - 90; // Adjust 70 to set space between QR and "Thank you"

																// Draw the QR code image
				e->Graphics->DrawImage(qrImage, qrX, qrY, qrWidth, qrHeight);
			}
			finally
			{
				// Dispose of the image after use to release the file
				if (qrImage != nullptr)
				{
					delete qrImage;
				}
			}
		
			textWidth = e->Graphics->MeasureString(praNo, gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
			xCentered = (pageWidth - textWidth) / 2; // Centering calculation
			e->Graphics->DrawString(praNo, gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular), Brushes::Black, xCentered, pageHeight - 80);

			textWidth = e->Graphics->MeasureString("Thank you for staying with us!", gcnew System::Drawing::Font("Arial", 8, FontStyle::Regular)).Width;
			xCentered = (pageWidth - textWidth) / 2; // Centering calculation
			e->Graphics->DrawString("Thank you for staying with us!", gcnew System::Drawing::Font("Arial", 8, FontStyle::Italic), Brushes::Black, xCentered, pageHeight - 40);

			// KAAF Devs - 0340-8898238
			textWidth = e->Graphics->MeasureString("Software by: KAAF Devs__0340-8898238", gcnew System::Drawing::Font("Arial", 6, FontStyle::Regular)).Width;
			xCentered = (pageWidth - textWidth) / 2; // Centering calculation
			e->Graphics->DrawString("Software by: KAAF Devs__0340-8898238", gcnew System::Drawing::Font("Arial", 6, FontStyle::Italic), Brushes::Black, xCentered, pageHeight - 20);

		}

private: System::Void btnPrint_Click(System::Object^ sender, System::EventArgs^ e) {
	// Define the file path for the QR code image
	std::string filePath = "qr_code.png";

	// Check if a row is selected in the DataGridView
	if (dgvCustomerData->SelectedRows->Count > 0)
	{
		// Show the print preview dialog
		printPreviewInvoice->Document = printDocInvoice;
		printDocInvoice->DefaultPageSettings->PaperSize = gcnew System::Drawing::Printing::PaperSize("Custom", 285, 700);

		// Show the print preview and wait for it to close
		System::Windows::Forms::DialogResult result = printPreviewInvoice->ShowDialog();

		// After the print preview is closed, attempt to delete the QR code image file
		if (result == System::Windows::Forms::DialogResult::OK || result == System::Windows::Forms::DialogResult::Cancel)
		{
			try {
				System::IO::File::Delete(gcnew String(filePath.c_str()));
				// MessageBox::Show("QR code image deleted successfully.");
			}
			catch (System::IO::IOException^ ex) {
				// MessageBox::Show("Error deleting QR code image: " + ex->Message);
			}
		}
	}
	else
	{
		MessageBox::Show("Please select a row to print.");
		return;
	}
}

private: System::Void printDocInvoice_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e) {
	if (dgvCustomerData->SelectedRows->Count > 0)
	{
		DataGridViewRow^ selectedRow = dgvCustomerData->SelectedRows[0];
		String^ id = Convert::ToString(selectedRow->Cells["Id"]->Value);
		String^ invoiceNo = Convert::ToString(selectedRow->Cells["InvoiceNo"]->Value);
		String^ praInvoiceNo = Convert::ToString(selectedRow->Cells["PRAInvoiceNo"]->Value);
		//String^ date = Convert::ToString(selectedRow->Cells["Date"]->Value);
		DateTime date = Convert::ToDateTime(selectedRow->Cells["Date"]->Value);
		String^ name = Convert::ToString(selectedRow->Cells["Name"]->Value);
		String^ cnic = Convert::ToString(selectedRow->Cells["CNIC"]->Value);
		String^ buyerPNTN = Convert::ToString(selectedRow->Cells["BuyerPNTN"]->Value);
		String^ contactNo = Convert::ToString(selectedRow->Cells["ContactNo"]->Value);
		String^ emergencyContact = Convert::ToString(selectedRow->Cells["EmergencyContact"]->Value);
		String^ address = Convert::ToString(selectedRow->Cells["Address"]->Value);
		String^ nationality = Convert::ToString(selectedRow->Cells["Nationality"]->Value);
		//String^ dateIn = Convert::ToString(selectedRow->Cells["DateIn"]->Value);
		DateTime dateIn = Convert::ToDateTime(selectedRow->Cells["DateIn"]->Value);
		//String^ dateOut = Convert::ToString(selectedRow->Cells["DateOut"]->Value);
		DateTime dateOut = Convert::ToDateTime(selectedRow->Cells["DateOut"]->Value);
		String^ timeIn = Convert::ToString(selectedRow->Cells["TimeIn"]->Value);
		String^ timeOut = Convert::ToString(selectedRow->Cells["TimeOut"]->Value);
		String^ roomNo = Convert::ToString(selectedRow->Cells["RoomNo"]->Value);
		String^ noOfRoomsStr = Convert::ToString(selectedRow->Cells["NoOfRooms"]->Value);
		String^ roomChargesStr = Convert::ToString(selectedRow->Cells["RoomCharges"]->Value);
		String^ gstStr = Convert::ToString(selectedRow->Cells["GST"]->Value);
		String^ discountStr = Convert::ToString(selectedRow->Cells["Discount"]->Value);
		String^ payableStr = Convert::ToString(selectedRow->Cells["Payable"]->Value);
		String^ paymentMode = Convert::ToString(selectedRow->Cells["PaymentMode"]->Value);
		String^ invoiceType = Convert::ToString(selectedRow->Cells["InvoiceType"]->Value);
		String^ managerName = Convert::ToString(selectedRow->Cells["ManagerName"]->Value);
		// Use the fetched data (for example, pass it to a method that generates and prints the invoice)
		GenerateAndPrintInvoice(invoiceNo, praInvoiceNo, date, name, cnic, buyerPNTN, contactNo, emergencyContact, address, nationality, dateIn, dateOut, timeIn, timeOut, roomNo, noOfRoomsStr, roomChargesStr, gstStr, discountStr, payableStr, paymentMode, invoiceType, managerName, e);
	}
}
};
}
