#include "LoginForm.h"
#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	HotelManagementSystem::LoginForm loginForm;

	loginForm.ShowDialog();
	User^ user = loginForm.user;

	if (user != nullptr) {
		MessageBox::Show("Successfully Authentication of " + user->name,
			"LoginForm.cpp", MessageBoxButtons::OK);

		// If authentication is successful, open MainForm
		HotelManagementSystem::MainForm mainForm;
		mainForm.ShowDialog();
	} 
	else {
		MessageBox::Show("Authentication Canceled",
			"LoginForm.cpp", MessageBoxButtons::OK);
	}
	return 0;
}


void HotelManagementSystem::LoginForm::LoginForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	// Code to execute when the form loads
}