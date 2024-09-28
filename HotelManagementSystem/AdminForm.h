#pragma once
#define IServiceProvider WindowsIServiceProvider // Rename Windows IServiceProvider
#include <curl/curl.h>
#undef IServiceProvider  // Undefine after including

#include <iostream>
#include <string>
#include <nlohmann\json.hpp>

#include "Invoice.h"
#include <msclr/marshal_cppstd.h> // For converting std::string to System::String
#include "UserDataForm.h"
#include "RoomDataForm.h"
#include "CustomerDataForm.h"
#include "SettingForm.h"
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
	/// Summary for AdminForm
	/// </summary>
	public ref class AdminForm : public System::Windows::Forms::Form
	{
	public:
		AdminForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AdminForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Button^  btnUserData;
	private: System::Windows::Forms::Button^  btnRoomData;
	private: System::Windows::Forms::Button^  btnCustomerData;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  tbAdminPassword;



	protected:

	protected:

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnUserData = (gcnew System::Windows::Forms::Button());
			this->btnRoomData = (gcnew System::Windows::Forms::Button());
			this->btnCustomerData = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tbAdminPassword = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(515, 40);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Admin Panel";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnUserData
			// 
			this->btnUserData->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnUserData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnUserData->Location = System::Drawing::Point(26, 43);
			this->btnUserData->Name = L"btnUserData";
			this->btnUserData->Size = System::Drawing::Size(150, 50);
			this->btnUserData->TabIndex = 1;
			this->btnUserData->Text = L"User Data";
			this->btnUserData->UseVisualStyleBackColor = false;
			this->btnUserData->Click += gcnew System::EventHandler(this, &AdminForm::btnUserData_Click);
			// 
			// btnRoomData
			// 
			this->btnRoomData->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnRoomData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRoomData->Location = System::Drawing::Point(182, 43);
			this->btnRoomData->Name = L"btnRoomData";
			this->btnRoomData->Size = System::Drawing::Size(150, 50);
			this->btnRoomData->TabIndex = 2;
			this->btnRoomData->Text = L"Room Data";
			this->btnRoomData->UseVisualStyleBackColor = false;
			this->btnRoomData->Click += gcnew System::EventHandler(this, &AdminForm::btnRoomData_Click);
			// 
			// btnCustomerData
			// 
			this->btnCustomerData->BackColor = System::Drawing::Color::DarkTurquoise;
			this->btnCustomerData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCustomerData->Location = System::Drawing::Point(338, 43);
			this->btnCustomerData->Name = L"btnCustomerData";
			this->btnCustomerData->Size = System::Drawing::Size(165, 50);
			this->btnCustomerData->TabIndex = 3;
			this->btnCustomerData->Text = L"Customer Data";
			this->btnCustomerData->UseVisualStyleBackColor = false;
			this->btnCustomerData->Click += gcnew System::EventHandler(this, &AdminForm::btnCustomerData_Click);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::DarkTurquoise;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(403, 221);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 37);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Setting";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &AdminForm::button1_Click);
			// 
			// tbAdminPassword
			// 
			this->tbAdminPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->tbAdminPassword->Location = System::Drawing::Point(36, 226);
			this->tbAdminPassword->Name = L"tbAdminPassword";
			this->tbAdminPassword->PasswordChar = '*';
			this->tbAdminPassword->Size = System::Drawing::Size(296, 26);
			this->tbAdminPassword->TabIndex = 5;
			// 
			// AdminForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(515, 270);
			this->Controls->Add(this->tbAdminPassword);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->btnRoomData);
			this->Controls->Add(this->btnCustomerData);
			this->Controls->Add(this->btnUserData);
			this->Controls->Add(this->label1);
			this->Name = L"AdminForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Admin Form";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &AdminForm::AdminForm_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		bool isRestarting = false;

	private: System::Void btnUserData_Click(System::Object^  sender, System::EventArgs^  e) {
		HotelManagementSystem::UserDataForm userDataForm;
		userDataForm.ShowDialog();
	}
private: System::Void btnRoomData_Click(System::Object^  sender, System::EventArgs^  e) {
	HotelManagementSystem::RoomDataForm roomDataForm;
	roomDataForm.ShowDialog();
}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ pass = tbAdminPassword->Text->ToString();
	if (pass == "q6dr080g")
	{
		tbAdminPassword->Text = "";
		HotelManagementSystem::SettingForm settingForm;
		settingForm.ShowDialog();
	}
	
}
private: System::Void btnCustomerData_Click(System::Object^  sender, System::EventArgs^  e) {
	HotelManagementSystem::CustomerDataForm customerDataForm;
	customerDataForm.ShowDialog();
}
private: System::Void AdminForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	if (!isRestarting) {
		isRestarting = true;
		Application::Restart();
	}
}
};
}
