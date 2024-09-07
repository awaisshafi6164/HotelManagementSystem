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
	/// Summary for UserDataForm
	/// </summary>
	public ref class UserDataForm : public System::Windows::Forms::Form
	{
	public:
		UserDataForm(void)
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
		~UserDataForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  dgvAdminUserData;
	private: System::Windows::Forms::Button^  btnAdd;

	private: System::Windows::Forms::Button^  btnUpdate;
	private: System::Windows::Forms::Button^  btnDelete;
	private: System::Windows::Forms::TextBox^  tbUsername;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  tbEmail;
	private: System::Windows::Forms::TextBox^  tbPassword;
	private: System::Windows::Forms::RadioButton^  rbAdmin;
	private: System::Windows::Forms::RadioButton^  rbBookingManager;
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
			this->dgvAdminUserData = (gcnew System::Windows::Forms::DataGridView());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->btnUpdate = (gcnew System::Windows::Forms::Button());
			this->btnDelete = (gcnew System::Windows::Forms::Button());
			this->tbUsername = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tbEmail = (gcnew System::Windows::Forms::TextBox());
			this->tbPassword = (gcnew System::Windows::Forms::TextBox());
			this->rbAdmin = (gcnew System::Windows::Forms::RadioButton());
			this->rbBookingManager = (gcnew System::Windows::Forms::RadioButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvAdminUserData))->BeginInit();
			this->SuspendLayout();
			// 
			// dgvAdminUserData
			// 
			this->dgvAdminUserData->AllowUserToAddRows = false;
			this->dgvAdminUserData->AllowUserToDeleteRows = false;
			this->dgvAdminUserData->AllowUserToOrderColumns = true;
			this->dgvAdminUserData->AllowUserToResizeRows = false;
			dataGridViewCellStyle4->BackColor = System::Drawing::Color::Silver;
			this->dgvAdminUserData->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle4;
			this->dgvAdminUserData->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dgvAdminUserData->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dgvAdminUserData->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;
			this->dgvAdminUserData->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dgvAdminUserData->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle5->BackColor = System::Drawing::Color::DodgerBlue;
			dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.5F));
			dataGridViewCellStyle5->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle5->Padding = System::Windows::Forms::Padding(5);
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle5->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvAdminUserData->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle5;
			this->dgvAdminUserData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle6->BackColor = System::Drawing::SystemColors::Menu;
			dataGridViewCellStyle6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
			dataGridViewCellStyle6->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle6->Padding = System::Windows::Forms::Padding(5);
			dataGridViewCellStyle6->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle6->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvAdminUserData->DefaultCellStyle = dataGridViewCellStyle6;
			this->dgvAdminUserData->EnableHeadersVisualStyles = false;
			this->dgvAdminUserData->GridColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->dgvAdminUserData->Location = System::Drawing::Point(12, 12);
			this->dgvAdminUserData->Name = L"dgvAdminUserData";
			this->dgvAdminUserData->RowTemplate->Height = 24;
			this->dgvAdminUserData->Size = System::Drawing::Size(882, 385);
			this->dgvAdminUserData->TabIndex = 1;
			// 
			// btnAdd
			// 
			this->btnAdd->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnAdd->Location = System::Drawing::Point(12, 403);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(153, 55);
			this->btnAdd->TabIndex = 2;
			this->btnAdd->Text = L"Add";
			this->btnAdd->UseVisualStyleBackColor = false;
			this->btnAdd->Click += gcnew System::EventHandler(this, &UserDataForm::btnAdd_Click);
			// 
			// btnUpdate
			// 
			this->btnUpdate->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnUpdate->Location = System::Drawing::Point(171, 403);
			this->btnUpdate->Name = L"btnUpdate";
			this->btnUpdate->Size = System::Drawing::Size(153, 55);
			this->btnUpdate->TabIndex = 3;
			this->btnUpdate->Text = L"Update";
			this->btnUpdate->UseVisualStyleBackColor = false;
			this->btnUpdate->Click += gcnew System::EventHandler(this, &UserDataForm::btnUpdate_Click);
			// 
			// btnDelete
			// 
			this->btnDelete->BackColor = System::Drawing::Color::DarkRed;
			this->btnDelete->ForeColor = System::Drawing::Color::White;
			this->btnDelete->Location = System::Drawing::Point(330, 403);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(153, 55);
			this->btnDelete->TabIndex = 4;
			this->btnDelete->Text = L"Delete";
			this->btnDelete->UseVisualStyleBackColor = false;
			this->btnDelete->Click += gcnew System::EventHandler(this, &UserDataForm::btnDelete_Click);
			// 
			// tbUsername
			// 
			this->tbUsername->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbUsername->Location = System::Drawing::Point(131, 474);
			this->tbUsername->Name = L"tbUsername";
			this->tbUsername->Size = System::Drawing::Size(270, 27);
			this->tbUsername->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 477);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(94, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Username";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(12, 509);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(56, 20);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Email";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(12, 541);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 20);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Password";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(12, 575);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(47, 20);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Role";
			// 
			// tbEmail
			// 
			this->tbEmail->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbEmail->Location = System::Drawing::Point(131, 506);
			this->tbEmail->Name = L"tbEmail";
			this->tbEmail->Size = System::Drawing::Size(270, 27);
			this->tbEmail->TabIndex = 6;
			// 
			// tbPassword
			// 
			this->tbPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbPassword->Location = System::Drawing::Point(131, 538);
			this->tbPassword->Name = L"tbPassword";
			this->tbPassword->PasswordChar = '*';
			this->tbPassword->Size = System::Drawing::Size(270, 27);
			this->tbPassword->TabIndex = 7;
			// 
			// rbAdmin
			// 
			this->rbAdmin->AutoSize = true;
			this->rbAdmin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rbAdmin->Location = System::Drawing::Point(131, 573);
			this->rbAdmin->Name = L"rbAdmin";
			this->rbAdmin->Size = System::Drawing::Size(77, 24);
			this->rbAdmin->TabIndex = 8;
			this->rbAdmin->Text = L"Admin";
			this->rbAdmin->UseVisualStyleBackColor = true;
			// 
			// rbBookingManager
			// 
			this->rbBookingManager->AutoSize = true;
			this->rbBookingManager->Checked = true;
			this->rbBookingManager->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->rbBookingManager->Location = System::Drawing::Point(214, 573);
			this->rbBookingManager->Name = L"rbBookingManager";
			this->rbBookingManager->Size = System::Drawing::Size(160, 24);
			this->rbBookingManager->TabIndex = 9;
			this->rbBookingManager->TabStop = true;
			this->rbBookingManager->Text = L"Booking Manager";
			this->rbBookingManager->UseVisualStyleBackColor = true;
			// 
			// UserDataForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(906, 612);
			this->Controls->Add(this->rbBookingManager);
			this->Controls->Add(this->rbAdmin);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tbPassword);
			this->Controls->Add(this->tbEmail);
			this->Controls->Add(this->tbUsername);
			this->Controls->Add(this->btnDelete);
			this->Controls->Add(this->btnUpdate);
			this->Controls->Add(this->btnAdd);
			this->Controls->Add(this->dgvAdminUserData);
			this->Name = L"UserDataForm";
			this->Text = L"User Data Form";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvAdminUserData))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		void LoadRoomData()
		{
			String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
			SqlConnection^ conDataBase = gcnew SqlConnection(conString);
			SqlCommand^ cmdDataBase = gcnew SqlCommand("SELECT name, email, password, admin FROM users;", conDataBase);

			try {
				SqlDataAdapter^ sda = gcnew SqlDataAdapter();
				sda->SelectCommand = cmdDataBase;
				DataTable^ dbdataset = gcnew DataTable();
				sda->Fill(dbdataset);
				BindingSource^ bSource = gcnew BindingSource();

				bSource->DataSource = dbdataset;
				dgvAdminUserData->DataSource = bSource;

				// Enable editing in DataGridView
				dgvAdminUserData->ReadOnly = false;
				dgvAdminUserData->AllowUserToAddRows = false;
				dgvAdminUserData->AllowUserToDeleteRows = false;
				dgvAdminUserData->AllowUserToResizeRows = false;
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message);
			}
			finally
			{
				conDataBase->Close();
			}
		}

