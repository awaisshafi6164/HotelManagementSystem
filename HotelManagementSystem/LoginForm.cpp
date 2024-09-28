#include "LoginForm.h"
#include "MainForm.h"
#include "AdminForm.h"
#include <msclr/marshal_cppstd.h> // For converting std::string to System::String

using namespace System;
using namespace System::Windows::Forms;

//[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	HotelManagementSystem::LoginForm loginForm;
	loginForm.ShowDialog();
	User^ user = loginForm.user;
	User^ adminUser = loginForm.adminUser;

	if (user != nullptr) {

		// MessageBox::Show("Successfully Authentication of " + user->name, "LoginForm.cpp", MessageBoxButtons::OK);

		// If authentication is successful, open MainForm
		HotelManagementSystem::MainForm mainForm(user->name);
		mainForm.ShowDialog();

	}
	else if (adminUser != nullptr)
	{
		//MessageBox::Show("Successfully Authentication of " + adminUser->name, "LoginForm.cpp", MessageBoxButtons::OK);
		
		// If authentication is successful, open AdminForm
		HotelManagementSystem::AdminForm adminForm;
		adminForm.ShowDialog();
		
	}
	else {
		//MessageBox::Show("Authentication Canceled",	"LoginForm.cpp", MessageBoxButtons::OK);
	}
	return 0;
}