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
using namespace std;
namespace HotelManagementSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// Summary for RoomDataForm
	/// </summary>
	public ref class RoomDataForm : public System::Windows::Forms::Form
	{
	public:
		RoomDataForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			LoadRoomData();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RoomDataForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  dgvAdminRoomData;
	private: System::Windows::Forms::Button^  btnAdminRoomUpdate;
	private: System::Windows::Forms::Button^  btnAdminRoomDelete;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  tbAdminRoomNo;

	private: System::Windows::Forms::ComboBox^  cbAdminRoomType;
	private: System::Windows::Forms::ComboBox^  cbAdminRoomCategory;
	private: System::Windows::Forms::TextBox^  tbAdminRoomRent;
	private: System::Windows::Forms::Button^  btnAdminRoomAdd;




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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->dgvAdminRoomData = (gcnew System::Windows::Forms::DataGridView());
			this->btnAdminRoomUpdate = (gcnew System::Windows::Forms::Button());
			this->btnAdminRoomDelete = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tbAdminRoomNo = (gcnew System::Windows::Forms::TextBox());
			this->cbAdminRoomType = (gcnew System::Windows::Forms::ComboBox());
			this->cbAdminRoomCategory = (gcnew System::Windows::Forms::ComboBox());
			this->tbAdminRoomRent = (gcnew System::Windows::Forms::TextBox());
			this->btnAdminRoomAdd = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvAdminRoomData))->BeginInit();
			this->SuspendLayout();
			// 
			// dgvAdminRoomData
			// 
			this->dgvAdminRoomData->AllowUserToAddRows = false;
			this->dgvAdminRoomData->AllowUserToDeleteRows = false;
			this->dgvAdminRoomData->AllowUserToOrderColumns = true;
			this->dgvAdminRoomData->AllowUserToResizeRows = false;
			dataGridViewCellStyle4->BackColor = System::Drawing::Color::Silver;
			this->dgvAdminRoomData->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle4;
			this->dgvAdminRoomData->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->dgvAdminRoomData->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dgvAdminRoomData->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;
			this->dgvAdminRoomData->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dgvAdminRoomData->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle5->BackColor = System::Drawing::Color::DodgerBlue;
			dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.5F));
			dataGridViewCellStyle5->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle5->Padding = System::Windows::Forms::Padding(5);
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle5->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvAdminRoomData->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle5;
			this->dgvAdminRoomData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle6->BackColor = System::Drawing::SystemColors::Menu;
			dataGridViewCellStyle6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
			dataGridViewCellStyle6->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle6->Padding = System::Windows::Forms::Padding(5);
			dataGridViewCellStyle6->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle6->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvAdminRoomData->DefaultCellStyle = dataGridViewCellStyle6;
			this->dgvAdminRoomData->EnableHeadersVisualStyles = false;
			this->dgvAdminRoomData->GridColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->dgvAdminRoomData->Location = System::Drawing::Point(12, 12);
			this->dgvAdminRoomData->Name = L"dgvAdminRoomData";
			this->dgvAdminRoomData->RowTemplate->Height = 24;
			this->dgvAdminRoomData->Size = System::Drawing::Size(966, 580);
			this->dgvAdminRoomData->TabIndex = 1;
			// 
			// btnAdminRoomUpdate
			// 
			this->btnAdminRoomUpdate->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnAdminRoomUpdate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAdminRoomUpdate->Location = System::Drawing::Point(984, 251);
			this->btnAdminRoomUpdate->Name = L"btnAdminRoomUpdate";
			this->btnAdminRoomUpdate->Size = System::Drawing::Size(139, 63);
			this->btnAdminRoomUpdate->TabIndex = 7;
			this->btnAdminRoomUpdate->Text = L"Update";
			this->btnAdminRoomUpdate->UseVisualStyleBackColor = false;
			this->btnAdminRoomUpdate->Click += gcnew System::EventHandler(this, &RoomDataForm::btnAdminRoomUpdate_Click);
			// 
			// btnAdminRoomDelete
			// 
			this->btnAdminRoomDelete->BackColor = System::Drawing::Color::DarkRed;
			this->btnAdminRoomDelete->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAdminRoomDelete->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btnAdminRoomDelete->Location = System::Drawing::Point(1129, 251);
			this->btnAdminRoomDelete->Name = L"btnAdminRoomDelete";
			this->btnAdminRoomDelete->Size = System::Drawing::Size(139, 63);
			this->btnAdminRoomDelete->TabIndex = 8;
			this->btnAdminRoomDelete->Text = L"Delete";
			this->btnAdminRoomDelete->UseVisualStyleBackColor = false;
			this->btnAdminRoomDelete->Click += gcnew System::EventHandler(this, &RoomDataForm::btnAdminRoomDelete_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(984, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(86, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Room No";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(984, 68);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(49, 20);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Type";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(984, 118);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(84, 20);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Category";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(984, 169);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(102, 20);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Room Rent";
			// 
			// tbAdminRoomNo
			// 
			this->tbAdminRoomNo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbAdminRoomNo->Location = System::Drawing::Point(1105, 17);
			this->tbAdminRoomNo->Name = L"tbAdminRoomNo";
			this->tbAdminRoomNo->Size = System::Drawing::Size(161, 27);
			this->tbAdminRoomNo->TabIndex = 2;
			this->tbAdminRoomNo->Text = L"000";
			// 
			// cbAdminRoomType
			// 
			this->cbAdminRoomType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbAdminRoomType->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbAdminRoomType->FormattingEnabled = true;
			this->cbAdminRoomType->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Deluxe", L"Single", L"Double" });
			this->cbAdminRoomType->Location = System::Drawing::Point(1105, 64);
			this->cbAdminRoomType->Name = L"cbAdminRoomType";
			this->cbAdminRoomType->Size = System::Drawing::Size(161, 28);
			this->cbAdminRoomType->TabIndex = 3;
			// 
			// cbAdminRoomCategory
			// 
			this->cbAdminRoomCategory->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbAdminRoomCategory->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->cbAdminRoomCategory->FormattingEnabled = true;
			this->cbAdminRoomCategory->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"AC", L"Non AC" });
			this->cbAdminRoomCategory->Location = System::Drawing::Point(1105, 110);
			this->cbAdminRoomCategory->Name = L"cbAdminRoomCategory";
			this->cbAdminRoomCategory->Size = System::Drawing::Size(161, 28);
			this->cbAdminRoomCategory->TabIndex = 4;
			// 
			// tbAdminRoomRent
			// 
			this->tbAdminRoomRent->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbAdminRoomRent->Location = System::Drawing::Point(1105, 162);
			this->tbAdminRoomRent->Name = L"tbAdminRoomRent";
			this->tbAdminRoomRent->Size = System::Drawing::Size(161, 27);
			this->tbAdminRoomRent->TabIndex = 5;
			this->tbAdminRoomRent->Text = L"0000";
			// 
			// btnAdminRoomAdd
			// 
			this->btnAdminRoomAdd->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnAdminRoomAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAdminRoomAdd->Location = System::Drawing::Point(988, 195);
			this->btnAdminRoomAdd->Name = L"btnAdminRoomAdd";
			this->btnAdminRoomAdd->Size = System::Drawing::Size(278, 37);
			this->btnAdminRoomAdd->TabIndex = 6;
			this->btnAdminRoomAdd->Text = L"Add";
			this->btnAdminRoomAdd->UseVisualStyleBackColor = false;
			this->btnAdminRoomAdd->Click += gcnew System::EventHandler(this, &RoomDataForm::btnAdminRoomAdd_Click);
			// 
			// RoomDataForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1279, 604);
			this->Controls->Add(this->cbAdminRoomCategory);
			this->Controls->Add(this->cbAdminRoomType);
			this->Controls->Add(this->tbAdminRoomRent);
			this->Controls->Add(this->tbAdminRoomNo);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnAdminRoomDelete);
			this->Controls->Add(this->btnAdminRoomAdd);
			this->Controls->Add(this->btnAdminRoomUpdate);
			this->Controls->Add(this->dgvAdminRoomData);
			this->Name = L"RoomDataForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Room Data Form";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvAdminRoomData))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		void LoadRoomData()
		{
			cbAdminRoomType->Text = "Single";
			cbAdminRoomCategory->Text = "AC";

			String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
			SqlConnection^ conDataBase = gcnew SqlConnection(conString);
			SqlCommand^ cmdDataBase = gcnew SqlCommand("SELECT Id, Room, Type, Category, Rent FROM room;", conDataBase);

			try {
				SqlDataAdapter^ sda = gcnew SqlDataAdapter();
				sda->SelectCommand = cmdDataBase;
				DataTable^ dbdataset = gcnew DataTable();
				sda->Fill(dbdataset);
				BindingSource^ bSource = gcnew BindingSource();

				bSource->DataSource = dbdataset;
				dgvAdminRoomData->DataSource = bSource;

				// Enable editing in DataGridView
				dgvAdminRoomData->ReadOnly = false;
				dgvAdminRoomData->AllowUserToAddRows = false;
				dgvAdminRoomData->AllowUserToDeleteRows = false;
				dgvAdminRoomData->AllowUserToResizeRows = false;
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message);
			}
			finally
			{
				conDataBase->Close();
			}
		}