private: System::Void btnUpdate_Click(System::Object^  sender, System::EventArgs^  e) {
	if (dgvAdminUserData->SelectedRows->Count > 0) {
		DataGridViewRow^ selectedRow = dgvAdminUserData->SelectedRows[0];
		String^ email = Convert::ToString(selectedRow->Cells["email"]->Value);
		String^ name = Convert::ToString(selectedRow->Cells["name"]->Value);
		String^ password = Convert::ToString(selectedRow->Cells["password"]->Value);
		bool admin = Convert::ToBoolean(selectedRow->Cells["admin"]->Value);

		String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
		SqlConnection^ conDataBase = gcnew SqlConnection(conString);
		SqlCommand^ cmdDataBase = gcnew SqlCommand("UPDATE users SET name=@name, password=@password, admin=@admin WHERE email=@email;", conDataBase);

		cmdDataBase->Parameters->AddWithValue("@name", name);
		cmdDataBase->Parameters->AddWithValue("@password", password);
		cmdDataBase->Parameters->AddWithValue("@admin", admin);
		cmdDataBase->Parameters->AddWithValue("@email", email);

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
private: System::Void btnDelete_Click(System::Object^  sender, System::EventArgs^  e) {
	if (dgvAdminUserData->SelectedRows->Count > 0) {
		DataGridViewRow^ selectedRow = dgvAdminUserData->SelectedRows[0];
		String^ email = Convert::ToString(selectedRow->Cells["email"]->Value);

		String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
		SqlConnection^ conDataBase = gcnew SqlConnection(conString);
		SqlCommand^ cmdDataBase = gcnew SqlCommand("DELETE FROM users WHERE email=@email;", conDataBase);

		cmdDataBase->Parameters->AddWithValue("@email", email);

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
private: System::Void btnAdd_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ name = tbUsername->Text->ToString(); // You might want to use input fields from the user interface
	String^ email = tbEmail->Text->ToString(); // Example email
	String^ password = tbPassword->Text->ToString(); // Example password	
	int admin = 0; // Example admin status

	if (rbAdmin->Checked)
	{
		admin = 1;
	}
	else
	{
		admin = 0;
	}

	if (name == "" || email == "" || password == "")
	{
		MessageBox::Show("Kindly fill all the fields.", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
	SqlConnection^ conDataBase = gcnew SqlConnection(conString);
	SqlCommand^ cmdDataBase = gcnew SqlCommand("INSERT INTO users (name, email, password, admin) VALUES (@name, @email, @password, @admin);", conDataBase);

	cmdDataBase->Parameters->AddWithValue("@name", name);
	cmdDataBase->Parameters->AddWithValue("@email", email);
	cmdDataBase->Parameters->AddWithValue("@password", password);
	cmdDataBase->Parameters->AddWithValue("@admin", admin);

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
};
}
