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
	private: System::Windows::Forms::TextBox^  tbCell;

	private: System::Windows::Forms::Label^  label7;


	private: System::Windows::Forms::Label^  label8;


	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::DateTimePicker^  dtpPresentDate;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::DateTimePicker^  dtpTimeIn;
	private: System::Windows::Forms::DateTimePicker^  dtpTimeOut;
	private: System::Windows::Forms::DataGridView^  dgvRoomData;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Button^  btnRefresh;

	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  tbNoOfRooms;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::Windows::Forms::Button^  btnSave;
	private: System::Windows::Forms::Button^  btnPrint;
	private: System::Windows::Forms::Button^  btnCalculateTotal;

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
			this->tbCell = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->dtpPresentDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->dtpTimeIn = (gcnew System::Windows::Forms::DateTimePicker());
			this->dtpTimeOut = (gcnew System::Windows::Forms::DateTimePicker());
			this->dgvRoomData = (gcnew System::Windows::Forms::DataGridView());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->btnRefresh = (gcnew System::Windows::Forms::Button());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->tbNoOfRooms = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->btnPrint = (gcnew System::Windows::Forms::Button());
			this->btnCalculateTotal = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvRoomData))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(354, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(215, 32);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Hotel Blue Sky";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(20, 54);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(105, 25);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Customer";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(14, 110);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 17);
			this->label3->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(21, 102);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(68, 25);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Name";
			// 
			// tbName
			// 
			this->tbName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbName->Location = System::Drawing::Point(113, 97);
			this->tbName->Name = L"tbName";
			this->tbName->Size = System::Drawing::Size(319, 30);
			this->tbName->TabIndex = 1;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(21, 138);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(65, 25);
			this->label5->TabIndex = 3;
			this->label5->Text = L"CNIC";
			// 
			// tbCnic
			// 
			this->tbCnic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbCnic->Location = System::Drawing::Point(113, 133);
			this->tbCnic->Name = L"tbCnic";
			this->tbCnic->Size = System::Drawing::Size(319, 30);
			this->tbCnic->TabIndex = 2;
			this->tbCnic->Text = L"xxxxx-xxxxxxx-x";
			this->tbCnic->Enter += gcnew System::EventHandler(this, &MainForm::tbCnic_Enter);
			this->tbCnic->Leave += gcnew System::EventHandler(this, &MainForm::tbCnic_Leave);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(491, 297);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(146, 25);
			this->label6->TabIndex = 3;
			this->label6->Text = L"No. Of Rooms";
			// 
			// tbCell
			// 
			this->tbCell->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbCell->Location = System::Drawing::Point(619, 133);
			this->tbCell->Name = L"tbCell";
			this->tbCell->Size = System::Drawing::Size(302, 30);
			this->tbCell->TabIndex = 3;
			this->tbCell->Text = L"03xx-xxxxxxx";
			this->tbCell->Enter += gcnew System::EventHandler(this, &MainForm::tbCell_Enter);
			this->tbCell->Leave += gcnew System::EventHandler(this, &MainForm::tbCell_Leave);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(21, 208);
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
			this->label8->Location = System::Drawing::Point(510, 208);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(103, 25);
			this->label8->TabIndex = 3;
			this->label8->Text = L"Time-Out";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(110, 166);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(71, 17);
			this->label9->TabIndex = 5;
			this->label9->Text = L"(Optional)";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(627, 166);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(71, 17);
			this->label10->TabIndex = 5;
			this->label10->Text = L"(Optional)";
			// 
			// dtpPresentDate
			// 
			this->dtpPresentDate->CalendarFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->dtpPresentDate->CustomFormat = L"dd-MM-yyyy";
			this->dtpPresentDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpPresentDate->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dtpPresentDate->Location = System::Drawing::Point(619, 95);
			this->dtpPresentDate->Name = L"dtpPresentDate";
			this->dtpPresentDate->Size = System::Drawing::Size(179, 30);
			this->dtpPresentDate->TabIndex = 6;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(510, 102);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(57, 25);
			this->label11->TabIndex = 3;
			this->label11->Text = L"Date";
			// 
			// dtpTimeIn
			// 
			this->dtpTimeIn->CalendarFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->dtpTimeIn->CustomFormat = L"";
			this->dtpTimeIn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dtpTimeIn->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->dtpTimeIn->Location = System::Drawing::Point(113, 203);
			this->dtpTimeIn->Name = L"dtpTimeIn";
			this->dtpTimeIn->Size = System::Drawing::Size(179, 30);
			this->dtpTimeIn->TabIndex = 6;
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
			this->dtpTimeOut->Location = System::Drawing::Point(619, 203);
			this->dtpTimeOut->Name = L"dtpTimeOut";
			this->dtpTimeOut->Size = System::Drawing::Size(179, 30);
			this->dtpTimeOut->TabIndex = 6;
			this->dtpTimeOut->Value = System::DateTime(2024, 8, 19, 21, 40, 0, 0);
			// 
			// dgvRoomData
			// 
			this->dgvRoomData->BackgroundColor = System::Drawing::Color::Beige;
			this->dgvRoomData->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->dgvRoomData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvRoomData->Location = System::Drawing::Point(17, 282);
			this->dgvRoomData->Name = L"dgvRoomData";
			this->dgvRoomData->RowTemplate->Height = 24;
			this->dgvRoomData->Size = System::Drawing::Size(468, 200);
			this->dgvRoomData->TabIndex = 7;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(20, 254);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(67, 25);
			this->label12->TabIndex = 1;
			this->label12->Text = L"Room";
			// 
			// btnRefresh
			// 
			this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRefresh->Location = System::Drawing::Point(17, 488);
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->Size = System::Drawing::Size(90, 30);
			this->btnRefresh->TabIndex = 8;
			this->btnRefresh->Text = L"Refresh";
			this->btnRefresh->UseVisualStyleBackColor = true;
			this->btnRefresh->Click += gcnew System::EventHandler(this, &MainForm::btnRefresh_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(510, 254);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(94, 25);
			this->label13->TabIndex = 1;
			this->label13->Text = L"Charges";
			// 
			// tbNoOfRooms
			// 
			this->tbNoOfRooms->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbNoOfRooms->Location = System::Drawing::Point(663, 288);
			this->tbNoOfRooms->Name = L"tbNoOfRooms";
			this->tbNoOfRooms->Size = System::Drawing::Size(258, 38);
			this->tbNoOfRooms->TabIndex = 1;
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(663, 345);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(258, 38);
			this->textBox1->TabIndex = 1;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(491, 354);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(111, 25);
			this->label14->TabIndex = 3;
			this->label14->Text = L"Total Rent";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(663, 397);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(258, 38);
			this->textBox2->TabIndex = 1;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(491, 406);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(121, 25);
			this->label15->TabIndex = 3;
			this->label15->Text = L"Gst @ 16%";
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(663, 448);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(258, 38);
			this->textBox3->TabIndex = 1;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(491, 457);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(126, 25);
			this->label16->TabIndex = 3;
			this->label16->Text = L"Grand Total";
			// 
			// btnCancel
			// 
			this->btnCancel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCancel->Location = System::Drawing::Point(308, 498);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(124, 51);
			this->btnCancel->TabIndex = 9;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			// 
			// btnSave
			// 
			this->btnSave->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSave->Location = System::Drawing::Point(445, 498);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(124, 51);
			this->btnSave->TabIndex = 9;
			this->btnSave->Text = L"Save";
			this->btnSave->UseVisualStyleBackColor = true;
			// 
			// btnPrint
			// 
			this->btnPrint->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnPrint->Location = System::Drawing::Point(585, 498);
			this->btnPrint->Name = L"btnPrint";
			this->btnPrint->Size = System::Drawing::Size(124, 51);
			this->btnPrint->TabIndex = 9;
			this->btnPrint->Text = L"Print";
			this->btnPrint->UseVisualStyleBackColor = true;
			// 
			// btnCalculateTotal
			// 
			this->btnCalculateTotal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnCalculateTotal->Location = System::Drawing::Point(113, 488);
			this->btnCalculateTotal->Name = L"btnCalculateTotal";
			this->btnCalculateTotal->Size = System::Drawing::Size(151, 30);
			this->btnCalculateTotal->TabIndex = 9;
			this->btnCalculateTotal->Text = L"Calculate Total";
			this->btnCalculateTotal->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DarkCyan;
			this->ClientSize = System::Drawing::Size(935, 561);
			this->Controls->Add(this->btnPrint);
			this->Controls->Add(this->btnSave);
			this->Controls->Add(this->btnCalculateTotal);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnRefresh);
			this->Controls->Add(this->dgvRoomData);
			this->Controls->Add(this->dtpTimeOut);
			this->Controls->Add(this->dtpTimeIn);
			this->Controls->Add(this->dtpPresentDate);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->tbCell);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->tbCnic);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->tbNoOfRooms);
			this->Controls->Add(this->tbName);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"MainForm";
			this->Text = L"Main Form";
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


private: System::Void tbCell_Enter(System::Object^  sender, System::EventArgs^  e) {
	if (tbCell->Text == "03xx-xxxxxxx") {
		tbCell->Text = "";
	}
}
private: System::Void tbCell_Leave(System::Object^  sender, System::EventArgs^  e) {
	if (tbCell->Text == "") {
		tbCell->Text = "03xx-xxxxxxx";
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

};

}