private: System::Void btnAdminRoomAdd_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ roomNo = tbAdminRoomNo->Text->ToString(); 
	String^ roomType = cbAdminRoomType->Text->ToString();
	String^ roomCategory = cbAdminRoomCategory->Text->ToString();
	String^ roomRent = tbAdminRoomRent->Text->ToString();

	if (roomNo == "" || roomRent == "")
	{
		MessageBox::Show("Kindly fill all the fields.", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
	SqlConnection^ conDataBase = gcnew SqlConnection(conString);
	SqlCommand^ cmdDataBase = gcnew SqlCommand("INSERT INTO room (Room, Type, Category, Rent) VALUES (@Room, @Type, @Category, @Rent);", conDataBase);

	cmdDataBase->Parameters->AddWithValue("@Room", roomNo);
	cmdDataBase->Parameters->AddWithValue("@Type", roomType);
	cmdDataBase->Parameters->AddWithValue("@Category", roomCategory);
	cmdDataBase->Parameters->AddWithValue("@Rent", roomRent);

	try {
		conDataBase->Open();
		cmdDataBase->ExecuteNonQuery();
		MessageBox::Show("Record added successfully!");
		LoadRoomData(); // Refresh data
	}
	catch (Exception^ ex) {
		MessageBox::Show(ex->Message);
	}
	finally
	{
		conDataBase->Close();
	}
}
private: System::Void btnAdminRoomUpdate_Click(System::Object^ sender, System::EventArgs^ e) {
	if (dgvAdminRoomData->SelectedRows->Count > 0) {
		DataGridViewRow^ selectedRow = dgvAdminRoomData->SelectedRows[0];
		String^ roomId = Convert::ToString(selectedRow->Cells["Id"]->Value);
		String^ roomNo = Convert::ToString(selectedRow->Cells["Room"]->Value);
		String^ roomType = Convert::ToString(selectedRow->Cells["Type"]->Value);
		String^ roomCategory = Convert::ToString(selectedRow->Cells["Category"]->Value);
		String^ roomRentStr = Convert::ToString(selectedRow->Cells["Rent"]->Value);

		// Convert Rent to integer
		int roomRent;
		try {
			roomRent = Convert::ToInt32(roomRentStr);
		}
		catch (FormatException^) {
			MessageBox::Show("Please enter a valid number for Rent.");
			return;
		}

		String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
		SqlConnection^ conDataBase = gcnew SqlConnection(conString);
		SqlCommand^ cmdDataBase = gcnew SqlCommand("UPDATE room SET Room=@Room, Type=@Type, Category=@Category, Rent=@Rent WHERE Id=@Id;", conDataBase);

		cmdDataBase->Parameters->AddWithValue("@Id", roomId); // Room is used for identification and should not be updated
		cmdDataBase->Parameters->AddWithValue("@Room", roomNo); // Room is used for identification and should not be updated
		cmdDataBase->Parameters->AddWithValue("@Type", roomType);
		cmdDataBase->Parameters->AddWithValue("@Category", roomCategory);
		cmdDataBase->Parameters->AddWithValue("@Rent", roomRent);

		try {
			conDataBase->Open();
			cmdDataBase->ExecuteNonQuery();
			MessageBox::Show("Record updated successfully!");
			LoadRoomData(); // Refresh data
		}
		catch (Exception^ ex) {
			MessageBox::Show(ex->Message);
		}
		finally
		{
			conDataBase->Close();
		}
	}
	else {
		MessageBox::Show("Please select a row to update.");
	}
}
private: System::Void btnAdminRoomDelete_Click(System::Object^  sender, System::EventArgs^  e) {
	if (dgvAdminRoomData->SelectedRows->Count > 0) {
		DataGridViewRow^ selectedRow = dgvAdminRoomData->SelectedRows[0];
		String^ roomNo = Convert::ToString(selectedRow->Cells["Room"]->Value);

		String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
		SqlConnection^ conDataBase = gcnew SqlConnection(conString);
		SqlCommand^ cmdDataBase = gcnew SqlCommand("DELETE FROM room WHERE Room=@Room;", conDataBase);

		cmdDataBase->Parameters->AddWithValue("@Room", roomNo);

		try {
			conDataBase->Open();
			cmdDataBase->ExecuteNonQuery();
			MessageBox::Show("Record deleted successfully!");
			LoadRoomData(); // Refresh data
		}
		catch (Exception^ ex) {
			MessageBox::Show(ex->Message);
		}
		finally
		{
			conDataBase->Close();
		}
	}
	else {
		MessageBox::Show("Please select a row to delete.");
	}
}
};
}
