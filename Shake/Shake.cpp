#include "Shake.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) { // ���������� � Strind �� String
    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();
    Shake::Shake form;
    Application::Run(% form); // ������� ������ ������� � ��������� ����� � �������
    return 0; // ���������� 0 ��� ���������� ���������
}
