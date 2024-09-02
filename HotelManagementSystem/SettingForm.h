#pragma once

namespace HotelManagementSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// Summary for SettingForm
	/// </summary>
	public ref class SettingForm : public System::Windows::Forms::Form
	{
	public:
		SettingForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			loadData();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SettingForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  tbPRAAccessID;
	protected:

	private: System::Windows::Forms::Button^  btnSettingSave;
	private: System::Windows::Forms::ComboBox^  cbPRAEnv;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  tbPRAAccessIDToken;

	private: System::Windows::Forms::Label^  label4;

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
			this->tbPRAAccessID = (gcnew System::Windows::Forms::TextBox());
			this->btnSettingSave = (gcnew System::Windows::Forms::Button());
			this->cbPRAEnv = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tbPRAAccessIDToken = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(595, 37);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Setting";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tbPRAAccessID
			// 
			this->tbPRAAccessID->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbPRAAccessID->Location = System::Drawing::Point(157, 49);
			this->tbPRAAccessID->Name = L"tbPRAAccessID";
			this->tbPRAAccessID->Size = System::Drawing::Size(172, 27);
			this->tbPRAAccessID->TabIndex = 1;
			// 
			// btnSettingSave
			// 
			this->btnSettingSave->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->btnSettingSave->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSettingSave->Location = System::Drawing::Point(213, 172);
			this->btnSettingSave->Name = L"btnSettingSave";
			this->btnSettingSave->Size = System::Drawing::Size(152, 49);
			this->btnSettingSave->TabIndex = 2;
			this->btnSettingSave->Text = L"SAVE";
			this->btnSettingSave->UseVisualStyleBackColor = false;
			this->btnSettingSave->Click += gcnew System::EventHandler(this, &SettingForm::btnSettingSave_Click);
			// 
			// cbPRAEnv
			// 
			this->cbPRAEnv->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbPRAEnv->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbPRAEnv->FormattingEnabled = true;
			this->cbPRAEnv->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"sandbox", L"production" });
			this->cbPRAEnv->Location = System::Drawing::Point(157, 128);
			this->cbPRAEnv->Name = L"cbPRAEnv";
			this->cbPRAEnv->Size = System::Drawing::Size(172, 28);
			this->cbPRAEnv->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(12, 56);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(139, 20);
			this->label2->TabIndex = 0;
			this->label2->Text = L"PRA Access ID";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(12, 94);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(195, 20);
			this->label3->TabIndex = 0;
			this->label3->Text = L"PRA Access ID Token";
			// 
			// tbPRAAccessIDToken
			// 
			this->tbPRAAccessIDToken->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tbPRAAccessIDToken->Location = System::Drawing::Point(213, 87);
			this->tbPRAAccessIDToken->Name = L"tbPRAAccessIDToken";
			this->tbPRAAccessIDToken->Size = System::Drawing::Size(370, 27);
			this->tbPRAAccessIDToken->TabIndex = 1;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(12, 131);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(113, 20);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Environment";
			// 
			// SettingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(595, 273);
			this->Controls->Add(this->cbPRAEnv);
			this->Controls->Add(this->btnSettingSave);
			this->Controls->Add(this->tbPRAAccessIDToken);
			this->Controls->Add(this->tbPRAAccessID);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(613, 320);
			this->MinimumSize = System::Drawing::Size(613, 320);
			this->Name = L"SettingForm";
			this->Text = L"SettingForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:
			void loadData()
			{
				// Load data from the database and set it to the required fields
				//String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
				String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
				SqlConnection^ conDataBase = gcnew SqlConnection(conString);
				SqlCommand^ cmdDataBase = gcnew SqlCommand("SELECT praAccessID, praAccessIDToken, praIDEnvironment FROM setting WHERE ID = 1;", conDataBase);

				try {
					conDataBase->Open();
					SqlDataReader^ reader = cmdDataBase->ExecuteReader();
					if (reader->Read()) {
						tbPRAAccessID->Text = reader["praAccessID"]->ToString();
						tbPRAAccessIDToken->Text = reader["praAccessIDToken"]->ToString();
						cbPRAEnv->SelectedItem = reader["praIDEnvironment"]->ToString();
					}
				}
				catch (Exception^ ex) {
					MessageBox::Show(ex->Message);
				}
				finally{
					conDataBase->Close();
				}

					// Default to sandbox if nothing is selected
					if (cbPRAEnv->SelectedItem == nullptr) {
						cbPRAEnv->SelectedItem = "sandbox";
					}
			}

	private: System::Void btnSettingSave_Click(System::Object^ sender, System::EventArgs^ e) {
		// Fetch text strings from tbPRAAccessIDToken and cbPRAEnv, and int from tbPRAAccessID
		String^ praAccessID = tbPRAAccessID->Text;
		String^ praAccessIDToken = tbPRAAccessIDToken->Text;
		String^ praIDEnvironment = cbPRAEnv->SelectedItem->ToString();

		// Store the data inside ID 1 of the SQL database
		String^ conString = "Data Source=localhost\\sqlexpress;Initial Catalog=myhotel;Integrated Security=True";
		SqlConnection^ conDataBase = gcnew SqlConnection(conString);
		SqlCommand^ cmdDataBase = gcnew SqlCommand("UPDATE setting SET praAccessID=@praAccessID, praAccessIDToken=@praAccessIDToken, praIDEnvironment=@praIDEnvironment WHERE ID = 1;", conDataBase);

		cmdDataBase->Parameters->AddWithValue("@praAccessID", praAccessID);
		cmdDataBase->Parameters->AddWithValue("@praAccessIDToken", praAccessIDToken);
		cmdDataBase->Parameters->AddWithValue("@praIDEnvironment", praIDEnvironment);

		try {
			conDataBase->Open();
			cmdDataBase->ExecuteNonQuery();
			MessageBox::Show("Settings saved successfully.");
			this->Close();
		}
		catch (Exception^ ex) {
			MessageBox::Show(ex->Message);
		}
		finally{
			conDataBase->Close();
		}
	}

};
}
